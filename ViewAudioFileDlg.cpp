/* Copyright (C) 2022-2024 Stefan-Mihai MOGA
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

// ViewAudioFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "ViewAudioFileDlg.h"

#include "Mmsystem.h"
#pragma comment(lib, "Winmm.lib")

// CViewAudioFileDlg dialog

IMPLEMENT_DYNAMIC(CViewAudioFileDlg, CDialogEx)

CViewAudioFileDlg::CViewAudioFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ViewAudioFileDlg, pParent)
{
	m_nTimerID = 0;
}

CViewAudioFileDlg::~CViewAudioFileDlg()
{
}

void CViewAudioFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CViewAudioFileDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CViewAudioFileDlg message handlers

extern bool g_bThreadRunning;
DWORD WINAPI PlaySoundThreadProc(LPVOID lpParam)
{
	CViewAudioFileDlg* dlgViewAudioFile = (CViewAudioFileDlg*)lpParam;
	// ASSERT_VALID(dlgSearchFile);

	g_bThreadRunning = true;
	::PlaySound(dlgViewAudioFile->m_strFilePath, nullptr, SND_FILENAME);

	// dlgViewAudioFile->EndDialog(IDCANCEL);
	g_bThreadRunning = false;

	::ExitThread(0);
	return 0;
}

BOOL CViewAudioFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_strFilePath);

	m_hPlaySoundThread = ::CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PlaySoundThreadProc, this, 0, &m_nPlaySoundThreadID);
	m_nTimerID = SetTimer(0x1234, 100, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool WaitWithMessageLoop(HANDLE hEvent, DWORD dwTimeout);
void CViewAudioFileDlg::OnDestroy()
{
	/* if (g_bThreadRunning)
	{
		// g_bThreadRunning = false;
		VERIFY(WaitWithMessageLoop(m_hPlaySoundThread, INFINITE));
	} */

	CDialogEx::OnDestroy();
}

void CViewAudioFileDlg::OnCancel()
{
	::PlaySound(nullptr, 0, 0);

	CDialogEx::OnCancel();
}

void CViewAudioFileDlg::OnTimer(UINT_PTR nIDEvent)
{

	if (m_nTimerID == nIDEvent)
	{
		if (!g_bThreadRunning)
		{
			VERIFY(KillTimer(m_nTimerID));
			CDialogEx::OnCancel();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
