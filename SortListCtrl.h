/* This file is part of IntelliFile application developed by Stefan-Mihai MOGA.

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once

#include "FileList.h"

// CSortListCtrl

class CSortListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CSortListCtrl)

public:
	CSortListCtrl();
	virtual ~CSortListCtrl();

protected:
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

public:
	CFileSystem* m_pFileSystem;

protected:
	DECLARE_MESSAGE_MAP()
};
