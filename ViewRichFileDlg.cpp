/* This file is part of IntelliFile application developed by Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile.  If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// ViewRichFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "ViewRichFileDlg.h"

// CViewRichFileDlg dialog

IMPLEMENT_DYNAMIC(CViewRichFileDlg, CDialogEx)

CViewRichFileDlg::CViewRichFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ViewRichFileDlg, pParent)
{
}

CViewRichFileDlg::~CViewRichFileDlg()
{
}

void CViewRichFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_FILE, m_ctrlTextFile);
}

BEGIN_MESSAGE_MAP(CViewRichFileDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CViewRichFileDlg message handlers

static DWORD CALLBACK StreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	try
	{
		CFile* pFile = (CFile*)dwCookie;
		ASSERT_VALID(pFile);
		*pcb = pFile->Read(pbBuff, cb);
	}
	catch (CFileException* pEx)
	{
		// if an error occurs, just make a message box
		pEx->ReportError();
		pEx->Delete();
	}
	return 0;
}

BOOL CViewRichFileDlg::OnInitDialog()
{
	EDITSTREAM es;
	CDialogEx::OnInitDialog();

	SetWindowText(m_strFilePath);

	try
	{
		// try to open the file
		CFile pTextFile(m_strFilePath, CFile::modeRead);
		// query the file's length
		const ULONGLONG nFileLength = pTextFile.GetLength();
		if (nFileLength > 0)
		{
			es.dwCookie = (DWORD_PTR)&pTextFile;
			es.pfnCallback = (EDITSTREAMCALLBACK)StreamInCallback;
			m_ctrlTextFile.StreamIn(SF_RTF, es);
		}
		// close the file handle
		pTextFile.Close();
	}
	catch (CFileException* pEx)
	{
		// if an error occurs, just make a message box
		pEx->ReportError();
		pEx->Delete();
	}

	VERIFY(m_pWindowResizer.Hook(this));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_TEXT_FILE, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP | ANCHOR_BOTTOM));

	CWinApp *pWinApp = AfxGetApp();
	ASSERT_VALID(pWinApp);
	const int nWidth = pWinApp->GetProfileInt(_T("Size"), _T("Width"), -1);
	const int nHeight = pWinApp->GetProfileInt(_T("Size"), _T("Height"), -1);
	if ((-1 != nWidth) && (-1 != nHeight))
	{
		CRect pWndRect(0, 0, nWidth, nHeight);
		MoveWindow(pWndRect, FALSE);
		CenterWindow();
		UpdateWindow();
	}

	m_nTimerID = SetTimer(0x1234, 0x100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewRichFileDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	RECT pWndRect;
	GetWindowRect(&pWndRect);
	const int nWidth = pWndRect.right - pWndRect.left;
	const int nHeight = pWndRect.bottom - pWndRect.top;
	CWinApp *pWinApp = AfxGetApp();
	ASSERT_VALID(pWinApp);
	pWinApp->WriteProfileInt(_T("Size"), _T("Width"), nWidth);
	pWinApp->WriteProfileInt(_T("Size"), _T("Height"), nHeight);
}

void CViewRichFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nTimerID == nIDEvent)
	{
		KillTimer(m_nTimerID);
		m_ctrlTextFile.SetSel(0, 0);
	}

	CDialogEx::OnTimer(nIDEvent);
}
