// TortoiseSVN - a Windows shell extension for easy version control
//
// Copyright (C) 2010, 2014 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// https://code.google.com/p/tortoisesvn/source/browse/trunk/src/Utils/IconExtractor.cpp?r=23796

// Copyright (C) 2015 - Patrik Mlekuž

//   Reorganized code (2015-10-23):
// - Optimized some procedures.
// - Reduced number of code rows in "Icon.cpp" from 261 to 151 with all functionality preserved, plus additional method "importIcon(LPCTSTR iconPath)" supplied.
// - Added "icon import" functionality for multi-language resource. 
// - Fixed memory leak at line "lpIR->IconImages[i].lpBits =(LPBYTE) malloc(lpIR->IconImages[i].dwNumBytes);" in method "DWORD CIconExtractor::ExtractIcon(HINSTANCE hResource, LPCTSTR id, LPCTSTR TargetICON)".
// http://www.codeproject.com/Articles/1036270/Advanced-Image-Control

#include "stdafx.h"
#include "Icon.h"

void CIconExtractor::release()
{
	if (m_lpIR)
	{
		for (UINT j = 0; j < m_nImages; j++) free(m_lpIR->iconImages[j].lpBits);
		free(m_lpIR); m_lpIR = NULL; m_nImages = 0;
	}
}

BOOL CIconExtractor::importIcon(HMODULE hModule, LPCTSTR name, WORD wlan)
{
	BOOL ok = FALSE; UINT i = 0; HRSRC hRsrc; HGLOBAL hGlobal, hGlobal2; LPGRPICONDIR lpIcon;

	release();
	if ((hRsrc = FindResourceEx(hModule, RT_GROUP_ICON, name, wlan)) && (hGlobal = LoadResource(hModule, hRsrc))) // Find the group icon resource and load it.
	{
		if ((lpIcon = (LPGRPICONDIR)LockResource(hGlobal)) != nullptr)
		{
			m_lpIR = (LPICONRESOURCE)malloc(sizeof(ICONRESOURCE) + (lpIcon->idCount - 1) * sizeof(ICONIMAGE));
			m_lpIR->nImages = lpIcon->idCount;

			for (i = 0; i < m_lpIR->nImages; i++) // Go through all the icon images and store a copy of each.
				if ((hRsrc = FindResourceEx(hModule, RT_ICON, MAKEINTRESOURCE(lpIcon->idEntries[i].nID), wlan)) && (hGlobal2 = LoadResource(hModule, hRsrc))) // Get and load individual icon.
				{
					m_lpIR->iconImages[i].lpBits = (LPBYTE)malloc(m_lpIR->iconImages[i].dwNumBytes = SizeofResource(hModule, hRsrc));
					memcpy(m_lpIR->iconImages[i].lpBits, LockResource(hGlobal2), m_lpIR->iconImages[i].dwNumBytes); UnlockResource(hGlobal2);
					m_lpIR->iconImages[i].lpbi = (LPBITMAPINFO)m_lpIR->iconImages[i].lpBits;                                                        // BITMAPINFO is at beginning of bits.
					m_lpIR->iconImages[i].width = m_lpIR->iconImages[i].lpbi->bmiHeader.biWidth;                                                    // Width - simple enough.	
					m_lpIR->iconImages[i].height = (m_lpIR->iconImages[i].lpbi->bmiHeader.biHeight) / 2;                                            // Icons are stored in funky format where height is doubled - account for it.	
					m_lpIR->iconImages[i].colors = m_lpIR->iconImages[i].lpbi->bmiHeader.biPlanes * m_lpIR->iconImages[i].lpbi->bmiHeader.biBitCount; // How many colors?		
					m_lpIR->iconImages[i].lpXOR = (PBYTE)findDibBits((LPSTR)m_lpIR->iconImages[i].lpbi);                                            // XOR bits follow the header and color table.
					m_lpIR->iconImages[i].lpAND = m_lpIR->iconImages[i].lpXOR + m_lpIR->iconImages[i].height * bytesPerLine((LPBITMAPINFOHEADER)m_lpIR->iconImages[i].lpbi); // AND bits follow the XOR bits.
				}
				else break;

			ok = ((m_nImages = i) == m_lpIR->nImages); UnlockResource(hGlobal);
		}
		FreeResource(hGlobal);
	}

	return ok;
}

BOOL CIconExtractor::importIcon(LPCTSTR iconPath)
{
	BOOL ok = false; UINT i; HANDLE hFile; LPICONDIRENTRY lpIDE; DWORD dwBytesRead; WORD input;

	release();
	if ((hFile = CreateFile(iconPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
	{
		if (ReadFile(hFile, &input, sizeof(WORD), &dwBytesRead, NULL) && dwBytesRead == sizeof(WORD) && input == 0)
			if (ReadFile(hFile, &input, sizeof(WORD), &dwBytesRead, NULL) && dwBytesRead == sizeof(WORD) && input == 1)
				if (ReadFile(hFile, &input, sizeof(WORD), &dwBytesRead, NULL) && dwBytesRead == sizeof(WORD) && input > 0)
				{
					m_lpIR = (LPICONRESOURCE)malloc(sizeof(ICONRESOURCE) + (input - 1) * sizeof(ICONIMAGE));
					lpIDE = (LPICONDIRENTRY)malloc((m_lpIR->nImages = input) * sizeof(ICONDIRENTRY)); i = 0;
					if (ReadFile(hFile, lpIDE, m_lpIR->nImages * sizeof(ICONDIRENTRY), &dwBytesRead, NULL) && dwBytesRead == m_lpIR->nImages * sizeof(ICONDIRENTRY))
						for (i = 0; i < m_lpIR->nImages; i++)
							if (SetFilePointer(hFile, lpIDE[i].dwImageOffset, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER)
							{
								m_lpIR->iconImages[i].lpBits = (LPBYTE)malloc(m_lpIR->iconImages[i].dwNumBytes = lpIDE[i].dwBytesInRes);
								if (ReadFile(hFile, m_lpIR->iconImages[i].lpBits, lpIDE[i].dwBytesInRes, &dwBytesRead, NULL) && dwBytesRead == lpIDE[i].dwBytesInRes)
								{
									m_lpIR->iconImages[i].lpbi = (LPBITMAPINFO)m_lpIR->iconImages[i].lpBits;                                                        // BITMAPINFO is at beginning of bits.
									m_lpIR->iconImages[i].width = m_lpIR->iconImages[i].lpbi->bmiHeader.biWidth;                                                    // Width - simple enough.	
									m_lpIR->iconImages[i].height = (m_lpIR->iconImages[i].lpbi->bmiHeader.biHeight) / 2;                                            // Icons are stored in funky format where height is doubled - account for it.	
									m_lpIR->iconImages[i].colors = m_lpIR->iconImages[i].lpbi->bmiHeader.biPlanes * m_lpIR->iconImages[i].lpbi->bmiHeader.biBitCount; // How many colors?		
									m_lpIR->iconImages[i].lpXOR = (PBYTE)findDibBits((LPSTR)m_lpIR->iconImages[i].lpbi);                                            // XOR bits follow the header and color table.
									m_lpIR->iconImages[i].lpAND = m_lpIR->iconImages[i].lpXOR + m_lpIR->iconImages[i].height * bytesPerLine((LPBITMAPINFOHEADER)m_lpIR->iconImages[i].lpbi); // AND bits follow the XOR bits.
								}
								else { i++; break; }
							}
							else break;
					ok = ((m_nImages = i) == m_lpIR->nImages); free(lpIDE);
				}
		CloseHandle(hFile);
	}

	return ok;
}

BOOL CIconExtractor::exportIcon(LPCTSTR iconPath)
{
	BOOL ok = false; UINT i; DWORD dwBytesWritten, dwSize; WORD idReserved = 0, idType = 1, idCount = (WORD)m_lpIR->nImages; HANDLE hFile; ICONDIRENTRY ide;

	if (m_lpIR && (hFile = CreateFile(iconPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
	{
		if (WriteFile(hFile, &idReserved, sizeof(WORD), &dwBytesWritten, NULL) && dwBytesWritten == sizeof(WORD))
			if (WriteFile(hFile, &idType, sizeof(WORD), &dwBytesWritten, NULL) && dwBytesWritten == sizeof(WORD))
				if (WriteFile(hFile, &idCount, sizeof(WORD), &dwBytesWritten, NULL) && dwBytesWritten == sizeof(WORD))
				{
					dwSize = (WORD)(3 * sizeof(WORD) + m_lpIR->nImages * sizeof(ICONDIRENTRY));
					for (i = 0; i < m_lpIR->nImages; ++i) // Write the ICONDIRENTRY's.
					{
						// Convert internal format to ICONDIRENTRY.
						ide.bWidth = (BYTE)m_lpIR->iconImages[i].width;
						ide.bHeight = (BYTE)m_lpIR->iconImages[i].height;
						ide.bReserved = 0;
						ide.wPlanes = m_lpIR->iconImages[i].lpbi->bmiHeader.biPlanes;
						ide.wBitCount = m_lpIR->iconImages[i].lpbi->bmiHeader.biBitCount;
						if (ide.wPlanes * ide.wBitCount >= 8) ide.bColorCount = 0;
						else ide.bColorCount = 1 << (ide.wPlanes * ide.wBitCount);
						ide.dwBytesInRes = m_lpIR->iconImages[i].dwNumBytes;
						ide.dwImageOffset = dwSize; dwSize += m_lpIR->iconImages[i].dwNumBytes;

						// Write the ICONDIRENTRY to disk.
						if (!WriteFile(hFile, &ide, sizeof(ICONDIRENTRY), &dwBytesWritten, NULL) || dwBytesWritten != sizeof(ICONDIRENTRY)) break;
					}
					if (i == m_lpIR->nImages)
						for (i = 0; i < m_lpIR->nImages; i++) // Write the image bits for each image.		
							if (!WriteFile(hFile, m_lpIR->iconImages[i].lpBits, m_lpIR->iconImages[i].dwNumBytes, &dwBytesWritten, NULL) || dwBytesWritten != m_lpIR->iconImages[i].dwNumBytes) break;
					ok = (i == m_lpIR->nImages);
				}
		CloseHandle(hFile);
	}

	return ok;
}

WORD CIconExtractor::dibNumColors(LPSTR lpbi)
{
	DWORD dwClrUsed;

	if ((dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed) != 0)
		return (WORD)dwClrUsed;
	switch (((LPBITMAPINFOHEADER)lpbi)->biBitCount)
	{
	case 1: return 2;
	case 4: return 16;
	case 8: return 256;
	default: return 0;
	}
}
