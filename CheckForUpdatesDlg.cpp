/* Copyright (C) 2022-2025 Stefan-Mihai MOGA
This file is part of IntelliFile application developed by Stefan-Mihai MOGA.
IntelliFile is an alternative Windows version to the famous Total Commander!

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// CheckForUpdatesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "CheckForUpdatesDlg.h"

#include "genUp4win/genUp4win.h"
#if _WIN64
#ifdef _DEBUG
#pragma comment(lib, "x64/Debug/genUp4win.lib")
#else
#pragma comment(lib, "x64/Release/genUp4win.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "Debug/genUp4win.lib")
#else
#pragma comment(lib, "Release/genUp4win.lib")
#endif
#endif

// CCheckForUpdatesDlg dialog

IMPLEMENT_DYNAMIC(CCheckForUpdatesDlg, CDialogEx)

CCheckForUpdatesDlg::CCheckForUpdatesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CheckForUpdatesDlg, pParent)
{
	m_nUpdateThreadID = 0;
	m_hUpdateThread = nullptr;
	m_nTimerID = 0;
}

CCheckForUpdatesDlg::~CCheckForUpdatesDlg()
{
}

void CCheckForUpdatesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_ctrlStatusMessage);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}

BEGIN_MESSAGE_MAP(CCheckForUpdatesDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCheckForUpdatesDlg message handlers
CCheckForUpdatesDlg* g_dlgCheckForUpdates = nullptr;
void UI_Callback(int, const std::wstring& strMessage)
{
	if (g_dlgCheckForUpdates != nullptr)
	{
		g_dlgCheckForUpdates->m_ctrlStatusMessage.SetWindowText(strMessage.c_str());
		g_dlgCheckForUpdates->m_ctrlStatusMessage.UpdateWindow();
	}
}

bool g_bThreadRunning = false;
bool g_bNewUpdateFound = false;
DWORD WINAPI UpdateThreadProc(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);

	g_bThreadRunning = true;
	if (g_dlgCheckForUpdates != nullptr)
	{
		g_dlgCheckForUpdates->m_ctrlProgress.SetMarquee(TRUE, 30);
	}
	const DWORD nLength = 0x1000 /* _MAX_PATH */;
	TCHAR lpszFilePath[nLength] = { 0, };
	GetModuleFileName(nullptr, lpszFilePath, nLength);
	g_bNewUpdateFound = CheckForUpdates(lpszFilePath, APPLICATION_URL, UI_Callback);
	if (g_dlgCheckForUpdates != nullptr)
	{
		g_dlgCheckForUpdates->m_ctrlProgress.SetMarquee(FALSE, 30);
	}
	g_bThreadRunning = false;

	::ExitThread(0);
	// return 0;
}

BOOL CCheckForUpdatesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	const DWORD nLength = 0x1000 /* _MAX_PATH */;
	TCHAR lpszFilePath[nLength] = { 0, };
	GetModuleFileName(nullptr, lpszFilePath, nLength);
	WriteConfigFile(lpszFilePath, INSTALLER_URL);
#endif

	g_dlgCheckForUpdates = this;
	m_hUpdateThread = ::CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UpdateThreadProc, this, 0, &m_nUpdateThreadID);
	m_nTimerID = SetTimer(0x1234, 100, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckForUpdatesDlg::OnCancel()
{
	while (g_bThreadRunning)
		Sleep(1000);
	CDialogEx::OnCancel();
}

void CCheckForUpdatesDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	if (m_nTimerID == nIDEvent)
	{
		if (!g_bThreadRunning)
		{
			VERIFY(KillTimer(m_nTimerID));
			CDialogEx::OnCancel();
			if (g_bNewUpdateFound)
			{
				PostQuitMessage(0);
			}
		}
	}
}
