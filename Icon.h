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

#pragma once

#define WIDTHBYTES(bits) ((((bits) + 31)>>5)<<2)

// These next two structures represent how the icon information is stored in an ICO file.
//  https://msdn.microsoft.com/en-us/library/ms997538
//
typedef struct
{
	BYTE    bWidth;               // Width (in pixels) of the image.
	BYTE    bHeight;              // Height (in pixels )of the image.
	BYTE    bColorCount;          // Number of colors in image (0 if >= 8bpp).
	BYTE    bReserved;            // Reserved (must be 0).
	WORD    wPlanes;              // Color Planes.
	WORD    wBitCount;            // Bits per pixel.
	DWORD   dwBytesInRes;         // How many bytes in this resource?
	DWORD   dwImageOffset;        // Where in the file is this image?
} ICONDIRENTRY, * LPICONDIRENTRY;

typedef struct
{
	WORD            idReserved;   // Reserved (must be 0).
	WORD            idType;       // Resource type (1 for icons).
	WORD            idCount;      // How many icon images?
	ICONDIRENTRY    idEntries[1]; // An entry for each icon image.
} ICONDIR, * LPICONDIR;
//
// These next two structs represent how the icon information is stored in an DLL/EXE file.
// The RT_GROUP_ICON resource is simply a GRPICONDIR structure.
// https://msdn.microsoft.com/en-us/library/ms997538
//
// #pragma pack
//               Instructs the compiler to pack structure members with particular alignment.
//               Most compilers, when you declare a struct, will insert padding between members to ensure that they are aligned to appropriate addresses in memory (usually a multiple of the type's size).
#pragma pack(push, 2)             // This directive is used to insure that structure's packing in memory reserved by compiler matches the one from EXE (or DLL). 

typedef struct
{
	BYTE    bWidth;               // Width (in pixels) of the image.
	BYTE    bHeight;              // Height (in pixels )of the image.
	BYTE    bColorCount;          // Number of colors in image (0 if >= 8bpp).
	BYTE    bReserved;            // Reserved (must be 0).
	WORD    wPlanes;              // Color Planes.
	WORD    wBitCount;            // Bits per pixel.
	DWORD   dwBytesInRes;         // How many bytes in this resource?
	WORD    nID;                  // The ID.
} GRPICONDIRENTRY, * LPGRPICONDIRENTRY;

typedef struct
{
	WORD            idReserved;   // Reserved (must be 0).
	WORD            idType;       // Resource type (1 for icons).
	WORD            idCount;      // Number of icon images.
	GRPICONDIRENTRY idEntries[1]; // An entry for each icon image.
} GRPICONDIR, * LPGRPICONDIR;

#pragma pack(pop)	              // Default packing.	

typedef struct
{
	UINT            width;        // Width.
	UINT            height;       // Height.
	UINT            colors;       // Colors.
	LPBYTE          lpBits;       // Pointer to DIB bits.
	DWORD           dwNumBytes;   // How many bytes in this image?
	LPBITMAPINFO    lpbi;         // Pointer to image header.
	LPBYTE          lpXOR;        // Pointer to XOR image bits.
	LPBYTE          lpAND;        // Pointer to AND image bits.
} ICONIMAGE, * LPICONIMAGE;

typedef struct
{
	UINT        nImages;          // How many icon images?
	ICONIMAGE   iconImages[1];    // Icon Image entries.
} ICONRESOURCE, * LPICONRESOURCE;

typedef struct
{
	DWORD	dwBytes;
	DWORD	dwOffset;
} RESOURCEPOSINFO, * LPRESOURCEPOSINFO;

class CIconExtractor
{
public:
	CIconExtractor() { m_lpIR = NULL; m_nImages = 0; }
	~CIconExtractor() { release(); }

	BOOL importIcon(HMODULE hModule, LPCTSTR name, WORD wlan); // Import icon from resource module (RT_GROUP_ICON).
	BOOL importIcon(LPCTSTR iconPath);                         // Import icon from *.ico file.
	BOOL exportIcon(LPCTSTR iconPath);                         // Export icon to *.ico file.

private:
	void release();

	inline LPSTR findDibBits(LPSTR lpbi) { return (lpbi + *(LPDWORD)lpbi + paletteSize(lpbi)); }
	inline WORD paletteSize(LPSTR lpbi) { return (dibNumColors(lpbi) * sizeof(RGBQUAD)); }
	inline DWORD bytesPerLine(LPBITMAPINFOHEADER lpBMIH) { return WIDTHBYTES(lpBMIH->biWidth * lpBMIH->biPlanes * lpBMIH->biBitCount); }
	WORD dibNumColors(LPSTR lpbi);

	LPICONRESOURCE m_lpIR;                                     // Pointer to icon resource data.
	UINT m_nImages;                                            // Number of icon images.
};
