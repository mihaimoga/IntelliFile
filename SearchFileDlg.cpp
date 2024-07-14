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

// CSearchFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "SearchFileDlg.h"


// CSearchFileDlg dialog

IMPLEMENT_DYNAMIC(CSearchFileDlg, CDialogEx)

CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SearchFileDlg, pParent)
{

}

CSearchFileDlg::~CSearchFileDlg()
{
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchFileDlg message handlers
