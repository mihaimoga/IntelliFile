/*
Module : AppSettings.h
Purpose: Implementation for a collection of C++ classes which provides for reading and writing application settings to a number of locations and formats:

         The supported output formats are:
         1. Per user in the Registry (HKEY_CURRENT_USER\Software\"Company Name"\"Product Name"\"Product Version") via the class CHKCUAppSettings
         2. Per machine in the Registry (HKEY_LOCAL_MACHINE\Software\"Company Name"\"Product Name"\"Product Version") via the class CHKLMAppSettings
         3. Service parameters in the registry (HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\"Service Name"\Parameters) via the class CServicesAppSettings
         4. A standard windows ini file via the class CIniAppSettings
         5. An XML file via the class CXMLAppSettings
         6. A JSON file via the class CJSONAppSettings

         The ini, XML and JSON file locations can be:

         1. A per user roaming file stored in "\Documents and Settings\<User Name>\Application Data\"Company Name"\"Product Name"\"Product Version" via the method
         CIniAppSettings::GetRoamingDataFileLocation.
         2. A per user non-roaming file stored in "\Documents and Settings\<User Name>\Local Settings\Application Data\"Company Name"\"Product Name"\"Product Version"
         via the method CIniAppSettings::GetNonRoamingDataFileLocation.
         3. A per computer (non-user specific and non-roaming) file stored in "\Documents and Settings\All Users\Application Data\"Company Name"\"Product Name"\"Product Version"
         via the method CIniAppSettings::GetPerComputerDataFileLocation.
         4. A file in the same directory as the current process via the method GetCurrentProcessIniFileLocation. Note, that using this location for an ini or xml file is not 
         a good idea for security reasons

         Other features

         1. The registry, XML and JSON output format can also be optionally flushed upon a write or left to be lazy written

Created: PJN / 07-06-2006
History: PJN / 12-06-2006 1. Minor update to a comment
         PJN / 29-07-2006 1. All AppSettings classes now support "GetSection" and "WriteSection" methods. These new functions are modelled on the "GetPrivateProfileSection" and 
                          "WritePrivateProfileSection" Win32 API calls. Thanks to Brad Bruce for suggesting these updates.
                          2. Made the AfxThrowWin32AppSettingsException function a member of IAppSettings and renamed it to ThrowWin32AppSettingsException
                          3. Made the AfxThrowCOMAppSettingsException function a member of IAppSettings and renamed it to ThrowCOMAppSettingsException
                          4. Code now uses newer C++ style casts instead of C style casts.
                          5. Made all the WriteBinary methods now accept a const BYTE* parameter instead of LPBYTE
                          6. Updated the code to clean compile on VC 2005
                          7. Fixed a bug in CXMLAppSettings::GetBinary where returned binary data was being returned incorrectly.
         PJN / 19-08-2006 1. Fixed compile problems when code is compiled in a mixed MFC / ATL project.
                          2. Addition of "WriteProfile..." functions to IAppSettings which provides similar functionality to the MFC CWinApp functions of the same
                          name. These new functions allow you to ignore errors reading a value and instead return a default value.
                          3. Removed the MFC C++ runtime macros from CAppSettingsException as they were not really required.
         PJN / 02-01-2007 1. Updated copyright details.
                          2. Fixed a bug in CRegistryAppSettings::SetStringArrayIntoRegistry related to use of _tcscpy_s
                          3. Fixed a bug in CIniAppSettings::WriteStringArray related to use of _tcscpy_s
                          4. Fixed a bug in CXMLAppSettings::WriteStringArray related to use of _tcscpy_s
         PJN / 05-07-2007 1. Added support for "Pretty Printing" to the CXMLAppSettings class. This is achieved through an additional parameter to the constructor
         PJN / 24-12-2007 1. CAppSettingsException::GetErrorMessage now uses the FORMAT_MESSAGE_IGNORE_INSERTS flag. For more information please see Raymond
                          Chen's blog at http://blogs.msdn.com/oldnewthing/archive/2007/11/28/6564257.aspx. Thanks to Alexey Kuznetsov for reporting this
                          issue.
                          2. Minor update to display HRESULT's correctly.
         PJN / 28-12-2007 1. CAppSettingsException::GetErrorMessage now uses Checked::tcsncpy_s if compiled using VC 2005 or later.
         PJN / 06-06-2008 1. Updated copyright details.
                          2. Updated sample app to clean compile on VC 2008
                          3. The code has now been updated to support VC 2005 or later only. 
                          4. Code now compiles cleanly using Code Analysis (/analyze) 
         PJN / 19-03-2009 1. Updated copyright details.
                          2. Updated the sample app solution settings to use more reasonable defaults
                          3. The IAppSettings interface now supports a new GetSections method. This returns all the root sections which a configuration file has.
                          Thanks to Rolf Kristensen for prompting this nice addition to the classes.
                          4. Updated the IAppSettings::GetSection method to support a boolean "bWithValues" parameter which determines if the returned string array 
                          should or should name include the values. This allows client code to easily get all the sections names. Thanks to Rolf Kristensen for 
                          providing this nice addition to the classes.
                          5. Reworked most of the internal code which does heap allocations using "new" to instead now use ATL::CHeapPtr.
         PJN / 04-01-2015 1. Updated copyright details
                          2. Updated the code to clean compile in VC 2010 - VC 2013.
         PJN / 12-12-2015 1. Verified code compiles cleanly in VC 2015.
                          2. Added SAL annotations to all the code.
                          3. CRegistryAppSettings::GetInt now throws an exception if the returned data type from the registry is not REG_DWORD.
                          4. CRegistryAppSettings::GetString now throws an exception if the returned data type from the registry is not REG_SZ.
                          5. CRegistryAppSettings::GetBinary now throws an exception if the returned data type from the registry is not REG_BINARY.
                          6. CRegistryAppSettings::GetStringArrayFromRegistry now throws an exception if the returned data type from the registry is not REG_MULTI_SZ.
                          7. CIniAppSettings::GetBinary now throws an exception if the returned data length is not even (a requirement because of how the data is
                          written to the ini files by WriteBinary).
                          8. Fixed an issue in CIniAppSettings::GetStringArray when a empty BLOB was returned from GetBinary.
                          9. CXMLAppSettings::GetBinary now throws an exception if the returned data length is not even (a requirement because of how the data is 
                          written to the ini files by WriteBinary).
                          10. Reworked the pretty print support for MSXML to use SAX writer instead of writing text nodes directly.
                          11. CRegistryAppSettings::GetString now handles non null terminated data as returned from the registry.
                          12. Updated CRegistryAppSettings::GetSection to handle value name lengths > 4096.
                          13. Updated CRegistryAppSettings::GetStringArrayFromRegistry now handles non doubly null terminated data as returned from the registry.
                          14. Fixed a bug in CRegistryAppSettings::SetStringArrayIntoRegistry where the code would not correctly set the cbData parameter when 
                          calling the RegSetValueEx API when compiled in UNICODE mode.
                          15. Reworked the classes to optionally compile without MFC. By default the classes now use STL classes and idioms but if you define 
                          CAPPSETTINGS_MFC_EXTENSIONS the classes will revert back to the MFC behaviour.
         PJN / 13-12-2015 1. Optimized usage of ATL::CW2T calls in Unicode builds
         PJN / 02-01-2016 1. Updated copyright details.
                          2. The code now uses wostringstream and ostringstream instead of wstringstream and stringstream.
         PJN / 21-03-2017 1. Updated copyright details.
                          2. Updated the code to compile cleanly on VC 2017
         PJN / 21-09-2017 1. Replaced CString::operator LPC*STR() calls throughout the codebase with CString::GetString calls
                          2. Replaced NULL throughout the codebase with nullptr. This means that the minimum requirement for the framework is now VC 2010.
                          3. Replaced LONG with LSTATUS for all registry return values throughout the codebase.
         PJN / 25-11-2017 1. Updated the code to compile cleanly when _ATL_NO_AUTOMATIC_NAMESPACE is defined. 
         PJN / 20-12-2017 1. Added support for JSON output via the author's JSON++ classes.
         PJN / 21-12-2017 1. Added code to CJSONAppSettings::GetInt to validate the JSON data type.
                          2. Added code to CJSONAppSettings::GetString to validate the JSON data type.
                          3. Added code to CJSONAppSettings::GetDocumentNode to validate the JSON data type.
                          4. Added code to CJSONAppSettings::GetSectionNode to validate the JSON data type.
                          5. CJSONAppSettings::WriteInt now writes the integer value out as a JSON number.
         PJN / 29-07-2018 1. Updated copyright details.
                          2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that the code will now only compile on 
                          VC 2017 or later.
                          3. Removed code path which supported CAPPSETTINGS_MFC_EXTENSIONS define
                          4. Reworked the various GetBinary methods to use a std::vector<BYTE> parameter or return value.
                          5. Reworked the various GetSections methods to return a std::vector<String>
                          6. Reworked the various GetSection methods to return a std::vector<String>
                          7. Reworked all usage of ATL::CHeapPtr to now use std::vector<BYTE>
                          8. Replaced BOOL throughout the codebase with bool.
         PJN / 02-09-2018 1. Fixed a number of compiler warnings when using VS 2017 15.8.2
                          2. Updated the code to work with the latest version of JSON++
         PJN / 22-04-2019 1. Updated copyright details
                          2. Updated the code to clean compile on VC 2019
         PJN / 26-05-2019 1. Removed the String CAppSettingsException::GetErrorMessage method. This avoids compile problems when the code is compiled 
                          in a project which is not using C++ 17. 
                          2. Fixed up other compile problems in the module when the code is compiled in a project which is not using C++ 17.
         PJN / 27-11-2019 1. Changed the default parameter lpszDefault in IAppSettings::GetProfileString from nullptr to _T(""). This avoids
                          problems where the default value is actually returned from this method. Thanks to Rene M. Laviolette for reporting
                          this bug.
         PJN / 17-03-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 30-01-2022 1. Updated copyright details.
                          2. Fixed more static code analysis warnings in Visual Studio 2022.
                          3. Updated the code to use C++ uniform initialization for all variable declarations
         PJN / 14-05-2023 1. Updated copyright details
                          2. Updated module to indicate that it needs to be compiled using /std:c++17. Thanks to Martin Richter
                          for reporting this issue.
         PJN / 03-10-2023 1. Optimized construction of various std::vector and std::[w]string instances throughout the codebase.
         PJN / 05-02-2025 1. Updated copyright details
                          2. Updated GetModuleFileName calls to handle path length > _MAX_PATH
                          3. Reworked CIniAppSettings::GetCurrentProcessIniFileLocation to use std::filesystem::path

Copyright (c) 2006 - 2025 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code.

*/


//////////////////////// Macros / Defines /////////////////////////////////////

#pragma once

#if _MSVC_LANG < 201703
#error AppSettings requires a minimum C++ language standard of /std:c++17
#endif //#if _MSVC_LANG < 201703

#ifndef __APPSETTINGS_H__
#define __APPSETTINGS_H__

#if (NTDDI_VERSION < NTDDI_VISTA)
#pragma error("AppSettings as of v1.18 requires NTDDI_VERSION to be >= NTDDI_VISTA")
#endif //#if (NTDDI_VERSION < NTDDI_VISTA)


//////////////////////// Includes /////////////////////////////////////////////

#ifndef _SHLOBJ_H_
#pragma message("To avoid this message, please put shlobj.h in your pre compiled header (normally stdafx.h)")
#include <shlobj.h>
#endif //#ifndef _SHLOBJ_H_

#ifndef __ATLBASE_H__
#pragma message("To avoid this message, please put atlbase.h in your pre compiled header (normally stdafx.h)")
#include <atlbase.h>
#endif //#ifndef __ATLBASE_H__

#include <msxml2.h>

#ifndef _EXCEPTION_
#pragma message("To avoid this message, please put exception in your pre compiled header (normally stdafx.h)")
#include <exception>
#endif //#ifndef _EXCEPTION_

#ifndef _STRING_
#pragma message("To avoid this message, please put string in your pre compiled header (normally stdafx.h)")
#include <string>
#endif //#ifndef _STRING_

#ifndef _VECTOR_
#pragma message("To avoid this message, please put vector in your pre compiled header (normally stdafx.h)")
#include <vector>
#endif //#ifndef _VECTOR_

#ifndef _SSTREAM_
#pragma message("To avoid this message, please put sstream in your pre compiled header (normally stdafx.h)")
#include <sstream>
#endif //#ifndef _SSTREAM_

#ifndef _FILESYSTEM_
#pragma message("To avoid this message, please put filesystem in your pre compiled header (normally stdafx.h)")
#include <filesystem>
#endif //#ifndef _FILESYSTEM_


#ifndef __ATLSTR_H__
#pragma message("To avoid this message, please put atlstr.h in your pre compiled header (normally stdafx.h)")
#include <atlstr.h>
#endif //#ifndef __ATLSTR_H__

#ifdef CAPPSETTINGS_JSON_SUPPORT
#ifndef __JSONPP_H__
#pragma message("To avoid this message, please put JSON++.h in your pre compiled header (normally stdafx.h)")
#include "JSON++.h" //If you get a compilation error about this missing header file, then you need to download my JSON++ class from http://www.naughter.com/jsonpp.html
#endif //#ifndef __JSONPP_H__

#ifndef __ATLFILE_H__
#pragma message("To avoid this message, please put atlfile.h in your pre compiled header (normally stdafx.h)")
#include <atlfile.h>
#endif //#ifndef __ATLFILE_H__
#endif //#ifdef CAPPSETTINGS_JSON_SUPPORT


//////////////////////// Classes //////////////////////////////////////////////

//The exception class which an AppSettings class can throw
class CAppSettingsException : public std::exception
{
public:
	//Typedefs
#ifdef _UNICODE
	using String = std::wstring;
#else
	using String = std::string;
#endif //#ifdef _UNICODE

	//Constructors / Destructors
	CAppSettingsException(_In_ HRESULT hr) noexcept : m_hr(hr),
		m_bNativeWin32Error(false)
	{
	}

	CAppSettingsException(_In_ DWORD dwError, _In_ DWORD dwFacility) noexcept : m_hr(MAKE_HRESULT(SEVERITY_ERROR, dwFacility, dwError)),
		m_bNativeWin32Error(true)
	{
	}

	//Methods
#pragma warning(suppress: 26429)
	bool GetErrorMessage(_Out_z_cap_(nMaxError) LPTSTR lpszError, _In_ UINT nMaxError, _Out_opt_ PUINT pnHelpContext = nullptr)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszError != nullptr);

		if (pnHelpContext != nullptr)
			*pnHelpContext = 0;

		//What will be the return value from this function (Assume the worst)
		bool bSuccess{ false };

		if (m_bNativeWin32Error)
		{
			//Lookup the error using FormatMessage
			LPTSTR lpBuffer = nullptr;
#pragma warning(suppress: 26490)
			const DWORD dwReturn{ FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
											   nullptr, HRESULT_CODE(m_hr), MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
											   reinterpret_cast<LPTSTR>(&lpBuffer), 0, nullptr) };

			if (dwReturn == 0)
				*lpszError = _T('\0');
			else
			{
				bSuccess = true;
				ATL::Checked::tcsncpy_s(lpszError, nMaxError, lpBuffer, _TRUNCATE);
				LocalFree(lpBuffer);
			}
		}
		else
		{
			ATL::CComPtr<IErrorInfo> pError;
			if (SUCCEEDED(GetErrorInfo(0, &pError)) && (pError != nullptr))
			{
				bSuccess = true;
				ATL::CComBSTR bstrDescription;
				pError->GetDescription(&bstrDescription);

				ATL::Checked::tcsncpy_s(lpszError, nMaxError, ATL::COLE2T(bstrDescription), _TRUNCATE);
			}
			else
				*lpszError = _T('\0');
		}

		return bSuccess;
	}

	//Data members
	HRESULT m_hr;
	bool m_bNativeWin32Error;
#pragma warning(suppress: 26495)
};

//The "interface" which an AppSettings class must implement
class IAppSettings
{
public:
	//Typedefs
#ifdef _UNICODE
	using String = std::wstring;
#else
	using String = std::string;
#endif //#ifdef _UNICODE

	//Constructors / Destructors
	IAppSettings() = default;
	IAppSettings(const IAppSettings&) = delete;
	IAppSettings(IAppSettings&&) = delete;
	virtual ~IAppSettings() {}; //NOLINT(modernize-use-equals-default)

	//Virtual methods
	virtual int GetInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) = 0;
	virtual String GetString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) = 0;
	virtual std::vector<BYTE> GetBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) = 0;
	virtual std::vector<String> GetStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) = 0;

	//Versions of the AppSettings functions which mimic as closely as possible the functions of the same name in CWinApp 
	//or the authors CNTService class framework
	virtual int GetProfileInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nDefault)
	{
		try
		{
			return GetInt(lpszSection, lpszEntry);
		}
		catch (CAppSettingsException& /*e*/)
		{
			return nDefault;
		}
	}

	virtual String GetProfileString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszDefault = _T(""))
	{
		try
		{
			return GetString(lpszSection, lpszEntry);
		}
		catch (CAppSettingsException& /*e*/)
		{
			return lpszDefault;
		}
	}

	virtual bool GetProfileBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _Out_ std::vector<BYTE>& data)
	{
		//What will be the the return value (assume the best)
		bool bSuccess = true;

		try
		{
			data = GetBinary(lpszSection, lpszEntry);
		}
		catch (CAppSettingsException& /*e*/)
		{
			bSuccess = false;
		}

		return bSuccess;
	}

	virtual bool GetProfileStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _Out_ std::vector<String>& arr)
	{
		//What will be the the return value (assume the best)
		bool bSuccess = true;

		try
		{
			arr = GetStringArray(lpszSection, lpszEntry);
		}
		catch (CAppSettingsException& /*e*/)
		{
			bSuccess = false;
		}

		return bSuccess;
	}

	virtual std::vector<String> GetSections() = 0;
	virtual std::vector<String> GetSection(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bWithValues = true) = 0;
	virtual void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue) = 0;
	virtual void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue) = 0;
	virtual void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes) = 0;
	virtual void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr) = 0;
	virtual void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries) = 0;

	//Helper methods
	static void ThrowWin32AppSettingsException(_In_ DWORD dwError = 0)
	{
		if (dwError == 0)
			dwError = GetLastError();

		ATLTRACE(_T("Warning: throwing CAppSettingsException for error %u\n"), dwError);
		CAppSettingsException e{ dwError, FACILITY_WIN32 };
		throw e;
	}

	static void ThrowCOMAppSettingsException(_In_ HRESULT hr)
	{
		ATLTRACE(_T("Warning: throwing CAppSettingsException for error %08X\n"), hr);
		CAppSettingsException e{ hr };
		throw e;
	}

	//Other methods
	IAppSettings& operator=(const IAppSettings&) = delete;
	IAppSettings& operator=(IAppSettings&&) = delete;
};


//The base app settings class which reads / writes application settings to the windows registry
class CRegistryAppSettings : public IAppSettings
{
public:
	//Constructors / Destructors
	CRegistryAppSettings() noexcept : m_bWriteFlush(false)
	{
	}

	//Accessors / Mutators
	void SetWriteFlush(_In_ bool bWriteFlush) noexcept
	{
		m_bWriteFlush = bWriteFlush;
	}

	[[nodiscard]] bool GetWriteFlush() const noexcept
	{
		return m_bWriteFlush;
	}

	//IAppSettings
	int GetInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Then query for the value below the section
		DWORD dwValue{ 0 };
		DWORD dwType{ 0 };
		DWORD dwCount{ sizeof(DWORD) };
#pragma warning(suppress: 26490)
		const LSTATUS lResult{ RegQueryValueEx(hSecKey, lpszEntry, nullptr, &dwType, reinterpret_cast<LPBYTE>(&dwValue), &dwCount) };
		RegCloseKey(hSecKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
		if (dwType != REG_DWORD)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);
#pragma warning(suppress: 26477)
		ATLASSERT(dwCount == sizeof(dwValue));
#pragma warning(suppress: 26472)
		return static_cast<int>(dwValue);
	}

	String GetString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Then query for the value below the section
		DWORD dwType{ 0 };
		DWORD dwCount{ 0 };
		LSTATUS lResult{ RegQueryValueEx(hSecKey, lpszEntry, nullptr, &dwType, nullptr, &dwCount) };
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(lResult);
		}
		if (dwType != REG_SZ)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);
		}

		const size_t nAllocatedSizeChars{ (dwCount / sizeof(TCHAR)) + 1 }; //+1 is to allow us to safely null terminate the data
		const size_t nAllocatedSizeBytes{ nAllocatedSizeChars * sizeof(TCHAR) };
		String strValue{ nAllocatedSizeChars, _T('\0'), std::allocator<TCHAR>{} };
#pragma warning(suppress: 26429 26446)
		LPTSTR pszStrValue{ strValue.data() };
#pragma warning(suppress: 26490)
		lResult = RegQueryValueEx(hSecKey, lpszEntry, nullptr, &dwType, reinterpret_cast<LPBYTE>(pszStrValue), &dwCount);
		RegCloseKey(hSecKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
		if (dwType != REG_SZ)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);

		//Handle the case where we will not be able to safely null terminate the data. This could occur where the data 
		//has been updated in the registry between the two calls to RegQueryValueEx above. Rather than
		//process a potentially non null terminated block of data, just fail the method call
		if ((dwCount + sizeof(TCHAR)) > nAllocatedSizeBytes)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);

		//Safely null terminate the data
#pragma warning(suppress: 26481)
		pszStrValue[(dwCount / sizeof(TCHAR))] = _T('\0');
		strValue.resize((dwCount / sizeof(TCHAR)) - 1);

		return strValue;
	}

	std::vector<BYTE> GetBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//First get the size of the binary data
		DWORD dwType{ 0 };
		DWORD dwCount{ 0 };
		LSTATUS lResult{ RegQueryValueEx(hSecKey, lpszEntry, nullptr, &dwType, nullptr, &dwCount) };
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(lResult);
		}
		if (dwType != REG_BINARY)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);
		}
		std::vector<BYTE> data{ dwCount, std::allocator<BYTE>{} };
		lResult = RegQueryValueEx(hSecKey, lpszEntry, nullptr, &dwType, data.data(), &dwCount);
		RegCloseKey(hSecKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
		if (dwType != REG_BINARY)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);

		return data;
	}

	std::vector<String> GetStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//What will be the return value from this method
		std::vector<String> arr;

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Call the helper function which does the heavy lifting
		try
		{
			arr = GetStringArrayFromRegistry(hSecKey, lpszEntry);
		}
#pragma warning(suppress: 26496)
		catch (CAppSettingsException& e)
		{
			RegCloseKey(hSecKey); //Close the section key before we rethrow the exception
			throw e;
		}

		//Close the key before we return
		RegCloseKey(hSecKey);

		return arr;
	}

	std::vector<String> GetSections() override
	{
		//What will be the return value from this method
		std::vector<String> sections;

		//Try to get the application key
		HKEY hAppKey{ GetAppKey(true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hAppKey != nullptr);

		//Enumerate all the section keys
		ATL::CAtlString sValueName;
		DWORD dwValueNameSize{ _MAX_PATH };
		DWORD dwIndex{ 0 };
		LPTSTR szValueName{ sValueName.GetBuffer(_MAX_PATH) };
		LSTATUS nEnum{ RegEnumKeyEx(hAppKey, dwIndex, szValueName, &dwValueNameSize, nullptr, nullptr, nullptr, nullptr) };
		while (nEnum == ERROR_SUCCESS)
		{
			//Add the section name to the array
			sections.emplace_back(sValueName);

			//Prepare for the next time around
			dwValueNameSize = _MAX_PATH;
			++dwIndex;
			nEnum = RegEnumKeyEx(hAppKey, dwIndex, szValueName, &dwValueNameSize, nullptr, nullptr, nullptr, nullptr);
		}
		sValueName.ReleaseBuffer();

		return sections;
	}

	std::vector<String> GetSection(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bWithValues) override
	{
		//Note that because we are trying to emulate the functionality of "GetPrivateProfileSection"
		//which returns a homogenous array of strings, either natively or thro CRegistryAppSetting
		//The supported data types this function supports is documented in the "switch (dwType)" code 
		//below. Note the 2 biggest omissions are REG_MULTI_SZ and REG_BINARY which both just return 
		//place holder values

		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//What will be the return value from this method
		std::vector<String> sectionEntries;

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, true) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Get the max length of the values below the section key
		DWORD dwMaxValueNameLen{ 0 };
		const LSTATUS nSuccess{ RegQueryInfoKey(hSecKey, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &dwMaxValueNameLen, nullptr, nullptr, nullptr) };
		if (nSuccess != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(nSuccess);

		//Allocate the memory we want
#pragma warning(suppress: 26472)
		std::vector<TCHAR> szValueName{ static_cast<size_t>(dwMaxValueNameLen) + 1, std::allocator<TCHAR>{} }; //+1 is for the null terminator

		//Now enumerate all the values for the section key
#pragma warning(suppress: 26446)
		szValueName[0] = _T('\0');
		DWORD dwValueNameSize{ dwMaxValueNameLen + 1 };
		DWORD dwIndex{ 0 };
		DWORD dwType{ 0 };
		LSTATUS nEnum{ RegEnumValue(hSecKey, dwIndex, szValueName.data(), &dwValueNameSize, nullptr, &dwType, nullptr, nullptr) };
		while (nEnum == ERROR_SUCCESS)
		{
			if (bWithValues)
			{
				switch (dwType)
				{
					case REG_EXPAND_SZ: //deliberate fallthrough
					case REG_SZ:
					{
						ATL::CAtlString sEntry;
						sEntry.Format(_T("%s=%s"), szValueName.data(), GetString(lpszSection, szValueName.data()).c_str());
						sectionEntries.emplace_back(sEntry);
						break;
					}
					case REG_DWORD:
					{
						ATL::CAtlString sEntry;
						sEntry.Format(_T("%s=%d"), szValueName.data(), GetInt(lpszSection, szValueName.data()));
						sectionEntries.emplace_back(sEntry);
						break;
					}
					case REG_BINARY:
					{
						ATL::CAtlString sEntry;
						sEntry.Format(_T("%s=<REG_BINARY VALUE>"), szValueName.data());
						sectionEntries.emplace_back(sEntry);
						break;
					}
					case REG_MULTI_SZ:
					{
						ATL::CAtlString sEntry;
						sEntry.Format(_T("%s=<REG_MULTI_SZ VALUE>"), szValueName.data());
						sectionEntries.emplace_back(sEntry);
						break;
					}
					default:
					{
						ATLTRACE(_T("CRegistryAppSettings::GetSection, Encountered a data type which will not be included in returned data, DataType:%d\n"), dwType);
						break;
					}
				}
			}
			else
			{
				//Simply use the value name
				sectionEntries.emplace_back(szValueName.data());
			}

			//Prepare for the next time around
			dwValueNameSize = dwMaxValueNameLen + 1;
			++dwIndex;
			nEnum = RegEnumValue(hSecKey, dwIndex, szValueName.data(), &dwValueNameSize, nullptr, &dwType, nullptr, nullptr);
		}

		return sectionEntries;
	}

	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteInt(lpszSection, lpszEntry, nValue, m_bWriteFlush);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteString(lpszSection, lpszEntry, lpszValue, m_bWriteFlush);
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteBinary(lpszSection, lpszEntry, pData, dwBytes, m_bWriteFlush);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteStringArray(lpszSection, lpszEntry, arr, m_bWriteFlush);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteSection(lpszSection, sectionEntries, m_bWriteFlush);
	}

	//Versions of the Write* methods which allow you to specify the flush setting as a parameter
	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue, _In_ bool bFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Then write out the value below the section
#pragma warning(suppress: 26490)
		const LSTATUS lResult{ RegSetValueEx(hSecKey, lpszEntry, 0, REG_DWORD, reinterpret_cast<LPBYTE>(&nValue), sizeof(nValue)) };
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(lResult);
		}

		//Flush if required
		if (bFlush)
			RegFlushKey(hSecKey);

		//Close the key before we return
		RegCloseKey(hSecKey);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue, _In_ bool bFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSUME(lpszSection != nullptr);

		if (lpszEntry == nullptr) //delete whole section
		{
			//Try to get the application key
			HKEY hAppKey{ GetAppKey(false) };
#pragma warning(suppress: 26477)
			ATLASSUME(hAppKey != nullptr);

			//Nuke the specified section
			const LSTATUS lResult{ RegDeleteKey(hAppKey, lpszSection) };
			if (lResult != ERROR_SUCCESS)
			{
				RegCloseKey(hAppKey); //Close the section key before we throw the exception
				ThrowWin32AppSettingsException(lResult);
			}

			//Flush if required
			if (bFlush)
				RegFlushKey(hAppKey);

			//Close the key before we return
			RegCloseKey(hAppKey);
		}
		else if (lpszValue == nullptr)
		{
			//Try to get the section key
			HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
			ATLASSUME(hSecKey != nullptr);

			//Delete the section key
			const LSTATUS lResult{ RegDeleteValue(hSecKey, lpszEntry) };
			if (lResult != ERROR_SUCCESS)
			{
				RegCloseKey(hSecKey); //Close the section key before we throw the exception
				ThrowWin32AppSettingsException(lResult);
			}

			//Flush if required
			if (bFlush)
				RegFlushKey(hSecKey);

			//Close the key before we return
			RegCloseKey(hSecKey);
		}
		else
		{
			//Try to get the section key
			HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
			ATLASSUME(hSecKey != nullptr);

			//Then write out the value below the section
#pragma warning(suppress: 26472 26490)
			const LSTATUS lResult{ RegSetValueEx(hSecKey, lpszEntry, 0, REG_SZ, reinterpret_cast<const BYTE*>(lpszValue), static_cast<DWORD>((_tcslen(lpszValue) + 1) * sizeof(TCHAR))) };
			if (lResult != ERROR_SUCCESS)
			{
				RegCloseKey(hSecKey); //Close the section key before we throw the exception
				ThrowWin32AppSettingsException(lResult);
			}

			//Flush if required
			if (bFlush)
				RegFlushKey(hSecKey);

			//Close the key before we return
			RegCloseKey(hSecKey);
		}
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes, _In_ bool bFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Then write out the value below the section
		const LSTATUS lResult{ RegSetValueEx(hSecKey, lpszEntry, 0, REG_BINARY, pData, dwBytes) };
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSecKey); //Close the section key before we throw the exception
			ThrowWin32AppSettingsException(lResult);
		}

		//Flush if required
		if (bFlush)
			RegFlushKey(hSecKey);

		//Close the key before we return
		RegCloseKey(hSecKey);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr, _In_ bool bFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//Try to get the section key
		HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		//Call the helper function which does the heavy lifting
		try
		{
			SetStringArrayIntoRegistry(hSecKey, lpszEntry, arr);
		}
#pragma warning(suppress: 26496)
		catch (CAppSettingsException& e)
		{
			RegCloseKey(hSecKey); //Close the section key before we rethrow the exception
			throw e;
		}

		//Flush if required
		if (bFlush)
			RegFlushKey(hSecKey);

		//Close the key before we return
		RegCloseKey(hSecKey);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries, _In_ bool bFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//First nuke the registry key entirely (using the WriteString delete section functionality)
		WriteString(lpszSection, nullptr, nullptr, bFlush);

		//Now get the (newly created) section key
		HKEY hSecKey{ GetSectionKey(lpszSection, false) };
#pragma warning(suppress: 26477)
		ATLASSUME(hSecKey != nullptr);

		try
		{
			//now write out all the new entries
			for (const auto& sEntry : sectionEntries)
			{
				String sName;
#pragma warning(suppress: 26489)
				String sValue;
#pragma warning(suppress: 26489)
				const auto nSeparator{ sEntry.find(_T('=')) };
				if (nSeparator != String::npos)
				{
#pragma warning(suppress: 26489)
					sName = sEntry.substr(0, nSeparator);
#pragma warning(suppress: 26489)
					sValue = sEntry.substr(nSeparator + 1, sEntry.length() - 1 - nSeparator);
				}
				else
#pragma warning(suppress: 26486 26489)
					sName = sEntry;

				WriteString(lpszSection, sName.c_str(), sValue.c_str(), false);
			}
		}
#pragma warning(suppress: 26496)
		catch (CAppSettingsException& e)
		{
			RegCloseKey(hSecKey); //Close the section key before we rethrow the exception
			throw e;
		}

		//Flush if required
		if (bFlush)
			RegFlushKey(hSecKey);

		//Close the key before we return
		RegCloseKey(hSecKey);
	}

protected:
	//Helper functions

	  //returns key one level down from GetAppKey. It is the responsibility of the caller to call RegCloseKey() on the returned HKEY
	HKEY GetSectionKey(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bReadOnly)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSUME(lpszSection != nullptr);

		//Try to get the application key
		HKEY hAppKey{ GetAppKey(bReadOnly) };
#pragma warning(suppress: 26477)
		ATLASSUME(hAppKey != nullptr);

		//Try to open/create the key
		HKEY hSectionKey = nullptr;
		const LSTATUS lResult{ RegCreateKeyEx(hAppKey, lpszSection, 0, nullptr, REG_OPTION_NON_VOLATILE, bReadOnly ? KEY_READ : KEY_WRITE | KEY_READ, nullptr, &hSectionKey, nullptr) };
		RegCloseKey(hAppKey);

		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		return hSectionKey;
	}

	static std::vector<String> GetStringArrayFromRegistry(_In_ HKEY hKey, _In_opt_z_ LPCTSTR lpszEntry)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSUME(hKey != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Get the type and size of the data
		DWORD dwType{ 0 };
		DWORD dwCount{ 0 };
		LSTATUS lResult{ RegQueryValueEx(hKey, lpszEntry, nullptr, &dwType, nullptr, &dwCount) };
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
		if (dwType != REG_MULTI_SZ)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);

		//Allocate some heap memory to hold the data
		const size_t nAllocatedSizeBytes{ dwCount + (2 * sizeof(TCHAR)) }; //the + (2 * sizeof(TCHAR)) is to allow us to safely doubly null terminate the data
		std::vector<BYTE> dataBuffer{ nAllocatedSizeBytes, std::allocator<BYTE>{} };

		lResult = RegQueryValueEx(hKey, lpszEntry, nullptr, &dwType, dataBuffer.data(), &dwCount);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
		if (dwType != REG_MULTI_SZ)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATATYPE);

		//Handle the case where we will not be able to safely doubly null terminator the data. This could occur where the data 
		//has been updated in the registry between the two calls to RegQueryValueEx above. Rather than
		//process a potentially non doubly null terminated block of data, just fail the method call
		if ((dwCount + (2 * sizeof(TCHAR))) > nAllocatedSizeBytes)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);

		//Safely doubly null terminate the data
#pragma warning(suppress: 26429 26490)
		auto lpszStrings{ reinterpret_cast<LPTSTR>(dataBuffer.data()) };
#pragma warning(suppress: 26481)
		lpszStrings[(dwCount / sizeof(TCHAR))] = _T('\0');
#pragma warning(suppress: 26481)
		lpszStrings[(dwCount / sizeof(TCHAR)) + 1] = _T('\0');

		//Iterate thro the multi SZ string and add each one to the string array
		std::vector<String> arr;
#pragma warning(suppress: 26481 26489)
		while (lpszStrings[0] != _T('\0'))
		{
#pragma warning(suppress: 26486 26489)
			arr.emplace_back(lpszStrings);
#pragma warning(suppress: 26481 26486)
			lpszStrings += (_tcslen(lpszStrings) + 1);
		}

		return arr;
	}

	static void SetStringArrayIntoRegistry(_In_ HKEY hKey, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr)
	{
		//Validate our input parameters
#pragma warning(suppress: 26477)
		ATLASSUME(hKey != nullptr);
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Work out the size of the buffer we will need
		size_t nSize{ 0 };
		for (const auto& entry : arr)
			nSize += (entry.length() + 1); //1 extra for each null terminator

		//Need one second null for the double null at the end
		nSize++;

		//Allocate the memory we want
		std::vector<TCHAR> dataBuffer{ nSize, std::allocator<TCHAR>{} };

		//Now copy the strings into the buffer
#pragma warning(suppress: 26429)
		LPTSTR lpszString{ dataBuffer.data() };
		size_t nCurOffset{ 0 };
		for (const auto& sText : arr)
		{
			const auto nCurrentStringLength{ sText.length() };
#pragma warning(suppress: 26481)
			_tcscpy_s(&lpszString[nCurOffset], nCurrentStringLength + 1, sText.c_str());
			nCurOffset += nCurrentStringLength;
			nCurOffset++;
		}
		//Don't forgot to doubly null terminate
#pragma warning(suppress: 26481)
		lpszString[nCurOffset] = _T('\0');

		//Finally write it into the registry
#pragma warning(suppress: 26472 26490)
		const LSTATUS lResult{ RegSetValueEx(hKey, lpszEntry, 0, REG_MULTI_SZ, reinterpret_cast<const BYTE*>(dataBuffer.data()), static_cast<DWORD>(nSize * sizeof(TCHAR))) };
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);
	}

	//pure virtual function which derived classes must implement to make a concrete class definition
	virtual HKEY GetAppKey(_In_ bool bReadOnly) = 0;

	//Member variables
	bool m_bWriteFlush;
};


//The base app settings class for CHKLMAppSettings and CHCURMAppSettings
class CRegistryApplicationAppSettings : public CRegistryAppSettings
{
public:
	//Accessors / Mutators
	void SetProductName(_In_ const String& sProductName)
	{
		m_sProductName = sProductName;
	}

	[[nodiscard]] String GetProductName() const
	{
		return m_sProductName;
	}

	void SetCompanyName(_In_ const String& sCompanyName)
	{
		m_sCompanyName = sCompanyName;
	}

	[[nodiscard]] String GetCompanyName() const
	{
		return m_sCompanyName;
	}

	void SetProductVersion(_In_ const String& sProductVersion)
	{
		m_sProductVersion = sProductVersion;
	}

	[[nodiscard]] String GetProductVersion() const
	{
		return m_sProductVersion;
	}

protected:
	//Helper functions
	HKEY GetAppKey(_In_ bool bReadOnly) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(m_sCompanyName.length()); //Did you forget to call "SetCompanyName"?
#pragma warning(suppress: 26477)
		ATLASSERT(m_sProductName.length());

		//Setup the access type
		REGSAM samDesired{ 0 };
		if (bReadOnly)
			samDesired = KEY_READ;
		else
			samDesired = KEY_WRITE | KEY_READ;

		//Open the software key
		HKEY hSoftKey{ nullptr };
		LSTATUS lResult{ RegOpenKeyEx(GetRootKey(), _T("Software"), 0, samDesired, &hSoftKey) };
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		//Open the company key
		HKEY hCompanyKey{ nullptr };
		lResult = RegCreateKeyEx(hSoftKey, m_sCompanyName.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, samDesired, nullptr, &hCompanyKey, nullptr);
		RegCloseKey(hSoftKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		//Open the product key
		HKEY hProductKey{ nullptr };
		lResult = RegCreateKeyEx(hCompanyKey, m_sProductName.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, samDesired, nullptr, &hProductKey, nullptr);
		RegCloseKey(hCompanyKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		//Open the ProductVersion key (if necessary)
		if (m_sProductVersion.length())
		{
			HKEY hProductVersionKey{ nullptr };
			lResult = RegCreateKeyEx(hProductKey, m_sProductVersion.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, samDesired, nullptr, &hProductVersionKey, nullptr);
			RegCloseKey(hProductKey);
			if (lResult != ERROR_SUCCESS)
				ThrowWin32AppSettingsException(lResult);

			return hProductVersionKey;
		}
		else
			return hProductKey;
	}
	virtual HKEY GetRootKey() = 0;

	//member variables
	String m_sCompanyName;
	String m_sProductName;
	String m_sProductVersion;
};


//The app settings class which reads / writes application settings to the HKLM node in the windows registry
class CHKLMAppSettings : public CRegistryApplicationAppSettings
{
public:
	//Constructors / Destructors
	CHKLMAppSettings(_In_ const String& sCompanyName, _In_ const String& sProductName,
		_In_ const String& sProductVersion = _T("1.0"), _In_ bool bWriteFlush = false)
	{
		m_sCompanyName = sCompanyName;
		m_sProductName = sProductName;
		m_sProductVersion = sProductVersion;
		m_bWriteFlush = bWriteFlush;
	}

protected:
	//virtual methods
	HKEY GetRootKey() noexcept override
	{
		return HKEY_LOCAL_MACHINE;
	}
};


//The app settings class which reads / writes application settings to the HKLM node in the windows registry
class CHKCUAppSettings : public CRegistryApplicationAppSettings
{
public:
	//Constructors / Destructors
	CHKCUAppSettings(_In_ const String& sCompanyName, _In_ const String& sProductName,
		_In_ const String& sProductVersion = _T("1.0"), _In_ bool bWriteFlush = false)
	{
		m_sCompanyName = sCompanyName;
		m_sProductName = sProductName;
		m_sProductVersion = sProductVersion;
		m_bWriteFlush = bWriteFlush;
	}

protected:
	//virtual methods
	HKEY GetRootKey() noexcept override
	{
		return HKEY_CURRENT_USER;
	}
};

//The app settings class which reads / writes settings to the HKLM\System\CurrentControlSet\Services\"ServiceName"\Parameters node in the windows registry
class CServicesAppSettings : public CRegistryAppSettings
{
public:
	//Constructors / Destructors
	CServicesAppSettings(_In_ const String& sServiceName, _In_ bool bWriteFlush = false)
	{
		m_bWriteFlush = bWriteFlush;
		m_sServiceName = sServiceName;
	}

	//Accessors / Mutators
	void SetServiceName(_In_ const String& sServiceName)
	{
		m_sServiceName = sServiceName;
	}

	[[nodiscard]] String GetServiceName() const
	{
		return m_sServiceName;
	}

protected:
	//Virtual methods
	HKEY GetAppKey(_In_ bool bReadOnly) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(m_sServiceName.length()); //Did you forget to call "SetServiceName"?

		//Setup the access type
		REGSAM samDesired{ 0 };
		if (bReadOnly)
			samDesired = KEY_READ;
		else
			samDesired = KEY_WRITE | KEY_READ;

		//Open the Services key
		HKEY hServicesKey{ nullptr };
		LSTATUS lResult{ RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services"), 0, samDesired, &hServicesKey) };
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		//Open the service key
		HKEY hServiceKey{ nullptr };
		lResult = RegCreateKeyEx(hServicesKey, m_sServiceName.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, samDesired, nullptr, &hServiceKey, nullptr);
		RegCloseKey(hServicesKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		//Open the Parameters key
		HKEY hParametersKey{ nullptr };
		lResult = RegCreateKeyEx(hServiceKey, _T("Parameters"), 0, nullptr, REG_OPTION_NON_VOLATILE, samDesired, nullptr, &hParametersKey, nullptr);
		RegCloseKey(hServiceKey);
		if (lResult != ERROR_SUCCESS)
			ThrowWin32AppSettingsException(lResult);

		return hParametersKey;
	}

	//Member variables
	String m_sServiceName;
};


//The App settings class which reads / writes application settings to an windows ini file
class CIniAppSettings : public IAppSettings
{
public:
	//Constructors / Destructors
	CIniAppSettings(_In_ String sIniFile) noexcept : m_sIniFile(std::move(sIniFile))
	{
	}

	//Accessors / Mutators
	void SetIniFile(_In_ const String& sIniFile)
	{
		m_sIniFile = sIniFile;
	}

	[[nodiscard]] String GetIniFile() const
	{
		return m_sIniFile;
	}

	//IAppSettings
	int GetInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		String sValue(GetString(lpszSection, lpszEntry));
		return _ttoi(sValue.c_str());
	}

	String GetString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(m_sIniFile.length());

		//Generate a GUID for the default string so that we will absolutely know when we have been returned a default 
		//string from GetPrivateProfileString
		GUID guid{};
		HRESULT hr{ CoCreateGuid(&guid) };
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		LPOLESTR wszCLSID{ nullptr };
		hr = StringFromCLSID(guid, &wszCLSID);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		ATL::COLE2T sCLSID{ wszCLSID };
		CoTaskMemFree(wszCLSID);

		ATL::CAtlString sT;
		GetPrivateProfileString(lpszSection, lpszEntry, sCLSID, sT.GetBuffer(4096), 4096, m_sIniFile.c_str());
		sT.ReleaseBuffer();

		//Check to see if the return value matches the default, and if it did throw an exception
		if (_tcscmp(sT, sCLSID) == 0)
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);

		return { sT.GetString() };
	}

	std::vector<BYTE> GetBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		String sBinary{ GetString(lpszSection, lpszEntry) };
		const auto nLen{ sBinary.length() };
		if (nLen == 0)
			return std::vector<BYTE>{};
		if (nLen % 2)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);
		std::vector<BYTE> data{ nLen / 2, std::allocator<BYTE>{} };
		for (size_t i = 0; i < nLen; i += 2)
		{
#pragma warning(suppress: 26446 26472)
			data[i / 2] = static_cast<BYTE>(((sBinary[i + 1] - 'A') << 4) + (sBinary[i] - 'A'));
		}

		return data;
	}

	std::vector<String> GetStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Try to get the binary data first
		std::vector<BYTE> data{ GetBinary(lpszSection, lpszEntry) };
		if (data.size() == 0)
			return std::vector<String>{};

		std::vector<String> arr;
#pragma warning(suppress: 26429 26490)
		auto lpszStrings{ reinterpret_cast<LPTSTR>(data.data()) };
#pragma warning(suppress: 26481 26489)
		while (lpszStrings[0] != _T('\0'))
		{
#pragma warning(suppress: 26486)
			arr.emplace_back(lpszStrings);
#pragma warning(suppress: 26481 26486)
			lpszStrings += (_tcslen(lpszStrings) + 1);
		}
		return arr;
	}

	std::vector<String> GetSections() override
	{
		//What will be the return value from this method
		std::vector<String> sections;

		DWORD dwSize{ 1024 };
		bool bSuccess{ false };
		while (!bSuccess)
		{
			//Allocate some heap memory for the SDK call
			std::vector<TCHAR> sectionsBuffer{ dwSize, std::allocator<TCHAR>{} };

			//Call the SDK function
			const DWORD dwRetrieved{ GetPrivateProfileString(nullptr, nullptr, nullptr, sectionsBuffer.data(), dwSize, m_sIniFile.c_str()) };
			if (dwRetrieved == (dwSize - 2))
			{
				//Realloc the array by doubling its size ready for the next loop around
				dwSize *= 2;
			}
			else if (dwRetrieved == 0)
			{
				const DWORD dwError{ GetLastError() };

				//Only consider it an error if no data was retrieved and GetLastError flagged an error
				if (dwError)
					ThrowWin32AppSettingsException(dwError);
				else
				{
					//Just return with an empty array
					bSuccess = true;
				}
			}
			else
			{
				//Convert from a multi sz string format to the std::vector<String> out parameter
				bSuccess = true;

#pragma warning(suppress: 26429)
				LPTSTR pszCurrentString{ sectionsBuffer.data() };
#pragma warning(suppress: 26481 26489)
				while (pszCurrentString[0] != _T('\0'))
				{
#pragma warning(suppress: 26486)
					sections.emplace_back(pszCurrentString);
#pragma warning(suppress: 26481 26486)
					pszCurrentString += (_tcslen(pszCurrentString) + 1);
				}
			}
		}

		return sections;
	}

	std::vector<String> GetSection(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bWithValues) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSUME(lpszSection != nullptr);

		//What will be the return value from this method
		std::vector<String> sectionEntries;

		DWORD dwSize{ 1024 };
		bool bSuccess{ false };
		while (!bSuccess)
		{
			//Allocate some heap memory for the SDK call
			std::vector<TCHAR> sectionEntriesBuffer{ dwSize, std::allocator<TCHAR>{} };

			//Call the SDK function
			DWORD dwRetrieved{ 0 };
			if (bWithValues)
				dwRetrieved = GetPrivateProfileSection(lpszSection, sectionEntriesBuffer.data(), dwSize, m_sIniFile.c_str());
			else
				dwRetrieved = GetPrivateProfileString(lpszSection, nullptr, nullptr, sectionEntriesBuffer.data(), dwSize, m_sIniFile.c_str());
			if (dwRetrieved == (dwSize - 2))
			{
				//Realloc the array by doubling its size ready for the next loop around
				dwSize *= 2;
			}
			else if (dwRetrieved == 0)
			{
				const DWORD dwError{ GetLastError() };

				//Only consider it an error if no data was retrieved and GetLastError flagged an error
				if (dwError)
					ThrowWin32AppSettingsException(dwError);
				else
				{
					//Just return with an empty array
					bSuccess = true;
				}
			}
			else
			{
				//Convert from a multi sz string format to the std::vector<String> out parameter
				bSuccess = true;

#pragma warning(suppress: 26429)
				LPTSTR pszCurrentString{ sectionEntriesBuffer.data() };
#pragma warning(suppress: 26481 26489)
				while (pszCurrentString[0] != _T('\0'))
				{
#pragma warning(suppress: 26486)
					sectionEntries.emplace_back(pszCurrentString);
#pragma warning(suppress: 26481 26486)
					pszCurrentString += (_tcslen(pszCurrentString) + 1);
				}
			}
		}

		return sectionEntries;
	}

	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue) override
	{
		ATL::CAtlString sValue;
		sValue.Format(_T("%d"), nValue);
		WriteString(lpszSection, lpszEntry, sValue);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue) override
	{
#pragma warning(suppress: 26477)
		ATLASSERT(m_sIniFile.length()); //Validate our parameters
		if (!WritePrivateProfileString(lpszSection, lpszEntry, lpszValue, m_sIniFile.c_str()))
			ThrowWin32AppSettingsException();
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes) override
	{
		//Allocate some heap memory for the data we will be writing out
#pragma warning(suppress: 26472)
		std::vector<TCHAR> dataBuffer{ (static_cast<size_t>(dwBytes) * 2) + 1, std::allocator<TCHAR>{} };

		//convert the data to write out to string format
		for (size_t i = 0; i < dwBytes; i++)
		{
#pragma warning(suppress: 26477)
			ATLASSUME(pData != nullptr);
#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[i * 2] = static_cast<TCHAR>((pData[i] & 0x0F) + 'A'); //low nibble
#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[(i * 2) + 1] = static_cast<TCHAR>(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
		}
#pragma warning(suppress: 26446 26472)
		dataBuffer[static_cast<size_t>(dwBytes) * 2] = _T('\0');

		//Call the WriteString method to write out the data for us
		WriteString(lpszSection, lpszEntry, dataBuffer.data());
	}

	void WriteStringArray(_In_opt_ LPCTSTR lpszSection, _In_opt_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr) override
	{
		//Work out the size of the buffer we will need
		size_t nSize{ 0 };
		for (const auto& sText : arr)
			nSize += (sText.length() + 1); //1 extra for each null terminator

		//Need one second null for the double null at the end
		nSize++;

		//Allocate the memory we want
		std::vector<TCHAR> dataBuffer{ nSize, std::allocator<TCHAR>{} };

		//Now copy the strings into the buffer
		size_t nCurOffset{ 0 };
#pragma warning(suppress: 26429)
		LPTSTR lpszString{ dataBuffer.data() };
		for (const auto& sText : arr)
		{
			const auto nCurrentStringLength{ sText.length() };
#pragma warning(suppress: 26481)
			_tcscpy_s(&lpszString[nCurOffset], nCurrentStringLength + 1, sText.c_str());
			nCurOffset += nCurrentStringLength;
			nCurOffset++;
		}
		//Don't forgot to doubly null terminate
#pragma warning(suppress: 26481)
		lpszString[nCurOffset] = _T('\0');

		//Call the WriteBinary method to write out the data for us
#pragma warning(suppress: 26472 26490)
		WriteBinary(lpszSection, lpszEntry, reinterpret_cast<const BYTE*>(dataBuffer.data()), static_cast<DWORD>(nSize * sizeof(TCHAR)));
	}

	void WriteSection(_In_opt_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries) override
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(m_sIniFile.length());

		//Work out the size of the doubly null terminated string we need
		size_t nStringSize{ 0 };
		for (const auto& sText : sectionEntries)
		{
			nStringSize += sText.length();
			nStringSize++; //Include the null terminator
		}
		nStringSize++; //Include the final null terminator

		//Allocate the memory we want
		std::vector<TCHAR> keyValuesBuffer{ nStringSize, std::allocator<TCHAR>{} };

		//Now copy the strings into the buffer
		size_t nCurOffset{ 0 };
#pragma warning(suppress: 26429)
		LPTSTR lpszString{ keyValuesBuffer.data() };
		for (const auto& sText : sectionEntries)
		{
			const auto nCurrentStringLength{ sText.length() };
#pragma warning(suppress: 26481)
			_tcscpy_s(&(lpszString[nCurOffset]), nCurrentStringLength + 1, sText.c_str());
			nCurOffset += nCurrentStringLength;
			++nCurOffset;
		}
#pragma warning(suppress: 26481)
		lpszString[nCurOffset] = _T('\0'); //Include the final null terminator

		//Call the SDK function
		const BOOL bSuccess{ WritePrivateProfileSection(lpszSection, keyValuesBuffer.data(), m_sIniFile.c_str()) };
		if (!bSuccess)
			ThrowWin32AppSettingsException();
	}

	//Static methods
	[[nodiscard]] static ATL::CAtlString GetModuleFileName(_Inout_opt_ DWORD* pdwLastError = nullptr)
	{
		ATL::CAtlString sModuleFileName;
		DWORD dwSize{ _MAX_PATH };
		while (true)
		{
			TCHAR* pszModuleFileName{ sModuleFileName.GetBuffer(dwSize) };
			const DWORD dwResult{ ::GetModuleFileName(nullptr, pszModuleFileName, dwSize) };
			if (dwResult == 0)
			{
				if (pdwLastError != nullptr)
					*pdwLastError = GetLastError();
				sModuleFileName.ReleaseBuffer(0);
				return ATL::CAtlString{};
			}
			else if (dwResult < dwSize)
			{
				if (pdwLastError != nullptr)
					*pdwLastError = ERROR_SUCCESS;
				sModuleFileName.ReleaseBuffer(dwResult);
				return sModuleFileName;
			}
			else if (dwResult == dwSize)
			{
				sModuleFileName.ReleaseBuffer(0);
				dwSize *= 2;
			}
		}
	}

	//Note, using this function for an ini path is not a good idea for security reasons, but if you really want to you can use this function to return a ini 
	//path which has a filename the same name as the current process and in the same directory as it.
	static String GetCurrentProcessIniFileLocation()
	{
		DWORD dwError{ ERROR_SUCCESS };
		ATL::CAtlString sIni{ GetModuleFileName(&dwError) };
		if (sIni.IsEmpty())
			ThrowWin32AppSettingsException(dwError);
		std::filesystem::path ini{ sIni.GetString() };
		ini.replace_extension(L"ini");
#ifdef _UNICODE
		return { ini.c_str() };
#else
		return { ATL::CW2A(ini.c_str()).operator LPSTR() };
#endif //#ifdef _UNICODE
	}

	static String GetRoamingDataFileLocation(_In_ const String& sCompanyName, _In_ const String& sProductName, _In_ const String& sProductVersion, _In_ const String& sIniFileName)
	{
		return GetSpecialFolder(FOLDERID_RoamingAppData, sCompanyName, sProductName, sProductVersion, sIniFileName);
	}

	static String GetNonRoamingDataFileLocation(_In_ const String& sCompanyName, _In_ const String& sProductName, _In_ const String& sProductVersion, _In_ const String& sIniFileName)
	{
		return GetSpecialFolder(FOLDERID_LocalAppData, sCompanyName, sProductName, sProductVersion, sIniFileName);
	}

	static String GetPerComputerDataFileLocation(_In_ const String& sCompanyName, _In_ const String& sProductName, _In_ const String& sProductVersion, _In_ const String& sIniFileName)
	{
		return GetSpecialFolder(FOLDERID_ProgramData, sCompanyName, sProductName, sProductVersion, sIniFileName);
	}

protected:
	//Helper functions
	static void MakeEnsureDirectory(_In_z_ LPCTSTR pszDirectory)
	{
		//Check to see if it already exists
		const DWORD dwAttributes{ GetFileAttributes(pszDirectory) };
		if (dwAttributes == INVALID_FILE_ATTRIBUTES) //Does not exist, then attempt to create it
		{
			if (!CreateDirectory(pszDirectory, nullptr))
				ThrowWin32AppSettingsException();
		}
		else
		{
			if ((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) //Check that what exists is a directory
				ThrowWin32AppSettingsException(ERROR_CANNOT_MAKE);
		}
	}

	static String GetSpecialFolder(_In_ REFKNOWNFOLDERID nFolder, _In_ const String& sCompanyName, _In_ const String& sProductName, _In_ const String& sProductVersion, _In_ const String& sIniFileName)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(sCompanyName.length());
#pragma warning(suppress: 26477)
		ATLASSERT(sProductName.length());
#pragma warning(suppress: 26477)
		ATLASSERT(sIniFileName.length());

		PWSTR pszPath{ nullptr };
		const HRESULT hr{ SHGetKnownFolderPath(nFolder, 0, nullptr, &pszPath) };
		if (FAILED(hr))
			ThrowWin32AppSettingsException(hr);
		ATL::CAtlString sPath{ pszPath };
		CoTaskMemFree(pszPath);

		//Now create/open the CompanyName folder below the required CSIDL folder
		sPath += _T("\\");
		sPath += sCompanyName.c_str();
		MakeEnsureDirectory(sPath);

		//Now create/open the ProductName folder below the CompanyName folder
		sPath += _T("\\");
		sPath += sProductName.c_str();
		MakeEnsureDirectory(sPath);

		if (sProductVersion.length()) //ProductVersion string is optional
		{
			sPath += _T("\\");
			sPath += sProductVersion.c_str();
			MakeEnsureDirectory(sPath);
		}

		//Finally tack on the filename required to the calculated path
		sPath += _T("\\");
		sPath += sIniFileName.c_str();

		//If we got here, then everything is cool
		return { sPath.GetString() };
	}

	//Member variables
	String m_sIniFile;
};


//The App settings class which reads / writes application settings to an windows XML file
class CXMLAppSettings : public IAppSettings
{
public:
	//Constructors / Destructors
	CXMLAppSettings(_In_ String sXMLFile, _In_ bool bWriteFlush = false, _In_ bool bPrettyPrint = false) noexcept : m_sXMLFile(std::move(sXMLFile)),
		m_bDirty(false),
		m_bWriteFlush(bWriteFlush),
		m_bPrettyPrint(bPrettyPrint)
	{
	}

	CXMLAppSettings(const CXMLAppSettings&) = delete;
	CXMLAppSettings(CXMLAppSettings&&) = delete;

	~CXMLAppSettings() noexcept //NOLINT(modernize-use-override)
	{
		//Note we avoid throwing exceptions from the destructor
		try
		{
#pragma warning(suppress: 26447)
			Flush();
		}
		catch (CAppSettingsException& /*e*/)
		{
		}
	}

	CXMLAppSettings& operator=(const CXMLAppSettings&) = delete;
	CXMLAppSettings& operator=(CXMLAppSettings&&) = delete;

	//Accessors / Mutators
	void SetXMLFile(_In_ const String& sXMLFile)
	{
		//Flush the document to ensure that we do not have remnants of the old document when we start with a new filename
		Flush();
		m_XMLDOM.Release();

		m_sXMLFile = sXMLFile;
	}

	[[nodiscard]] String GetXMLFile() const
	{
		return m_sXMLFile;
	}

	void SetWriteFlush(_In_ bool bWriteFlush) noexcept
	{
		m_bWriteFlush = bWriteFlush;
	}

	[[nodiscard]] bool GetWriteFlush() const noexcept
	{
		return m_bWriteFlush;
	}

	//IAppSettings
	int GetInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		String sValue{ GetString(lpszSection, lpszEntry) };
		return _ttoi(sValue.c_str());
	}

	String GetString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Get the entry node
		ATL::CComPtr<IXMLDOMNode> entryNode{ GetEntryNode(lpszSection, lpszEntry, true) };

		//Pull out the text of the node
		ATL::CComBSTR bstrText;
		const HRESULT hr{ entryNode->get_text(&bstrText) };
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

#ifdef _UNICODE
		return { bstrText.operator LPWSTR() };
#else
		return { ATL::CW2A(bstrText).operator LPSTR() };
#endif //#ifdef _UNICODE
	}

	std::vector<BYTE> GetBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		String sBinary{ GetString(lpszSection, lpszEntry) };
		const auto nLen{ sBinary.length() };
		if (nLen == 0)
			return std::vector<BYTE>{};
		if (nLen % 2)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);
		std::vector<BYTE> data{ nLen / 2, std::allocator<BYTE>{} };
		for (size_t i = 0; i < nLen; i += 2)
		{
#pragma warning(suppress: 26446 26472)
			data[i / 2] = static_cast<BYTE>(((sBinary[i + 1] - 'A') << 4) + (sBinary[i] - 'A'));
		}
		return data;
	}

	std::vector<String> GetStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Try to get the binary data first
		std::vector<BYTE> data{ GetBinary(lpszSection, lpszEntry) };
		if (data.size() == 0)
			return std::vector<String>{};

		std::vector<String> arr;
#pragma warning(suppress: 26490)
		auto lpszStrings{ reinterpret_cast<LPTSTR>(data.data()) };
		if (lpszStrings != nullptr)
		{
#pragma warning(suppress: 26481 26489)
			while (lpszStrings[0] != _T('\0'))
			{
#pragma warning(suppress: 26486)
				arr.emplace_back(lpszStrings);
#pragma warning(suppress: 26481 26486)
				lpszStrings += (_tcslen(lpszStrings) + 1);
			}
		}
		return arr;
	}

	std::vector<String> GetSections() override
	{
		//What will be the return value from this method
		std::vector<String> sections;

		//Get the document node
		ATL::CComPtr<IXMLDOMNode> documentNode{ GetDocumentNode(true) };

		//Get all the child nodes of the document node
		ATL::CComPtr<IXMLDOMNodeList> childNodes;
		HRESULT hr = documentNode->get_childNodes(&childNodes);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Now get the name and value of each of the child nodes
		long lLength{ 0 };
		hr = childNodes->get_length(&lLength);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		for (long i = 0; i < lLength; i++)
		{
			ATL::CComPtr<IXMLDOMNode> childNode;
			hr = childNodes->get_item(i, &childNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Get the name of the node
			ATL::CComBSTR bstrValueName;
			hr = childNode->get_nodeName(&bstrValueName);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

#ifdef _UNICODE
#pragma warning(suppress: 26489)
			String sValueName{ bstrValueName };
#else
#pragma warning(suppress: 26489)
			String sValueName{ ATL::CW2A(bstrValueName).operator LPSTR() };
#endif //#ifdef _UNICODE
			sections.push_back(sValueName);
		}

		return sections;
	}

	std::vector<String> GetSection(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bWithValues) override
	{
		//What will be the return value from this method
		std::vector<String> sectionEntries;

		//get the section node
		ATL::CComPtr<IXMLDOMNode> sectionNode{ GetSectionNode(lpszSection, true) };

		//Get all the child nodes of the section node
		ATL::CComPtr<IXMLDOMNodeList> childNodes;
		HRESULT hr{ sectionNode->get_childNodes(&childNodes) };
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Now get the name and value of each of the child nodes
		long lLength{ 0 };
		hr = childNodes->get_length(&lLength);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		for (long i = 0; i < lLength; i++)
		{
			ATL::CComPtr<IXMLDOMNode> childNode;
			hr = childNodes->get_item(i, &childNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Get the name of the node
			ATL::CComBSTR bstrValueName;
			hr = childNode->get_nodeName(&bstrValueName);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);
#ifdef _UNICODE
#pragma warning(suppress: 26489)
			String sValueName{ bstrValueName };
#else
#pragma warning(suppress: 26489)
			String sValueName{ ATL::CW2A(bstrValueName).operator LPSTR() };
#endif //#ifdef _UNICODE

			//Add the appropriate value to the array
#pragma warning(suppress: 26489)
			String sEntry;
			if (bWithValues)
			{
				ATL::CAtlString sTemp;
				sTemp.Format(_T("%s=%s"), sValueName.c_str(), GetString(lpszSection, sValueName.c_str()).c_str());
				sEntry = sTemp;
			}
			else
				sEntry = sValueName;

			sectionEntries.push_back(sEntry);
		}

		return sectionEntries;
	}

	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteInt(lpszSection, lpszEntry, nValue, m_bWriteFlush);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteString(lpszSection, lpszEntry, lpszValue, m_bWriteFlush);
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteBinary(lpszSection, lpszEntry, pData, dwBytes, m_bWriteFlush);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteStringArray(lpszSection, lpszEntry, arr, m_bWriteFlush);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteSection(lpszSection, sectionEntries, m_bWriteFlush);
	}

	//Versions of the Write* methods which allow you to specify the flush setting as a parameter
	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue, _In_ bool bWriteFlush)
	{
		//Simply convert to a string and delegate to WriteString
		ATL::CAtlString sValue;
		sValue.Format(_T("%d"), nValue);
		WriteString(lpszSection, lpszEntry, sValue, bWriteFlush);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue, _In_ bool bWriteFlush)
	{
		if (lpszEntry == nullptr) //delete the section node
		{
			//Get the document node
			ATL::CComPtr<IXMLDOMNode> documentNode{ GetDocumentNode(true) };

			//Also get the section node
			ATL::CComPtr<IXMLDOMNode> sectionNode{ GetSectionNode(lpszSection, true) };

			//now try to delete the node
			const HRESULT hr{ documentNode->removeChild(sectionNode, nullptr) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true; //Set the dirty flag
		}
		else if (lpszValue == nullptr) //Delete the entry node
		{
			//Get the section node
			ATL::CComPtr<IXMLDOMNode> sectionNode{ GetSectionNode(lpszSection, true) };

			//Also get the entry node
			ATL::CComPtr<IXMLDOMNode> entryNode{ GetEntryNode(lpszSection, lpszEntry, true) };

			//now try to delete the node
			const HRESULT hr{ sectionNode->removeChild(entryNode, nullptr) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true; //Set the dirty flag
		}
		else
		{
			//Get the entry node
			ATL::CComPtr<IXMLDOMNode> entryNode{ GetEntryNode(lpszSection, lpszEntry, false) };

			//update the text of the entry node
			const HRESULT hr{ entryNode->put_text(ATL::CComBSTR(lpszValue)) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true; //Set the dirty flag
		}

		//Now save the settings
		if (bWriteFlush)
			Flush();
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes, _In_ bool bWriteFlush)
	{
		//Allocate some heap memory for the data we will be writing out
#pragma warning(suppress: 26472)
		std::vector<TCHAR> dataBuffer{ (static_cast<size_t>(dwBytes) * 2) + 1, std::allocator<TCHAR>{} };

		//convert the data to write out to string format
		for (size_t i = 0; i < dwBytes; i++)
		{
#pragma warning(suppress: 26477)
			ATLASSUME(pData != nullptr);

#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[i * 2] = static_cast<TCHAR>((pData[i] & 0x0F) + 'A'); //low nibble
#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[(i * 2) + 1] = static_cast<TCHAR>(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
		}
#pragma warning(suppress: 26446 26472)
		dataBuffer[static_cast<size_t>(dwBytes) * 2] = _T('\0');

		//Call the WriteString method to write out the data for us
		WriteString(lpszSection, lpszEntry, dataBuffer.data(), bWriteFlush);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr, _In_ bool bWriteFlush)
	{
		//Work out the size of the buffer we will need
		size_t nSize{ 0 };
		for (const auto& sText : arr)
			nSize += (sText.length() + 1); //1 extra for each null terminator

		//Need one second null for the double null at the end
		nSize++;

		//Allocate the memory we want
		std::vector<TCHAR> dataBuffer{ nSize, std::allocator<TCHAR>{} };

		//Now copy the strings into the buffer
		size_t nCurOffset{ 0 };
#pragma warning(suppress: 26429)
		LPTSTR lpszString{ dataBuffer.data() };
		for (const auto& sText : arr)
		{
			const auto nCurrentStringLength{ sText.length() };
#pragma warning(suppress: 26481)
			_tcscpy_s(&lpszString[nCurOffset], nCurrentStringLength + 1, sText.c_str());
			nCurOffset += nCurrentStringLength;
			nCurOffset++;
		}
		//Don't forgot to doubly null terminate
#pragma warning(suppress: 26481)
		lpszString[nCurOffset] = _T('\0');

		//Call the WriteBinary method to write out the data for us
#pragma warning(suppress: 26472 26490)
		WriteBinary(lpszSection, lpszEntry, reinterpret_cast<const BYTE*>(dataBuffer.data()), static_cast<DWORD>(nSize * sizeof(TCHAR)), bWriteFlush);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries, _In_ bool bWriteFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//First nuke the registry key entirely (using the WriteString delete section functionality)
		WriteString(lpszSection, nullptr, nullptr, false);

		//now write out all the new entries
		for (const auto& sEntry : sectionEntries)
		{
			String sName;
#pragma warning(suppress: 26489)
			String sValue;
#pragma warning(suppress: 26489)
			const auto nSeparator{ sEntry.find(_T('=')) };
			if (nSeparator != String::npos)
			{
#pragma warning(suppress: 26489)
				sName = sEntry.substr(0, nSeparator);
#pragma warning(suppress: 26489)
				sValue = sEntry.substr(nSeparator + 1, sEntry.length() - 1 - nSeparator);
			}
			else
#pragma warning(suppress: 26486 26489)
				sName = sEntry;

			WriteString(lpszSection, sName.c_str(), sValue.c_str(), false);
		}

		//Now save the settings
		if (bWriteFlush)
			Flush();
	}

	void Flush()
	{
		//Save to disk if we are dirty
		if (m_bDirty && (m_XMLDOM != nullptr))
		{
			//Pretty print the DOM if necessary
			if (m_bPrettyPrint)
				PrettyPrint();

			const HRESULT hr{ m_XMLDOM->save(ATL::CComVariant{m_sXMLFile.c_str()}) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = false; //Reset the dirty flag
		}
	}

protected:
	//Helper functions
	ATL::CComPtr<IXMLDOMNode> GetDocumentNode(_In_ bool bReadOnly)
	{
		//Create and load the DOM
		CreateDOMIfNecessary(bReadOnly);

		//get the root XML node
		ATL::CComPtr<IXMLDOMElement> documentElement;
		HRESULT hr{ m_XMLDOM->get_documentElement(&documentElement) };
		if (bReadOnly && FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		else if (bReadOnly && (documentElement == nullptr))
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);

		if (FAILED(hr) || (documentElement == nullptr))
		{
			//Create the new section node
			ATL::CComPtr<IXMLDOMNode> rootNode;
			hr = m_XMLDOM->createNode(ATL::CComVariant{ static_cast<long>(NODE_ELEMENT), VT_I4 }, ATL::CComBSTR{ L"xml" }, ATL::CComBSTR{ L"" }, &rootNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Append the root node to the DOM
			ATL::CComPtr<IXMLDOMNode> newRootNode;
			hr = m_XMLDOM->appendChild(rootNode, &newRootNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true; //set the dirty flag now that we have updated the DOM

			return newRootNode;
		}
		else
		{
			//Convert the IXMLDOMElement interface to a IXMLDOMNode interface
			ATL::CComPtr<IXMLDOMNode> documentElementNode{ documentElement };
			return documentElementNode;
		}
	}

	ATL::CComPtr<IXMLDOMNode> GetSectionNode(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bReadOnly)
	{
		//For compatibility reasons, we allow a lpszSection of an empty string. Normally
		//this would not be allowed in XML.
		String sSection;
		if (lpszSection != nullptr)
			sSection = lpszSection;
		if (sSection.length() == 0)
			sSection = _T("IAPPSettings_Empty");

		//Get the document node
		ATL::CComPtr<IXMLDOMNode> documentNode{ GetDocumentNode(bReadOnly) };

		//First try to use the existing node
		ATL::CComPtr<IXMLDOMNode> node;
		HRESULT hr{ documentNode->selectSingleNode(ATL::CComBSTR{sSection.c_str()}, &node) };
		if (bReadOnly && FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		else if (bReadOnly && (node == nullptr))
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);

		if (FAILED(hr) || (node == nullptr))
		{
			//Ok, we couldn't get the existing node, so create a new one from scratch
			ATL::CComPtr<IXMLDOMNode> sectionNode;
			hr = m_XMLDOM->createNode(ATL::CComVariant{ static_cast<long>(NODE_ELEMENT), VT_I4 }, ATL::CComBSTR{ sSection.c_str() }, ATL::CComBSTR{ L"" }, &sectionNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Append the section node to the DOM
			ATL::CComPtr<IXMLDOMNode> newSectionNode;
			hr = documentNode->appendChild(sectionNode, &newSectionNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true; //set the dirty flag now that we have updated the DOM

			return newSectionNode;
		}
		else
			return node;
	}

	ATL::CComPtr<IXMLDOMNode> GetEntryNode(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ bool bReadOnly)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Get the section node
		ATL::CComPtr<IXMLDOMNode> sectionNode{ GetSectionNode(lpszSection, bReadOnly) };

		//First try to use the existing node
		ATL::CComPtr<IXMLDOMNode> node;
		HRESULT hr{ sectionNode->selectSingleNode(ATL::CComBSTR{lpszEntry}, &node) };
		if (bReadOnly && FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		else if (bReadOnly && (node == nullptr))
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);

		if (FAILED(hr) || (node == nullptr))
		{
			//Ok, we couldn't get the existing node, so create a new one from scratch
			hr = m_XMLDOM->createNode(ATL::CComVariant{ static_cast<long>(NODE_ELEMENT), VT_I4 }, ATL::CComBSTR{ lpszEntry }, ATL::CComBSTR{ L"" }, &node);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Finally append the new node to the DOM
			ATL::CComPtr<IXMLDOMNode> newNode;
			hr = sectionNode->appendChild(node, &newNode);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			m_bDirty = true;

			return newNode;
		}
		else
			return node;
	}

	void CreateDOMIfNecessary(_In_ bool bFailIfNotPresent)
	{
		//If the DOM document does not exist, then create it
		if (m_XMLDOM == nullptr)
		{
			HRESULT hr{ m_XMLDOM.CoCreateInstance(__uuidof(DOMDocument), nullptr, CLSCTX_INPROC_SERVER) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);
			hr = m_XMLDOM->put_async(VARIANT_FALSE);
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);

			//Validate our parameters
#pragma warning(suppress: 26477)
			ATLASSERT(m_sXMLFile.length());

			ATL::CComVariant varXMLFile{ m_sXMLFile.c_str() };
			VARIANT_BOOL bSuccess{ VARIANT_FALSE };
			hr = m_XMLDOM->load(varXMLFile, &bSuccess);
			if (bFailIfNotPresent)
			{
				if (FAILED(hr))
					ThrowCOMAppSettingsException(hr);
				if (bSuccess != VARIANT_TRUE)
					ThrowCOMAppSettingsException(E_FAIL);
			}

			m_bDirty = false; //Reset the dirty flag
		}
	}

	virtual void PrettyPrint()
	{
		//Create the MXWriter
		ATL::CComPtr<IMXWriter> pMXWriter;
		HRESULT hr{ pMXWriter.CoCreateInstance(__uuidof(MXXMLWriter), nullptr, CLSCTX_INPROC_SERVER) };
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		ATL::CComPtr<ISAXContentHandler> pISAXContentHandler;
		hr = pMXWriter.QueryInterface(&pISAXContentHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		ATL::CComPtr<ISAXErrorHandler> pISAXErrorHandler;
		hr = pMXWriter.QueryInterface(&pISAXErrorHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		ATL::CComPtr<ISAXDTDHandler> pISAXDTDHandler;
		hr = pMXWriter.QueryInterface(&pISAXDTDHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pMXWriter->put_indent(VARIANT_TRUE);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Create the SAX reader
		ATL::CComPtr<ISAXXMLReader> pSAXReader;
		hr = pSAXReader.CoCreateInstance(__uuidof(SAXXMLReader), nullptr, CLSCTX_INPROC_SERVER);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->putContentHandler(pISAXContentHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->putDTDHandler(pISAXDTDHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->putErrorHandler(pISAXErrorHandler);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->putProperty(L"http://xml.org/sax/properties/lexical-handler", ATL::CComVariant(pMXWriter));
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->putProperty(L"http://xml.org/sax/properties/declaration-handler", ATL::CComVariant(pMXWriter));
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Do the actual writing
		ATL::CComVariant varXML;
		varXML.vt = VT_BSTR;
		hr = m_XMLDOM->get_xml(&varXML.bstrVal);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pMXWriter->put_output(ATL::CComVariant{ m_XMLDOM });
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
		hr = pSAXReader->parse(varXML);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
	}

	//Member variables
	String m_sXMLFile; //The filename of the XML file to use
	ATL::CComPtr<IXMLDOMDocument> m_XMLDOM; //the XML DOM for the file
	bool m_bDirty; //Is a DOM save pending
	bool m_bWriteFlush; //Should an immediate save be done any time a modification is made to the DOM
	bool m_bPrettyPrint; //Should the resultant XML file be "pretty printed" when saved
};


//The App settings class which reads / writes application settings to a JSON file
#ifdef CAPPSETTINGS_JSON_SUPPORT
class CJSONAppSettings : public IAppSettings
{
public:
	//Constructors / Destructors
	CJSONAppSettings(_In_ String sJSONFile, _In_ bool bWriteFlush = false) noexcept : m_sJSONFile(std::move(sJSONFile)),
		m_bDirty(false),
		m_bWriteFlush(bWriteFlush),
		m_nEncodeFlags(0)
	{
	}

	~CJSONAppSettings() noexcept //NOLINT(modernize-use-override)
	{
		//Note we avoid throwing exceptions from the destructor
		try
		{
#pragma warning(suppress: 26447)
			Flush();
		}
		catch (CAppSettingsException& /*e*/)
		{
		}
	}

	CJSONAppSettings(const CJSONAppSettings&) = delete;
	CJSONAppSettings(CJSONAppSettings&&) = delete;
	CJSONAppSettings& operator=(const CJSONAppSettings&) = delete;
	CJSONAppSettings& operator=(CJSONAppSettings&&) = delete;

	//Accessors / Mutators
	void SetJSONFile(_In_ const String& sJSONFile)
	{
		//Flush the document to ensure that we do not have remnants of the old document when we start with a new filename
		Flush();
		m_JSON.SetNull();

		m_sJSONFile = sJSONFile;
	}

	[[nodiscard]] String GetJSONFile() const
	{
		return m_sJSONFile;
	}

	void SetWriteFlush(_In_ bool bWriteFlush) noexcept
	{
		m_bWriteFlush = bWriteFlush;
	}

	[[nodiscard]] bool GetWriteFlush() const noexcept
	{
		return m_bWriteFlush;
	}

	void SetEncodeFlags(_In_ unsigned long nEncodeFlags) noexcept
	{
		m_nEncodeFlags = nEncodeFlags;
	}

	[[nodiscard]] unsigned long GetEncodeFlags() const noexcept
	{
		return m_nEncodeFlags;
	}

	//IAppSettings
	int GetInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Get the entry node
		JSONPP::CValue& entryNode(GetEntryNode(lpszSection, lpszEntry, true));

		int nValue = 0;
		if (entryNode.IsString())
			nValue = _wtoi(entryNode.AsString().c_str());
		else if (entryNode.IsNumber())
			nValue = static_cast<int>(entryNode.AsNumber());
		else
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);

		return nValue;
	}

	String GetString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Get the entry node
		JSONPP::CValue& entryNode{ GetEntryNode(lpszSection, lpszEntry, true) };

		if (!entryNode.IsString())
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);

		//Pull out the text of the node
		std::wstring sText{ entryNode.AsString() };

#ifdef _UNICODE
		return sText;
#else
		return { ATL::CW2A(sText.c_str()).operator LPSTR() };
#endif //#ifdef _UNICODE
	}

	std::vector<BYTE> GetBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		String sBinary{ GetString(lpszSection, lpszEntry) };
		const auto nLen{ sBinary.length() };
		if (nLen == 0)
			return std::vector<BYTE>{};
		if (nLen % 2)
			ThrowWin32AppSettingsException(ERROR_INVALID_DATA);
		std::vector<BYTE> data{ nLen / 2, std::allocator<BYTE>{} };
		for (size_t i = 0; i < nLen; i += 2)
#pragma warning(suppress: 26446 26472)
			data[i / 2] = static_cast<BYTE>(((sBinary[i + 1] - 'A') << 4) + (sBinary[i] - 'A'));
		return data;
	}

	std::vector<String> GetStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry) override
	{
		//Try to get the binary data first
		std::vector<BYTE> data{ GetBinary(lpszSection, lpszEntry) };
		if (data.size() == 0)
			return std::vector<String>{};
#pragma warning(suppress: 26490)
		auto lpszStrings{ reinterpret_cast<LPTSTR>(data.data()) };
		std::vector<String> arr;
		if (lpszStrings != nullptr)
		{
#pragma warning(suppress: 26481 26489)
			while (lpszStrings[0] != _T('\0'))
			{
#pragma warning(suppress: 26486)
				arr.emplace_back(lpszStrings);
#pragma warning(suppress: 26481 26486)
				lpszStrings += (_tcslen(lpszStrings) + 1);
			}
		}
		return arr;
	}

	std::vector<String> GetSections() override
	{
		//What will be the return value from this method
		std::vector<String> sections;

		//Get the document node
		JSONPP::Object& documentNode{ GetDocumentNode(true) };

		//Now get the name and value of each of the child nodes
		for (const auto& section : documentNode)
		{
#ifdef _UNICODE
#pragma warning(suppress: 26489)
			String sValueName{ section.first };
#else
#pragma warning(suppress: 26489 26486)
			String sValueName{ ATL::CW2A{section.first.c_str()}.operator LPSTR() };
#endif //#ifdef _UNICODE
			sections.push_back(sValueName);
		}

		return sections;
	}

	std::vector<String> GetSection(_In_z_ LPCTSTR lpszSection, _In_ bool bWithValues) override
	{
		//What will be the return value from this method
		std::vector<String> sectionEntries;

		//get the section node
		JSONPP::Object& sectionNode{ GetSectionNode(lpszSection, true) };

		for (const auto& entry : sectionNode)
		{
			//Get the name of the node
#ifdef _UNICODE
#pragma warning(suppress: 26489)
			String sValueName{ entry.first };
#else
#pragma warning(suppress: 26486 26489)
			String sValueName{ ATL::CW2A{entry.first.c_str()}.operator LPSTR() };
#endif //#ifdef _UNICODE

			//Add the appropriate value to the array
#pragma warning(suppress: 26489)
			String sEntry;
			if (bWithValues)
			{
				ATL::CAtlString sTemp;
				if (entry.second.IsNumber())
					sTemp.Format(_T("%s=%d"), sValueName.c_str(), GetInt(lpszSection, sValueName.c_str()));
				else
					sTemp.Format(_T("%s=%s"), sValueName.c_str(), GetString(lpszSection, sValueName.c_str()).c_str());
				sEntry = sTemp;
			}
			else
				sEntry = sValueName;

			sectionEntries.push_back(sEntry);
		}

		return sectionEntries;
	}

	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteInt(lpszSection, lpszEntry, nValue, m_bWriteFlush);
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteString(lpszSection, lpszEntry, lpszValue, m_bWriteFlush);
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteBinary(lpszSection, lpszEntry, pData, dwBytes, m_bWriteFlush);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteStringArray(lpszSection, lpszEntry, arr, m_bWriteFlush);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries) override
	{
		//Just delegate to the version which specifies the flush setting as a parameter
		WriteSection(lpszSection, sectionEntries, m_bWriteFlush);
	}

	//Versions of the Write* methods which allow you to specify the flush setting as a parameter
	void WriteInt(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ int nValue, _In_ bool bWriteFlush)
	{
		if (lpszEntry == nullptr)
		{
			ATL::CAtlString sValue;
			sValue.Format(_T("%d"), nValue);
			WriteString(lpszSection, lpszEntry, sValue, bWriteFlush);
		}
		else
		{
			//Get the entry node
			JSONPP::CValue& entryNode{ GetEntryNode(lpszSection, lpszEntry, false) };

			//update the value of the entry node
			entryNode = static_cast<double>(nValue);
			m_bDirty = true; //Set the dirty flag

			//Now save the settings
			if (bWriteFlush)
				Flush();
		}
	}

	void WriteString(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_z_ LPCTSTR lpszValue, _In_ bool bWriteFlush)
	{
		if (lpszEntry == nullptr) //delete the section node
		{
			//Get the document node
			JSONPP::Object& documentNode{ GetDocumentNode(true) };

			//now try to delete the node
#pragma warning(suppress: 26477)
			ATLASSUME(lpszSection != nullptr);
#ifdef _UNICODE
			std::wstring sSection{ lpszSection };
#else
#pragma warning(suppress: 26486)
			std::wstring sSection{ ATL::CT2W{lpszSection}.operator LPWSTR() };
#endif //#ifdef _UNICODE
			const auto iter{ documentNode.find(sSection) };
			if (iter == documentNode.end())
				ThrowWin32AppSettingsException(ERROR_NOT_FOUND);
#pragma warning(suppress: 26444)
			documentNode.erase(iter);
			m_bDirty = true; //Set the dirty flag
		}
		else if (lpszValue == nullptr) //Delete the entry node
		{
			//Get the section node
			JSONPP::Object& sectionNode{ GetSectionNode(lpszSection, true) };

			//now try to delete the node
#pragma warning(suppress: 26477)
			ATLASSUME(lpszEntry != nullptr);
#ifdef _UNICODE
			std::wstring sEntry{ lpszEntry };
#else
#pragma warning(suppress: 26486)
			std::wstring sEntry{ ATL::CT2W{lpszEntry}.operator LPWSTR() };
#endif //#ifdef _UNICODE
			const auto iter{ sectionNode.find(sEntry) };
			if (iter == sectionNode.end())
				ThrowWin32AppSettingsException(ERROR_NOT_FOUND);
#pragma warning(suppress: 26444)
			sectionNode.erase(iter);
			m_bDirty = true; //Set the dirty flag
		}
		else
		{
			//Get the entry node
			JSONPP::CValue& entryNode{ GetEntryNode(lpszSection, lpszEntry, false) };

			//update the text of the entry node
#ifdef _UNICODE
			entryNode = std::wstring{ lpszValue };
#else
			entryNode = std::wstring{ ATL::CT2W(lpszValue).operator LPWSTR() };
#endif //#ifdef _UNICODE
			m_bDirty = true; //Set the dirty flag
		}

		//Now save the settings
		if (bWriteFlush)
			Flush();
	}

	void WriteBinary(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_opt_ const BYTE* pData, _In_ DWORD dwBytes, _In_ bool bWriteFlush)
	{
		//Allocate some temp memory for the data we will be writing out
#pragma warning(suppress: 26472)
		std::vector<TCHAR> dataBuffer{ (static_cast<size_t>(dwBytes) * 2) + 1, std::allocator<TCHAR>{} };

		//convert the data to write out to string format
		for (size_t i = 0; i < dwBytes; i++)
		{
#pragma warning(suppress: 26477)
			ATLASSUME(pData != nullptr);

#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[i * 2] = static_cast<TCHAR>((pData[i] & 0x0F) + 'A'); //low nibble
#pragma warning(suppress: 26446 26472 26481)
			dataBuffer[(i * 2) + 1] = static_cast<TCHAR>(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
		}
#pragma warning(suppress: 26446 26472)
		dataBuffer[static_cast<size_t>(dwBytes) * 2] = _T('\0');

		//Call the WriteString method to write out the data for us
		WriteString(lpszSection, lpszEntry, dataBuffer.data(), bWriteFlush);
	}

	void WriteStringArray(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ const std::vector<String>& arr, _In_ bool bWriteFlush)
	{
		//Work out the size of the buffer we will need
		size_t nSize{ 0 };
		for (const auto& sText : arr)
			nSize += (sText.length() + 1); //1 extra for each null terminator

		//Need one second null for the double null at the end
		nSize++;

		//Allocate the memory we want
		std::vector<TCHAR> dataBuffer{ nSize, std::allocator<TCHAR>{} };

		//Now copy the strings into the buffer
		size_t nCurOffset{ 0 };
#pragma warning(suppress: 26429)
		LPTSTR lpszString{ dataBuffer.data() };
		for (const auto& sText : arr)
		{
			const auto nCurrentStringLength{ sText.length() };
#pragma warning(suppress: 26481)
			_tcscpy_s(&lpszString[nCurOffset], nCurrentStringLength + 1, sText.c_str());
			nCurOffset += nCurrentStringLength;
			nCurOffset++;
		}
		//Don't forgot to doubly null terminate
#pragma warning(suppress: 26481)
		lpszString[nCurOffset] = _T('\0');

		//Call the WriteBinary method to write out the data for us
#pragma warning(suppress: 26472 26490)
		WriteBinary(lpszSection, lpszEntry, reinterpret_cast<const BYTE*>(dataBuffer.data()), static_cast<DWORD>(nSize * sizeof(TCHAR)), bWriteFlush);
	}

	void WriteSection(_In_opt_z_ LPCTSTR lpszSection, _In_ const std::vector<String>& sectionEntries, _In_ bool bWriteFlush)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszSection != nullptr);

		//First nuke the registry key entirely (using the WriteString delete section functionality)
		WriteString(lpszSection, nullptr, nullptr, false);

		//now write out all the new entries
		for (const auto& sEntry : sectionEntries)
		{
			String sName;
#pragma warning(suppress: 26489)
			String sValue;
#pragma warning(suppress: 26489)
			const auto nSeparator{ sEntry.find(_T('=')) };
			if (nSeparator != String::npos)
			{
#pragma warning(suppress: 26489)
				sName = sEntry.substr(0, nSeparator);
#pragma warning(suppress: 26489)
				sValue = sEntry.substr(nSeparator + 1, sEntry.length() - 1 - nSeparator);
			}
			else
#pragma warning(suppress: 26486 26489)
				sName = sEntry;

			WriteString(lpszSection, sName.c_str(), sValue.c_str(), false);
		}

		//Now save the settings
		if (bWriteFlush)
			Flush();
	}

	void Flush()
	{
		//Save to disk if we are dirty
		if (m_bDirty)
		{
			Save();
			m_bDirty = false; //Reset the dirty flag
		}
	}

protected:
	//Helper methods
	void Save()
	{
		//Save to UTF-16
		std::wstring sJSON{ m_JSON.Encode(m_nEncodeFlags) };

		//Convert to UTF-8
		int nUTF8Length{ WideCharToMultiByte(CP_UTF8, 0, sJSON.c_str(), -1, nullptr, 0, nullptr, nullptr) };

		//Now recall with the buffer to get the converted text
#pragma warning(suppress: 26472)
		std::string sUTF8String{ static_cast<size_t>(nUTF8Length), _T('\0'), std::allocator<TCHAR>{} };
		nUTF8Length = WideCharToMultiByte(CP_UTF8, 0, sJSON.c_str(), -1, sUTF8String.data(), nUTF8Length, nullptr, nullptr);
		sUTF8String.resize(nUTF8Length);

		//Save the UTF-8 to disk
		ATL::CAtlFile file;
		HRESULT hr{ file.Create(m_sJSONFile.c_str(), GENERIC_WRITE, 0, OPEN_ALWAYS) };
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Set the file back to 0 in size
		hr = file.SetSize(0);
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);

		//Write out the JSON
#pragma warning(suppress: 26472)
		hr = file.Write(sUTF8String.c_str(), static_cast<DWORD>(sUTF8String.size()));
		if (FAILED(hr))
			ThrowCOMAppSettingsException(hr);
	}

	HRESULT Load(bool bFailIfNotPresent)
	{
		ATL::CAtlFile file;
		HRESULT hr{ file.Create(m_sJSONFile.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN) };
		if (FAILED(hr))
		{
			if (bFailIfNotPresent)
				return hr;
			else
				return S_OK;
		}

		//Get the length of the file (we only support sending JSON files less than 2GB!)
		ULONGLONG nFileSize{ 0 };
		hr = file.GetSize(nFileSize);
		if (FAILED(hr))
			return hr;
		if (nFileSize >= INT_MAX)
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_FILE_TOO_LARGE);

		//Allocate some memory for the contents of the file
#pragma warning(suppress: 26472)
		std::vector<char> json{ static_cast<size_t>(nFileSize + 1) , std::allocator<char>{} };

		//Read in the contents of the file
		DWORD dwBytesWritten{ 0 };
#pragma warning(suppress: 26472)
		hr = file.Read(json.data(), static_cast<DWORD>(nFileSize), dwBytesWritten);
		if (FAILED(hr))
			return hr;
#pragma warning(suppress: 26446 26472)
		json[static_cast<size_t>(nFileSize)] = '\0';

		//Parse the JSON. Note that this can throw JSONPP::CParseException exceptions which client code is expected to handle
		m_JSON.Parse(json.data());

		return S_OK;
	}

	JSONPP::Object& GetDocumentNode(_In_ bool bReadOnly)
	{
		//Create and load the JSON
		CreateDOMIfNecessary(bReadOnly);

		if (m_JSON.IsNull())
		{
			m_JSON = JSONPP::Object();
			m_bDirty = true; //set the dirty flag now that we have updated the DOM
			return m_JSON.AsObject();
		}
		else
		{
			if (!m_JSON.IsObject())
				ThrowWin32AppSettingsException(ERROR_INVALID_DATA);
			return m_JSON.AsObject();
		}
	}

	JSONPP::Object& GetSectionNode(_In_opt_z_ LPCTSTR lpszSection, _In_ bool bReadOnly)
	{
		std::wstring sWideSection;
#ifdef _UNICODE
		if (lpszSection != nullptr)
			sWideSection = lpszSection;
#else
		if (lpszSection != nullptr)
			sWideSection = ATL::CT2W(lpszSection);
#endif //#ifdef _UNICODE

		//Get the document node
		JSONPP::Object& documentNode{ GetDocumentNode(bReadOnly) };

		//First try to use the existing node
		const auto iter{ documentNode.find(sWideSection) };
		if (bReadOnly && (iter == documentNode.end()))
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);

		if (iter == documentNode.end())
		{
			documentNode[sWideSection] = JSONPP::Object();
			m_bDirty = true; //set the dirty flag now that we have updated the DOM
#pragma warning(suppress: 26487 26489)
			return documentNode[sWideSection].AsObject();
		}
		else
		{
			if (!iter->second.IsObject())
				ThrowWin32AppSettingsException(ERROR_INVALID_DATA);
#pragma warning(suppress: 26489)
			return iter->second.AsObject();
		}
	}

	JSONPP::CValue& GetEntryNode(_In_opt_z_ LPCTSTR lpszSection, _In_opt_z_ LPCTSTR lpszEntry, _In_ bool bReadOnly)
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		ATLASSERT(lpszEntry != nullptr);

		//Get the section node
		JSONPP::Object& sectionNode{ GetSectionNode(lpszSection, bReadOnly) };

		//First try to use the existing node
		std::wstring sEntry;
#ifdef _UNICODE
		if (lpszEntry != nullptr)
			sEntry = lpszEntry;
#else
		if (lpszEntry != nullptr)
			sEntry = ATL::CT2W{ lpszEntry }.operator LPWSTR();
#endif //#ifdef _UNICODE
		const auto iter{ sectionNode.find(sEntry) };
		if (bReadOnly && (iter == sectionNode.end()))
			ThrowWin32AppSettingsException(ERROR_NOT_FOUND);
		if (iter == sectionNode.end())
		{
			sectionNode[sEntry] = JSONPP::CValue();
			m_bDirty = true;
#pragma warning(suppress: 26487 26489)
			return sectionNode[sEntry];
		}
		else
#pragma warning(suppress: 26489)
			return iter->second;
	}

	void CreateDOMIfNecessary(_In_ bool bFailIfNotPresent)
	{
		//If the JSON document does not exist, then create it
		if (m_JSON.IsNull())
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			ATLASSERT(m_sJSONFile.length());

			const HRESULT hr{ Load(bFailIfNotPresent) };
			if (FAILED(hr))
				ThrowCOMAppSettingsException(hr);
			m_bDirty = false; //Reset the dirty flag
		}
	}

	//Member variables
	String m_sJSONFile; //The filename of the JSON file to use
	JSONPP::CValue m_JSON; //The JSON for the file
	bool m_bDirty; //Is a JSON save pending
	bool m_bWriteFlush; //Should an immediate save be done any time a modification is made to the JSON
	unsigned long m_nEncodeFlags; //Flags to pass to CValue::Encode
};
#endif //#ifdef CAPPSETTINGS_JSON_SUPPORT

#endif //#ifndef __APPSETTINGS_H__
