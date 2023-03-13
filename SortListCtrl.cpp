/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

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
	m_pFileSystem = NULL;
}

CSortListCtrl::~CSortListCtrl()
{
}

BEGIN_MESSAGE_MAP(CSortListCtrl, CMFCListCtrl)
END_MESSAGE_MAP()

// CSortListCtrl message handlers

int CSortListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	UNREFERENCED_PARAMETER(iColumn);
	if (m_pFileSystem != NULL)
	{
		CFileData* pParam1 = m_pFileSystem->GetAt((int)lParam1);
		CFileData* pParam2 = m_pFileSystem->GetAt((int)lParam2);
		if ((pParam1 != NULL) && (pParam2 != NULL))
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
					return pParam1->GetFileName().CompareNoCase(pParam2->GetFileName());
				}
			}
		}
	}
	return 0;
}
