/*
Module : HLinkCtrl.h
Purpose: Interface for a MFC class for a static text control class with hyperlink support
Created: PJN / 16-06-1997

Copyright (c) 1997 - 2022 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////// Defines ///////////////////////////////////////////

#pragma once

#ifndef __HLINKCTRL_H__
#define __HLINKCTRL_H__

#ifndef HLINKCTRL_EXT_CLASS
#define HLINKCTRL_EXT_CLASS
#endif //#ifndef HLINKCTRL_EXT_CLASS


/////////////////////////// Classes ///////////////////////////////////////////

class HLINKCTRL_EXT_CLASS CHLinkCtrl : public CStatic
{
public:
	//Enums
	enum class TriStateSetting
	{
		YES,
		NO,
		HOVER
	};

	//Constructors / Destructors
	CHLinkCtrl();

	//Methods
	  //Set or get the hyperlink to use
	void SetHyperLink(_In_ const CString& sLink);
	_NODISCARD CString GetHyperLink() const { return m_sLink; };

	//Set or get the hyperlink color 
	void SetLinkColor(_In_ const COLORREF& color);
	_NODISCARD COLORREF GetLinkColor() const noexcept { return m_Color; };

	//Set or get the hyperlink color for visited links
	void SetVisitedLinkColor(_In_ const COLORREF& color);
	_NODISCARD COLORREF GetVisitedLinkColor() const noexcept { return m_VisitedColor; };

	//Set or get the hyperlink color for highlighted links
	void SetHighlightLinkColor(_In_ const COLORREF& color);
	_NODISCARD COLORREF GetHighlightLinkColor() const noexcept { return m_HighlightColor; };
	void SetUseHighlightColor(_In_ bool bUseHighlight) noexcept { m_bUseHighlight = bUseHighlight; };

	//Set or get whether the hyperlink should be drawn underlined
	void SetUnderline(_In_ TriStateSetting underline);
	_NODISCARD TriStateSetting GetUnderline() const noexcept { return m_Underline; };

	//Gets whether the hyperlink has been visited
	_NODISCARD bool GetVisited() const noexcept { return m_State == LinkState::VISITED; };

	//Should tooltips be shown or not
	void SetToolTips(_In_ bool bToolTip);
	_NODISCARD bool GetToolTips() const noexcept { return m_bToolTips; };

	//Set or get the ShellExecute verb to use
	void SetShellExecuteVerb(_In_ const CString& sVerb) { m_sShellExecuteVerb = sVerb; };
	_NODISCARD CString GetShellExecuteVerb() const { return m_sShellExecuteVerb; };

	//Executes the URL
	virtual bool Open();

	//Free and cache the parent window's bitmap
	void FreeParentBitmap();
	bool CacheParentBitmap();

protected:
	//Enums
	enum class LinkState
	{
		NOT_VISITED,
		VISITED,
		HIGHLIGHTED
	};

	//Virtual methods
	COLORREF GetDefaultLinkColor(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ COLORREF clrDefault);
	bool GetDefaultLinkBoolean(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ bool bDefault);
	TriStateSetting GetDefaultLinkTriStateSetting(_In_z_ LPCTSTR pszSubKey, _In_z_ LPCTSTR lpszEntry, _In_ TriStateSetting defaultSettting);
	void PreSubclassWindow() override;
	INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const override;

	//Message handlers
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnToolTipTextA(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnToolTipTextW(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseLeave();
	afx_msg void OnStnClicked();

	//Member variables
	CString m_sLink;
	HCURSOR m_hLinkCursor;
	COLORREF m_Color;
	COLORREF m_VisitedColor;
	COLORREF m_HighlightColor;
	bool m_bUseHighlight;
	TriStateSetting m_Underline;
	LinkState m_State;
	LinkState m_OldState;
	CFont m_UnderlineFont;
	bool m_bToolTips;
	CString m_sShellExecuteVerb;
	bool m_bTrackLeave;
	CBitmap m_bmpParent;

	DECLARE_MESSAGE_MAP()
};

#endif //#ifndef __HLINKCTRL_H__
