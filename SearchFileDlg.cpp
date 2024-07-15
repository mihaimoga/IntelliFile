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
#include "SelectFileDlg.h"
#include "FolderDlg.h"

// CSearchFileDlg dialog

IMPLEMENT_DYNAMIC(CSearchFileDlg, CDialogEx)

CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SearchFileDlg, pParent)
{
	m_pMainFrame = nullptr;

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

	m_pFileSystem = nullptr;
	m_nSearchThreadID = 0;
	m_hSearchThread = nullptr;
}

CSearchFileDlg::~CSearchFileDlg()
{
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_FOR, m_ctrlSearchFor);
	DDX_Control(pDX, IDC_FOLDER, m_ctrlSearchFolder);
	DDX_Control(pDX, IDC_FIND_TEXT, m_ctrlFindText);
	DDX_Control(pDX, IDC_INPUT_TEXT, m_ctrlInputText);
	DDX_Control(pDX, IDC_REPLACE_TEXT, m_ctrlReplaceText);
	DDX_Control(pDX, IDC_OUTPUT_TEXT, m_ctrlOutputText);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, IDC_FILE_LIST, m_ctrlFileList);
	DDX_Control(pDX, IDC_ADVANCE, m_btnAdvance);
	DDX_Control(pDX, IDC_BROWSE, m_btnBrowse);
	DDX_Control(pDX, IDC_SEARCH, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_FILE_LIST, &CSearchFileDlg::OnDblclkFileList)
	ON_NOTIFY(NM_RCLICK, IDC_FILE_LIST, &CSearchFileDlg::OnRclickFileList)
	ON_EN_CHANGE(IDC_SEARCH_FOR, &CSearchFileDlg::OnChangeSearchFor)
	ON_BN_CLICKED(IDC_FIND_TEXT, &CSearchFileDlg::OnClickedFindText)
	ON_BN_CLICKED(IDC_REPLACE_TEXT, &CSearchFileDlg::OnClickedReplaceText)
	ON_BN_CLICKED(IDC_ADVANCE, &CSearchFileDlg::OnClickedAdvance)
	ON_BN_CLICKED(IDC_BROWSE, &CSearchFileDlg::OnClickedBrowse)
	ON_BN_CLICKED(IDC_SEARCH, &CSearchFileDlg::OnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, &CSearchFileDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// CSearchFileDlg message handlers

BOOL CSearchFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrlSearchFor.SetWindowText(m_strSearchFor);
	m_ctrlSearchFolder.SetWindowText(m_strCurrentFolder);
	m_ctrlProgress.ShowWindow(SW_HIDE);

	OnClickedFindText();
	OnClickedReplaceText();

	m_ctrlFileList.SetExtendedStyle(m_ctrlFileList.GetExtendedStyle()
		| LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rectClient;
	m_ctrlFileList.GetClientRect(&rectClient);
	const int nColumnSize = rectClient.Width() - GetSystemMetrics(SM_CXVSCROLL);
	m_ctrlFileList.InsertColumn(0, _T("Result(s)"), LVCFMT_LEFT, nColumnSize);
	ASSERT_VALID(m_pMainFrame);
	m_ctrlFileList.SetImageList(&m_pMainFrame->m_pImageList, LVSIL_SMALL);

	VERIFY(m_pWindowResizer.Hook(this));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_SEARCH_FOR, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_ADVANCE, ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_FOLDER, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_BROWSE, ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_INPUT_TEXT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_OUTPUT_TEXT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_PROGRESS, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_SEARCH, ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDCANCEL, ANCHOR_RIGHT | ANCHOR_TOP));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_FILE_LIST, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP | ANCHOR_BOTTOM));

	const int nWidth = theApp.GetInt(_T("Width"), -1);
	const int nHeight = theApp.GetInt(_T("Height"), -1);
	if ((-1 != nWidth) && (-1 != nHeight))
	{
		CRect pWndRect(0, 0, nWidth, nHeight);
		MoveWindow(pWndRect, FALSE);
		CenterWindow();
		UpdateWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchFileDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	RECT pWndRect;
	GetWindowRect(&pWndRect);
	const int nWidth = pWndRect.right - pWndRect.left;
	const int nHeight = pWndRect.bottom - pWndRect.top;
	theApp.WriteInt(_T("Width"), nWidth);
	theApp.WriteInt(_T("Height"), nHeight);
}

void CSearchFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_ctrlFileList.GetSafeHwnd() != nullptr)
	{
		HDITEM hdItem = { 0 };
		hdItem.cxy = 0;
		hdItem.mask = HDI_WIDTH;
		if (m_ctrlFileList.GetSafeHwnd() != nullptr)
		{
			CRect rectClient;
			m_ctrlFileList.GetClientRect(&rectClient);

			CMFCHeaderCtrl& pHeaderCtrl = m_ctrlFileList.GetHeaderCtrl();
			if (pHeaderCtrl.GetItem(0, &hdItem))
			{
				hdItem.cxy = rectClient.Width() - GetSystemMetrics(SM_CXVSCROLL);
				if (pHeaderCtrl.SetItem(0, &hdItem))
				{
					m_ctrlFileList.Invalidate();
					m_ctrlFileList.UpdateWindow();
				}
			}
		}
	}
}

void CSearchFileDlg::OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		const CString strFilePath = m_ctrlFileList.GetItemText(pNMItemActivate->iItem, 0);
		// if (IsApplication(strFilePath)) # requested by Rick Dishman
		{
			if (ShellExecute(m_hWnd, _T("open"), strFilePath, nullptr, m_strCurrentFolder, SW_SHOWNORMAL) > (HINSTANCE)32)
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->HideMessageBar();
			}
			else
			{
				// DisplayErrorBox(m_pFileSystem->GetWindow(), _T("ShellExecute"), GetLastError());
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
			}
		}
	}
	*pResult = 0;
}

bool openShellContextMenuForObject(const std::wstring& path, int xPos, int yPos, void* parentWindow);
void CSearchFileDlg::OnRclickFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CPoint pt(pNMItemActivate->ptAction);
	POINT p;
	p.x = pt.x;
	p.y = pt.y;
	::ClientToScreen(pNMHDR->hwndFrom, &p);
	if (pNMItemActivate->iItem != -1)
	{
		const CString strFilePath = m_ctrlFileList.GetItemText(pNMItemActivate->iItem, 0);
		const std::wstring lpszFilePath(strFilePath);
		openShellContextMenuForObject(lpszFilePath, p.x, p.y, this->m_hWnd);
	}
	*pResult = 0;
}

void CSearchFileDlg::OnChangeSearchFor()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CString strSearchFor;
	m_ctrlSearchFor.GetWindowText(strSearchFor);
	m_btnSearch.EnableWindow(!strSearchFor.IsEmpty());
}

void CSearchFileDlg::OnClickedFindText()
{
	m_bFindTextCheck = ((m_ctrlFindText.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlInputText.EnableWindow(m_bFindTextCheck);
}

void CSearchFileDlg::OnClickedReplaceText()
{
	m_bReplaceTextCheck = ((m_ctrlReplaceText.GetState() & BST_CHECKED) == BST_CHECKED);
	m_ctrlOutputText.EnableWindow(m_bReplaceTextCheck);
}

void CSearchFileDlg::OnClickedAdvance()
{
	CSelectFileDlg dlgSelectFile(this);
	dlgSelectFile.m_bHideDirectoryFlag = true;
	dlgSelectFile.m_strSearchFor = m_strSearchFor;
	dlgSelectFile.m_bFileDateCheck = m_bFileDateCheck;
	dlgSelectFile.m_ftDateTimeFrom = m_ftDateTimeFrom;
	dlgSelectFile.m_ftDateTimeTo = m_ftDateTimeTo;
	dlgSelectFile.m_bFileSizeCheck = m_bFileSizeCheck;
	dlgSelectFile.m_chFileSize = m_chFileSize;
	dlgSelectFile.m_nFileSize = m_nFileSize;
	dlgSelectFile.m_bFileAttrCheck = m_bFileAttrCheck;
	dlgSelectFile.m_dwFileAttrData = m_dwFileAttrData;
	dlgSelectFile.m_dwFileAttrMask = m_dwFileAttrMask;
	// backup values for next show
	dlgSelectFile.m_nFileSizeSign = m_nFileSizeSign;
	dlgSelectFile.m_strFileSize = m_strFileSize;
	dlgSelectFile.m_nFileSizeType = m_nFileSizeType;

	if (dlgSelectFile.DoModal() == IDOK)
	{
		m_strSearchFor = dlgSelectFile.m_strSearchFor;
		m_bFileDateCheck = dlgSelectFile.m_bFileDateCheck;
		m_ftDateTimeFrom = dlgSelectFile.m_ftDateTimeFrom;
		m_ftDateTimeTo = dlgSelectFile.m_ftDateTimeTo;
		m_bFileSizeCheck = dlgSelectFile.m_bFileSizeCheck;
		m_chFileSize = dlgSelectFile.m_chFileSize;
		m_nFileSize = dlgSelectFile.m_nFileSize;
		m_bFileAttrCheck = dlgSelectFile.m_bFileAttrCheck;
		m_dwFileAttrData = dlgSelectFile.m_dwFileAttrData;
		m_dwFileAttrMask = dlgSelectFile.m_dwFileAttrMask;
		// backup values for next show
		m_nFileSizeSign = dlgSelectFile.m_nFileSizeSign;
		m_strFileSize = dlgSelectFile.m_strFileSize;
		m_nFileSizeType = dlgSelectFile.m_nFileSizeType;

		m_ctrlSearchFor.SetWindowText(m_strSearchFor);
		OnChangeSearchFor();
	}
}

void CSearchFileDlg::OnClickedBrowse()
{
	const UINT nFolderFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_VALIDATE;
	CFolderDialog dlgFileDialog(nullptr, m_strCurrentFolder, this, nFolderFlags);
	if (dlgFileDialog.DoModal() == IDOK)
	{
		m_strCurrentFolder = dlgFileDialog.GetFolderPath();
		const UINT lenRootFolder = m_strCurrentFolder.GetLength();
		if (lenRootFolder > 0)
		{
			if (m_strCurrentFolder.GetAt(lenRootFolder - 1) != _T('\\'))
				m_strCurrentFolder += _T("\\");
			m_ctrlSearchFolder.SetWindowText(m_strCurrentFolder);
		}
	}
}

bool g_bThreadRunning = false;
DWORD WINAPI SearchThreadProc(LPVOID lpParam)
{
	CSearchFileDlg* dlgSearchFile = (CSearchFileDlg*)lpParam;
	// ASSERT_VALID(dlgSearchFile);
	CFileSystem* pFileSystem = dlgSearchFile->m_pFileSystem;
	// ASSERT_VALID(pFileView);

	g_bThreadRunning = true;
	dlgSearchFile->m_ctrlFileList.DeleteAllItems();
	VERIFY(pFileSystem->SearchFile(
		dlgSearchFile->m_ctrlFileList, dlgSearchFile->m_strSearchFor, dlgSearchFile->m_strCurrentFolder,
		dlgSearchFile->m_bFileDateCheck, dlgSearchFile->m_ftDateTimeFrom, dlgSearchFile->m_ftDateTimeTo,
		dlgSearchFile->m_bFileSizeCheck, dlgSearchFile->m_chFileSize, dlgSearchFile->m_nFileSize,
		dlgSearchFile->m_bFileAttrCheck, dlgSearchFile->m_dwFileAttrData, dlgSearchFile->m_dwFileAttrMask,
		dlgSearchFile->m_bFindTextCheck, dlgSearchFile->m_strFindText, dlgSearchFile->m_bReplaceTextCheck, dlgSearchFile->m_strReplaceText));

	dlgSearchFile->m_btnAdvance.EnableWindow(TRUE);
	dlgSearchFile->m_btnBrowse.EnableWindow(TRUE);
	dlgSearchFile->m_btnSearch.EnableWindow(TRUE);
	dlgSearchFile->m_ctrlProgress.SetMarquee(FALSE, 30);
	dlgSearchFile->m_ctrlProgress.ShowWindow(SW_HIDE);
	::ExitThread(0);
	return 0;
}

void CSearchFileDlg::OnClickedSearch()
{
	m_ctrlSearchFor.GetWindowText(m_strSearchFor);

	m_ctrlInputText.GetWindowText(m_strFindText);
	m_ctrlOutputText.GetWindowText(m_strReplaceText);

	m_btnAdvance.EnableWindow(FALSE);
	m_btnBrowse.EnableWindow(FALSE);
	m_btnSearch.EnableWindow(FALSE);
	m_ctrlProgress.ShowWindow(SW_SHOW);
	m_ctrlProgress.SetMarquee(TRUE, 30);

	m_hSearchThread = ::CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SearchThreadProc, this, 0, &m_nSearchThreadID);
}

bool WaitWithMessageLoop(HANDLE hEvent, DWORD dwTimeout)
{
	DWORD dwRet;
	MSG msg;
	hEvent = hEvent ? hEvent : CreateEvent(NULL, FALSE, FALSE, NULL);

	while (true)
	{
		dwRet = MsgWaitForMultipleObjects(1, &hEvent, FALSE, dwTimeout, QS_ALLINPUT);
		if (dwRet == WAIT_OBJECT_0)
			return TRUE;
		if (dwRet != WAIT_OBJECT_0 + 1)
			break;
		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0)
				return true;
		}
	}
	return false;
}

void CSearchFileDlg::OnBnClickedCancel()
{
	if (g_bThreadRunning)
	{
		g_bThreadRunning = false;
		VERIFY(WaitWithMessageLoop(m_hSearchThread, INFINITE));
	}
	CDialogEx::OnCancel();
}
