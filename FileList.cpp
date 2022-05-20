/* This file is part of IntelliFile application developed by Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile.  If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

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

	LPVOID lpszMsgBuf = NULL;
	LPVOID lpszDisplayBuf = NULL;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpszMsgBuf,
		0, NULL);

	// Display the error message and clean up

	lpszDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpszMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
	_stprintf_s((LPTSTR)lpszDisplayBuf, 
		LocalSize(lpszDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s\n"), 
		lpszFunction, dwError, (LPCTSTR) lpszMsgBuf);
	OutputDebugString((LPCTSTR) lpszDisplayBuf);
	if (wndCaptionBar != NULL)
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
	if (wndCaptionBar != NULL)
	{
		wndCaptionBar->SetText((LPCTSTR) lpszMsgBuf, CMFCCaptionBar::ALIGN_LEFT);
		wndCaptionBar->ShowWindow(SW_SHOW);
		wndCaptionBar->Invalidate();
		wndCaptionBar->UpdateWindow();
	}
}

BOOL IsApplication(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if (_tcsicmp(lpszExtension, _T(".exe")) == 0)
		return TRUE;
	return FALSE;
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
	// CString strFormatDate;
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

BOOL CFileData::IsFolder()
{
	return ((m_dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
}

///////////////////////////////////////////////////////////////////////////////
// CFileSystem member functions
///////////////////////////////////////////////////////////////////////////////

CFileSystem::CFileSystem()
{
	m_wndCaptionBar = NULL;
	m_hWndParent = NULL;
	m_nSystemType = FILE_TYPE_FAT;
	m_strCurrentFolder = DEFAULT_FOLDER;
}

CFileSystem::~CFileSystem()
{
	VERIFY(RemoveAll());
}

BOOL CFileSystem::RemoveAll()
{
	const int nSize = (int)m_arrFiles.GetSize();
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		CFileData* pFileData = m_arrFiles.GetAt(nIndex);
		ASSERT(pFileData != NULL);
		delete pFileData;
		pFileData = NULL;
	}
	m_arrFiles.RemoveAll();
	return TRUE;
}

BOOL CFileSystem::SetCurrentFolder(CString strFolder)
{
	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (SetCurrentDirectory(strFolder))
			{
				m_strCurrentFolder = strFolder;
				return TRUE;
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("SetCurrentDirectory"), GetLastError());
			}
			break;
		}
	}
	return FALSE;
}

BOOL CFileSystem::Refresh()
{
	HANDLE hFindFile = NULL;
	WIN32_FIND_DATA pFindData = { 0 };

	VERIFY(RemoveAll());
	switch (m_nSystemType)
	{
		case FILE_TYPE_FAT:
		{
			if (!SetCurrentFolder(m_strCurrentFolder))
				return FALSE;

			hFindFile = FindFirstFile(_T("*.*"), &pFindData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (CString(pFindData.cFileName).CompareNoCase(_T(".")) != 0)
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

				const DWORD dwError = GetLastError();
				if (dwError != ERROR_NO_MORE_FILES) 
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindNextFile"), dwError);
				}

				if (!FindClose(hFindFile))
				{
					DisplayErrorBox(m_wndCaptionBar, _T("FindClose"), GetLastError());
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("FindFirstFile"), GetLastError());
				CFileData* pFileData = new CFileData(
					FILE_ATTRIBUTE_DIRECTORY,
					COleDateTime(), // ftCreationTime
					COleDateTime(), // ftLastAccessTime,
					COleDateTime(), // ftLastWriteTime,
					0,
					_T(".."),
					_T(".."));
				m_arrFiles.Add(pFileData);
				return FALSE;
			}
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFileSystem::ViewFile(CString strFilePath)
{
	return FALSE;
}

BOOL CFileSystem::EditFile(CString strFilePath)
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

		if (strApplication.IsEmpty())
		{
			MessageBox(m_hWndParent, _T("There is no application associated with this type of file."), _T("IntelliFile"), MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
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
			if ((int) ShellExecute(m_hWndParent, _T("open"), strFilePath, NULL, NULL, SW_SHOWNORMAL) <= 32)
			{
				DisplayErrorBox(m_wndCaptionBar, _T("ShellExecute"), GetLastError());
				return FALSE;
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
			pShellExecuteInfo.lpVerb = NULL;
			pShellExecuteInfo.lpFile = (LPCWSTR)(strExe);
			pShellExecuteInfo.lpParameters = (LPCWSTR)(strParam);
			pShellExecuteInfo.lpDirectory = NULL;
			pShellExecuteInfo.nShow = SW_SHOWNORMAL;

			if (!ShellExecuteEx(&pShellExecuteInfo))
			{
				DisplayErrorBox(m_wndCaptionBar, _T("ShellExecute"), GetLastError());
				return FALSE;
			}
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CFileSystem::CopyFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	HRESULT hResult = S_OK;
	if ((pDestination != NULL) && (arrSelection != NULL))
	{
		IFileOperation* pFileOperation = NULL;
		if (SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation))))
		{
			if (SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent)))
			{
				if (SUCCEEDED(hResult = pFileOperation->SetOperationFlags(
					FOF_NOCONFIRMMKDIR |
					FOF_NOERRORUI |
					FOFX_SHOWELEVATIONPROMPT)))
				{
					CString strDestination = pDestination->GetCurrentFolder();
					IShellItem* pFolderItem = NULL;
					if (SUCCEEDED(hResult = SHCreateItemFromParsingName(strDestination, NULL, IID_PPV_ARGS(&pFolderItem))))
					{
						if (arrSelection->GetCount() == 1)
						{
							CFileData* pFileData = arrSelection->GetAt(0);
							ASSERT_VALID(pFileData);
							CString strFileName = pFileData->GetFileName();
							CString strFolder = GetCurrentFolder();
							CString strFilePath = strFolder + strFileName;

							IShellItem* pShellItem = NULL;
							if (SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, NULL, IID_PPV_ARGS(&pShellItem))))
							{
								if (SUCCEEDED(hResult = pFileOperation->CopyItem(pShellItem, pFolderItem, NULL, NULL)))
								{
								}
								else
								{
									DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->CopyItem"), hResult);
									pShellItem->Release();
									pFolderItem->Release();
									pFileOperation->Release();
									return FALSE;
								}

								pShellItem->Release();
								pShellItem = NULL;
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("SHCreateItemFromParsingName"), hResult);
								pFolderItem->Release();
								pFileOperation->Release();
								return FALSE;
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

							IShellItemArray* pShellItemArray = NULL;
							if (SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray)))
							{
								if (SUCCEEDED(hResult = pFileOperation->CopyItems(pShellItemArray, pFolderItem)))
								{
								}
								else
								{
									DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->CopyItems"), hResult);
									pShellItemArray->Release();
									pFolderItem->Release();
									pFileOperation->Release();
									delete arrItemIDList;
									return FALSE;
								}

								pShellItemArray->Release();
								pShellItemArray = NULL;
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("SHCreateShellItemArrayFromIDLists"), hResult);
								pFileOperation->Release();
								pFolderItem->Release();
								delete arrItemIDList;
								return FALSE;
							}

							for (int nIndex = 0; nIndex < nCount; nIndex++)
							{
								ILFree((LPITEMIDLIST) arrItemIDList[nIndex]);
							}
							delete arrItemIDList;
							arrItemIDList = NULL;
						}

						pFolderItem->Release();
						pFolderItem = NULL;
					}
					else
					{
						DisplayErrorBox(m_wndCaptionBar, _T("SHCreateItemFromParsingName"), hResult);
						pFileOperation->Release();
						return FALSE;
					}

					if (SUCCEEDED(hResult = pFileOperation->PerformOperations()))
					{
					}
					else
					{
						DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->PerformOperations"), hResult);
						pFileOperation->Release();
						return FALSE;
					}
				}
				else
				{
					DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOperationFlags"), hResult);
					pFileOperation->Release();
					return FALSE;
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOwnerWindow"), hResult);
				pFileOperation->Release();
				return FALSE;
			}

			pFileOperation->Release();
			pFileOperation = NULL;

			return TRUE;
		}
		else
		{
			OutputDebugString(_T("CoCreateInstance(IFileOperation) failed!\n"));
		}
	}
	return FALSE;
}

BOOL CFileSystem::MoveFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	HRESULT hResult = S_OK;
	if ((pDestination != NULL) && (arrSelection != NULL))
	{
		IFileOperation* pFileOperation = NULL;
		if (SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation))))
		{
			if (SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent)))
			{
				if (SUCCEEDED(hResult = pFileOperation->SetOperationFlags(
					FOF_NOCONFIRMMKDIR |
					FOF_NOERRORUI |
					FOFX_SHOWELEVATIONPROMPT)))
				{
					CString strDestination = pDestination->GetCurrentFolder();
					IShellItem* pFolderItem = NULL;
					if (SUCCEEDED(hResult = SHCreateItemFromParsingName(strDestination, NULL, IID_PPV_ARGS(&pFolderItem))))
					{
						if (arrSelection->GetCount() == 1)
						{
							CFileData* pFileData = arrSelection->GetAt(0);
							ASSERT_VALID(pFileData);
							CString strFileName = pFileData->GetFileName();
							CString strFolder = GetCurrentFolder();
							CString strFilePath = strFolder + strFileName;

							IShellItem* pShellItem = NULL;
							if (SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, NULL, IID_PPV_ARGS(&pShellItem))))
							{
								if (SUCCEEDED(hResult = pFileOperation->MoveItem(pShellItem, pFolderItem, NULL, NULL)))
								{
								}
								else
								{
									DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->MoveItem"), hResult);
									pShellItem->Release();
									pFolderItem->Release();
									pFileOperation->Release();
									return FALSE;
								}

								pShellItem->Release();
								pShellItem = NULL;
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("SHCreateItemFromParsingName"), hResult);
								pFolderItem->Release();
								pFileOperation->Release();
								return FALSE;
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

							IShellItemArray* pShellItemArray = NULL;
							if (SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray)))
							{
								if (SUCCEEDED(hResult = pFileOperation->MoveItems(pShellItemArray, pFolderItem)))
								{
								}
								else
								{
									DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->MoveItems"), hResult);
									pShellItemArray->Release();
									pFolderItem->Release();
									pFileOperation->Release();
									delete arrItemIDList;
									return FALSE;
								}

								pShellItemArray->Release();
								pShellItemArray = NULL;
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("SHCreateShellItemArrayFromIDLists"), hResult);
								pFileOperation->Release();
								pFolderItem->Release();
								delete arrItemIDList;
								return FALSE;
							}

							for (int nIndex = 0; nIndex < nCount; nIndex++)
							{
								ILFree((LPITEMIDLIST) arrItemIDList[nIndex]);
							}
							delete arrItemIDList;
							arrItemIDList = NULL;
						}

						pFolderItem->Release();
						pFolderItem = NULL;
					}
					else
					{
						DisplayErrorBox(m_wndCaptionBar, _T("SHCreateItemFromParsingName"), hResult);
						pFileOperation->Release();
						return FALSE;
					}

					if (SUCCEEDED(hResult = pFileOperation->PerformOperations()))
					{
					}
					else
					{
						DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->PerformOperations"), hResult);
						pFileOperation->Release();
						return FALSE;
					}
				}
				else
				{
					DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOperationFlags"), hResult);
					pFileOperation->Release();
					return FALSE;
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOwnerWindow"), hResult);
				pFileOperation->Release();
				return FALSE;
			}

			pFileOperation->Release();
			pFileOperation = NULL;

			return TRUE;
		}
		else
		{
			OutputDebugString(_T("CoCreateInstance(IFileOperation) failed!\n"));
		}
	}
	return FALSE;
}

BOOL CFileSystem::NewFolder(CFileSystem* pDestination, CString strNewFolderName)
{
	if (pDestination != NULL)
	{
		switch (m_nSystemType)
		{
			case FILE_TYPE_FAT:
			{
				if (!SetCurrentFolder(m_strCurrentFolder))
					return FALSE;

				if (!::CreateDirectory(strNewFolderName, NULL))
					return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CFileSystem::DeleteFile(CFileSystem* pDestination, CFileList* arrSelection)
{
	HRESULT hResult = S_OK;
	if ((pDestination != NULL) && (arrSelection != NULL))
	{
		IFileOperation* pFileOperation = NULL;
		if (SUCCEEDED(hResult = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOperation))))
		{
			if (SUCCEEDED(hResult = pFileOperation->SetOwnerWindow(m_hWndParent)))
			{
				if (SUCCEEDED(hResult = pFileOperation->SetOperationFlags(
					FOF_NOCONFIRMMKDIR |
					FOF_NOERRORUI |
					FOFX_SHOWELEVATIONPROMPT)))
				{
					if (arrSelection->GetCount() == 1)
					{
						CFileData* pFileData = arrSelection->GetAt(0);
						ASSERT_VALID(pFileData);
						CString strFileName = pFileData->GetFileName();
						CString strFolder = GetCurrentFolder();
						CString strFilePath = strFolder + strFileName;

						IShellItem* pShellItem = NULL;
						if (SUCCEEDED(hResult = SHCreateItemFromParsingName(strFilePath, NULL, IID_PPV_ARGS(&pShellItem))))
						{
							if (SUCCEEDED(hResult = pFileOperation->DeleteItem(pShellItem, NULL)))
							{
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->DeleteItem"), hResult);
								pShellItem->Release();
								pFileOperation->Release();
								return FALSE;
							}

							pShellItem->Release();
							pShellItem = NULL;
						}
						else
						{
							DisplayErrorBox(m_wndCaptionBar, _T("SHCreateItemFromParsingName"), hResult);
							pFileOperation->Release();
							return FALSE;
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

						IShellItemArray* pShellItemArray = NULL;
						if (SUCCEEDED(hResult = SHCreateShellItemArrayFromIDLists(nCount, arrItemIDList, &pShellItemArray)))
						{
							if (SUCCEEDED(hResult = pFileOperation->DeleteItems(pShellItemArray)))
							{
							}
							else
							{
								DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->DeleteItems"), hResult);
								pShellItemArray->Release();
								pFileOperation->Release();
								delete arrItemIDList;
								return FALSE;
							}

							pShellItemArray->Release();
							pShellItemArray = NULL;
						}
						else
						{
							DisplayErrorBox(m_wndCaptionBar, _T("SHCreateShellItemArrayFromIDLists"), hResult);
							pFileOperation->Release();
							delete arrItemIDList;
							return FALSE;
						}

						for (int nIndex = 0; nIndex < nCount; nIndex++)
						{
							ILFree((LPITEMIDLIST) arrItemIDList[nIndex]);
						}
						delete arrItemIDList;
						arrItemIDList = NULL;
					}

					if (SUCCEEDED(hResult = pFileOperation->PerformOperations()))
					{
					}
					else
					{
						DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->PerformOperations"), hResult);
						pFileOperation->Release();
						return FALSE;
					}
				}
				else
				{
					DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOperationFlags"), hResult);
					pFileOperation->Release();
					return FALSE;
				}
			}
			else
			{
				DisplayErrorBox(m_wndCaptionBar, _T("pFileOperation->SetOwnerWindow"), hResult);
				pFileOperation->Release();
				return FALSE;
			}

			pFileOperation->Release();
			pFileOperation = NULL;

			return TRUE;
		}
		else
		{
			OutputDebugString(_T("CoCreateInstance(IFileOperation) failed!\n"));
		}
	}
	return FALSE;
}
