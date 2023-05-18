/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// FileView.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "FileView.h"
#include "MainFrame.h"
#include "ChangeDriveDlg.h"
#include "NewFolderDlg.h"
#include "ViewMetaFileDlg.h"
#include "ViewRichFileDlg.h"
#include "ViewTextFileDlg.h"

#include <Shobjidl.h>
#include <ShlObj.h>
#include <windowsx.h>

// CFileView

IMPLEMENT_DYNCREATE(CFileView, CMFCListView)

	CFileView::CFileView()
{
	m_bInitialized = false;
	m_pMainFrame = nullptr;
	m_bIsLeftPane = true;

	m_bShiftPressed = false;
	m_bCtrlPressed = false;
	m_bMenuPressed = false;

	GetListCtrl().m_pFileSystem = &m_pFileSystem;
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CMFCListView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, ID_MFCLISTCTRL, OnDblClickEntry)
	ON_NOTIFY(NM_RCLICK, ID_MFCLISTCTRL, OnContextMenu)
	ON_NOTIFY(LVN_ENDLABELEDIT, ID_MFCLISTCTRL, OnEndLabelEdit)
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

class CItemIdListReleaser {
public:
	explicit CItemIdListReleaser(ITEMIDLIST * idList) : _idList(idList) {}
	~CItemIdListReleaser() { if (_idList) CoTaskMemFree(_idList); }
private:
	ITEMIDLIST * _idList;
};

class CComInterfaceReleaser {
public:
	explicit CComInterfaceReleaser(IUnknown * i) : _i(i) {}
	~CComInterfaceReleaser() { if (_i) _i->Release(); }
private:
	IUnknown * _i;
};

class CItemIdArrayReleaser {
public:
	explicit CItemIdArrayReleaser(const std::vector<ITEMIDLIST*>& idArray) : _array(idArray) {}
	~CItemIdArrayReleaser() {
		for (ITEMIDLIST* item : _array)
			CoTaskMemFree(item);
	}

	CItemIdArrayReleaser& operator=(const CItemIdArrayReleaser&) = delete;
private:
	const std::vector<ITEMIDLIST*>& _array;
};

bool openShellContextMenuForObject(const std::wstring &path, int xPos, int yPos, void* parentWindow)
{
	ITEMIDLIST * id = 0;
	std::wstring windowsPath = path;
	std::replace(windowsPath.begin(), windowsPath.end(), '/', '\\');
	HRESULT result = SHParseDisplayName(windowsPath.c_str(), 0, &id, 0, 0);
	if (!SUCCEEDED(result) || !id)
		return false;
	CItemIdListReleaser idReleaser(id);

	IShellFolder* ifolder = 0;

	LPCITEMIDLIST idChild = 0;
	result = SHBindToParent(id, IID_IShellFolder, (void**)&ifolder, &idChild);
	if (!SUCCEEDED(result) || !ifolder)
		return false;
	CComInterfaceReleaser ifolderReleaser(ifolder);

	IContextMenu* imenu = 0;
	result = ifolder->GetUIObjectOf((HWND)parentWindow, 1, (const ITEMIDLIST **)&idChild, IID_IContextMenu, 0, (void**)&imenu);
	if (!SUCCEEDED(result) || !ifolder)
		return false;
	CComInterfaceReleaser menuReleaser(imenu);

	HMENU hMenu = CreatePopupMenu();
	if (!hMenu)
		return false;
	if (SUCCEEDED(imenu->QueryContextMenu(hMenu, 0, 1, 0x7FFF, CMF_NORMAL)))
	{
		int iCmd = TrackPopupMenuEx(hMenu, TPM_RETURNCMD, xPos, yPos, (HWND)parentWindow, nullptr);
		if (iCmd > 0)
		{
			CMINVOKECOMMANDINFOEX info = { 0 };
			info.cbSize = sizeof(info);
			info.fMask = CMIC_MASK_UNICODE;
			info.hwnd = (HWND)parentWindow;
			info.lpVerb = MAKEINTRESOURCEA(iCmd - 1);
			info.lpVerbW = MAKEINTRESOURCEW(iCmd - 1);
			info.nShow = SW_SHOWNORMAL;
			imenu->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);
		}
	}
	DestroyMenu(hMenu);

	return true;
}

void CFileView::OnInitialUpdate()
{
	CMFCListView::OnInitialUpdate();

	if (!m_bInitialized)
	{
		m_bInitialized = true;

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
	if (pResult != nullptr) *pResult = 0;
	if (pItemActivate->iItem != -1)
	{
		DoubleClickEntry(pItemActivate->iItem);
	}
}

void CFileView::OnContextMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CPoint pt(pItemActivate->ptAction);
	POINT p;
	p.x = pt.x;
	p.y = pt.y;
	::ClientToScreen(pNMHDR->hwndFrom, &p);
	if (pResult != nullptr) *pResult = 0;
	if (pItemActivate->iItem != -1)
	{
		// DoubleClickEntry(pItemActivate->iItem);
		ASSERT(GetListCtrl().m_hWnd != nullptr);
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(pItemActivate->iItem));
		ASSERT(pFileData != nullptr);
		if (pFileData->IsFolder())
		{
			if (pFileData->GetFileName().CompareNoCase(_T("..")) != 0)
			{
				const std::wstring strFilePath = m_pFileSystem.GetCurrentFolder() + pFileData->GetFileName() + _T("\\");
				openShellContextMenuForObject(strFilePath, p.x, p.y, this->m_hWnd);
			}
		}
		else
		{
			CString strFolder = m_pFileSystem.GetCurrentFolder();
			const std::wstring strFilePath = strFolder + pFileData->GetFileName();
			openShellContextMenuForObject(strFilePath, p.x, p.y, this->m_hWnd);
		}
	}
}

void CFileView::OnEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	if (pResult != nullptr) *pResult = 0;
	if (pDispInfo->item.iItem != -1)
	{
		RenameClickEntry(pDispInfo->item.iItem, pDispInfo->item.pszText);
	}
}

BOOL CFileView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg != nullptr)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
				case VK_MENU:
				{
					m_bMenuPressed = true;
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
					m_bMenuPressed = false;
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
	if (GetListCtrl().GetSafeHwnd() != nullptr)
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
	ASSERT(GetListCtrl().m_hWnd != nullptr);
	CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nIndex));
	ASSERT(pFileData != nullptr);
	if (pFileData->IsFolder())
	{
		if (pFileData->GetFileName().CompareNoCase(_T(".")) != 0)
		{
			CString strFolder = m_pFileSystem.GetCurrentFolder();
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
			if (m_pFileSystem.SetCurrentFolder(strFolder))
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
		CString strFolder = m_pFileSystem.GetCurrentFolder();
		CString strFilePath = strFolder + pFileData->GetFileName();
		if (IsApplication(strFilePath))
		{
			if (ShellExecute(m_hWnd, _T("open"), strFilePath, nullptr, strFolder, SW_SHOWNORMAL) > (HINSTANCE)32)
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

bool CFileView::RenameClickEntry(int nIndex, CString strText)
{
	ASSERT(GetListCtrl().m_hWnd != nullptr);
	CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nIndex));
	ASSERT(pFileData != nullptr);
	CString strFolder = m_pFileSystem.GetCurrentFolder();
	CString strOldFilePath = strFolder + pFileData->GetFileName();
	TRACE(_T("strOldFilePath = %s\n"), static_cast<LPCWSTR>(strOldFilePath));
	CString strNewFilePath = strFolder + strText;
	TRACE(_T("strNewFilePath = %s\n"), static_cast<LPCWSTR>(strNewFilePath));
	if (m_pFileSystem.RenameFile(strOldFilePath, strNewFilePath) && Refresh(&strText))
	{
		ASSERT_VALID(m_pMainFrame);
		m_pMainFrame->HideMessageBar();
		return true;
	}
	else
	{
		ASSERT_VALID(m_pMainFrame);
		m_pMainFrame->RecalcLayout();
		return false;
	}
}

bool CFileView::Refresh(CString* strNewFolderName)
{
	CString strListItem;
	GetListCtrl().SetRedraw(FALSE);
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (nListItem != -1)
	{
		strListItem = GetListCtrl().GetItemText(nListItem, 0);
	}
	if (strNewFolderName != nullptr)
	{
		strListItem = *strNewFolderName;
	}
	VERIFY(GetListCtrl().DeleteAllItems());
	bool bRetVal = m_pFileSystem.Refresh();
	const int nSize = m_pFileSystem.GetSize();
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		CFileData* pFileData = m_pFileSystem.GetAt(nIndex);
		ASSERT(pFileData != nullptr);
		nListItem = GetListCtrl().InsertItem(GetListCtrl().GetItemCount(), pFileData->GetFileName());
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
	m_pMainFrame->SetStatusBar(m_bIsLeftPane, m_pFileSystem.GetCurrentFolder());
	return bRetVal;
}

bool CFileView::ResetView()
{
	if (m_pFileSystem.SetCurrentFolder(_T("C:\\")) && Refresh(nullptr))
	{
		ASSERT_VALID(m_pMainFrame);
		m_pMainFrame->HideMessageBar();
		return true;
	}
	else
	{
		ASSERT_VALID(m_pMainFrame);
		m_pMainFrame->RecalcLayout();
		return false;
	}
}

bool CFileView::ChangeDrive()
{
	CChangeDriveDlg dlgChangeDrive(this);
	if (dlgChangeDrive.DoModal() == IDOK)
	{
		if (m_pFileSystem.SetCurrentFolder(dlgChangeDrive.m_strNewDriveName) && Refresh(nullptr))
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return true;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return false;
		}
	}
	return true;
}

bool CFileView::ViewFile()
{
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != nullptr);
		if (!pFileData->IsFolder())
		{
			CString strFolder = m_pFileSystem.GetCurrentFolder();
			CString strFilePath = strFolder + pFileData->GetFileName();
			/*if (m_pFileSystem.ViewFile(strFilePath))
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->HideMessageBar();
				return true;
			}
			else
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
				return false;
			}*/
			if (IsTextFile(strFilePath))
			{
				CViewTextFileDlg dlgViewTextFile(this);
				dlgViewTextFile.m_strFilePath = strFilePath;
				dlgViewTextFile.DoModal();
				return true;
			}
			else
			{
				if (IsRichTextFile(strFilePath))
				{
					CViewRichFileDlg dlgViewRichFile(this);
					dlgViewRichFile.m_strFilePath = strFilePath;
					dlgViewRichFile.DoModal();
					return true;
				}
				else
				{
					if (IsMetaFile(strFilePath))
					{
						CViewMetaFileDlg dlgViewMetaFile(this);
						dlgViewMetaFile.m_strFilePath = strFilePath;
						dlgViewMetaFile.DoModal();
						return true;
					}
					else
					{
						MessageBox(_T("The selected file format cannot be viewed!\n Text, RichText or Metafile formats are supported"), _T("View File Warning"), MB_OK | MB_ICONWARNING);
						return true;
					}

				}
			}
		}
	}
	return false;
}

bool CFileView::EditFile()
{
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED);
	if (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != nullptr);
		if (!pFileData->IsFolder())
		{
			CString strFolder = m_pFileSystem.GetCurrentFolder();
			CString strFilePath = strFolder + pFileData->GetFileName();
			if (m_pFileSystem.EditFile(strFilePath))
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->HideMessageBar();
				return true;
			}
			else
			{
				ASSERT_VALID(m_pMainFrame);
				m_pMainFrame->RecalcLayout();
				return false;
			}
		}
	}
	return false;
}

bool CFileView::CopyFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != nullptr);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.CopyFile(&pDestination->m_pFileSystem, &arrSelection) && pDestination->Refresh() && Refresh(nullptr))
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return true;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return false;
		}
	}
	return false;
}

bool CFileView::MoveFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != nullptr);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.MoveFile(&pDestination->m_pFileSystem, &arrSelection) && pDestination->Refresh() && Refresh(nullptr))
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return true;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return false;
		}
	}
	return false;
}

bool CFileView::NewFolder(CFileView* pDestination)
{
	CNewFolderDlg dlgNewFolder(m_pMainFrame);
	if (dlgNewFolder.DoModal() == IDOK)
	{
		if (m_pFileSystem.NewFolder(&pDestination->m_pFileSystem, dlgNewFolder.m_strNewFolderName) && Refresh(&dlgNewFolder.m_strNewFolderName))
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return true;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return false;
		}
	}
	return false;
}

bool CFileView::DeleteFile(CFileView* pDestination)
{
	CFileList arrSelection;
	int nListItem = GetListCtrl().GetNextItem(-1, LVIS_SELECTED);
	while (nListItem != -1)
	{
		CFileData* pFileData = m_pFileSystem.GetAt((int)GetListCtrl().GetItemData(nListItem));
		ASSERT(pFileData != nullptr);
		arrSelection.Add(pFileData);
		nListItem = GetListCtrl().GetNextItem(nListItem, LVIS_SELECTED);
	}
	if (arrSelection.GetCount() > 0)
	{
		if (m_pFileSystem.DeleteFile(&pDestination->m_pFileSystem, &arrSelection) && Refresh(nullptr))
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->HideMessageBar();
			return true;
		}
		else
		{
			ASSERT_VALID(m_pMainFrame);
			m_pMainFrame->RecalcLayout();
			return false;
		}
	}
	return false;
}
