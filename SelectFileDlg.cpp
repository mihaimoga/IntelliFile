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

// CSelectFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "SelectFileDlg.h"

// CSelectFileDlg dialog

IMPLEMENT_DYNAMIC(CSelectFileDlg, CDialogEx)

CSelectFileDlg::CSelectFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SelectFileDlg, pParent)
{
	m_bHideDirectoryFlag = false;
	m_strSearchFor = _T("*.*");
	m_bFileDateCheck = false;
	m_bFileSizeCheck = false;
	m_chFileSize = _T('='); // sign
	m_nFileSize = 0ULL; // amount
	m_bFileAttrCheck = false;
	m_dwFileAttrData = 0;
	m_dwFileAttrMask = 0;

	m_nFileSizeSign = 0;
	m_nFileSizeType = 0;
}

CSelectFileDlg::~CSelectFileDlg()
{
}

void CSelectFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_FOR, m_ctrlSearchFor);
	DDX_Control(pDX, IDC_DATE_BETWEEN, m_ctrlFileDateCheck);
	DDX_Control(pDX, IDC_DATE_FROM, m_ctrlFileDateFrom);
	DDX_Control(pDX, IDC_TIME_FROM, m_ctrlFileTimeFrom);
	DDX_Control(pDX, IDC_DATE_TO, m_ctrlFileDateTo);
	DDX_Control(pDX, IDC_TIME_TO, m_ctrlFileTimeTo);
	DDX_Control(pDX, IDC_FILE_SIZE_CHECK, m_ctrlFileSizeCheck);
	DDX_Control(pDX, IDC_FILE_SIZE_SIGN, m_ctrlFileSizeSign);
	DDX_Control(pDX, IDC_FILE_SIZE_AMOUNT, m_ctrlFileSizeAmount);
	DDX_Control(pDX, IDC_FILE_SIZE_TYPE, m_ctrlFileSizeType);
	DDX_Control(pDX, IDC_FILE_ATTR_CHECK, m_ctrlFileAttrCheck);
	DDX_Control(pDX, IDC_FILE_ATTR_READ_ONLY, m_ctrlFileAttrReadOnly);
	DDX_Control(pDX, IDC_FILE_ATTR_HIDDEN, m_ctrlFileAttrHidden);
	DDX_Control(pDX, IDC_FILE_ATTR_SYSTEM, m_ctrlFileAttrSystem);
	DDX_Control(pDX, IDC_FILE_ATTR_ARCHIVE, m_ctrlFileAttrArchive);
	DDX_Control(pDX, IDC_FILE_ATTR_DIRECTORY, m_ctrlFileAttrDirectory);
	DDX_Control(pDX, IDOK, m_ctrlOkButton);
}

BEGIN_MESSAGE_MAP(CSelectFileDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_SEARCH_FOR, &CSelectFileDlg::OnChangeSearchFor)
	ON_BN_CLICKED(IDC_DATE_BETWEEN, &CSelectFileDlg::OnClickedDateBetween)
	ON_BN_CLICKED(IDC_FILE_SIZE_CHECK, &CSelectFileDlg::OnClickedFileSizeCheck)
	ON_BN_CLICKED(IDC_FILE_ATTR_CHECK, &CSelectFileDlg::OnClickedFileAttrCheck)
END_MESSAGE_MAP()

// CSelectFileDlg message handlers

BOOL CSelectFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrlSearchFor.SetWindowText(m_strSearchFor);

	m_ctrlFileDateCheck.SetCheck(m_bFileDateCheck);
	m_ctrlFileDateFrom.SetTime(m_ftDateTimeFrom);
	m_ctrlFileTimeFrom.SetTime(m_ftDateTimeFrom);
	m_ctrlFileDateTo.SetTime(m_ftDateTimeTo);
	m_ctrlFileTimeTo.SetTime(m_ftDateTimeTo);

	m_ctrlFileSizeCheck.SetCheck(m_bFileSizeCheck);
	m_ctrlFileSizeSign.AddString(_T("="));
	m_ctrlFileSizeSign.AddString(_T("<"));
	m_ctrlFileSizeSign.AddString(_T(">"));
	m_ctrlFileSizeSign.SetCurSel(m_nFileSizeSign);

	m_ctrlFileSizeAmount.SetWindowText(m_strFileSize);

	m_ctrlFileSizeType.AddString(_T("bytes"));
	m_ctrlFileSizeType.AddString(_T("KB"));
	m_ctrlFileSizeType.AddString(_T("MB"));
	m_ctrlFileSizeType.AddString(_T("GB"));
	m_ctrlFileSizeType.SetCurSel(m_nFileSizeType);

	m_ctrlFileAttrCheck.SetCheck(m_bFileAttrCheck);
	m_ctrlFileAttrReadOnly.SetCheck(
		((m_dwFileAttrMask & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY) ?
		(((m_dwFileAttrData & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY) ?
			BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE);
	m_ctrlFileAttrHidden.SetCheck(
		((m_dwFileAttrMask & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) ?
		(((m_dwFileAttrData & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) ?
			BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE);
	m_ctrlFileAttrSystem.SetCheck(
		((m_dwFileAttrMask & FILE_ATTRIBUTE_SYSTEM) == FILE_ATTRIBUTE_SYSTEM) ?
		(((m_dwFileAttrData & FILE_ATTRIBUTE_SYSTEM) == FILE_ATTRIBUTE_SYSTEM) ?
			BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE);
	m_ctrlFileAttrArchive.SetCheck(
		((m_dwFileAttrMask & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) ?
		(((m_dwFileAttrData & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) ?
			BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE);
	m_ctrlFileAttrDirectory.SetCheck(
		((m_dwFileAttrMask & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) ?
		(((m_dwFileAttrData & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) ?
			BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE);
	m_ctrlFileAttrDirectory.EnableWindow(!m_bHideDirectoryFlag);

	OnClickedDateBetween();
	OnClickedFileSizeCheck();
	OnClickedFileAttrCheck();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectFileDlg::OnDestroy()
{
	COleDateTime ftDateFrom;
	COleDateTime ftTimeFrom;
	COleDateTime ftDateTo;
	COleDateTime ftTimeTo;

	m_ctrlSearchFor.GetWindowText(m_strSearchFor);

	m_bFileDateCheck = ((m_ctrlFileDateCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlFileDateFrom.GetTime(ftDateFrom);
	m_ctrlFileTimeFrom.GetTime(ftTimeFrom);
	m_ftDateTimeFrom = COleDateTime(
		ftDateFrom.GetYear(),
		ftDateFrom.GetMonth(),
		ftDateFrom.GetDay(),
		ftTimeFrom.GetHour(),
		ftTimeFrom.GetMinute(),
		ftTimeFrom.GetSecond());
	TRACE(_T("m_ftDateTimeFrom = %s\n"), static_cast<LPCWSTR>(m_ftDateTimeFrom.Format()));
	m_ctrlFileDateTo.GetTime(ftDateTo);
	m_ctrlFileTimeTo.GetTime(ftTimeTo);
	m_ftDateTimeTo = COleDateTime(
		ftDateTo.GetYear(),
		ftDateTo.GetMonth(),
		ftDateTo.GetDay(),
		ftTimeTo.GetHour(),
		ftTimeTo.GetMinute(),
		ftTimeTo.GetSecond());
	TRACE(_T("m_ftDateTimeTo = %s\n"), static_cast<LPCWSTR>(m_ftDateTimeTo.Format()));

	m_bFileSizeCheck = ((m_ctrlFileSizeCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_nFileSizeSign = m_ctrlFileSizeSign.GetCurSel();
	switch (m_nFileSizeSign)
	{
		case 1:
			m_chFileSize = _T('<');
			break;
		case 2:
			m_chFileSize = _T('>');
			break;
		case 0:
		default:
			m_chFileSize = _T('=');
			break;
	}
	m_ctrlFileSizeAmount.GetWindowText(m_strFileSize);
	m_nFileSize = 0;
	if (m_strFileSize.GetLength() > 0)
	{
		m_nFileSize = std::stoull(m_strFileSize.GetBuffer());
		m_strFileSize.ReleaseBuffer();
	}
	m_nFileSizeType = m_ctrlFileSizeType.GetCurSel();
	switch (m_nFileSizeType)
	{
		case 1:
			m_nFileSize *= 1024ULL;
			break;
		case 2:
			m_nFileSize *= (1024ULL * 1024ULL);
			break;
		case 3:
			m_nFileSize *= (1024ULL * 1024ULL * 1024ULL);
	}
	TRACE(_T("m_nFileSize = %llu\n"), m_nFileSize);

	m_bFileAttrCheck = ((m_ctrlFileAttrCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_dwFileAttrData = m_dwFileAttrMask = 0;
	if (((m_ctrlFileAttrReadOnly.GetState() & BST_CHECKED) == BST_CHECKED))
	{
		m_dwFileAttrData |= FILE_ATTRIBUTE_READONLY;
		m_dwFileAttrMask |= FILE_ATTRIBUTE_READONLY;
	}
	else
	{
		if (!((m_ctrlFileAttrReadOnly.GetState() & BST_INDETERMINATE) == BST_INDETERMINATE))
		{
			m_dwFileAttrMask |= FILE_ATTRIBUTE_READONLY;
		}
	}
	if (((m_ctrlFileAttrHidden.GetState() & BST_CHECKED) == BST_CHECKED))
	{
		m_dwFileAttrData |= FILE_ATTRIBUTE_HIDDEN;
		m_dwFileAttrMask |= FILE_ATTRIBUTE_HIDDEN;
	}
	else
	{
		if (!((m_ctrlFileAttrHidden.GetState() & BST_INDETERMINATE) == BST_INDETERMINATE))
		{
			m_dwFileAttrMask |= FILE_ATTRIBUTE_HIDDEN;
		}
	}
	if (((m_ctrlFileAttrSystem.GetState() & BST_CHECKED) == BST_CHECKED))
	{
		m_dwFileAttrData |= FILE_ATTRIBUTE_SYSTEM;
		m_dwFileAttrMask |= FILE_ATTRIBUTE_SYSTEM;
	}
	else
	{
		if (!((m_ctrlFileAttrSystem.GetState() & BST_INDETERMINATE) == BST_INDETERMINATE))
		{
			m_dwFileAttrMask |= FILE_ATTRIBUTE_SYSTEM;
		}
	}
	if (((m_ctrlFileAttrArchive.GetState() & BST_CHECKED) == BST_CHECKED))
	{
		m_dwFileAttrData |= FILE_ATTRIBUTE_ARCHIVE;
		m_dwFileAttrMask |= FILE_ATTRIBUTE_ARCHIVE;
	}
	else
	{
		if (!((m_ctrlFileAttrArchive.GetState() & BST_INDETERMINATE) == BST_INDETERMINATE))
		{
			m_dwFileAttrMask |= FILE_ATTRIBUTE_ARCHIVE;
		}
	}
	if (((m_ctrlFileAttrDirectory.GetState() & BST_CHECKED) == BST_CHECKED))
	{
		m_dwFileAttrData |= FILE_ATTRIBUTE_DIRECTORY;
		m_dwFileAttrMask |= FILE_ATTRIBUTE_DIRECTORY;
	}
	else
	{
		if (!((m_ctrlFileAttrDirectory.GetState() & BST_INDETERMINATE) == BST_INDETERMINATE))
		{
			m_dwFileAttrMask |= FILE_ATTRIBUTE_DIRECTORY;
		}
	}
	TRACE(_T("m_dwFileAttrData = 0x%08X\n"), m_dwFileAttrData);
	TRACE(_T("m_dwFileAttrMask = 0x%08X\n"), m_dwFileAttrMask);

	CDialogEx::OnDestroy();
}

void CSelectFileDlg::OnChangeSearchFor()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CString strSearchFor;
	m_ctrlSearchFor.GetWindowText(strSearchFor);
	m_ctrlOkButton.EnableWindow(!strSearchFor.IsEmpty());
}

void CSelectFileDlg::OnClickedDateBetween()
{
	const bool bIsChecked = ((m_ctrlFileDateCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlFileDateFrom.EnableWindow(bIsChecked);
	m_ctrlFileTimeFrom.EnableWindow(bIsChecked);
	m_ctrlFileDateTo.EnableWindow(bIsChecked);
	m_ctrlFileTimeTo.EnableWindow(bIsChecked);
}

void CSelectFileDlg::OnClickedFileSizeCheck()
{
	const bool bIsChecked = ((m_ctrlFileSizeCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlFileSizeSign.EnableWindow(bIsChecked);
	m_ctrlFileSizeAmount.EnableWindow(bIsChecked);
	m_ctrlFileSizeType.EnableWindow(bIsChecked);
}

void CSelectFileDlg::OnClickedFileAttrCheck()
{
	const bool bIsChecked = ((m_ctrlFileAttrCheck.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlFileAttrReadOnly.EnableWindow(bIsChecked);
	m_ctrlFileAttrHidden.EnableWindow(bIsChecked);
	m_ctrlFileAttrSystem.EnableWindow(bIsChecked);
	m_ctrlFileAttrArchive.EnableWindow(bIsChecked);
	m_ctrlFileAttrDirectory.EnableWindow(bIsChecked && !m_bHideDirectoryFlag);
}
