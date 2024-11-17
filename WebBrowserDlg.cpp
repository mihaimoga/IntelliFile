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
IntelliEdit. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// WebBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "WebBrowserDlg.h"

// CWebBrowserDlg dialog

IMPLEMENT_DYNAMIC(CWebBrowserDlg, CDialogEx)

CWebBrowserDlg::CWebBrowserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WebBrowserDlg, pParent)
{
}

CWebBrowserDlg::~CWebBrowserDlg()
{
}

void CWebBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebBrowserDlg, CDialogEx)
	ON_WM_DESTROY()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CWebBrowserDlg message handlers

BOOL CWebBrowserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    CRect rectClient;
    GetClientRect(rectClient);

    m_pCustomControl.CreateAsync(
        WS_VISIBLE | WS_CHILD,
        rectClient,
        this,
        1,
        [this]() {
            m_pCustomControl.SetParentView((CView*)this);
            m_pCustomControl.DisablePopups();
            m_pCustomControl.Navigate(USER_MANUAL_URL, nullptr);

            m_pCustomControl.RegisterCallback(CWebBrowser::CallbackType::TitleChanged, [this]() {
                CString strTitle = m_pCustomControl.GetTitle();
                SetWindowText(strTitle);
                });
        });

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWebBrowserDlg::OnDestroy()
{
    VERIFY(m_pCustomControl.DestroyWindow());
	
    CDialogEx::OnDestroy();
}

void CWebBrowserDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    if (m_pCustomControl.GetSafeHwnd() != nullptr)
    {
        m_pCustomControl.MoveWindow(0, 0, cx, cy);
    }
}
