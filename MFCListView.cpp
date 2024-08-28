/* Copyright (C) 2022-2024 Stefan-Mihai MOGA
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

// MFCListView.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "MFCListView.h"
#include "FileView.h"

// CMFCListView

IMPLEMENT_DYNCREATE(CMFCListView, CFormView)

CMFCListView::CMFCListView()
	: CFormView(CMFCListView::IDD)
{
}

CMFCListView::~CMFCListView()
{
}

void CMFCListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCListView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCListView diagnostics

#ifdef _DEBUG
void CMFCListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMFCListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CMFCListView message handlers

int CMFCListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_mfcListCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_EDITLABELS, CRect(0, 0, 0, 0), this, ID_MFCLISTCTRL))
		return -1;

	return 0;
}

void CMFCListView::OnDestroy()
{
	CFormView::OnDestroy();

	VERIFY(m_mfcListCtrl.DestroyWindow());
}

void CMFCListView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (m_mfcListCtrl.GetSafeHwnd() != nullptr)
		m_mfcListCtrl.MoveWindow(0, 0, cx, cy);
}

BOOL CMFCListView::OnEraseBkgnd(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	// return CFormView::OnEraseBkgnd(pDC);

	return TRUE;
}

void CMFCListView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0, 0));
}

BOOL CMFCListView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_mfcListCtrl.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
