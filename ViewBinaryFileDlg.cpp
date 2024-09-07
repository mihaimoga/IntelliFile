// ViewBinaryFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "afxdialogex.h"
#include "ViewBinaryFileDlg.h"
#include "HexCtrl/HexCtrl/HexCtrl.h"

// CViewBinaryFileDlg dialog

IMPLEMENT_DYNAMIC(CViewBinaryFileDlg, CDialogEx)

CViewBinaryFileDlg::CViewBinaryFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ViewBinaryFileDlg, pParent)
{
}

CViewBinaryFileDlg::~CViewBinaryFileDlg()
{
}

void CViewBinaryFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CViewBinaryFileDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CViewBinaryFileDlg message handlers

BOOL CViewBinaryFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_strFilePath);

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	m_pHexDlg->CreateDialogCtrl(IDC_BINARY_FILE, m_hWnd);
	m_pHexDlg->SetScrollRatio(2, true); //Two lines scroll with mouse-wheel.
	m_pHexDlg->SetPageSize(64);

	try
	{
		// try to open the file
		CFile pBinaryFile(m_strFilePath, CFile::modeRead);
		// query the file's length
		const ULONGLONG nFileLength = pBinaryFile.GetLength();
		if (nFileLength > 0)
		{
			// allocate buffer for reading file's content
			char* pFileBuffer = new char[(UINT)nFileLength + 1];
			if (nullptr != pFileBuffer)
			{
				memset(pFileBuffer, 0, sizeof(pFileBuffer));
				// read file's content
				const UINT nActualLength = pBinaryFile.Read(pFileBuffer, (UINT)nFileLength);
				pFileBuffer[nActualLength] = 0;
				// actual show the content of file
				HEXDATA hds;
				hds.spnData = { reinterpret_cast<std::byte*>(pFileBuffer), nFileLength };
				m_pHexDlg->SetData(hds);
				/* delete buffer
				delete pFileBuffer;
				pFileBuffer = nullptr;*/
			}
		}
		// close the file handle
		pBinaryFile.Close();
	}
	catch (CFileException* pEx)
	{
		// if an error occurs, just make a message box
		pEx->ReportError();
		pEx->Delete();
	}

	VERIFY(m_pWindowResizer.Hook(this));
	VERIFY(m_pWindowResizer.SetAnchor(IDC_BINARY_FILE, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP | ANCHOR_BOTTOM));

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

void CViewBinaryFileDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	RECT pWndRect;
	GetWindowRect(&pWndRect);
	const int nWidth = pWndRect.right - pWndRect.left;
	const int nHeight = pWndRect.bottom - pWndRect.top;
	theApp.WriteInt(_T("Width"), nWidth);
	theApp.WriteInt(_T("Height"), nHeight);
}
