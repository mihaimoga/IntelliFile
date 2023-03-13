/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

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

BOOL IsApplication(CString strFilePath);
BOOL IsBinaryFile(CString strFilePath);
BOOL IsTextFile(CString strFilePath);
BOOL IsRichTextFile(CString strFilePath);
BOOL IsCodeFile(CString strFilePath);
BOOL IsDataFile(CString strFilePath);
BOOL IsMetaFile(CString strFilePath);

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
	BOOL IsFolder();

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
	BOOL RemoveAll();
	int GetSize() { return (int)m_arrFiles.GetSize(); }
	CFileData* GetAt(int nIndex) { return m_arrFiles.GetAt(nIndex); }

	int GetSystemType() { return m_nSystemType; }
	void SetSystemType(int nSystemType) { m_nSystemType = nSystemType; }

	CMFCCaptionBar* GetWindow() { return m_wndCaptionBar; }
	void SetWindow(CMFCCaptionBar* wndCaptionBar) { m_wndCaptionBar = wndCaptionBar; }

	HWND GetParent() { return m_hWndParent; }
	void SetParent(HWND hWndParent) { m_hWndParent = hWndParent; }

	CString GetCurrentFolder() { return m_strCurrentFolder; }
	BOOL SetCurrentFolder(CString strFolder);

	BOOL Refresh();
	BOOL ViewFile(CString strFilePath);
	BOOL EditFile(CString strFilePath);
	BOOL CopyFile(CFileSystem* pDestination, CFileList* arrSelection);
	BOOL MoveFile(CFileSystem* pDestination, CFileList* arrSelection);
	BOOL NewFolder(CFileSystem* pDestination, CString strNewFolderName);
	BOOL DeleteFile(CFileSystem* pDestination, CFileList* arrSelection);

protected:
	CMFCCaptionBar* m_wndCaptionBar;
	HWND m_hWndParent;
	int m_nSystemType;
	CString m_strCurrentFolder;
	CFileList m_arrFiles;
};
