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

#pragma once

#include "WndResizer.h"

#include "HexCtrl/HexCtrl/HexCtrl.h"
using namespace HEXCTRL;

// CViewBinaryFileDlg dialog

class CViewBinaryFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewBinaryFileDlg)

public:
	CViewBinaryFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CViewBinaryFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ViewBinaryFileDlg };
#endif
	CWndResizer m_pWindowResizer;
	IHexCtrlPtr m_pHexDlg{ CreateHexCtrl() };
	CLongBinary m_pFileData;
	CString m_strFilePath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};
