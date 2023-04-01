//
// Microsoft Systems Journal -- January 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably Windows NT too.
//
#include "StdAfx.h"
#include "HtmlCtrl.h"								//Web browser control

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CHtmlCtrl, CHtmlView)
BEGIN_MESSAGE_MAP(CHtmlCtrl, CHtmlView)
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

//////////////////
// Create control in same position as an existing static control with
// the same ID (could be any kind of control, really)
//
BOOL CHtmlCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;

	// Get static control rect, convert to parent's client coords.
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.DestroyWindow();

	// create HTML control (CHtmlView)
	return Create(nullptr,				// class name
		nullptr,						// title
		(WS_CHILD | WS_VISIBLE),		// style
		rc,								// rectangle
		pParent,						// parent
		nID,							// control ID
		nullptr);						// frame/doc context not used
}

////////////////
// Override to avoid CView stuff that assumes a frame.
//
void CHtmlCtrl::OnDestroy()
{
	// This is probably unecessary since ~CHtmlView does it, but
	// safer to mimic CHtmlView::OnDestroy.
	if (m_pBrowserApp)
	{
		//FYI m_pBrowserApp->Release();
		m_pBrowserApp = nullptr;
	}
	CWnd::OnDestroy(); // bypass CView doc/frame stuff
}

////////////////
// Override to avoid CView stuff that assumes a frame.
//
int CHtmlCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
	// bypass CView doc/frame stuff
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}

//////////////////
// Override navigation handler to pass to "app:" links to virtual handler.
// Cancels the navigation in the browser, since app: is a pseudo-protocol.
//
void CHtmlCtrl::OnBeforeNavigate2(LPCTSTR		lpszURL,
	DWORD			/*nFlags*/,
	LPCTSTR		/*lpszTargetFrameName*/,
	CByteArray&	/*baPostedData*/,
	LPCTSTR		/*lpszHeaders*/,
	BOOL*			pbCancel)
{
	const TCHAR APP_PROTOCOL[] = _T("app:");
	int len = (int)_tcslen(APP_PROTOCOL);
	if (_tcsnicmp(lpszURL, APP_PROTOCOL, len) == 0)
	{
		OnAppCmd(lpszURL + len);
		*pbCancel = TRUE;
	}
}


// ***************************************************************************
//DESCRIPTION:
//		This is called by OnBeforeNavigate2() when a link starting with
//		"app:" is requested. 
//PARAMS:
//		lpszWhere	String identifing the action to perform.
//CREATED:
//		10-3-2001, 8:05:08 PM by john@mctainsh.com
// ***************************************************************************
void CHtmlCtrl::OnAppCmd(LPCTSTR lpszWhere)
{
	if (_tcscmp(_T("Minimise"), lpszWhere) == 0)
	{
		AfxGetMainWnd()->ShowWindow(SW_MINIMIZE);
	}
	else if (_tcscmp(_T("Beep"), lpszWhere) == 0)
	{
		MessageBeep(MB_ICONASTERISK);
	}
	else
	{
		MessageBox(lpszWhere, _T("Unexpected Command"), MB_ICONQUESTION);
	}
}
