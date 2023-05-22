/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

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

CViewTextFileDlg::CViewTextFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ViewTextFileDlg, pParent)
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

BOOL CViewTextFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_strFilePath);

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
				m_ctrlTextFile.SetWindowText(strConvertedText);
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

	VERIFY(m_fontTerminal.CreateFont(
		-MulDiv(10, GetDeviceCaps(::GetDC(nullptr), LOGPIXELSY), 72), // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		ANTIALIASED_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_MODERN, // nPitchAndFamily
		_T("Consolas")));
	m_ctrlTextFile.SetFont(&m_fontTerminal);

	VERIFY(m_pWindowResizer.Hook(this));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_TEXT_FILE, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP | ANCHOR_BOTTOM));

	const int nWidth = theApp.GetProfileInt(_T("Size"), _T("Width"), -1);
	const int nHeight = theApp.GetProfileInt(_T("Size"), _T("Height"), -1);
	if ((-1 != nWidth) && (-1 != nHeight))
	{
		CRect pWndRect(0, 0, nWidth, nHeight);
		MoveWindow(pWndRect, FALSE);
		CenterWindow();
		UpdateWindow();
	}

	m_nTimerID = SetTimer(0x1234, 0x100, nullptr);

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
	theApp.WriteProfileInt(_T("Size"), _T("Width"), nWidth);
	theApp.WriteProfileInt(_T("Size"), _T("Height"), nHeight);

	VERIFY(m_fontTerminal.DeleteObject());
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
