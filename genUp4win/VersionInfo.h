/*
Module : VersionInfo.h
Purpose: Interface for an C++ class encapsulation of Window's "Version Infos"

Copyright (c) 2000 - 2022 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////// Macros / Defines //////////////////////////////

#pragma once

#ifndef __VERSIONINFO_H__
#define __VERSIONINFO_H__
 
#ifndef CVERSIONINFO_EXT_CLASS
#define CVERSIONINFO_EXT_CLASS
#endif //#ifndef CVERSIONINFO_EXT_CLASS

#ifndef CVERSIONINFO_EXT_API
#define CVERSIONINFO_EXT_API
#endif //#ifndef CVERSIONINFO_EXT_API

#ifndef _STRING_
#pragma message("To avoid this message, please put string in your pre compiled header (normally stdafx.h)")
#include <string>
#endif //#ifndef _STRING_

#ifndef _VECTOR_
#pragma message("To avoid this message, please put vector in your pre compiled header (normally stdafx.h)")
#include <vector>
#endif //#ifndef _VECTOR_


/////////////////////////////// Classes ///////////////////////////////////////

class CVERSIONINFO_EXT_CLASS CVersionInfo
{
public:
	//Typedefs
#ifdef _UNICODE
	using String = std::wstring;
#else
	using String = std::string;
#endif //#ifdef _UNICODE

	//Structs
	struct TRANSLATION
	{
		WORD m_wLangID; //e.g. 0x0409 LANG_ENGLISH, SUBLANG_ENGLISH_USA
		WORD m_wCodePage; //e.g. 1252 Codepage for Windows:Multilingual
	};

	//Constructors / Destructors
	CVersionInfo() noexcept;
	CVersionInfo(_In_ const CVersionInfo&) = delete;
	CVersionInfo(_In_ CVersionInfo&&) = delete;
	~CVersionInfo() noexcept;

	//Methods
	CVersionInfo& operator=(_In_ const CVersionInfo&) = delete;
	CVersionInfo& operator=(_In_ CVersionInfo&&) = delete;
	BOOL Load(_In_z_ LPCTSTR szFileName);
	_NODISCARD VS_FIXEDFILEINFO* GetFixedFileInfo() const noexcept;
	_NODISCARD DWORD GetFileFlagsMask() const noexcept;
	_NODISCARD DWORD GetFileFlags() const noexcept;
	_NODISCARD DWORD GetOS() const noexcept;
	_NODISCARD DWORD GetFileType() const noexcept;
	_NODISCARD DWORD GetFileSubType() const noexcept;
	_NODISCARD FILETIME GetCreationTime() const noexcept;
	_NODISCARD unsigned __int64  GetFileVersion() const noexcept;
	_NODISCARD unsigned __int64  GetProductVersion() const noexcept;
	_NODISCARD String GetValue(_In_z_ LPCTSTR pszKeyName) const;
	_NODISCARD String GetComments() const;
	_NODISCARD String GetCompanyName() const;
	_NODISCARD String GetFileDescription() const;
	_NODISCARD String GetFileVersionAsString() const;
	_NODISCARD String GetInternalName() const;
	_NODISCARD String GetLegalCopyright() const;
	_NODISCARD String GetLegalTrademarks() const;
	_NODISCARD String GetOriginalFilename() const;
	_NODISCARD String GetPrivateBuild() const;
	_NODISCARD String GetProductName() const;
	_NODISCARD String GetProductVersionAsString() const;
	_NODISCARD String GetSpecialBuild() const;
	_NODISCARD int GetNumberOfTranslations() const noexcept;
	_NODISCARD TRANSLATION* GetTranslation(_In_ int nIndex) const noexcept;
	void SetTranslation(_In_ int nIndex) noexcept;

protected:
	//Methods
	void Unload() noexcept;

	//Data
	WORD m_wLangID; //The current language ID of the resource
	WORD m_wCharset; //The current Character set ID of the resource
	std::vector<BYTE> m_VerData; //Pointer to the version info blob
	TRANSLATION* m_pTranslations; //Pointer to the "\\VarFileInfo\\Translation" version info
	int m_nTranslations; //The number of translated version infos in the resource
	VS_FIXEDFILEINFO* m_pffi; //Pointer to the fixed size version info data
};

#endif //#ifndef __VERSIONINFO_H__
