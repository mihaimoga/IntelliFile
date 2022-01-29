/* This file is part of IntelliFile application developed by Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile.  If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// FileView.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "FileView.h"
#include "MainFrame.h"

// CFileView

IMPLEMENT_DYNCREATE(CFileView, CMFCListView)

	CFileView::CFileView()
{
	m_bInitialized = FALSE;
	m_pMainFrame = NULL;
	m_bIsLeftPane = TRUE;

	m_bShiftPressed = FALSE;
	m_bCtrlPressed = FALSE;
	m_bMenuPressed = FALSE;

	GetListCtrl().m_pFileSystem = &m_pFileSystem;
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CMFCListView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, ID_MFCLISTCTRL, OnDblClickEntry)
END_MESSAGE_MAP()

// CFileView diagnostics

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CMFCListView::AssertValid();
}

#ifndef _WIN32_WCE
void CFileView::Dump(CDumpContext& dc) const
{
	CMFCListView::Dump(dc);
}
#endif
#endif //_DEBUG

// CFileView message handlers

void CFileView::OnInitialUpdate()
{
	CMFCListView::OnInitialUpdate();

	if (!m_bInitialized)
	{
		m_bInitialized = TRUE;

		m_pFileSystem.SetParent(this->m_hWnd);

		GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle()
			| LVS_EX_DOUBLEBUFFER |LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

		CRect rectClient;
		GetListCtrl().GetClientRect(&rectClient);

		const int nSizeColumnLength = SIZE_COLUMN_LENGTH;
		const int nDateColumnLength = DATE_COLUMN_LENGTH;
		const int nAttrColumnLength = ATTR_COLUMN_LENGTH;
		const int nNameColumnLength = rectClient.Width() - nSizeColumnLength - nDateColumnLength - nAttrColumnLength;

		GetListCtrl().InsertColumn(0, _T("Name"), LVCFMT_LEFT, nNameColumnLength);
		GetListCtrl().InsertColumn(1, _T("Size"), LVCFMT_RIGHT, nSizeColumnLength);
		GetListCtrl().InsertColumn(2, _T("Date"), LVCFMT_RIGHT, nDateColumnLength);
		GetListCtrl().InsertColumn(3, _T("Attr"), LVCFMT_RIGHT, nAttrColumnLength);
	}
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CMFCListView::OnSize(nType, cx, cy);
	ResizeListCtrl();
}

void CFileView::OnDblClickEntry(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pResult != NULL) *pResult = 0;
	if (pItemActivate->iItem != -1)
	{
		DoubleClickEntry(pItemActivate->iItem);
	}
}

BOOL CFileView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg != NULL)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
				case VK_MENU:
				{
					m_bMenuPressed = TRUE;
					break;
				}
			}
		}
		if (pMsg->message == WM_KEYUP)
		{
			m_bCtrlPressed = (GetAsyncKeyState(VK_CONTROL) != 0);
			m_bShiftPressed = (GetAsyncKeyState(VK_SHIFT) != 0);

			switch (pMsg->wParam)
			{
				case VK_MENU:
				{
					m_bMenuPressed = FALSE;
					break;
				}
			}
		}
	}

	return CMFCListView::PreTranslateMessage(pMsg);
}

void CFileView::ResizeListCtrl()
{
	HDITEM hdItem = { 0 };
	hdItem.cxy = 0;
	hdItem.mask = HDI_WIDTH;
	if (GetListCtrl().GetSafeHwnd() != NULL)
	{
		CRect rectClient;
		GetListCtrl().GetClientRect(&rectClient);

		const int nSizeColumnLength = SIZE_COLUMN_LENGTH;
		const int nDateColumnLength = DATE_COLUMN_LENGTH;
		const int nAttrColumnLength = ATTR_COLUMN_LENGTH;
		const int nNameColumnLength = rectClient.Width() - nSizeColumnLength - nDateColumnLength - nAttrColumnLength;

		CMFCHeaderCtrl& pHeaderCtrl = GetListCtrl().GetHeaderCtrl();
		if (pHeaderCtrl.GetItem(0, &hdItem))
		{
			hdItem.cxy = nNameColumnLength;
			if (pHeaderCtrl.SetItem(0, &hdItem))
			{
				GetListCtrl().Invalidate();
				GetListCtrl().UpdateWindow();
			}
		}
	}
}

void CFileView::DoubleClickEntry(int nIndex)
{
	ASSERT(GetListCtrl().m_hWnd != NULL);
	CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nIndex));
	ASSERT(pFileData != NULL);
	if (pFileData->IsFolder())
	{
		if (pFileData->GetFileName().CompareNoCase(_T(".")) != 0)
		{
			CString strFolder = m_pFileSystem.GetFolder();
			if (pFileData->GetFileName().CompareNoCase(_T("..")) != 0)
			{
				strFolder += pFileData->GetFileName();
				strFolder += _T("\\");
			}
			else
			{
				strFolder.SetAt(strFolder.GetLength() - 1, _T('\0'));
				strFolder = strFolder.Left(strFolder.ReverseFind(_T('\\')));
				strFolder += _T("\\");
			}
			if (m_pFileSystem.SetFolder(strFolder))
			{
				if (Refresh())
				{
					ASSERT_VALID(m_pMainFrame);
					m_pMainFrame->HideMessageBar();
				}
				else // operation failed
				{
					ASSERT_VALID(m_pMainFrame);
					m_pMainFrame->RecalcLayout();
				}
			}
			else // operation failed
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
			}
		}
	}
	else
	{
		CString strFolder = m_pFileSystem.GetFolder();
		CString strFilePath = strFolder + pFileData->GetFileName();
		if (IsApplication(strFilePath))
		{
			if ((int) ShellExecute(m_hWnd, _T("open"), strFilePath, NULL, strFolder, SW_SHOWNORMAL) > 32)
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->HideMessageBar();
			}
			else
			{
				DisplayErrorBox(m_pFileSystem.GetWindow(), _T("ShellExecute"), GetLastError());
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
			}
		}
	}
}

BOOL CFileView::Refresh()
{
	CString strListItem;
	GetListCtrl().SetRedraw(FALSE);
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (nListItem != -1)
	{
		strListItem = GetListCtrl().GetItemText(nListItem, 0);
	}
	VERIFY(GetListCtrl().DeleteAllItems());
	BOOL bRetVal = m_pFileSystem.Refresh();
	const int nSize = m_pFileSystem.GetSize();
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(nIndex);
		ASSERT(pFileData != NULL);
		const int nListItem = GetListCtrl().InsertItem(GetListCtrl().GetItemCount(), pFileData->GetFileName());
		GetListCtrl().SetItemText(nListItem, 1, pFileData->FormatSize());
		GetListCtrl().SetItemText(nListItem, 2, pFileData->FormatDate());
		GetListCtrl().SetItemText(nListItem, 3, pFileData->FormatAttr());
		GetListCtrl().SetItemData(nListItem, nIndex);

		SHFILEINFO pshFileInfo = { 0 };
		SHGetFileInfo(
			(LPCTSTR)pFileData->GetFileName(),
			pFileData->IsFolder() ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL,
			&pshFileInfo, sizeof(pshFileInfo),
			SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
		LVITEM lviItem = { 0 };
		lviItem.mask = LVIF_IMAGE;
		lviItem.iItem = nListItem;
		lviItem.iSubItem = 0;
		lviItem.iImage = (pFileData->GetFileName().CompareNoCase(_T("..")) == 0) ? 0 : pshFileInfo.iIcon;
		VERIFY(GetListCtrl().SetItem(&lviItem));
	}
	GetListCtrl().Sort(0, TRUE, FALSE);
	nListItem = 0;
	if (!strListItem.IsEmpty())
	{
		for (int nIndex = 0; nIndex < GetListCtrl().GetItemCount(); nIndex++)
		{
			if (strListItem.CompareNoCase(GetListCtrl().GetItemText(nIndex, 0)) == 0)
			{
				nListItem = nIndex;
				break;
			}
		}
	}
	GetListCtrl().SetItemState(nListItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	GetListCtrl().SetRedraw(TRUE);
	GetListCtrl().UpdateWindow();
	ResizeListCtrl();
	ASSERT_VALID(m_pMainFrame);
	m_pMainFrame->SetStatusBar(m_bIsLeftPane, m_pFileSystem.GetFolder());
	return bRetVal;
}

BOOL CFileView::ViewFile()
{
	return TRUE;
}

BOOL CFileView::EditFile()
{
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != NULL);
		if (!pFileData->IsFolder())
		{
			CString strFolder = m_pFileSystem.GetFolder();
			CString strFilePath = strFolder + pFileData->GetFileName();
			if (m_pFileSystem.EditFile(strFilePath))
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->HideMessageBar();
				return TRUE;
			}
			else
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
				return FALSE;
			}
		}
	}
	return FALSE;
}

BOOL CFileView::CopyFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != NULL);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.CopyFile(&pDestination->m_pFileSystem, &arrSelection) && pDestination->Refresh() && Refresh())
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return TRUE;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CFileView::MoveFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != NULL);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.MoveFile(&pDestination->m_pFileSystem, &arrSelection) && pDestination->Refresh() && Refresh())
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return TRUE;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CFileView::NewFolder(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != NULL);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.NewFolder(&pDestination->m_pFileSystem, &arrSelection) && Refresh())
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return TRUE;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CFileView::DeleteFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != NULL);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.DeleteFile(&pDestination->m_pFileSystem, &arrSelection) && Refresh())
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return TRUE;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return FALSE;
		}
	}
	return FALSE;
}
