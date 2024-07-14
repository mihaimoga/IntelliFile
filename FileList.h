/* Copyright (C) 2022-2024 Stefan-Mihai MOGA
This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once

#define DEFAULT_FOLDER _T("C:\\")

#define FILE_TYPE_FAT 0x0001
#define FILE_TYPE_LAN 0x0002
#define FILE_TYPE_FTP 0x0004
#define FILE_TYPE_ZIP 0x0008

void DisplayErrorBox(CMFCCaptionBar* wndCaptionBar, LPCTSTR lpszFunction, DWORD dwError);
void DisplayErrorBox(CMFCCaptionBar* wndCaptionBar, LPCTSTR lpszFunction, HRESULT hResult);

bool IsApplication(CString strFilePath);
bool IsBinaryFile(CString strFilePath);
bool IsTextFile(CString strFilePath);
bool IsRichTextFile(CString strFilePath);
bool IsCodeFile(CString strFilePath);
bool IsDataFile(CString strFilePath);
bool IsMetaFile(CString strFilePath);

///////////////////////////////////////////////////////////////////////////////
// CFileData command target
///////////////////////////////////////////////////////////////////////////////

class CFileData : public CObject
{
protected:
	DECLARE_DYNAMIC(CFileData)
	
public:
	CFileData();
	CFileData(DWORD dwFileAttributes,
		COleDateTime ftCreationTime,
		COleDateTime ftLastAccessTime,
		COleDateTime ftLastWriteTime,
		ULONGLONG nFileSize,
		CString strFileName,
		CString strAlternateFileName);
	virtual ~CFileData();

public:
	DWORD GetFileAttributes() { return m_dwFileAttributes; }
	void SetFileAttributes(DWORD dwFileAttributes) { m_dwFileAttributes = dwFileAttributes; }
	COleDateTime GetCreationTime() { return m_ftCreationTime; }
	void SetCreationTime(COleDateTime ftCreationTime) { m_ftCreationTime = ftCreationTime; }
	COleDateTime GetLastAccessTime() { return m_ftLastAccessTime; }
	void SetLastAccessTime(COleDateTime ftLastAccessTime) { m_ftLastAccessTime = ftLastAccessTime; }
	COleDateTime GetLastWriteTime() { return m_ftLastWriteTime; }
	void SetLastWriteTime(COleDateTime ftLastWriteTime) { m_ftLastWriteTime = ftLastWriteTime; }
	ULONGLONG GetFileSize() { return m_nFileSize; }
	void SetFileSize(ULONGLONG nFileSize) { m_nFileSize = nFileSize; }
	CString GetFileName() { return m_strFileName; }
	void SetFileName(CString strFileName) { m_strFileName = strFileName; }
	CString GetAlternate() { return m_strAlternateFileName; }
	void SetAlternate(CString strAlternateFileName) { m_strAlternateFileName = strAlternateFileName; }

public:
	CString FormatSize();
	CString FormatDate();
	CString FormatAttr();
	bool IsFolder();

protected:
	DWORD m_dwFileAttributes;
	COleDateTime m_ftCreationTime;
	COleDateTime m_ftLastAccessTime;
	COleDateTime m_ftLastWriteTime;
	ULONGLONG m_nFileSize;
	CString m_strFileName;
	CString m_strAlternateFileName;
};

typedef CArray<CFileData*> CFileList;

///////////////////////////////////////////////////////////////////////////////
// CFileSystem command target
///////////////////////////////////////////////////////////////////////////////

class CFileSystem : public CObject
{
protected:
	DECLARE_DYNAMIC(CFileSystem)
	
public:
	CFileSystem();
	virtual ~CFileSystem();

public:
	bool RemoveAll();
	int GetSize() { return (int)m_arrFiles.GetSize(); }
	CFileData* GetAt(int nIndex) { return m_arrFiles.GetAt(nIndex); }

	int GetSystemType() { return m_nSystemType; }
	void SetSystemType(int nSystemType) { m_nSystemType = nSystemType; }

	CMFCCaptionBar* GetWindow() { return m_wndCaptionBar; }
	void SetWindow(CMFCCaptionBar* wndCaptionBar) { m_wndCaptionBar = wndCaptionBar; }

	HWND GetParent() { return m_hWndParent; }
	void SetParent(HWND hWndParent) { m_hWndParent = hWndParent; }

	CString GetCurrentFolder() { return m_strCurrentFolder; }
	bool SetCurrentFolder(CString strFolder);

	bool Refresh();
	bool ViewFile(CString strFilePath);
	bool EditFile(CString strFilePath);

	bool SelectFile(CStringArray& arrFileList, const CString& strSearchFor,
		const bool& bFileDateCheck, const COleDateTime& ftDateTimeFrom, const COleDateTime& ftDateTimeTo,
		const bool& bFileSizeCheck, const TCHAR& chFileSize, const ULONGLONG& dwFileSize,
		const bool& bFileAttrCheck, const DWORD& dwFileAttrData, const DWORD& dwFileAttrMask);
	bool SearchFile(CStringArray& arrFileList, const CString& strSearchFor);

	bool CopyFile(CFileSystem* pDestination, CFileList* arrSelection);
	bool MoveFile(CFileSystem* pDestination, CFileList* arrSelection);
	bool NewFolder(CFileSystem* pDestination, CString strNewFolderName);
	bool DeleteFile(CFileSystem* pDestination, CFileList* arrSelection);
	bool RenameFile(const CString& strOldFilePath, const CString& strNewFilePath);

	bool CommandPrompt(bool bAdministrator);

protected:
	CMFCCaptionBar* m_wndCaptionBar;
	HWND m_hWndParent;
	int m_nSystemType;
	CString m_strCurrentFolder;
	CFileList m_arrFiles;
};
