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

// IntelliFile.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "MainFrame.h"

#include "VersionInfo.h"
#include "HLinkCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIntelliFileApp

BEGIN_MESSAGE_MAP(CIntelliFileApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CIntelliFileApp::OnAppAbout)
END_MESSAGE_MAP()

// CIntelliFileApp construction

CIntelliFileApp::CIntelliFileApp() : m_pInstanceChecker(_T("IntelliFile")),
m_pCreateLexer{ nullptr },
m_hScintilla{ nullptr },
m_hLexilla{ nullptr }
{
	EnableHtmlHelp();

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("IntelliFile.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CIntelliFileApp object

CIntelliFileApp theApp;

// CIntelliFileApp initialization

BOOL CIntelliFileApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	CoInitialize(nullptr);

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	AfxInitRichEdit2();

	// Check for the previous instance as soon as possible
	if (m_pInstanceChecker.PreviousInstanceRunning())
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		AfxMessageBox(_T("Previous version detected, will now restore it..."), MB_OK | MB_ICONINFORMATION);
		m_pInstanceChecker.ActivatePreviousInstance(cmdInfo.m_strFileName);
		return FALSE;
	}

	CString sLexillaDLL;
	sLexillaDLL.Format(_T("%s%s"), _T(LEXILLA_LIB), _T(LEXILLA_EXTENSION));
	m_hLexilla = LoadLibraryFromApplicationDirectory(sLexillaDLL);
	if (m_hLexilla == nullptr)
	{
		CString sMsg;
		sMsg.Format(_T("%s is not installed, Please built the Scintilla '%s' and copy it into this application's directory"), sLexillaDLL.GetString(), sLexillaDLL.GetString());
		AfxMessageBox(sMsg);
		return FALSE;
	}
	m_hScintilla = LoadLibraryFromApplicationDirectory(_T("Scintilla.dll"));
	if (m_hScintilla == nullptr)
	{
		AfxMessageBox(_T("Scintilla DLL is not installed, Please built the Scintilla 'Scintilla.dll' and copy it into this application's directory"));
		return FALSE;
	}

	// Create the C++ Lexer from Lexilla
#pragma warning(suppress: 26490)
	m_pCreateLexer = reinterpret_cast<Lexilla::CreateLexerFn>(GetProcAddress(m_hLexilla, LEXILLA_CREATELEXER));
	if (m_pCreateLexer == nullptr)
	{
		AfxMessageBox(_T("Could not find the Lexilla CreateLexer function"));
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Mihai Moga"));

	LoadStdProfileSettings(10);

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr, nullptr);

	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// pFrame->MoveWindow(CRect(0, 0, 800, 600));
	// pFrame->CenterWindow();

	// If this is the first instance of our App then track it so any other instances can find us
	m_pInstanceChecker.TrackFirstInstanceRunning(m_pMainWnd->GetSafeHwnd());

	return TRUE;
}

int CIntelliFileApp::ExitInstance()
{
	// TODO: handle additional resources you may have added
	if (m_hScintilla != nullptr)
	{
		FreeLibrary(m_hScintilla);
		m_hScintilla = nullptr;
	}
	if (m_hLexilla != nullptr)
	{
		FreeLibrary(m_hLexilla);
		m_hLexilla = nullptr;
	}

	AfxOleTerm(FALSE);

	CoUninitialize();

	return CWinAppEx::ExitInstance();
}

// CIntelliFileApp message handlers
HMODULE CIntelliFileApp::LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName)
{
	// Get the Application directory
	CString sFullPath;
	const DWORD dwGMFN{ GetModuleFileName(nullptr, sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH) };
	sFullPath.ReleaseBuffer();
	if (dwGMFN == 0)
#pragma warning(suppress: 26487)
		return nullptr;

	// Form the new path
	CString sDrive;
	CString sDir;
	_tsplitpath_s(sFullPath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, nullptr, 0, nullptr, 0);
	sDir.ReleaseBuffer();
	sDrive.ReleaseBuffer();
	CString sFname;
	CString sExt;
	_tsplitpath_s(lpFileName, nullptr, 0, nullptr, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
	sExt.ReleaseBuffer();
	sFname.ReleaseBuffer();
	_tmakepath_s(sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH, sDrive, sDir, sFname, sExt);
	sFullPath.ReleaseBuffer();

	// Delegate to LoadLibrary
#pragma warning(suppress: 26487)
	return LoadLibrary(sFullPath);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

protected:
	CStatic m_ctrlVersion;
	CEdit m_ctrlWarning;
	CVersionInfo m_pVersionInfo;
	CHLinkCtrl m_ctrlWebsite;
	CHLinkCtrl m_ctrlEmail;
	CHLinkCtrl m_ctrlContributors;

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VERSION, m_ctrlVersion);
	DDX_Control(pDX, IDC_WARNING, m_ctrlWarning);
	DDX_Control(pDX, IDC_WEBSITE, m_ctrlWebsite);
	DDX_Control(pDX, IDC_EMAIL, m_ctrlEmail);
	DDX_Control(pDX, IDC_CONTRIBUTORS, m_ctrlContributors);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR lpszDrive[_MAX_DRIVE];
	TCHAR lpszDirectory[_MAX_DIR];
	TCHAR lpszFilename[_MAX_FNAME];
	TCHAR lpszExtension[_MAX_EXT];
	TCHAR lpszFullPath[_MAX_PATH];

	VERIFY(0 == _tsplitpath_s(AfxGetApp()->m_pszHelpFilePath, lpszDrive, _MAX_DRIVE, lpszDirectory, _MAX_DIR, lpszFilename, _MAX_FNAME, lpszExtension, _MAX_EXT));
	VERIFY(0 == _tmakepath_s(lpszFullPath, _MAX_PATH, lpszDrive, lpszDirectory, lpszFilename, _T(".exe")));

	if (m_pVersionInfo.Load(lpszFullPath))
	{
		CString strName = m_pVersionInfo.GetProductName().c_str();
		CString strVersion = m_pVersionInfo.GetProductVersionAsString().c_str();
		strVersion.Replace(_T(" "), _T(""));
		strVersion.Replace(_T(","), _T("."));
		const int nFirst = strVersion.Find(_T('.'));
		const int nSecond = strVersion.Find(_T('.'), nFirst + 1);
		strVersion.Truncate(nSecond);
#if _WIN32 || _WIN64
#if _WIN64
		m_ctrlVersion.SetWindowText(strName + _T(" version ") + strVersion + _T(" (64-bit)"));
#else
		m_ctrlVersion.SetWindowText(strName + _T(" version ") + strVersion + _T(" (32-bit)"));
#endif
#endif
	}

	m_ctrlWarning.SetWindowText(_T("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>."));

	m_ctrlWebsite.SetHyperLink(_T("https://www.moga.doctor/"));
	m_ctrlEmail.SetHyperLink(_T("mailto:stefan-mihai@moga.doctor"));
	m_ctrlContributors.SetHyperLink(_T("https://github.com/mihaimoga/IntelliFile/graphs/contributors"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

// App command to run the dialog
void CIntelliFileApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIntelliFileApp customization load/save methods

void CIntelliFileApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CIntelliFileApp::LoadCustomState()
{
}

void CIntelliFileApp::SaveCustomState()
{
}

// CIntelliFileApp message handlers
