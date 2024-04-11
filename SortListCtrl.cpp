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

// SortListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "SortListCtrl.h"

// CSortListCtrl

IMPLEMENT_DYNAMIC(CSortListCtrl, CMFCListCtrl)

CSortListCtrl::CSortListCtrl()
{
	m_pFileSystem = nullptr;
}

CSortListCtrl::~CSortListCtrl()
{
}

BEGIN_MESSAGE_MAP(CSortListCtrl, CMFCListCtrl)
END_MESSAGE_MAP()

// CSortListCtrl message handlers

int CSortListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	if (m_pFileSystem != nullptr)
	{
		CFileData* pParam1 = m_pFileSystem->GetAt((int)lParam1);
		CFileData* pParam2 = m_pFileSystem->GetAt((int)lParam2);
		if ((pParam1 != nullptr) && (pParam2 != nullptr))
		{
			if (pParam1->GetFileName().CompareNoCase(_T("..")) == 0)
			{
				return (GetHeaderCtrl().IsAscending() ? -1 : 1);
			}
			else
			{
				if (((pParam1->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) &&
					((pParam2->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == 0))
				{
					return -1;
				}
				else
				{
					if (((pParam1->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == 0) &&
						((pParam2->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY))
					{
						return 1;
					}
					else // both items are either files or folders
					{
						if (((pParam1->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) &&
							((pParam2->GetFileAttributes() & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY))
						{
							return pParam1->GetFileName().CompareNoCase(pParam2->GetFileName());
						}
						else
						{
							if (1 == iColumn) // Size column
							{
								if (pParam1->GetFileSize() == pParam2->GetFileSize())
									return pParam1->GetFileName().CompareNoCase(pParam2->GetFileName());
								else
									return (pParam1->GetFileSize() > pParam2->GetFileSize() ? 1 : -1);
							}
							else
							{
								if (2 == iColumn) // Date column
								{
									COleDateTime pFileDate1(pParam1->GetLastWriteTime());
									COleDateTime pFileDate2(pParam2->GetLastWriteTime());
									CString strFileDate1 = pFileDate1.Format(_T("%Y/%m/%d/%H/%M/%S"));
									CString strFileDate2 = pFileDate2.Format(_T("%Y/%m/%d/%H/%M/%S"));
									if (strFileDate1.Compare(strFileDate2) == 0)
										return pParam1->GetFileName().CompareNoCase(pParam2->GetFileName());
									else
										return strFileDate1.Compare(strFileDate2);
								}
								else // Name column
								{
									return pParam1->GetFileName().CompareNoCase(pParam2->GetFileName());
									// Cannot sort by attributes! Sorry folks!
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
