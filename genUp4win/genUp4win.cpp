/* MIT License

Copyright (c) 2024 Stefan-Mihai MOGA

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "pch.h"
#include "resource.h"
#include "genUp4win.h"
#include "AppSettings.h"
#include "VersionInfo.h"

#include "Urlmon.h" // URLDownloadToFile function
#pragma comment(lib, "Urlmon.lib")

#include "shellapi.h" // ShellExecuteEx function
#pragma comment(lib, "Shell32.lib")

#include <comdef.h>

const std::wstring GetAppSettingsFilePath(const std::wstring& strFilePath, const std::wstring& strProductName)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0, };
	TCHAR lpszDirectory[_MAX_DIR] = { 0, };
	TCHAR lpszFilename[_MAX_FNAME] = { 0, };
	TCHAR lpszExtension[_MAX_EXT] = { 0, };
	TCHAR lpszFullPath[_MAX_PATH] = { 0, };

	WCHAR* lpszSpecialFolderPath = nullptr;
	if ((SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &lpszSpecialFolderPath)) == S_OK)
	{
		std::wstring result(lpszSpecialFolderPath);
		CoTaskMemFree(lpszSpecialFolderPath);
		result += _T("\\");
		result += strProductName;
		result += _T(".xml");
		OutputDebugString(result.c_str());
		return result;
	}

	_tsplitpath_s(strFilePath.c_str(), lpszDrive, _MAX_DRIVE, lpszDirectory, _MAX_DIR, lpszFilename, _MAX_FNAME, lpszExtension, _MAX_EXT);
	_tmakepath_s(lpszFullPath, _MAX_PATH, lpszDrive, lpszDirectory, strProductName.c_str(), _T(".xml"));
	OutputDebugString(lpszFullPath);
	return lpszFullPath;
}

bool WriteConfigFile(const std::wstring& strFilePath, const std::wstring& strDownloadURL, fnCallback ParentCallback)
{
	bool retVal = false;
	CVersionInfo pVersionInfo;

	if (pVersionInfo.Load(strFilePath.c_str()))
	{
		const std::wstring& strProductName = pVersionInfo.GetProductName();
		try {
			const HRESULT hr{ CoInitialize(nullptr) };
			if (FAILED(hr))
			{
				_com_error pError(hr);
				LPCTSTR lpszErrorMessage = pError.ErrorMessage();
				ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
				return false;
			}

			CXMLAppSettings pAppSettings(GetAppSettingsFilePath(strFilePath, strProductName), true, true);
			pAppSettings.WriteString(strProductName.c_str(), VERSION_ENTRY_ID, pVersionInfo.GetProductVersionAsString().c_str());
			pAppSettings.WriteString(strProductName.c_str(), DOWNLOAD_ENTRY_ID, strDownloadURL.c_str());
			retVal = true;
		}
		catch (CAppSettingsException& pException)
		{
			const int nErrorLength = 0x100;
			TCHAR lpszErrorMessage[nErrorLength] = { 0, };
			pException.GetErrorMessage(lpszErrorMessage, nErrorLength);
			ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
		}
	}
	return retVal;
}

bool ReadConfigFile(const std::wstring& strConfigURL, const std::wstring& strProductName, std::wstring& strLatestVersion, std::wstring& strDownloadURL, fnCallback ParentCallback)
{
	CString strStatusMessage;
	HRESULT hResult = S_OK;
	bool retVal = false;
	TCHAR lpszTempPath[_MAX_PATH] = { 0 };
	DWORD nLength = GetTempPath(_MAX_PATH, lpszTempPath);
	if (nLength > 0)
	{
		TCHAR lpszFilePath[_MAX_PATH] = { 0 };
		nLength = GetTempFileName(lpszTempPath, nullptr, 0, lpszFilePath);
		if (nLength > 0)
		{
			CString strFileName = lpszFilePath;
			strFileName.Replace(_T(".tmp"), _T(".xml"));
			if (strStatusMessage.LoadString(IDS_CONNECTING))
			{
				ParentCallback(GENUP4WIN_INPROGRESS, std::wstring(strStatusMessage));
			}
			if ((hResult = URLDownloadToFile(nullptr, strConfigURL.c_str(), strFileName, 0, nullptr)) == S_OK)
			{
				try {
					const HRESULT hr{ CoInitialize(nullptr) };
					if (FAILED(hr))
					{
						_com_error pError(hr);
						LPCTSTR lpszErrorMessage = pError.ErrorMessage();
						ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
						return false;
					}

					CXMLAppSettings pAppSettings(std::wstring(strFileName), true, true);
					strLatestVersion = pAppSettings.GetString(strProductName.c_str(), VERSION_ENTRY_ID);
					strDownloadURL = pAppSettings.GetString(strProductName.c_str(), DOWNLOAD_ENTRY_ID);
					retVal = true;
				}
				catch (CAppSettingsException& pException)
				{
					const int nErrorLength = 0x100;
					TCHAR lpszErrorMessage[nErrorLength] = { 0, };
					pException.GetErrorMessage(lpszErrorMessage, nErrorLength);
					ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
				}
			}
			else
			{
				_com_error pError(hResult);
				LPCTSTR lpszErrorMessage = pError.ErrorMessage();
				ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
			}
		}
	}
	return retVal;
}

bool CheckForUpdates(const std::wstring& strFilePath, const std::wstring& strConfigURL, fnCallback ParentCallback)
{
	CString strStatusMessage;
	HRESULT hResult = S_OK;
	bool retVal = false;
	CVersionInfo pVersionInfo;
	std::wstring strLatestVersion, strDownloadURL;

	if (pVersionInfo.Load(strFilePath.c_str()))
	{
		const std::wstring& strProductName = pVersionInfo.GetProductName();
		OutputDebugString(strProductName.c_str());
		if (ReadConfigFile(strConfigURL, strProductName, strLatestVersion, strDownloadURL, ParentCallback))
		{
			bool bNewUpdateFound = (strLatestVersion.compare(pVersionInfo.GetProductVersionAsString()) != 0);
			if (bNewUpdateFound)
			{
				TCHAR lpszTempPath[_MAX_PATH] = { 0 };
				DWORD nLength = GetTempPath(_MAX_PATH, lpszTempPath);
				if (nLength > 0)
				{
					TCHAR lpszFilePath[_MAX_PATH] = { 0 };
					nLength = GetTempFileName(lpszTempPath, nullptr, 0, lpszFilePath);
					if (nLength > 0)
					{
						CString strFileName = lpszFilePath;
						strFileName.Replace(_T(".tmp"), DEFAULT_EXTENSION);
						if (strStatusMessage.LoadString(IDS_DOWNLOADING))
						{
							ParentCallback(GENUP4WIN_INPROGRESS, std::wstring(strStatusMessage));
						}
						if ((hResult = URLDownloadToFile(nullptr, strDownloadURL.c_str(), strFileName, 0, nullptr)) == S_OK)
						{
							SHELLEXECUTEINFO pShellExecuteInfo;
							pShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
							pShellExecuteInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
							pShellExecuteInfo.hwnd = nullptr;
							pShellExecuteInfo.lpVerb = _T("open");
							pShellExecuteInfo.lpFile = strFileName;
							pShellExecuteInfo.lpParameters = nullptr;
							pShellExecuteInfo.lpDirectory = nullptr;
							pShellExecuteInfo.nShow = SW_SHOWNORMAL;
							const bool bLauched = ShellExecuteEx(&pShellExecuteInfo);
							if (strStatusMessage.LoadString(bLauched ? IDS_SUCCESS : IDS_FAILED))
							{
								ParentCallback(GENUP4WIN_INPROGRESS, std::wstring(strStatusMessage));
							}
							retVal = true; // Download was successful
						}
						else
						{
							_com_error pError(hResult);
							LPCTSTR lpszErrorMessage = pError.ErrorMessage();
							ParentCallback(GENUP4WIN_ERROR, lpszErrorMessage);
						}
					}
				}
			}
		}
	}
	return retVal;
}
