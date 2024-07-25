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

// ViewTextFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "ViewTextFileDlg.h"

// CViewTextFileDlg dialog

IMPLEMENT_DYNAMIC(CViewTextFileDlg, CDialogEx)

const TCHAR* g_cppKeywords
{
	_T("alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept auto bitand bitor bool break ")
	_T("case catch char char8_t char16_t char32_t class compl concept const consteval constexpr constinit const_cast continue ")
	_T("co_await co_return co_yield decltype default delete do double dynamic_cast else enum explicit export extern false float for ")
	_T("friend goto if inline int long mutable namespace new noexcept not not_eq nullptr ")
	_T("operator or or_eq private protected public ")
	_T("reflexpr register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct switch synchronized ")
	_T("template this thread_local throw true try typedef typeid typename union unsigned using ")
	_T("virtual void volatile wchar_t while xor xor_eq")
};

const TCHAR* g_javaKeywords
{
	/* https://www.w3schools.com/java/java_ref_keywords.asp */
	_T("abstract assert boolean break byte case catch char class continue const ")
	_T("default do double else enum exports extends final finally float for goto ")
	_T("if implements import instanceof int interface long module native new ")
	_T("package private protected public requires return short static strictfp ")
	_T("super switch synchronized this throw throws transient try var void ")
	_T("volatile while")
};

const TCHAR* g_pyKeywords
{
	/* https://www.w3schools.com/python/python_ref_keywords.asp */
	_T("and as assert break class continue def del elif else except False finally ")
	_T("for from global if import in is lambda None nonlocal not or pass raise ")
	_T("return True try while with yield")
};

bool IsCppFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".c")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".cpp")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".cxx")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".h")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".hpp")) == 0))
		return true;
	return false;
}

bool IsJavaFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if ((_tcsicmp(lpszExtension, _T(".java")) == 0) ||
		(_tcsicmp(lpszExtension, _T(".js")) == 0))
		return true;
	return false;
}

bool IsPythonFile(CString strFilePath)
{
	TCHAR lpszDrive[_MAX_DRIVE] = { 0 };
	TCHAR lpszFolder[_MAX_DIR] = { 0 };
	TCHAR lpszFileName[_MAX_FNAME] = { 0 };
	TCHAR lpszExtension[_MAX_EXT] = { 0 };
	strFilePath.MakeLower();
	_tsplitpath_s(strFilePath,
		lpszDrive, _MAX_DRIVE,
		lpszFolder, _MAX_DIR,
		lpszFileName, _MAX_FNAME,
		lpszExtension, _MAX_EXT);
	if (_tcsicmp(lpszExtension, _T(".py")) == 0)
		return true;
	return false;
}

CViewTextFileDlg::CViewTextFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ViewTextFileDlg, pParent), m_pCLexer{ nullptr }
{
}

CViewTextFileDlg::~CViewTextFileDlg()
{
}

void CViewTextFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_FILE, m_ctrlTextFile);
}

BEGIN_MESSAGE_MAP(CViewTextFileDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CViewTextFileDlg message handlers

std::wstring utf8_to_wstring(const std::string& str)
{
	// convert UTF-8 string to wstring
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

std::string wstring_to_utf8(const std::wstring& str)
{
	// convert wstring to UTF-8 string
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

void CViewTextFileDlg::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
	m_ctrlTextFile.StyleSetFore(style, fore);
	m_ctrlTextFile.StyleSetBack(style, back);
	if (size >= 1)
		m_ctrlTextFile.StyleSetSize(style, size);
	if (face)
		m_ctrlTextFile.StyleSetFont(style, face);
}

void CViewTextFileDlg::DefineMarker(int marker, Scintilla::MarkerSymbol markerType, COLORREF fore, COLORREF back)
{
	m_ctrlTextFile.MarkerDefine(marker, markerType);
	m_ctrlTextFile.MarkerSetFore(marker, fore);
	m_ctrlTextFile.MarkerSetBack(marker, back);
}

#define STR_SCINTILLAWND _T("Scintilla")

BOOL CViewTextFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_strFilePath);

	if (IsCppFile(m_strFilePath))
	{
		// Create the C++ Lexer
#pragma warning(suppress: 26429)
		m_pCLexer = theApp.m_pCreateLexer("cpp");
		if (m_pCLexer == nullptr)
			return FALSE;

		m_ctrlTextFile.SetupDirectAccess();

		// Setup the C++ Lexer
		m_ctrlTextFile.SetILexer(m_pCLexer);
		m_ctrlTextFile.SetKeyWords(0, g_cppKeywords);
	}
	else
	{
		if (IsJavaFile(m_strFilePath))
		{
			// Create the C++ Lexer
#pragma warning(suppress: 26429)
			m_pCLexer = theApp.m_pCreateLexer("cpp");
			if (m_pCLexer == nullptr)
				return FALSE;

			m_ctrlTextFile.SetupDirectAccess();

			// Setup the C++ Lexer
			m_ctrlTextFile.SetILexer(m_pCLexer);
			m_ctrlTextFile.SetKeyWords(0, g_javaKeywords);
		}
		else
		{
			if (IsPythonFile(m_strFilePath))
			{
				// Create the Python Lexer
#pragma warning(suppress: 26429)
				m_pCLexer = theApp.m_pCreateLexer("python");
				if (m_pCLexer == nullptr)
					return FALSE;

				m_ctrlTextFile.SetupDirectAccess();

				// Setup the Python Lexer
				m_ctrlTextFile.SetILexer(m_pCLexer);
				m_ctrlTextFile.SetKeyWords(0, g_pyKeywords);
			}
			else
			{
				m_ctrlTextFile.SetupDirectAccess();
				// Setup the C++ Lexer
				m_ctrlTextFile.SetILexer(m_pCLexer);

			}
		}
	}

	SetAStyle(static_cast<int>(Scintilla::StylesCommon::Default), RGB(0, 0, 0), RGB(0xff, 0xff, 0xff), 10, "Consolas");
	// Setup styles
	m_ctrlTextFile.StyleClearAll();
	SetAStyle(SCE_C_DEFAULT, RGB(0, 0, 0));
	SetAStyle(SCE_C_COMMENT, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_COMMENTLINE, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_COMMENTDOC, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_COMMENTLINEDOC, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_COMMENTDOCKEYWORD, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_COMMENTDOCKEYWORDERROR, RGB(0, 0x80, 0));
	SetAStyle(SCE_C_NUMBER, RGB(0, 0x80, 0x80));
	SetAStyle(SCE_C_WORD, RGB(0, 0, 0x80));
	m_ctrlTextFile.StyleSetBold(SCE_C_WORD, 1);
	SetAStyle(SCE_C_STRING, RGB(0x80, 0, 0x80));
	SetAStyle(SCE_C_IDENTIFIER, RGB(0, 0, 0));
	SetAStyle(SCE_C_PREPROCESSOR, RGB(0x80, 0, 0));
	SetAStyle(SCE_C_OPERATOR, RGB(0x80, 0x80, 0));

	// Setup folding
	m_ctrlTextFile.SetMarginWidthN(2, 16);
	m_ctrlTextFile.SetMarginSensitiveN(2, TRUE);
	m_ctrlTextFile.SetMarginTypeN(2, Scintilla::MarginType::Symbol);
	m_ctrlTextFile.SetMarginMaskN(2, Scintilla::MaskFolders);
	m_ctrlTextFile.SetSCIProperty(_T("fold"), _T("1"));

	// Setup markers
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), Scintilla::MarkerSymbol::Minus, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::Folder), Scintilla::MarkerSymbol::Plus, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderSub), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderTail), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderEnd), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderOpenMid), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderMidTail), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

	// Setup auto completion
	m_ctrlTextFile.AutoCSetSeparator(10); //Use a separator of line feed

	// Setup call tips
	m_ctrlTextFile.SetMouseDwellTime(1000);

	// Enable Multiple selection
	// m_ctrlTextFile.SetMultipleSelection(TRUE);

	try
	{
		// try to open the file
		CFile pTextFile(m_strFilePath, CFile::modeRead);
		// query the file's length
		const ULONGLONG nFileLength = pTextFile.GetLength();
		if (nFileLength > 0)
		{
			// allocate buffer for reading file's content
			char* pFileBuffer = new char[(UINT)nFileLength + 1];
			if (nullptr != pFileBuffer)
			{
				memset(pFileBuffer, 0, sizeof(pFileBuffer));
				// read file's content
				const UINT nActualLength = pTextFile.Read(pFileBuffer, (UINT)nFileLength);
				pFileBuffer[nActualLength] = 0;
				// convert UTF8 to Unicode characters
				CString strConvertedText(utf8_to_wstring(pFileBuffer).c_str());
				// actual show the content of file
				m_ctrlTextFile.SetText(strConvertedText);
				// delete buffer
				delete pFileBuffer;
				pFileBuffer = nullptr;
			}
		}
		// close the file handle
		pTextFile.Close();
	}
	catch (CFileException* pEx)
	{
		// if an error occurs, just make a message box
		pEx->ReportError();
		pEx->Delete();
	}

	VERIFY(m_pWindowResizer.Hook(this));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_TEXT_FILE, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP | ANCHOR_BOTTOM));

	const int nWidth = theApp.GetInt(_T("Width"), -1);
	const int nHeight = theApp.GetInt(_T("Height"), -1);
	if ((-1 != nWidth) && (-1 != nHeight))
	{
		CRect pWndRect(0, 0, nWidth, nHeight);
		MoveWindow(pWndRect, FALSE);
		CenterWindow();
		UpdateWindow();
	}

	m_nTimerID = SetTimer(0x1234, 0x100, nullptr);
	// const int nMarginWidth{ m_ctrlTextFile.GetMarginWidthN(0) };
	m_ctrlTextFile.SetMarginWidthN(0, 32);

	m_ctrlTextFile.SetReadOnly(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewTextFileDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	RECT pWndRect;
	GetWindowRect(&pWndRect);
	const int nWidth = pWndRect.right - pWndRect.left;
	const int nHeight = pWndRect.bottom - pWndRect.top;
	theApp.WriteInt(_T("Width"), nWidth);
	theApp.WriteInt(_T("Height"), nHeight);
}

void CViewTextFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nTimerID == nIDEvent)
	{
		KillTimer(m_nTimerID);
		m_ctrlTextFile.SetSel(0, 0);
	}

	CDialogEx::OnTimer(nIDEvent);
}
