/*
Module : HlinkCtrl.cpp
Purpose: Implementation for a MFC class for a static text control class with hyperlink support
Created: PJN / 16-06-1997
History: PJN / 24-06-1997 hyperlinks are now colored ala IE
         PJN / 15-07-1997 Now supports ShrinkToFit
         PJN / 11-09-1997 1. Added support for a highlight look which includes a highlight color and
                          a shadowed look. Also fixed a bug relating to the Edit controls context menu.
                          2. Also included is a new context menu ala IE3
         PJN / 06-11-1997 1. Improved drawing of control by handling WM_CTLCOLOR through MFC message reflection
                          2. class now derived from CStatic as it should have been from the beginning
                          3. Dropped support for shrink to fit as now no need
                          4. Description is now taken from controls window text
                          5. Now using more standard visited and unvisited colors
                          6. Dropped support for optional underlying and drop shadow effects
                          7. streamlined some of the functions declarations
                          8. Wait cursor is now shown when a shortcut is being saved
                          9. Context menu for control can now be turned off if so desired
         PJN / 08-12-1997 1. Removed ON_COMMAND(ID_POPUP_OPEN, OnOpen) from #define which was causing 
                             to the hyperlink correctly
                          2. Removed a level 4 warning which was being generated when building in release mode  
         PJN / 09-01-1998 1. Removed duplicate OnAddToFavorites and OnAddToDesktop functions
         PJN / 29-03-1999 1. General code tidy up
                          2. Unicode enabled all the source code
                          3. Now uses new IDC_HAND cursor in preference to my own hand cursor
                          4. Removed a number of unused member variables
         PJN / 11-12-1999 1. Now supports a disabled hyperlink cursor similar to the offline cursor in IE.
         PJN / 12-01-2000 1. The zip file lists disabled.cur in the home directory, not in the RES directory 
                          where it belongs.
                          2. When compiling for UNICODE, the copy-to-clipboard feature sets the incorrect clipboard 
                          type CF_TEXT, not CF_UNICODETEXT. This results in only the first character being available 
                          in the clipboard.
         PJN / 03-04-2002 1. Fixed a problem where the underlined style was not being set for the control when the 
                          "No wrap" window style was applied.
                          2. Now includes copyright message in the source code and documentation.
         PJN / 21-12-2006 1. Updated copyright details
                          2. Optimized CHLinkCtrl constructor code
                          3. Optimized CHLinkPage constructor code
                          4. Code now compiles cleanly on VC 2005
                          5. Code now only uses ShellExecute approach to executing hyperlinks
                          6. Stripped context menu support from the class. This provides for a more leaner control 
                          implementation. Derived classes are of course free to implement their own functionality
                          7. Reviewed all TRACE statements for correctness
                          8. Renamed module to be HLinkCtrl to be consistent with the name of the class
                          9. Hyperlink is now executed on mouse up instead of on mouse down. This is to maintain
                          consistency with how a command button operates
         PJN / 27-01-2007 1. Updated copyright details
                          2. Class now by default sports a tooltip with the hyperlink text as its data.
                          3. Class now only shows the underline when the hyperlink is highlighted.
                          4. The "EnableLink" property has now been removed. Instead you can use the standard
                          windows WS_DISABLED style. By also doing this, the code now no longer requires the disabled
                          cursor resource.
                          5. Class now reverts to standard static control colors and style when disabled
                          6. Removed code which loads up the IDC_HLINKCTRL_ENABLED_CURSOR cursor.  This now means
                          that the code has no dependency on any resources which you need to add to your project.
         PJN / 02-02-2007 1. Fixed a small redraw glitch when you use "Use the System Font" setting in the dialog
                          resource editor in VC 2005. 
                          2. Fixed a small redraw glitch when the enabled state of the control is changed.
         PJN / 21-12-2008 1. Updated copyright details
                          2. Removed VC 6 style AppWizard comments from the code
                          3. The code has now been updated to support VC 2005 or later only
                          4. Code now compiles cleanly using Code Analysis (/analyze)
                          5. Made the "Open" method virtual
                          6. The verb passed to ShellExecute can now be customized.
                          7. Notifications for the static control are now enabled via a WM_NCHITTEST message handler
                          8. All the default colors and behaviour for the hyperlink are now taken from the users 
                          default settings at HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Settings|Main. 
                          These settings include a new setting which controls the underline behaviour. The programmer 
                          can still change these values if you so desire.
                          9. Fixed a redraw glitch when the control is sent what looks like unsolicited reflected
                          CTLCOLOR messages from the parent even when it does not look like the control needs
                          repainting. The control now does not draw transparently, instead it uses SetDCBrushColor and
                          GetStockObject(DC_BRUSH). Please note that this means that the control will only work on
                          Windows 2000 or later and requires _WIN32_WINNT to be defined >= 0x0500.
         PJN / 22-12-2008 1. The code now uses TrackMouseEvent to implement support for highlighting instead of 
                          capturing the mouse.
         PJN / 25-01-2009 1. Updated copyright details.
                          2. After some research, the control is now again drawn transparently. This means that the 
                          Windows 2000 minimum requirement for the code has been dropped as well as the need to define
                          _WIN32_WINNT >= 0x0500.
         PJN / 23-06-2013 1. Updated copyright details.
                          2. Updated the sample app to clean compile on VC 2010 and later.
                          3. Made a number of Getter methods of the CHLinkCtrl class const.
                          4. Updated the zip file to include the correct project files. Thanks to "Franc" for reporting 
                          this issue.
         PJN / 28-06-2013 1. Updated the sample app to draw a hatched background to verify that the hyperlink class
                          works correctly where the parent window has a custom drawn background.
         PJN / 18-01-2015 1. Updated copyright details.
                          2. Updated the code and sample app to clean compile on VC 2013
         PJN / 22-11-2015 1. Verified the code compiles cleanly on VC 2015.
                          2. Updated the sample apps main icon.
         PJN / 15-10-2017 1. Updated copyright details.
                          2. Replaced NULL with nullptr throughout the codebase. This means that the code now requires 
                          VC 2010 at a minimum to compile
                          3. Removed some unnecessary defines from HLinkCtrl.cpp
                          4. Replaced LONG with LSTATUS for all registry functions.
                          5. Replaced raw registry API calls throughout the code with ATL::CRegKey class
                          6. Replaced "BOOL" values throughout the code with "bool"
                          7. Replaced CString::operator LPC*STR() calls with CString::GetString calls
         PJN / 17-02-2018 1. Updated copyright details.
                          2. Reworked the class to use STN_CLICKED notifications for handling the hyperlink click 
                          instead of via OnLButtonUp. Please note that the control now requires the SS_NOTIFY style to
                          be set. Thanks to "sen" for reporting this issue.
                          3. Added SAL annotations to all the code
         PJN / 06-08-2018 1. Fixed a number of C++ core guidelines compiler warnings. These changes mean that the code will 
                          now only compile on VC 2017 or later.
                          2. Replaced enum with enum class throughout the codebase
         PJN / 02-06-2019 1. Updated copyright details.
                          2. Updated the code to clean compile on VC 2019
         PJN / 11-09-2019 1. Replaced enum with enum class throughout the code
                          2. Fixed a number of compiler warnings when the code is compiled with VS 2019 Preview
         PJN / 19-12-2019 1. Fixed various Clang-Tidy static code analysis warnings in the code.
         PJN / 01-03-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 13-04-2020 1. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 27-11-2021 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
         PJN / 21-02-2022 1. Updated copyright details.
                          2. Updated the code to use C++ uniform initialization for all variable declarations

Copyright (c) 1997 - 2022 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code.

*/


/////////////////////////// Includes //////////////////////////////////////////

#include "stdafx.h"
#include "HLinkCtrl.h"


/////////////////////////// Macros & Defines //////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG


/////////////////////////// Implementation ////////////////////////////////////

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CHLinkCtrl, CStatic) //NOLINT(modernize-avoid-c-arrays)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_NCHITTEST()
#pragma warning(suppress: 26454)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &CHLinkCtrl::OnToolTipTextA)
#pragma warning(suppress: 26454)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &CHLinkCtrl::OnToolTipTextW)
	ON_MESSAGE(WM_SETTEXT, &CHLinkCtrl::OnSetText)
	ON_WM_MOUSELEAVE()
	ON_WM_ENABLE()
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT(STN_CLICKED, &CHLinkCtrl::OnStnClicked)
END_MESSAGE_MAP()

#pragma warning(suppress: 26455)
CHLinkCtrl::CHLinkCtrl() : m_bUseHighlight{ true },
m_State{ LinkState::NOT_VISITED },
m_OldState{ LinkState::NOT_VISITED },
m_bToolTips{ true },
m_bTrackLeave{ false }
{
	//Load up the hand cursor
	const CWinApp* pApp{ AfxGetApp() };
#pragma warning(suppress: 26496)
	AFXASSUME(pApp != nullptr);
	m_hLinkCursor = pApp->LoadStandardCursor(IDC_HAND);

	//Get the initial behaviors from the settings as stored in the Control Panel
	m_Color = GetDefaultLinkColor(_T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Anchor Color"), GetSysColor(COLOR_HOTLIGHT));
	const COLORREF clrWindow{ GetSysColor(COLOR_WINDOW) };
	const COLORREF clrText{ GetSysColor(COLOR_WINDOWTEXT) };
	const COLORREF clrDefaultVisitedColor{ RGB((GetRValue(clrWindow) + GetRValue(clrText)) / 2, GetGValue(clrText), (GetBValue(clrWindow) + GetBValue(clrText)) / 2) };
	m_VisitedColor = GetDefaultLinkColor(_T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Anchor Color Visited"), clrDefaultVisitedColor);
	m_HighlightColor = GetDefaultLinkColor(_T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Anchor Color Hover"), RGB(255, 0, 0));
	m_bUseHighlight = GetDefaultLinkBoolean(_T("Software\\Microsoft\\Internet Explorer\\Settings"), _T("Use Anchor Hover Color"), true);
	m_Underline = GetDefaultLinkTriStateSetting(_T("Software\\Microsoft\\Internet Explorer\\Main"), _T("Anchor Underline"), TriStateSetting::YES);
}

COLORREF CHLinkCtrl::GetDefaultLinkColor(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ COLORREF clrDefault)
{
	//What will be the return value from this function 
	COLORREF clrFound{ clrDefault };

	//Open the key which contains the users link settings
	ATL::CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, pszSubKey, KEY_READ) == ERROR_SUCCESS)
	{
		//Then query the value for its size
		ULONG nChars{ 0 };
		LSTATUS lResult{ key.QueryStringValue(lpszEntry, nullptr, &nChars) };
		if (lResult == ERROR_SUCCESS)
		{
			//The get the actual value
			CString sValue;
			lResult = key.QueryStringValue(lpszEntry, sValue.GetBuffer(nChars), &nChars);
			sValue.ReleaseBuffer();
			if (lResult == ERROR_SUCCESS)
			{
				WORD wRed{ GetRValue(clrFound) };
				WORD wGreen{ GetGValue(clrFound) };
				WORD wBlue{ GetBValue(clrFound) };
				_stscanf_s(sValue.GetString(), _T("%hu,%hu,%hu"), &wRed, &wGreen, &wBlue);
				clrFound = RGB(wRed, wGreen, wBlue);
			}
		}
	}

	return clrFound;
}

bool CHLinkCtrl::GetDefaultLinkBoolean(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ bool bDefault)
{
	//What will be the return value from this function 
	bool bReturn{ bDefault };

	//Open the key which contains the users link settings
	ATL::CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, pszSubKey, KEY_READ) == ERROR_SUCCESS)
	{
		//Then query the value for its size
		ULONG nChars{ 0 };
		LSTATUS lResult{ key.QueryStringValue(lpszEntry, nullptr, &nChars) };
		if (lResult == ERROR_SUCCESS)
		{
			//The get the actual value
			CString sValue;
			lResult = key.QueryStringValue(lpszEntry, sValue.GetBuffer(nChars), &nChars);
			sValue.ReleaseBuffer();
			if (lResult == ERROR_SUCCESS)
			{
				if (sValue.CompareNoCase(_T("no")) == 0)
					bReturn = false;
				else
					bReturn = true;
			}
		}
	}

	return bReturn;
}

CHLinkCtrl::TriStateSetting CHLinkCtrl::GetDefaultLinkTriStateSetting(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ TriStateSetting defaultSetting)
{
	//What will be the return value from this function 
	TriStateSetting setting{ defaultSetting };

	//Open the key which contains the users link settings
	ATL::CRegKey key;
	if (key.Open(HKEY_CURRENT_USER, pszSubKey, KEY_READ) == ERROR_SUCCESS)
	{
		//Then query the value for its size
		ULONG nChars{ 0 };
		LSTATUS lResult{ key.QueryStringValue(lpszEntry, nullptr, &nChars) };
		if (lResult == ERROR_SUCCESS)
		{
			//The get the actual value
			CString sValue;
			lResult = key.QueryStringValue(lpszEntry, sValue.GetBuffer(nChars), &nChars);
			sValue.ReleaseBuffer();
			if (lResult == ERROR_SUCCESS)
			{
				if (sValue.CompareNoCase(_T("no")) == 0)
					setting = TriStateSetting::NO;
				else if (sValue.CompareNoCase(_T("hover")) == 0)
					setting = TriStateSetting::HOVER;
				else
					setting = TriStateSetting::YES;
			}
		}
	}

	return setting;
}

void CHLinkCtrl::SetHyperLink(_In_ const CString& sLink)
{
	m_sLink = sLink;
	if (GetSafeHwnd())
		Invalidate();
}

void CHLinkCtrl::SetLinkColor(_In_ const COLORREF& color)
{
	m_Color = color;
	if (GetSafeHwnd())
		Invalidate();
}

void CHLinkCtrl::SetVisitedLinkColor(_In_ const COLORREF& color)
{
	m_VisitedColor = color;
	if (GetSafeHwnd())
		Invalidate();
}

void CHLinkCtrl::SetHighlightLinkColor(_In_ const COLORREF& color)
{
	m_HighlightColor = color;
	if (GetSafeHwnd())
		Invalidate();
}

void CHLinkCtrl::SetToolTips(_In_ bool bToolTip)
{
	m_bToolTips = bToolTip;
	EnableToolTips(bToolTip);
}

void CHLinkCtrl::SetUnderline(_In_ TriStateSetting underline)
{
	m_Underline = underline;
	if (GetSafeHwnd())
		Invalidate();
}

#pragma warning(suppress: 26434 26440)
BOOL CHLinkCtrl::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
	::SetCursor(m_hLinkCursor); //Use the hand cursor
	return TRUE;
}

#pragma warning(suppress: 26434)
void CHLinkCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	//Nothing to do if we're not using highlighting
	if (m_bUseHighlight)
	{
		CRect rc;
		GetClientRect(rc);
		if (rc.PtInRect(point))
		{
			if (m_State != LinkState::HIGHLIGHTED)
			{
				m_OldState = m_State;
				m_State = LinkState::HIGHLIGHTED;
				Invalidate();
			}

			//Ask that we be informed when the mouse leaves the button
			if (!m_bTrackLeave)
			{
				TRACKMOUSEEVENT tme{};
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = GetSafeHwnd();
				tme.dwFlags = TME_LEAVE;
				TrackMouseEvent(&tme);
				m_bTrackLeave = true;
			}
		}
		else
		{
			//Return the control to its non highlight state
			if (m_State == LinkState::HIGHLIGHTED)
			{
				m_State = m_OldState;
				Invalidate();
			}
		}
	}

	//Let the base class do its thing
	__super::OnMouseMove(nFlags, point);
}

#pragma warning(suppress: 26434)
void CHLinkCtrl::OnMouseLeave()
{
	//Return the control to its non highlight state
	if (m_State == LinkState::HIGHLIGHTED)
	{
		m_State = m_OldState;
		Invalidate();
	}
	m_bTrackLeave = false;
}

bool CHLinkCtrl::Open()
{
	//What will be the return value from this function (assume the worst)
	bool bSuccess = false;

	CWaitCursor cursor;
	HINSTANCE hRun = ShellExecute(GetParent()->GetSafeHwnd(), m_sShellExecuteVerb.GetLength() ? m_sShellExecuteVerb : nullptr, m_sLink, nullptr, nullptr, SW_SHOW);
#pragma warning(suppress: 26490)
	if (reinterpret_cast<DWORD_PTR>(hRun) <= 32)
	{
		TRACE(_T("CHLinkCtrl::Open, Failed to invoke URL using ShellExecute\n"));
	}
	else
		bSuccess = true;

	return bSuccess;
}

#pragma warning(suppress: 26434 26440)
LRESULT CHLinkCtrl::OnNcHitTest(CPoint /*point*/)
{
	//This will ensure the control generates notifications
	return HTCLIENT;
}

LRESULT CHLinkCtrl::OnSetText(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	//let the base class do its thing
	const LRESULT lResult = Default();

	//Update ourselves
	Invalidate();
	UpdateWindow();

	return lResult;
}

#pragma warning(suppress: 26434)
void CHLinkCtrl::OnEnable(BOOL bEnable)
{
	//Let the base class do its thing
	__super::OnEnable(bEnable);

	//Update ourselves
	Invalidate();
	UpdateWindow();
}

#pragma warning(suppress: 26429)
HBRUSH CHLinkCtrl::CtlColor(CDC* pDC, UINT nCtlColor)
{
	//Validate our parameters
	ASSERT(pDC != nullptr);
#ifndef _DEBUG
	UNREFERENCED_PARAMETER(nCtlColor);
#endif //#ifndef _DEBUG
	ASSERT(nCtlColor == CTLCOLOR_STATIC);

	if ((GetStyle() & WS_DISABLED) == 0)
	{
		//set the DC details depending on our state
		switch (m_State)
		{
			case LinkState::NOT_VISITED:
			{
				if (m_Underline == TriStateSetting::YES)
					pDC->SelectObject(&m_UnderlineFont);
				pDC->SetTextColor(m_Color);
				break;
			}
			case LinkState::VISITED:
			{
				if (m_Underline == TriStateSetting::YES)
					pDC->SelectObject(&m_UnderlineFont);
				pDC->SetTextColor(m_VisitedColor);
				break;
			}
			case LinkState::HIGHLIGHTED:
			{
				if ((m_Underline == TriStateSetting::HOVER) || (m_Underline == TriStateSetting::YES))
					pDC->SelectObject(&m_UnderlineFont);
				pDC->SetTextColor(m_HighlightColor);
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}
	}
	pDC->SetBkMode(TRANSPARENT);

	//return a hollow brush
	return static_cast<HBRUSH>(::GetStockObject(NULL_BRUSH));
}

void CHLinkCtrl::PreSubclassWindow()
{
	//Let the base class do its thing
	__super::PreSubclassWindow();

	//The control must have the SS_NOTIFY style set
	ASSERT(GetStyle() & SS_NOTIFY);

	//Enable tooltips (if required)
	if (m_bToolTips)
		EnableToolTips(TRUE);

	//Create the underline font if necessary
	if (!m_UnderlineFont.operator HFONT())
	{
		LOGFONT lf{};
		GetFont()->GetObject(sizeof(lf), &lf);

		lf.lfUnderline = TRUE;
		m_UnderlineFont.CreateFontIndirect(&lf);
	}
}

INT_PTR CHLinkCtrl::OnToolHitTest(CPoint /*point*/, TOOLINFO* pTI) const
{
	//Validate our parameters
#pragma warning(suppress: 26496)
	AFXASSUME(pTI != nullptr);

	//Fill in the TOOLTIP struct
	pTI->hwnd = GetSafeHwnd();
	pTI->uFlags = TTF_IDISHWND;
#pragma warning(suppress: 26490)
	pTI->uId = reinterpret_cast<UINT_PTR>(pTI->hwnd);
	pTI->lpszText = LPSTR_TEXTCALLBACK;

	return pTI->uId;
}

BOOL CHLinkCtrl::OnToolTipTextA(UINT /*id*/, NMHDR* pNMHDR, LRESULT* pResult)
{
	//Validate our parameters
	ASSERT(pNMHDR != nullptr);
#pragma warning(suppress: 26496)
	AFXASSUME(pResult != nullptr);

#pragma warning(suppress: 26490)
	auto pTTTA{ reinterpret_cast<TOOLTIPTEXTA*>(pNMHDR) };
#pragma warning(suppress: 26496)
	AFXASSUME(pTTTA != nullptr);
	constexpr const int nMaxToolTipLength{ _countof(pTTTA->szText) - 1 }; //Allow space for the null terminator
	CStringA sToolTip{ m_sLink.Left(nMaxToolTipLength) };
#pragma warning(suppress: 26485)
	strcpy_s(pTTTA->szText, _countof(pTTTA->szText), sToolTip);
	*pResult = 0;

	return TRUE;
}

BOOL CHLinkCtrl::OnToolTipTextW(UINT /*id*/, NMHDR* pNMHDR, LRESULT* pResult)
{
	//Validate our parameters
	ASSERT(pNMHDR != nullptr);
#pragma warning(suppress: 26496)
	AFXASSUME(pResult != nullptr);

#pragma warning(suppress: 26490)
	auto pTTTW{ reinterpret_cast<TOOLTIPTEXTW*>(pNMHDR) };
#pragma warning(suppress: 26496)
	AFXASSUME(pTTTW != nullptr);
	constexpr const int nMaxToolTipLength{ _countof(pTTTW->szText) - 1 }; //Allow space for the null terminator
	CStringW sToolTip{ m_sLink.Left(nMaxToolTipLength) };
#pragma warning(suppress: 26485)
	wcscpy_s(pTTTW->szText, _countof(pTTTW->szText), sToolTip);
	*pResult = 0;

	return TRUE;
}

void CHLinkCtrl::FreeParentBitmap()
{
	//Destroy the current parent bitmap if created
	if (m_bmpParent.GetSafeHandle() != nullptr)
		m_bmpParent.DeleteObject();
}

bool CHLinkCtrl::CacheParentBitmap()
{
	//Get our coordinates as client coordinates relative to the parent
	CRect rect;
	GetWindowRect(&rect);
	CWnd* pParent{ GetParent() };
#pragma warning(suppress: 26496)
	AFXASSUME(pParent != nullptr);
	pParent->ScreenToClient(&rect);

	//Get the DC of the parent
	CDC* pDC{ pParent->GetDC() };
	if (pDC == nullptr)
		return false;

	//copy what is on the parent at our coordinates into the bitmap "m_bmpParent"
	CDC memDC;
#pragma warning(suppress: 26486)
	BOOL bSuccess{ memDC.CreateCompatibleDC(pDC) };
	if (bSuccess)
	{
		//Create a bitmap compatible with the parent DC
		bSuccess = m_bmpParent.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		if (bSuccess)
		{
			//Select our bitmap into the memory dc and then bitblt from the parents DC into the memory DC
			//which ends up copying the pixels into "m_bmpParent"
			CBitmap* pOldBitmap{ memDC.SelectObject(&m_bmpParent) };
			memDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);
			memDC.SelectObject(pOldBitmap);
		}
	}

	//Don't forget to release the parent DC before we return
	pParent->ReleaseDC(pDC);

	return bSuccess;
}

#pragma warning(suppress: 26434 26429)
BOOL CHLinkCtrl::OnEraseBkgnd(CDC* pDC)
{
	//Validate our parameters
	ASSERT(pDC != nullptr);

	//Cache the parent bitmap if we have not done so already
	if (m_bmpParent.GetSafeHandle() == nullptr)
		CacheParentBitmap();

	//Get our client rect
	CRect rect;
	GetClientRect(rect);

	//Bitblt the parents bitmap into our client area
	CDC memDC;
	if (!memDC.CreateCompatibleDC(pDC))
		return FALSE;
	CBitmap* pOldBitmap{ memDC.SelectObject(&m_bmpParent) };
#pragma warning(suppress: 26486)
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	return TRUE;
}

void CHLinkCtrl::OnStnClicked()
{
	//Just call the "Open" method which executes the hyperlink
	if (Open())
	{
		//Set the visited state
		m_State = LinkState::VISITED;
		Invalidate();
	}
}
