/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// NewFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "NewFolderDlg.h"

// CNewFolderDlg dialog

IMPLEMENT_DYNAMIC(CNewFolderDlg, CDialogEx)

CNewFolderDlg::CNewFolderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NewFolderDlg, pParent)
{
}

CNewFolderDlg::~CNewFolderDlg()
{
}

void CNewFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEW_FOLDER_NAME, m_editNewFolderName);
}

BEGIN_MESSAGE_MAP(CNewFolderDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewFolderDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CNewFolderDlg message handlers

void CNewFolderDlg::OnBnClickedOk()
{
	m_editNewFolderName.GetWindowText(m_strNewFolderName);
	CDialogEx::OnOK();
}
