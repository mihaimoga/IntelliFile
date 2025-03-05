/* MIT License

Copyright (c) 2024-2025 Stefan-Mihai MOGA

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

#pragma once
#ifdef __cplusplus

#include <string>
#include <functional>

#ifdef GENUP4WIN_EXPORTS
#define GENUP4WIN __declspec(dllexport)
#else
#define GENUP4WIN __declspec(dllimport)
#endif

typedef enum {
	GENUP4WIN_ERROR = -1,
	GENUP4WIN_OK,
	GENUP4WIN_INPROGRESS
} GENUP4WIN_STATUS;

void StatusCallback(int, const std::wstring& strMessage) { OutputDebugString(strMessage.c_str()); };

typedef std::function<void(int, const std::wstring& strMessage)> fnCallback;

// Generates the configuration XML file path
GENUP4WIN const std::wstring GetAppSettingsFilePath(const std::wstring& strFilePath, const std::wstring& strProductName);

// Writes the configuration XML file; the result should be install on Web for futher access
GENUP4WIN bool WriteConfigFile(const std::wstring& strFilePath, const std::wstring& strDownloadURL, fnCallback = StatusCallback);

// Reads the config XML file (i.e. downloads it on local machine); the result is stored in `strLatestVersion` and `strDownloadURL`
GENUP4WIN bool ReadConfigFile(const std::wstring& strConfigURL, const std::wstring& strProductName, std::wstring& strLatestVersion, std::wstring& strDownloadURL, fnCallback = StatusCallback);

// Checks for updates; first, it downloads the config XML file; then, it actual downloads the installer
GENUP4WIN bool CheckForUpdates(const std::wstring& strFilePath, const std::wstring& strConfigURL, fnCallback = StatusCallback);

#endif
