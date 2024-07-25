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

// FileList.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "FileList.h"

IMPLEMENT_DYNAMIC(CFileData, CObject)

IMPLEMENT_DYNAMIC(CFileSystem, CObject)

void DisplayErrorBox(CMFCCaptionBar* wndCaptionBar, LPCTSTR lpszFunction, DWORD dwError) 
{ 
	// Retrieve the system error message for the last-error code

	LPVOID lpszMsgBuf = nullptr;
	LPVOID lpszDisplayBuf = nullptr;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpszMsgBuf,
		0, nullptr);

	// Display the error message and clean up

	lpszDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpszMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
	_stprintf_s((LPTSTR)lpszDisplayBuf, 
		LocalSize(lpszDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s\n"), 
		lpszFunction, dwError, (LPCTSTR) lpszMsgBuf);
	OutputDebugString((LPCTSTR) lpszDisplayBuf);
	if (wndCaptionBar != nullptr)
	{
		wndCaptionBar->SetText((LPCTSTR) lpszMsgBuf, CMFCCaptionBar::ALIGN_LEFT);
		wndCaptionBar->ShowWindow(SW_SHOW);
		wndCaptionBar->Invalidate();
		wndCaptionBar->UpdateWindow();
	}

	LocalFree(lpszMsgBuf);
	LocalFree(lpszDisplayBuf);
}

void DisplayErrorBox(CMFCCaptionBar* wndCaptionBar, LPCTSTR lpszFunction, HRESULT hResult)
{
	_com_error pError(hResult);
	LPCTSTR lpszMsgBuf = pError.ErrorMessage();

	CString lpszDisplayBuf;
	lpszDisplayBuf.Format(TEXT("%s failed with error 0x%X: %s\n"), lpszFunction, hResult, lpszMsgBuf);
	OutputDebugString((LPCTSTR) lpszDisplayBuf);
	if (wndCaptionBar != nullptr)
	{
		wndCaptionBar->SetText((LPCTSTR) lpszMsgBuf, CMFCCaptionBar::ALIGN_LEFT);
		wndCaptionBar->ShowWindow(SW_SHOW);
		wndCaptionBar->Invalidate();
		wndCaptionBar->UpdateWindow();
	}
}

bool IsApplication(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if (_tcsicmp(lpszExtension, _T(".exe")) == 0)
		return true;
	return false;
}

bool IsBinaryFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".exe")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".com")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".bin")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".elf")) == 0))
		return true;
	return false;
}

bool IsTextFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".txt")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".log")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".c")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".cpp")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".cxx")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".java")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".js")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".h")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".hpp")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".py")) == 0))
		return true;
	return false;
}

bool IsRichTextFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if (_tcsicmp(lpszExtension, _T(".rtf")) == 0)
		return true;
	return false;
}

bool IsCodeFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".cpp")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".c")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".h")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".hpp")) == 0))
		return true;
	return false;
}

bool IsDataFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if (_tcsicmp(lpszExtension, _T(".csv")) == 0)
		return true;
	return false;
}

bool IsMetaFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".xml")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".htm")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".html")) == 0))
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// CFileList member functions
///////////////////////////////////////////////////////////////////////////////

CFileData::CFileData()
{
	m_dwFileAttributes = 0;
	m_nFileSize = 0;
}

CFileData::CFileData(DWORD dwFileAttributes,
	COleDateTime ftCreationTime,
	COleDateTime ftLastAccessTime,
	COleDateTime ftLastWriteTime,
	ULONGLONG nFileSize,
	CString strFileName,
	CString strAlternateFileName)
{
	m_dwFileAttributes = dwFileAttributes;
	m_ftCreationTime = ftCreationTime;
	m_ftLastAccessTime = ftLastAccessTime;
	m_ftLastWriteTime = ftLastWriteTime;
	m_nFileSize = nFileSize;
	m_strFileName = strFileName;
	m_strAlternateFileName = strAlternateFileName;
}

CFileData::~CFileData()
{
}

CString CFileData::FormatSize()
{
	if (IsFolder())
	{
		return _T("<DIR>");
	}
	else
	{
		CString strFormatSize;
		ULONGLONG nFormatRest = 0;
		ULONGLONG nFormatSize = m_nFileSize;
		if (nFormatSize < 1024)
		{
			strFormatSize.Format(_T("%d"), (int) nFormatSize);
		}
		else
		{
			nFormatRest = nFormatSize % 1024;
			nFormatSize = nFormatSize / 1024;
			if (nFormatSize < 1024)
			{
				if (nFormatRest != 0) nFormatSize++;
				strFormatSize.Format(_T("%d KB"), (int) nFormatSize);
			}
			else
			{
				nFormatRest = nFormatSize % 1024;
				nFormatSize = nFormatSize / 1024;
				if (nFormatSize < 1024)
				{
					if (nFormatRest != 0) nFormatSize++;
					strFormatSize.Format(_T("%d MB"), (int) nFormatSize);
				}
				else
				{
					nFormatRest = nFormatSize % 1024;
					nFormatSize = nFormatSize / 1024;
					if (nFormatSize < 1024)
					{
						if (nFormatRest != 0) nFormatSize++;
						strFormatSize.Format(_T("%d GB"), (int) nFormatSize);
					}
					else
					{
						nFormatRest = nFormatSize % 1024;
						nFormatSize = nFormatSize / 1024;
						if (nFormatRest != 0) nFormatSize++;
						strFormatSize.Format(_T("%d TB"), (int) nFormatSize);
					}
				}
			}
		}
		return strFormatSize;
	}
}

CString CFileData::FormatDate()
{
	return m_ftLastWriteTime.Format();
}

CString CFileData::FormatAttr()
{
	CString strFormatAttr;
	strFormatAttr += ((m_dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) ? _T('a') : _T('-');
	strFormatAttr += ((m_dwFileAttributes & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY) ? _T('r') : _T('-');
	strFormatAttr += ((m_dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) ? _T('h') : _T('-');
	strFormatAttr += ((m_dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) == FILE_ATTRIBUTE_SYSTEM) ? _T('s') : _T('-');
	return strFormatAttr;
}

bool CFileData::IsFolder()
{
	return ((m_dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
}

///////////////////////////////////////////////////////////////////////////////
// CFileSystem member functions
///////////////////////////////////////////////////////////////////////////////

CFileSystem::CFileSystem()
{
	m_wndCaptionBar = nullptr;
	m_hWndParent = nullptr;
	m_nSystemType = FILE_TYPE_FAT;
	m_strCurrentFolder = DEFAULT_FOLDER;
}

CFileSystem::~CFileSystem()
{
	VERIFY(RemoveAll());
}

bool CFileSystem::RemoveAll()
{
	const int nSize = (int)m_arrFiles.GetSize();
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		CFileData* pFileData = m_arrFiles.GetAt(nIndex);
		ASSERT(pFileData != nullptr);
		delete pFileData;
		pFileData = nullptr;
	}
	m_arrFiles.RemoveAll();
	return true;
}

bool CFileSystem::SetCurrentFolder(CString strFolder)
{
	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (SetCurrentDirectory(strFolder))
			{
				m_strCurrentFolder = strFolder;
				return true;
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("SetCurrentDirectory"), GetLastError());
			}
			break;
		}
	}
	return false;
}

bool CFileSystem::Refresh()
{
	HANDLE hFindFile = nullptr;
	WIN32_FIND_DATA pFindData = { 0 };

	VERIFY(RemoveAll());
	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (!SetCurrentFolder(m_strCurrentFolder))
				return false;

			hFindFile = FindFirstFile(_T("*.*"), &pFindData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if ((CString(pFindData.cFileName).CompareNoCase(_T(".")) != 0) &&
						((CString(pFindData.cFileName).CompareNoCase(_T("..")) != 0) || (m_strCurrentFolder.GetLength() > 3)))
					{
						const ULONGLONG nFileSize = (ULONGLONG)(pFindData.nFileSizeLow) +
							((ULONGLONG)(pFindData.nFileSizeHigh) << 32);
						CFileData* pFileData = new CFileData(
							pFindData.dwFileAttributes,
							pFindData.ftCreationTime,
							pFindData.ftLastAccessTime,
							pFindData.ftLastWriteTime,
							nFileSize,
							pFindData.cFileName,
							pFindData.cAlternateFileName);
						m_arrFiles.Add(pFileData);
					}
				}
				while (FindNextFile(hFindFile, &pFindData) != 0);

				DWORD dwError = GetLastError();
				if (dwError != ERROR_NO_MORE_FILES) 
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindNextFile"), dwError);
					return false;
				}

				if (!FindClose(hFindFile))
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindClose"), GetLastError());
					return false;
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("FindFirstFile"), GetLastError());
				return false;
			}
			return true;
		}
	}

	return false;
}

bool CFileSystem::ViewFile(CString strFilePath)
{
	return false;
}

bool CFileSystem::EditFile(CString strFilePath)
{
	const int nDot = strFilePath.ReverseFind(_T('.'));
	if ((nDot != -1) && !IsApplication(strFilePath))
	{
		CString strExtension = strFilePath.Mid(nDot);

		CString strApplication;
		TCHAR lpszBuffer[0x1000] = { 0 };
		DWORD cbLength = sizeof(lpszBuffer);
		if (SUCCEEDED(AssocQueryString(0, ASSOCSTR_COMMAND, strExtension, _T("open"), lpszBuffer, &cbLength)))
		{
			lpszBuffer[cbLength] = 0;
			strApplication = lpszBuffer;
		}
		else
		{
			if (SUCCEEDED(AssocQueryString(0, ASSOCSTR_COMMAND, strExtension, _T("edit"), lpszBuffer, &cbLength)))
			{
				lpszBuffer[cbLength] = 0;
				strApplication = lpszBuffer;
			}
		}

		if (strApplication.IsEmpty())
		{
			MessageBox(m_hWndParent, _T("There is no application associated with this type of file."), _T("IntelliFile"), MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		if (strApplication.Find(_T("%1")) != -1)
		{
			strApplication.Replace(_T("\"%1\""), (_T("\"") + strFilePath + _T("\"")));
			strApplication.Replace(_T("%1"), (_T("\"") + strFilePath + _T("\"")));
		}
		else
		{
			strApplication += _T(" ") + (_T("\"") + strFilePath + _T("\""));
		}

		CString strExe;
		CString strParam;
		if (strApplication.Find(_T("rundll32.exe")) != -1)
		{
			if (ShellExecute(m_hWndParent, _T("open"), strFilePath, nullptr, nullptr, SW_SHOWNORMAL) <= (HINSTANCE)32)
			{
				DisplayErrorBox(m_wndCaptionBar, _T("ShellExecute"), GetLastError());
				return false;
			}
		}
		else
		{
			if (strApplication[0] == _T('"'))
			{
				int nPos = strApplication.Find('"', 1);
				if (nPos != -1)
				{
					strExe = strApplication.Left(nPos+1);
					strParam = strApplication.Mid(nPos+1);
				}
				else
				{
					ASSERT(0);
				}
			}
			else
			{
				int nPos = strApplication.Find(' ', 1);
				if (nPos != -1)
				{
					strExe = strApplication.Left(nPos+1);
					strParam = strApplication.Mid(nPos+1);
				}
				else
				{
					ASSERT(0);
				}
			}

			strExe.Trim(_T(" \r\n\t"));
			strParam.Trim(_T(" \r\n\t"));

			SHELLEXECUTEINFO pShellExecuteInfo;
			pShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			pShellExecuteInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
			pShellExecuteInfo.hwnd = m_hWndParent;
			pShellExecuteInfo.lpVerb = nullptr;
			pShellExecuteInfo.lpFile = (LPCWSTR)(strExe);
			pShellExecuteInfo.lpParameters = (LPCWSTR)(strParam);
			pShellExecuteInfo.lpDirectory = nullptr;
			pShellExecuteInfo.nShow = SW_SHOWNORMAL;

			if (!ShellExecuteEx(&pShellExecuteInfo))
			{
				DisplayErrorBox(m_wndCaptionBar, _T("ShellExecute"), GetLastError());
				return false;
			}
		}
		return true;
	}

	return false;
}

std::string wstring_to_utf8(const std::wstring& str);

bool CFileSystem::FindText(const std::wstring& strFilePath, const std::wstring& strFindText)
{
	bool retVal = false;
	const std::string lpszFindText = wstring_to_utf8(strFindText);
	std::ifstream pInputFile(strFilePath, std::ifstream::in | std::ofstream::binary);
	if (pInputFile.is_open())
	{
		std::string strBuffer;
		while (std::getline(pInputFile, strBuffer))
		{
			if (strBuffer.find(lpszFindText) != std::string::npos)
			{
				retVal = true;
				break;
			}
		}
		pInputFile.close();
	}
	return retVal;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

bool CFileSystem::ReplaceText(const std::wstring& strFilePath, const std::wstring& strFindText, const std::wstring& strReplaceText)
{
	bool retVal = false;
	const std::string lpszFindText = wstring_to_utf8(strFindText);
	const std::string lpszReplaceText = wstring_to_utf8(strReplaceText);
	const std::wstring lpszBackup = strFilePath + _T(".bak");
	if (::MoveFile(strFilePath.c_str(), lpszBackup.c_str()))
	{
		std::ifstream pInputFile(lpszBackup, std::ifstream::in | std::ofstream::binary);
		if (pInputFile.is_open())
		{
			std::ofstream pOutputFile(strFilePath, std::ofstream::out | std::ofstream::binary);
			if (pOutputFile.is_open())
			{
				std::string strBuffer;
				while (std::getline(pInputFile, strBuffer))
				{
					replaceAll(strBuffer, lpszFindText, lpszReplaceText);
					pOutputFile.write(strBuffer.c_str(), strBuffer.length());
				}
				retVal = true;
				pOutputFile.close();
			}
			pInputFile.close();
		}

	}
	return retVal;
}

bool CFileSystem::SelectFile(
	CStringArray& arrFileList, const CString& strSearchFor,
	const bool& bFileDateCheck, const COleDateTime& ftDateTimeFrom, const COleDateTime& ftDateTimeTo,
	const bool& bFileSizeCheck, const TCHAR& chFileSize, const ULONGLONG& dwFileSize,
	const bool& bFileAttrCheck, const DWORD& dwFileAttrData, const DWORD& dwFileAttrMask)
{
	HANDLE hFindFile = nullptr;
	WIN32_FIND_DATA pFindData = { 0 };

	arrFileList.RemoveAll();
	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (!::SetCurrentDirectory(m_strCurrentFolder))
				return false;

			hFindFile = FindFirstFile(strSearchFor, &pFindData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if ((CString(pFindData.cFileName).CompareNoCase(_T(".")) != 0) &&
						(CString(pFindData.cFileName).CompareNoCase(_T("..")) != 0))
					{
						if (bFileDateCheck)
						{
							if (COleDateTime(pFindData.ftLastWriteTime) < ftDateTimeFrom)
								continue;
							if (COleDateTime(pFindData.ftLastWriteTime) > ftDateTimeTo)
								continue;
						}

						if (bFileSizeCheck)
						{
							const ULONGLONG nFileSize = (ULONGLONG)(pFindData.nFileSizeLow) +
								((ULONGLONG)(pFindData.nFileSizeHigh) << 32);
							if (_T('=') == chFileSize)
							{
								if (nFileSize != dwFileSize)
									continue;
							}
							else
							{
								if (_T('<') == chFileSize)
								{
									if (nFileSize > dwFileSize)
										continue;
								}
								else
								{
									if (_T('>') == chFileSize)
									{
										if (nFileSize < dwFileSize)
											continue;
									}
								}
							}
						}

						if (bFileAttrCheck)
						{
							if ((pFindData.dwFileAttributes & dwFileAttrMask) != dwFileAttrData)
								continue;
						}

						arrFileList.Add(pFindData.cFileName);
						TRACE(pFindData.cFileName);
					}
				} while (FindNextFile(hFindFile, &pFindData) != 0);

				DWORD dwError = GetLastError();
				if (dwError != ERROR_NO_MORE_FILES)
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindNextFile"), dwError);
					return false;
				}

				if (!FindClose(hFindFile))
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindClose"), GetLastError());
					return false;
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("FindFirstFile"), GetLastError());
				return false;
			}

			return true;
		}
	}

	return false;
}

extern bool g_bThreadRunning;
bool CFileSystem::SearchFile(
	CMFCListCtrl& pListCtrl, const CString& strSearchFor, const CString& strCurrentFolder,
	const bool& bFileDateCheck, const COleDateTime& ftDateTimeFrom, const COleDateTime& ftDateTimeTo,
	const bool& bFileSizeCheck, const TCHAR& chFileSize, const ULONGLONG& dwFileSize,
	const bool& bFileAttrCheck, const DWORD& dwFileAttrData, const DWORD& dwFileAttrMask,
	const bool& bFindTextCheck, const CString& strFindText, const bool& bReplaceTextCheck, const CString& strReplaceText)
{
	HANDLE hFindFile = nullptr;
	WIN32_FIND_DATA pFindData = { 0 };
	WIN32_FIND_DATA pNextData = { 0 };

	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (!::SetCurrentDirectory(strCurrentFolder))
				return false;

			hFindFile = FindFirstFile(strSearchFor, &pFindData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if ((CString(pFindData.cFileName).CompareNoCase(_T(".")) != 0) &&
						(CString(pFindData.cFileName).CompareNoCase(_T("..")) != 0))
					{
						if ((pFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
						{
							continue; // skip folders in search results
						}

						if (bFileDateCheck)
						{
							if (COleDateTime(pFindData.ftLastWriteTime) < ftDateTimeFrom)
								continue;
							if (COleDateTime(pFindData.ftLastWriteTime) > ftDateTimeTo)
								continue;
						}

						if (bFileSizeCheck)
						{
							const ULONGLONG nFileSize = (ULONGLONG)(pFindData.nFileSizeLow) +
								((ULONGLONG)(pFindData.nFileSizeHigh) << 32);
							if (_T('=') == chFileSize)
							{
								if (nFileSize != dwFileSize)
									continue;
							}
							else
							{
								if (_T('<') == chFileSize)
								{
									if (nFileSize > dwFileSize)
										continue;
								}
								else
								{
									if (_T('>') == chFileSize)
									{
										if (nFileSize < dwFileSize)
											continue;
									}
								}
							}
						}

						if (bFileAttrCheck)
						{
							if ((pFindData.dwFileAttributes & dwFileAttrMask) != dwFileAttrData)
								continue;
						}

						const CString strFilePath = strCurrentFolder + pFindData.cFileName;
						if (bFindTextCheck)
						{
							if (!FindText(static_cast<LPCWSTR>(strFilePath), static_cast<LPCWSTR>(strFindText)))
								continue;
							else
							{
								if (bReplaceTextCheck)
								{
									if (!ReplaceText(static_cast<LPCWSTR>(strFilePath), static_cast<LPCWSTR>(strFindText), static_cast<LPCWSTR>(strReplaceText)))
										continue;
								}
							}
						}

						pListCtrl.SetRedraw(FALSE);
						const int nListItem = pListCtrl.InsertItem(pListCtrl.GetItemCount(), strFilePath);
						SHFILEINFO pshFileInfo = { 0 };
						SHGetFileInfo(
							pFindData.cFileName,
							FILE_ATTRIBUTE_NORMAL,
							&pshFileInfo, sizeof(pshFileInfo),
							SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
						LVITEM lviItem = { 0 };
						lviItem.mask = LVIF_IMAGE;
						lviItem.iItem = nListItem;
						lviItem.iSubItem = 0;
						lviItem.iImage = pshFileInfo.iIcon;
						VERIFY(pListCtrl.SetItem(&lviItem));
						pListCtrl.EnsureVisible(nListItem, FALSE);
						pListCtrl.SetRedraw(TRUE);
						// pListCtrl.Invalidate();
						pListCtrl.UpdateWindow();
						TRACE(_T("%s\n"), pFindData.cFileName);
					}
				} while (g_bThreadRunning && (FindNextFile(hFindFile, &pFindData) != 0));

				if (g_bThreadRunning)
				{
					DWORD dwError = GetLastError();
					if (dwError != ERROR_NO_MORE_FILES)
					{
						// DisplayErrorBox(m_wndCaptionBar, _T("FindNextFile"), dwError);
						return false;
					}
				}

				if (!FindClose(hFindFile))
				{
					// DisplayErrorBox(m_wndCaptionBar, _T("FindClose"), GetLastError());
					return false;
				}
			}
			else
			{
				// DisplayErrorBox(m_wndCaptionBar, _T("FindFirstFile"), GetLastError());
				// return false;
			}

			hFindFile = FindFirstFile(_T("*.*"), &pNextData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if ((CString(pNextData.cFileName).CompareNoCase(_T(".")) != 0) &&
						(CString(pNextData.cFileName).CompareNoCase(_T("..")) != 0))
					{
						if ((pNextData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
						{
							const CString strSearchFolder = strCurrentFolder + pNextData.cFileName + _T("\\");
							TRACE(_T("%s\n"), static_cast<LPCWSTR>(strSearchFolder));
							SearchFile(pListCtrl, strSearchFor, strSearchFolder,
								bFileDateCheck, ftDateTimeFrom, ftDateTimeTo,
								bFileSizeCheck, chFileSize, dwFileSize,
								bFileAttrCheck, dwFileAttrData, dwFileAttrMask,
								bFindTextCheck, strFindText, bReplaceTextCheck, strReplaceText);
						}
					}
				} while (g_bThreadRunning && (FindNextFile(hFindFile, &pNextData) != 0));

				if (g_bThreadRunning)
				{
					DWORD dwError = GetLastError();
					if (dwError != ERROR_NO_MORE_FILES)
					{
						// DisplayErrorBox(m_wndCaptionBar, _T("FindNextFile"), dwError);
						return false;
					}
				}

				if (!FindClose(hFindFile))
				{
					// DisplayErrorBox(m_wndCaptionBar, _T("FindClose"), GetLastError());
					return false;
				}
			}
			else
			{
				// DisplayErrorBox(m_wndCaptionBar, _T("FindFirstFile"), GetLastError());
				// return false;
			}

			return true;
		}
	}

	return false;
}

bool CFileSystem::CopyFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	bool bRetVal = false;
	HRESULT hResult = S_OK;
	IFileOperation* pFileOperation = nullptr;
	IShellItem* pFolderItem = nullptr;
	IShellItem* pShellItem = nullptr;
	IShellItemArray* pShellItemArray = nullptr;
	CString strDestination = pDestination->GetCurrentFolder();

	ASSERT(pDestination != nullptr);
	ASSERT(arrSelection != nullptr);
	if ((SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation)))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOperationFlags(FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOFX_SHOWELEVATIONPROMPT))) &&
		(SUCCEEDED(hResult = SHCreateItemFromParsingName(strDestination, nullptr, IID_PPV_ARGS(&pFolderItem)))))
	{
		if (arrSelection->GetCount() == 1)
		{
			CFileData* pFileData = arrSelection->GetAt(0);
			ASSERT_VALID(pFileData);
			CString strFileName = pFileData->GetFileName();
			CString strFolder = GetCurrentFolder();
			CString strFilePath = strFolder + strFileName;

			if ((SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, nullptr, IID_PPV_ARGS(&pShellItem)))) &&
				(SUCCEEDED(hResult = pFileOperation->CopyItem(pShellItem, pFolderItem, nullptr, nullptr))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;

			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::CopyFile"), hResult);
			}
		}
		else
		{
			const int nCount = (int)arrSelection->GetCount();
			LPCITEMIDLIST* arrItemIDList = new LPCITEMIDLIST[nCount];
			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				CFileData* pFileData = arrSelection->GetAt(nIndex);
				ASSERT_VALID(pFileData);
				CString strFileName = pFileData->GetFileName();
				CString strFolder = GetCurrentFolder();
				CString strFilePath = strFolder + strFileName;

				arrItemIDList[nIndex] = ILCreateFromPath(strFilePath);
			}

			if ((SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray))) &&
				(SUCCEEDED(hResult = pFileOperation->CopyItems(pShellItemArray, pFolderItem))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::CopyFile"), hResult);
			}

			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				ILFree((LPITEMIDLIST)arrItemIDList[nIndex]);
			}
			delete arrItemIDList;
			arrItemIDList = nullptr;
		}
	}
	else
	{
		DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::CopyFile"), hResult);
	}

	if (pShellItemArray != nullptr)
	{
		pShellItemArray->Release();
		pShellItemArray = nullptr;
	}

	if (pShellItem != nullptr)
	{
		pShellItem->Release();
		pShellItem = nullptr;
	}

	if (pFolderItem != nullptr)
	{
		pFolderItem->Release();
		pFolderItem = nullptr;
	}

	if (pFileOperation != nullptr)
	{
		pFileOperation->Release();
		pFileOperation = nullptr;
	}

	return bRetVal;
}

bool CFileSystem::MoveFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	bool bRetVal = false;
	HRESULT hResult = S_OK;
	IFileOperation* pFileOperation = nullptr;
	IShellItem* pFolderItem = nullptr;
	IShellItem* pShellItem = nullptr;
	IShellItemArray* pShellItemArray = nullptr;
	CString strDestination = pDestination->GetCurrentFolder();

	ASSERT(pDestination != nullptr);
	ASSERT(arrSelection != nullptr);
	if ((SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation)))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOperationFlags(FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOFX_SHOWELEVATIONPROMPT))) &&
		(SUCCEEDED(hResult = SHCreateItemFromParsingName(strDestination, nullptr, IID_PPV_ARGS(&pFolderItem)))))
	{
		if (arrSelection->GetCount() == 1)
		{
			CFileData* pFileData = arrSelection->GetAt(0);
			ASSERT_VALID(pFileData);
			CString strFileName = pFileData->GetFileName();
			CString strFolder = GetCurrentFolder();
			CString strFilePath = strFolder + strFileName;

			if ((SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, nullptr, IID_PPV_ARGS(&pShellItem)))) &&
				(SUCCEEDED(hResult = pFileOperation->MoveItem(pShellItem, pFolderItem, nullptr, nullptr))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;

			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::MoveFile"), hResult);
			}
		}
		else
		{
			const int nCount = (int)arrSelection->GetCount();
			LPCITEMIDLIST* arrItemIDList = new LPCITEMIDLIST[nCount];
			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				CFileData* pFileData = arrSelection->GetAt(nIndex);
				ASSERT_VALID(pFileData);
				CString strFileName = pFileData->GetFileName();
				CString strFolder = GetCurrentFolder();
				CString strFilePath = strFolder + strFileName;

				arrItemIDList[nIndex] = ILCreateFromPath(strFilePath);
			}

			if ((SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray))) &&
				(SUCCEEDED(hResult = pFileOperation->MoveItems(pShellItemArray, pFolderItem))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::MoveFile"), hResult);
			}

			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				ILFree((LPITEMIDLIST)arrItemIDList[nIndex]);
			}
			delete arrItemIDList;
			arrItemIDList = nullptr;
		}
	}
	else
	{
		DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::MoveFile"), hResult);
	}

	if (pShellItemArray != nullptr)
	{
		pShellItemArray->Release();
		pShellItemArray = nullptr;
	}

	if (pShellItem != nullptr)
	{
		pShellItem->Release();
		pShellItem = nullptr;
	}

	if (pFolderItem != nullptr)
	{
		pFolderItem->Release();
		pFolderItem = nullptr;
	}

	if (pFileOperation != nullptr)
	{
		pFileOperation->Release();
		pFileOperation = nullptr;
	}

	return bRetVal;
}

bool CFileSystem::NewFolder(CFileSystem* pDestination, CString strNewFolderName)
{
	if (pDestination != nullptr)
	{
		switch (m_nSystemType)
		{
			case FILE_TYPE_FAT:
			{
				if (!SetCurrentFolder(m_strCurrentFolder))
					return false;

				if (::CreateDirectory(strNewFolderName, nullptr))
				{

				}
				else
				{
					const DWORD dwError = GetLastError();
					DisplayErrorBox(m_wndCaptionBar, _T("CreateDirectory"), dwError);
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

bool CFileSystem::DeleteFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	bool bRetVal = false;
	HRESULT hResult = S_OK;
	IFileOperation* pFileOperation = nullptr;
	IShellItem* pShellItem = nullptr;
	IShellItemArray* pShellItemArray = nullptr;
	CString strDestination = pDestination->GetCurrentFolder();

	ASSERT(pDestination != nullptr);
	ASSERT(arrSelection != nullptr);
	if ((SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation)))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent))) &&
		(SUCCEEDED(hResult = pFileOperation->SetOperationFlags(FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOFX_SHOWELEVATIONPROMPT))))
	{
		if (arrSelection->GetCount() == 1)
		{
			CFileData* pFileData = arrSelection->GetAt(0);
			ASSERT_VALID(pFileData);
			CString strFileName = pFileData->GetFileName();
			CString strFolder = GetCurrentFolder();
			CString strFilePath = strFolder + strFileName;

			if ((SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, nullptr, IID_PPV_ARGS(&pShellItem)))) &&
				(SUCCEEDED(hResult = pFileOperation->DeleteItem(pShellItem, nullptr))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;

			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::DeleteFile"), hResult);
			}
		}
		else
		{
			const int nCount = (int)arrSelection->GetCount();
			LPCITEMIDLIST* arrItemIDList = new LPCITEMIDLIST[nCount];
			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				CFileData* pFileData = arrSelection->GetAt(nIndex);
				ASSERT_VALID(pFileData);
				CString strFileName = pFileData->GetFileName();
				CString strFolder = GetCurrentFolder();
				CString strFilePath = strFolder + strFileName;

				arrItemIDList[nIndex] = ILCreateFromPath(strFilePath);
			}

			if ((SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray))) &&
				(SUCCEEDED(hResult = pFileOperation->DeleteItems(pShellItemArray))) &&
				(SUCCEEDED(hResult = pFileOperation->PerformOperations())))
			{
				bRetVal = true;
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::DeleteFile"), hResult);
			}

			for (int nIndex = 0; nIndex < nCount; nIndex++)
			{
				ILFree((LPITEMIDLIST)arrItemIDList[nIndex]);
			}
			delete arrItemIDList;
			arrItemIDList = nullptr;
		}
	}
	else
	{
		DisplayErrorBox(m_wndCaptionBar, _T("CFileSystem::DeleteFile"), hResult);
	}

	if (pShellItemArray != nullptr)
	{
		pShellItemArray->Release();
		pShellItemArray = nullptr;
	}

	if (pShellItem != nullptr)
	{
		pShellItem->Release();
		pShellItem = nullptr;
	}

	if (pFileOperation != nullptr)
	{
		pFileOperation->Release();
		pFileOperation = nullptr;
	}

	return bRetVal;
}

bool CFileSystem::RenameFile(const CString& strOldFilePath, const CString& strNewFilePath)
{
	if (MoveFileEx(strOldFilePath, strNewFilePath, 0))
	{
		return true;
	}
	else
	{
		const DWORD dwError = GetLastError();
		DisplayErrorBox(m_wndCaptionBar, _T("RenameFile"), dwError);
		return false;
	}
}

bool CFileSystem::CommandPrompt(bool bAdministrator)
{
	SHELLEXECUTEINFO pShellExecuteInfo;
	pShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	pShellExecuteInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
	pShellExecuteInfo.hwnd = m_hWndParent;
	pShellExecuteInfo.lpVerb = (bAdministrator ? _T("runas") : nullptr);
	pShellExecuteInfo.lpFile = _T("cmd.exe");
	pShellExecuteInfo.lpParameters = nullptr;
	pShellExecuteInfo.lpDirectory = GetCurrentFolder();
	pShellExecuteInfo.nShow = SW_SHOWNORMAL;

	if (!ShellExecuteEx(&pShellExecuteInfo))
	{
		DisplayErrorBox(m_wndCaptionBar, _T("ShellExecute"), GetLastError());
		return false;
	}
	return true;
}
