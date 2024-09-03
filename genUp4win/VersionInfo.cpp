/*
Module : VersionInfo.cpp
Purpose: Implementation for a C++ class encapsulation of Window's "Version Infos"
Created: PJN / 10-04-2000
History: PJN / 07-07-2006 1. Updated copyright details
                          2. Updated the code to clean compile on VC 2005
                          3. Addition of CVERSIONINFO_EXT_CLASS and CVERSIONINFO_EXT_API macros to allow
                          the class to be easily added to an extension DLL.
                          4. Optimized CVersionInfo constructor code
                          5. Reviewed all TRACE statements for correctness
                          6. Updated the documentation to use the same style as the web site.
         PJN / 14-09-2008 1. Updated copyright details.
                          2. Code now compiles cleanly using Code Analysis (/analyze)
                          3. Updated code to compile correctly using _ATL_CSTRING_EXPLICIT_CONSTRUCTORS define
                          4. Updated sample app to clean compile on VC 2008
                          5. The code has now been updated to support VC 2005 or later only. 
                          6. Removed VC 6 style AppWizard comments from the code.
                          7. Reworked code to use ATL::CHeapPtr for required memory allocations
         PJN / 04-01-2015 1. Updated the code to clean compile in VC 2010 - VC 2013.
                          2. Updated copyright details.
                          3. Replaced all TRACE calls with ATLTRACE.
         PJN / 29-11-2015 1. Updated the code to clean compile in VC 2015. 
                          2. Reworked the classes to optionally compile without MFC. By default the class now 
                          use STL classes and idioms but if you define CVERSIONINFO_MFC_EXTENSIONS the class 
                          will revert back to the MFC behaviour.
                          3. All the class methods have had SAL annotations added 
         PJN / 02-01-2016 1. Updated copyright details.
                          2. CVersionInfo::GetValue now uses wostringstream and ostringstream instead of 
                          wstringstream and stringstream.
         PJN / 26-09-2017 1. Updated copyright details.
                          2. Replaced NULL throughout the codebase with nullptr. This means that the minimum
                          requirement for the framework is now VC 2010.
                          3. Replaced CString::operator LPC*STR() calls throughout the codebase with
                          CString::GetString calls
                          4. Made all the Get* methods const.
         PJN / 04-06-2018 1. Updated copyright details.
                          2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that
                          the code will now only compile on VC 2017 or later.
         PJN / 16-09-2018 1. Fixed a number of compiler warnings when using VS 2017 15.8.4
         PJN / 21-04-2019 1. Updated copyright details.
                          2. Removed the code path supported by the non defunct CVERSIONINFO_MFC_EXTENSIONS
                          enum
         PJN / 21-12-2019 1. Fixed various Clang-Tidy static code analysis warnings in the code.
         PJN / 14-03-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 12-04-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 07-02-2022 1. Updated the code to use C++ uniform initialization for all variable declarations
                          2. Updated copyright details.

Copyright (c) 2000 - 2022 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

//////////////// Includes /////////////////////////////////////////////////////

#include "pch.h"
#include "VersionInfo.h"

#ifndef _SSTREAM_
#pragma message("To avoid this message, please put sstream in your pre compiled header (normally stdafx.h)")
#include <sstream>
#endif //#ifndef _SSTREAM_

#ifndef _IOMANIP_
#pragma message("To avoid this message, please put iomanip in your pre compiled header (normally stdafx.h)")
#include <iomanip>
#endif //#ifndef _IOMANIP_


//////////////// Macros / Locals //////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

//Automatically pull in the win32 version Library
#pragma comment(lib, "version.lib")


//////////////// Implementation ///////////////////////////////////////////////

CVersionInfo::CVersionInfo() noexcept : m_wLangID{0},
                                        m_wCharset{1252}, //Use the ANSI code page as a default
                                        m_pTranslations{nullptr},
                                        m_nTranslations{0},
                                        m_pffi{nullptr}
{
}

CVersionInfo::~CVersionInfo() noexcept
{
	Unload();
}

void CVersionInfo::Unload() noexcept
{
	m_pffi = nullptr;
	m_VerData.clear();
	m_wLangID = 0;
	m_wCharset = 1252; //Use the ANSI code page as a default
	m_pTranslations = nullptr;
	m_nTranslations = 0;
}

#pragma warning(suppress: 26440)
BOOL CVersionInfo::Load(_In_z_ LPCTSTR szFileName)
{
	//Free up any previous memory lying around
	Unload();

	BOOL bSuccess{ FALSE };
	const DWORD dwSize{ GetFileVersionInfoSize(szFileName, nullptr) };
	if (dwSize)
	{
		//Allocate some memory to hold the version info data
		m_VerData.resize(dwSize);
		if (GetFileVersionInfo(szFileName, 0, dwSize, m_VerData.data()))
		{
			//Get the fixed size version info data
			UINT nLen{ 0 };
#pragma warning(suppress: 26490)
			if (VerQueryValue(m_VerData.data(), _T("\\"), reinterpret_cast<LPVOID*>(&m_pffi), &nLen))
			{
				//Retrieve the Lang ID and Character set ID
#pragma warning(suppress: 26490)
				if (VerQueryValue(m_VerData.data(), _T("\\VarFileInfo\\Translation"), reinterpret_cast<LPVOID*>(&m_pTranslations), &nLen) && (nLen >= sizeof(TRANSLATION)))
				{
					m_nTranslations = nLen / sizeof(TRANSLATION);
#pragma warning(suppress: 26481)
					m_wLangID = m_pTranslations[0].m_wLangID;
#pragma warning(suppress: 26481)
					m_wCharset = m_pTranslations[0].m_wCodePage;
				}
				bSuccess = TRUE;
			}
			else
				ATLTRACE(_T("CVersionInfo::Load, Failed to query file size version info for file %s, Error:%u\n"), szFileName, ::GetLastError());
		}
		else
			ATLTRACE(_T("CVersionInfo::Load, Failed to read in version info for file %s, Error:%u\n"), szFileName, ::GetLastError());
	}
	else
		ATLTRACE(_T("CVersionInfo::Load, Failed to get version info for file %s, Error:%u\n"), szFileName, ::GetLastError());

	return bSuccess;
}

VS_FIXEDFILEINFO* CVersionInfo::GetFixedFileInfo() const noexcept
{
	return m_pffi;
}

DWORD CVersionInfo::GetFileFlagsMask() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	return m_pffi->dwFileFlagsMask;
}

DWORD CVersionInfo::GetFileFlags() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	return m_pffi->dwFileFlags;
}

DWORD CVersionInfo::GetOS() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	return m_pffi->dwFileOS;
}

DWORD CVersionInfo::GetFileType() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	return m_pffi->dwFileType;
}

DWORD CVersionInfo::GetFileSubType() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	return m_pffi->dwFileSubtype;
}

FILETIME CVersionInfo::GetCreationTime() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	FILETIME CreationTime{};
	CreationTime.dwHighDateTime = m_pffi->dwFileDateMS;
	CreationTime.dwLowDateTime = m_pffi->dwFileDateLS;
	return CreationTime;
}

unsigned __int64 CVersionInfo::GetFileVersion() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	unsigned __int64 nFileVersion{ m_pffi->dwFileVersionLS };
#pragma warning(suppress: 26472)
	nFileVersion += ((static_cast<unsigned __int64>(m_pffi->dwFileVersionMS)) << 32);
	return nFileVersion;
}

unsigned __int64 CVersionInfo::GetProductVersion() const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSUME(m_pffi != nullptr);

	unsigned __int64 nProductVersion{ m_pffi->dwProductVersionLS };
#pragma warning(suppress: 26472)
	nProductVersion += ((static_cast<unsigned __int64>(m_pffi->dwProductVersionMS)) << 32);
	return nProductVersion;
}

CVersionInfo::String CVersionInfo::GetValue(_In_z_ LPCTSTR pszKey) const
{
	//What will be the return value from this function
	String sVal;

	//Form the string to query with
	String sQueryValue;
#ifdef _UNICODE
	std::wostringstream ss;
#else
	std::ostringstream ss;
#endif //#ifdef _UNICODE
	ss << _T("\\StringFileInfo\\");
	ss << std::setfill(_T('0')) << std::setw(4) << std::hex << m_wLangID;
	ss << std::setfill(_T('0')) << std::setw(4) << std::hex << m_wCharset;
	ss << _T("\\");
	ss << pszKey;
	sQueryValue = ss.str();

	LPCTSTR pszQueryValue = sQueryValue.c_str();

	//Do the query
	LPTSTR pVal{ nullptr };
	UINT nLen{ 0 };
#pragma warning(suppress: 26490)
	if (VerQueryValue(m_VerData.data(), pszQueryValue, reinterpret_cast<LPVOID*>(&pVal), &nLen))
		sVal = pVal;

	return sVal;
}

CVersionInfo::String CVersionInfo::GetCompanyName() const
{
	return GetValue(_T("CompanyName"));
}

CVersionInfo::String CVersionInfo::GetFileDescription() const
{
	return GetValue(_T("FileDescription"));
}

CVersionInfo::String CVersionInfo::GetFileVersionAsString() const
{
	return GetValue(_T("FileVersion"));
}

CVersionInfo::String CVersionInfo::GetInternalName() const
{
	return GetValue(_T("InternalName"));
}

CVersionInfo::String CVersionInfo::GetLegalCopyright() const
{
	return GetValue(_T("LegalCopyright"));
}

CVersionInfo::String CVersionInfo::GetOriginalFilename() const
{
	return GetValue(_T("OriginalFilename"));
}

CVersionInfo::String CVersionInfo::GetProductName() const
{
	return GetValue(_T("Productname"));
}

CVersionInfo::String CVersionInfo::GetProductVersionAsString() const
{
	return GetValue(_T("ProductVersion"));
}

int CVersionInfo::GetNumberOfTranslations() const noexcept
{
	return m_nTranslations;
}

CVersionInfo::String CVersionInfo::GetComments() const
{
	return GetValue(_T("Comments"));
}

CVersionInfo::String CVersionInfo::GetLegalTrademarks() const
{
	return GetValue(_T("LegalTrademarks"));
}

CVersionInfo::String CVersionInfo::GetPrivateBuild() const
{
	return GetValue(_T("PrivateBuild"));
}

CVersionInfo::String CVersionInfo::GetSpecialBuild() const
{
	return GetValue(_T("SpecialBuild"));
}

CVersionInfo::TRANSLATION* CVersionInfo::GetTranslation(_In_ int nIndex) const noexcept
{
	//Validate our parameters
#pragma warning(suppress: 26477)
	ATLASSERT((nIndex >= 0) && (nIndex < m_nTranslations));
#pragma warning(suppress: 26477)
	ATLASSUME(m_pTranslations != nullptr);

#pragma warning(suppress: 26481)
	return &m_pTranslations[nIndex];
}

void CVersionInfo::SetTranslation(_In_ int nIndex) noexcept
{
	const TRANSLATION* pTranslation{ GetTranslation(nIndex) };
#pragma warning(suppress: 26477)
	ATLASSUME(pTranslation != nullptr);

	m_wLangID = pTranslation->m_wLangID; //NOLINT(clang-analyzer-core.NullDereference)
	m_wCharset = pTranslation->m_wCodePage;
}
