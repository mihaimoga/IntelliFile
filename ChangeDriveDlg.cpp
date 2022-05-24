/* This file is part of IntelliFile application developed by Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile.  If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// ChangeDrive.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "ChangeDriveDlg.h"

// CChangeDriveDlg dialog

IMPLEMENT_DYNAMIC(CChangeDriveDlg, CDialogEx)

CChangeDriveDlg::CChangeDriveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChangeDriveDlg, pParent)
{
}

CChangeDriveDlg::~CChangeDriveDlg()
{
}

void CChangeDriveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRIVE_LIST, m_ctrlDriveList);
}

BEGIN_MESSAGE_MAP(CChangeDriveDlg, CDialogEx)
	ON_LBN_DBLCLK(IDC_DRIVE_LIST, &CChangeDriveDlg::OnDblclkDriveList)
END_MESSAGE_MAP()

// CChangeDriveDlg message handlers

BOOL CChangeDriveDlg::OnInitDialog()
{
	const int nVolumeNameSize = MAX_PATH + 1;
	TCHAR VolumeNameBuffer[nVolumeNameSize];
	CString strDriveName;
	CDialogEx::OnInitDialog();

	const DWORD nDriveList = ::GetLogicalDrives();
	VERIFY(nDriveList != 0);
	for (DWORD nIndex = 0; nIndex < 26; nIndex++)
	{
		if ((nDriveList & (1 << nIndex)) == (((DWORD)1 << nIndex)))
		{
			strDriveName.Format(_T("%c:\\"), (_T('A') + nIndex));
			const UINT nDriveType = ::GetDriveType(strDriveName);
			switch (nDriveType)
			{
				case DRIVE_REMOVABLE:
				{
					if (::GetVolumeInformation(strDriveName, VolumeNameBuffer, nVolumeNameSize, NULL, NULL, NULL, NULL, 0))
					{
						m_arrDriveName.Add(strDriveName);
						strDriveName.Format(_T("%c: %s (%s)"), (_T('A') + nIndex), VolumeNameBuffer, _T("REMOVABLE"));
						m_ctrlDriveList.AddString(strDriveName);
					}
					break;
				}
				case DRIVE_FIXED:
				{
					if (::GetVolumeInformation(strDriveName, VolumeNameBuffer, nVolumeNameSize, NULL, NULL, NULL, NULL, 0))
					{
						m_arrDriveName.Add(strDriveName);
						strDriveName.Format(_T("%c: %s (%s)"), (_T('A') + nIndex), VolumeNameBuffer, _T("FIXED"));
						m_ctrlDriveList.AddString(strDriveName);
					}
					break;
				}
				case DRIVE_REMOTE:
				{
					if (::GetVolumeInformation(strDriveName, VolumeNameBuffer, nVolumeNameSize, NULL, NULL, NULL, NULL, 0))
					{
						m_arrDriveName.Add(strDriveName);
						strDriveName.Format(_T("%c: %s (%s)"), (_T('A') + nIndex), VolumeNameBuffer, _T("REMOTE"));
						m_ctrlDriveList.AddString(strDriveName);
					}
					break;
				}
				case DRIVE_CDROM:
				{
					if (::GetVolumeInformation(strDriveName, VolumeNameBuffer, nVolumeNameSize, NULL, NULL, NULL, NULL, 0))
					{
						m_arrDriveName.Add(strDriveName);
						strDriveName.Format(_T("%c: %s (%s)"), (_T('A') + nIndex), VolumeNameBuffer, _T("CDROM"));
						m_ctrlDriveList.AddString(strDriveName);
					}
					break;
				}
				case DRIVE_RAMDISK:
				{
					if (::GetVolumeInformation(strDriveName, VolumeNameBuffer, nVolumeNameSize, NULL, NULL, NULL, NULL, 0))
					{
						m_arrDriveName.Add(strDriveName);
						strDriveName.Format(_T("%c: %s (%s)"), (_T('A') + nIndex), VolumeNameBuffer, _T("RAMDISK"));
						m_ctrlDriveList.AddString(strDriveName);
					}
					break;
				}
				default:
					break; // not a drive, ERRROR!
			}
		}
	}
	m_ctrlDriveList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CChangeDriveDlg::OnOK()
{
	m_strNewDriveName = m_arrDriveName.GetAt(m_ctrlDriveList.GetCurSel());
	CDialogEx::OnOK();
}


void CChangeDriveDlg::OnDblclkDriveList()
{
	m_strNewDriveName = m_arrDriveName.GetAt(m_ctrlDriveList.GetCurSel());
	CDialogEx::OnOK();
}
