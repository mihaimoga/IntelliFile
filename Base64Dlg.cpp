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

// Base64Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "Base64Dlg.h"

#include "base64.h"

// CBase64Dlg dialog

IMPLEMENT_DYNAMIC(CBase64Dlg, CDialogEx)

CBase64Dlg::CBase64Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Base64Dlg, pParent)
{
}

CBase64Dlg::~CBase64Dlg()
{
}

void CBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_ctrlInputFile);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_ctrlOutputFile);
	DDX_Control(pDX, IDC_ENCODE, m_ctrlEncode);
	DDX_Control(pDX, IDC_DECODE, m_ctrlDecode);
}

BEGIN_MESSAGE_MAP(CBase64Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BROWSE_INPUT, &CBase64Dlg::OnBnClickedBrowseInput)
	ON_BN_CLICKED(IDC_BROWSE_OUTPUT, &CBase64Dlg::OnBnClickedBrowseOutput)
	ON_BN_CLICKED(IDC_ENCODE, &CBase64Dlg::OnBnClickedEncode)
	ON_BN_CLICKED(IDC_DECODE, &CBase64Dlg::OnBnClickedDecode)
END_MESSAGE_MAP()

BOOL CBase64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrlEncode.EnableWindow(FALSE);
	m_ctrlDecode.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// CBase64Dlg message handlers

void CBase64Dlg::OnBnClickedBrowseInput()
{
	CFileDialog pFileDialog(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES,
		_T("All files\0*.*\0"), this);
	if (pFileDialog.DoModal() == IDOK)
	{
		m_strInputFile = pFileDialog.GetPathName();
		m_ctrlInputFile.SetWindowText(m_strInputFile);
		m_ctrlEncode.EnableWindow(!m_strInputFile.IsEmpty() && !m_strOutputFile.IsEmpty());
		m_ctrlDecode.EnableWindow(!m_strInputFile.IsEmpty() && !m_strOutputFile.IsEmpty());
	}
}

void CBase64Dlg::OnBnClickedBrowseOutput()
{
	CFileDialog pFileDialog(FALSE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_LONGNAMES | OFN_PATHMUSTEXIST,
		_T("All files\0*.*\0"), this);
	if (pFileDialog.DoModal() == IDOK)
	{
		m_strOutputFile = pFileDialog.GetPathName();
		m_ctrlOutputFile.SetWindowText(m_strOutputFile);
		m_ctrlEncode.EnableWindow(!m_strInputFile.IsEmpty() && !m_strOutputFile.IsEmpty());
		m_ctrlDecode.EnableWindow(!m_strInputFile.IsEmpty() && !m_strOutputFile.IsEmpty());
	}
}

void CBase64Dlg::OnBnClickedEncode()
{
	std::ifstream pInputFile(m_strInputFile.GetBuffer(), std::ifstream::in | std::ofstream::binary);
	m_strInputFile.ReleaseBuffer();
	if (pInputFile.is_open())
	{
		std::ofstream pOutputFile(m_strOutputFile.GetBuffer(), std::ofstream::out | std::ofstream::binary);
		m_strOutputFile.ReleaseBuffer();
		if (pOutputFile.is_open())
		{
			pInputFile.seekg(0, std::ios::end);
			std::streampos size = pInputFile.tellg();
			char* memblock = new char[(unsigned long long)size + 1];
			if (memblock)
			{
				pInputFile.seekg(0, std::ios::beg);
				pInputFile.read(memblock, size);
				memblock[size] = 0;

				std::string encoded = base64_encode(reinterpret_cast<const unsigned char *>(memblock), size);
				pOutputFile.write(encoded.c_str(), encoded.length());

				delete[] memblock;
				memblock = nullptr;
			}
			pOutputFile.close();
		}
		pInputFile.close();
	}
	CDialogEx::EndDialog(IDOK);
}

void CBase64Dlg::OnBnClickedDecode()
{
	std::ifstream pInputFile(m_strInputFile.GetBuffer(), std::ifstream::in | std::ofstream::binary);
	m_strInputFile.ReleaseBuffer();
	if (pInputFile.is_open())
	{
		std::ofstream pOutputFile(m_strOutputFile.GetBuffer(), std::ofstream::out | std::ofstream::binary);
		m_strOutputFile.ReleaseBuffer();
		if (pOutputFile.is_open())
		{
			pInputFile.seekg(0, std::ios::end);
			std::streampos size = pInputFile.tellg();
			char* memblock = new char[(unsigned long long)size + 1];
			if (memblock)
			{
				pInputFile.seekg(0, std::ios::beg);
				pInputFile.read(memblock, size);
				memblock[size] = 0;

				std::string decoded = base64_decode(memblock);
				pOutputFile.write(decoded.c_str(), decoded.length());

				delete[] memblock;
				memblock = nullptr;
			}
			pOutputFile.close();
		}
		pInputFile.close();
	}
	CDialogEx::EndDialog(IDOK);
}
