#pragma once

#include "WndResizer.h"
#include "HexCtrl/HexCtrl/HexCtrl.h"
using namespace HEXCTRL;

// CViewBinaryFileDlg dialog

class CViewBinaryFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewBinaryFileDlg)

public:
	CViewBinaryFileDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CViewBinaryFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ViewBinaryFileDlg };
#endif
	CWndResizer m_pWindowResizer;
	IHexCtrlPtr m_pHexDlg{ CreateHexCtrl() };
	CLongBinary m_pFileData;
	CString m_strFilePath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};
