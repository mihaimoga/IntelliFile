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

#pragma once
#include "afxdialogex.h"

// CSearchFileDlg dialog

class CSearchFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchFileDlg)

public:
	CSearchFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSearchFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SearchFileDlg };
#endif

public:
	CString m_strSearchFor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
