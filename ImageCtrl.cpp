/* Copyright (C) 2022-2025 Stefan-Mihai MOGA
This file is part of IntelliFile application developed by Stefan-Mihai MOGA.
IntelliFile is an alternative Windows version to the famous Total Commander!

IntelliFile is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliFile is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliFile. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#include "stdafx.h"
#include "Icon.h"
#include "ImageCtrl.h"

CImageCtrl::CImageCtrl(void)
	: CStatic(),
	m_pBmp(NULL),
	m_gdiplusToken(0),
	m_sizeType(sizeType::SIZE_SCALETOFIT),
	m_maintainAspectRatio(true),
	m_aspectRatio(1),
	m_allignmentType(allignmentType::ALLIGN_MIDDLECENTER),
	m_isPanMode(FALSE),
	m_isZoomMode(FALSE)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	m_isImageShown = FALSE;
	m_panAtPt.SetPoint(-1, -1);
	m_panOffset.SetPoint(0, 0);
	m_zoomAtPt.SetPoint(-1, -1);
	m_zoomFactor = 1.0;
	m_zoomMin = 1;
	m_zoomMax = 99999;
}

CImageCtrl::~CImageCtrl(void)
{
	release(false);
	GdiplusShutdown(m_gdiplusToken);
}

BEGIN_MESSAGE_MAP(CImageCtrl, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CImageCtrl::release(bool calcFrameAspectRatio)
{
	CRect rect;

	if (m_pBmp) { delete m_pBmp; m_pBmp = NULL; }
	m_panAtPt.SetPoint(-1, -1);
	m_panOffset.SetPoint(0, 0);
	m_zoomAtPt.SetPoint(-1, -1);
	m_zoomFactor = 1;

	if (calcFrameAspectRatio)
	{
		GetClientRect(rect);
		m_aspectRatio = (double)rect.Height() / rect.Width();
	}
}

void CImageCtrl::update()
{
	m_isInitialShow = TRUE;
	Invalidate();
	UpdateWindow();
	m_isInitialShow = FALSE;
}

void CImageCtrl::erase()
{
	CDC* pDC = NULL; CRect rect;

	if ((pDC = GetDC()) != nullptr)
	{
		GetClientRect(rect);
		pDC->FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
		CStatic::OnEraseBkgnd(pDC);
		ReleaseDC(pDC);
	}
	release();
}

BOOL CImageCtrl::load(CString szFilePath)
{
	release();
	if ((m_pBmp = Bitmap::FromFile(szFilePath)) &&
		m_pBmp->GetLastStatus() != Status::Ok)
	{
		delete m_pBmp;
		m_pBmp = NULL;
	}
	m_isInitialShow = TRUE;
	Invalidate();
	UpdateWindow();
	m_isInitialShow = FALSE;
	return m_isImageShown;
}

BOOL CImageCtrl::load(IStream* piStream)
{
	release();
	if ((m_pBmp = Bitmap::FromStream(piStream)) &&
		m_pBmp->GetLastStatus() != Status::Ok)
	{
		delete m_pBmp;
		m_pBmp = NULL;
	}
	m_isInitialShow = TRUE;
	Invalidate();
	UpdateWindow();
	m_isInitialShow = FALSE;
	return m_isImageShown;
}

BOOL CImageCtrl::load(BYTE* pData, size_t nSize)
{
	IStream* pStream = NULL;

	release();
	if (CreateStreamOnHGlobal(NULL, TRUE, &pStream) == S_OK)
	{
		if (pStream->Write(pData, (ULONG)nSize, NULL) == S_OK)
			if ((m_pBmp = Bitmap::FromStream(pStream)) &&
				m_pBmp->GetLastStatus() != Status::Ok)
			{
				delete m_pBmp;
				m_pBmp = NULL;
			}
		pStream->Release();
	}
	m_isInitialShow = TRUE;
	Invalidate();
	UpdateWindow();
	m_isInitialShow = FALSE;
	return m_isImageShown;
}

BOOL CImageCtrl::load(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType, WORD wlan)
{
	HRSRC hRes; DWORD resSize; HGLOBAL hGlobal, hGlobal2, hGlobal3; void* pRes = NULL, * pRes2 = NULL; IStream* pStream = NULL; Bitmap* pBmp = NULL; HICON hIcon; GRPICONDIR* pIconDir = NULL;

	release();
	if ((hRes = FindResourceEx(hModule, lpType, lpName, wlan)) && (resSize = SizeofResource(hModule, hRes)) && (hGlobal = LoadResource(hModule, hRes)))
	{
		if (lpType != RT_GROUP_ICON)
		{
			if (lpType == RT_BITMAP) { m_pBmp = new Bitmap((HBITMAP)LoadImage(hModule, lpName, IMAGE_BITMAP, 0, 0, 0), NULL); }
			else if ((pRes = LockResource(hGlobal)) != nullptr)
			{
				if ((hGlobal2 = GlobalAlloc(GMEM_MOVEABLE, resSize)) != nullptr)
				{
					if ((pRes2 = GlobalLock(hGlobal2)) != nullptr)
					{
						CopyMemory(pRes2, pRes, resSize);
						if (CreateStreamOnHGlobal(hGlobal2, TRUE, &pStream) == S_OK)
						{
							if ((pBmp = Bitmap::FromStream(pStream)) != nullptr)
							{
								Graphics g(m_pBmp = new Bitmap(pBmp->GetWidth(), pBmp->GetHeight()));
								g.DrawImage(pBmp, 0, 0, pBmp->GetWidth(), pBmp->GetHeight()); delete pBmp;
							}
							pStream->Release();
						}
						UnlockResource(hGlobal2);
					}
					GlobalFree(hGlobal2);
				}
				UnlockResource(hGlobal);
			}
		}
		else // https://msdn.microsoft.com/en-us/library/ms997538.aspx
		{
			if ((pIconDir = (GRPICONDIR*)LockResource(hGlobal)) != nullptr)
			{
				if (pIconDir->idCount && (hRes = FindResource(hModule, MAKEINTRESOURCE(pIconDir->idEntries[0].nID), RT_ICON)) && (resSize = SizeofResource(hModule, hRes)) && (hGlobal3 = LoadResource(hModule, hRes)))
				{
					if ((pRes = LockResource(hGlobal3)) != nullptr)
					{
						if ((hGlobal2 = GlobalAlloc(GMEM_MOVEABLE, resSize)) != nullptr)
							if ((pRes2 = GlobalLock(hGlobal2)) != nullptr)
							{
								CopyMemory(pRes2, pRes, resSize);
								if (CreateStreamOnHGlobal(hGlobal2, TRUE, &pStream) == S_OK)
								{
									if ((pBmp = Bitmap::FromStream(pStream)) && pBmp->GetLastStatus() == Status::Ok)
									{
										Graphics g(m_pBmp = new Bitmap(pBmp->GetWidth(), pBmp->GetHeight()));
										g.DrawImage(pBmp, 0, 0, pBmp->GetWidth(), pBmp->GetHeight()); delete pBmp;
									}
									else if ((hIcon = CreateIconFromResourceEx((PBYTE)pRes, resSize, TRUE, 0x00030000, pBmp->GetWidth(), pBmp->GetHeight(), LR_DEFAULTCOLOR)) != nullptr)
									{
										m_pBmp = new Bitmap(hIcon); DestroyIcon(hIcon);
									}
									pStream->Release();
								}
								UnlockResource(hGlobal2);
							}
						UnlockResource(hGlobal3);
					}
					FreeResource(hGlobal3);
				}
				UnlockResource(hGlobal);
			}
		} //  else // https://msdn.microsoft.com/en-us/library/ms997538.aspx
		FreeResource(hGlobal);
	}

	m_isInitialShow = TRUE; Invalidate(); UpdateWindow(); m_isInitialShow = FALSE; return m_isImageShown;
}

BOOL CImageCtrl::convert(CString pathName, CString imageType)
{
	BOOL ok = FALSE; UINT j, n, size; CString fd; DWORD N, M; HANDLE hFile; HGLOBAL hGlobal; void* pBuffer; IStream* pStream = NULL; ImageCodecInfo* pImageCodecInfo = NULL; Bitmap* pBmp = NULL; Metafile* pMeta = NULL; CDC* pDC = NULL;

	if (m_pBmp && m_pBmp->GetLastStatus() == Status::Ok)
	{
		if (imageType == _T("BMP") || imageType == _T("DIB")) fd = _T("BMP");
		else if (imageType == _T("JPG") || imageType == _T("JPEG") || imageType == _T("JPE") || imageType == _T("JFIF")) fd = _T("JPEG");
		else if (imageType == _T("GIF")) fd = _T("GIF");
		else if (imageType == _T("TIF") || imageType == _T("TIFF")) fd = _T("TIFF");
		else if (imageType == _T("PNG")) fd = _T("PNG");
		else if (imageType == _T("ICO")) fd = _T("ICO");

		if (fd != _T(""))
		{
			GetImageEncodersSize(&n, &size);                   // Get number of image encoders and size (in bytes) of the image encoder array.
			pImageCodecInfo = (ImageCodecInfo*)(malloc(size)); // Create a buffer large enough to hold the array of ImageCodecInfo objects that will be returned by GetImageEncoders.
			GetImageEncoders(n, size, pImageCodecInfo);        // GetImageEncoders creates an array of ImageCodecInfo objects and copies that array into a previously allocated buffer. The third argument, pImageCodecInfo, is a pointer to that buffer. 

			if (fd != _T("ICO"))
			{
				for (j = 0; j < n; j++)
					if (pImageCodecInfo[j].FormatDescription == fd)
					{
						Graphics graphics(pBmp = new Bitmap((int)(m_width + 1e-6), (int)(m_height + 1e-6)));
						if (graphics.DrawImage(m_pBmp, 0, 0, (int)(m_width + 1e-6), (int)(m_height + 1e-6)) == Status::Ok)
							ok = (pBmp->Save(pathName, &pImageCodecInfo[j].Clsid) == Status::Ok);
						delete pBmp; break;
					}
			}
			else // Icon.
				for (j = 0; j < n; j++)
					if (pImageCodecInfo[j].FormatDescription == CString(_T("BMP")))
					{
						Graphics graphics(pBmp = new Bitmap((int)(m_width + 1e-6), (int)(m_height + 1e-6)));
						if (graphics.DrawImage(m_pBmp, 0, 0, (int)(m_width + 1e-6), (int)(m_height + 1e-6)) == Status::Ok)
							if (CreateStreamOnHGlobal(0, TRUE, &pStream) == S_OK)
							{
								if (pBmp->Save(pStream, &pImageCodecInfo[j].Clsid) == Status::Ok)
									if ((GetHGlobalFromStream(pStream, &hGlobal) == S_OK) && ((N = GlobalSize(hGlobal)) != 0) && (pBuffer = GlobalLock(hGlobal)))
									{
										if ((hFile = CreateFile(pathName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0)) != nullptr)
										{
											ok = WriteFile(hFile, pBuffer, N, &M, 0); CloseHandle(hFile);
										}
										GlobalUnlock(hGlobal);
									}
								pStream->Release();
							}
						delete pBmp; break;
					}
			free(pImageCodecInfo);
		}
		else if (imageType == _T("WMF") || imageType == _T("EMF"))
		{
			Graphics graphicsMeta(pMeta = new Metafile(pathName, (pDC = GetDC())->m_hDC));
			ok = (pMeta->GetLastStatus() == Status::Ok) && (graphicsMeta.DrawImage(m_pBmp, 0, 0, (int)(m_width + 1e-6), (int)(m_height + 1e-6)) == Status::Ok);
			ReleaseDC(pDC); delete pMeta;
		}
	}

	return ok;
}

BOOL CImageCtrl::iconResourceToFile(CString resPathName, LPCTSTR lpName, WORD wlan, CString icoPathName)
{
	BOOL ok = FALSE; HMODULE hModule; CIconExtractor ie;

	if ((hModule = LoadLibrary(resPathName)) != nullptr)
	{
		ok = (ie.importIcon(hModule, lpName, wlan) &&
			ie.exportIcon(icoPathName)); FreeLibrary(hModule);
	}

	return ok;
}

void CImageCtrl::PreSubclassWindow()
{
	CRect rect;

	CStatic::PreSubclassWindow();

	ModifyStyle(0, SS_OWNERDRAW | SS_NOTIFY);
	GetClientRect(rect);
	m_aspectRatio = (m_height = m_heightOriginal = rect.Height()) / (m_width = m_widthOriginal = rect.Width());
}

BOOL CImageCtrl::OnEraseBkgnd(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	// return CStatic::OnEraseBkgnd(pDC);
	return TRUE;
}

void CImageCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	double /*w0, h0, */sx, sy, s /*, dx, dy*/; CRect rect; CDC* pDC = NULL, dcMem; CBitmap bmpMem, * oldBmp = NULL;

	if ((pDC = GetDC()) != nullptr)
	{
		if (m_pBmp)
		{
			dcMem.CreateCompatibleDC(pDC);                                   // Create an in-memory device context, compatible with the painting device context.
			GetClientRect(rect);
			bmpMem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()); // Create bitmap compatible with the painting device context. 
			oldBmp = dcMem.SelectObject(&bmpMem);                            // Select the bitmap into this in-memory device context.

			Graphics graphics(dcMem.m_hDC);
			dcMem.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));            // Paint with dialog-background color.

			// if (m_isInitialShow)
			{
				m_widthOriginal = m_pBmp->GetWidth();
				m_heightOriginal = m_pBmp->GetHeight();
				m_aspectRatio = m_heightOriginal / m_widthOriginal;

				if (!m_maintainAspectRatio)
				{
					if (m_sizeType == sizeType::SIZE_SCALETOFIT)
					{
						m_width = rect.Width();
						m_height = rect.Height();
					}
					else if (m_sizeType == sizeType::SIZE_ORIGINAL)
					{
						m_width = m_widthOriginal;
						m_height = m_heightOriginal;
					}
					m_left = m_top = 0;
				}
				else
				{
					if (m_sizeType == sizeType::SIZE_SCALETOFIT)
					{
						if ((rect.Width() < m_widthOriginal) ||
							(rect.Height() < m_heightOriginal))
						{
							sx = rect.Width() / m_widthOriginal;
							sy = rect.Height() / m_heightOriginal;
							s = (sx > sy) ? sy : sx;
							m_height = m_aspectRatio * (m_width = s * m_widthOriginal);
						}
						else
						{
							m_width = m_widthOriginal;
							m_height = m_heightOriginal;
						}
					}
					else if (m_sizeType == sizeType::SIZE_CUSTOM)
					{
						sx = m_width / m_widthOriginal;
						sy = m_height / m_heightOriginal;
						s = (sx > sy) ? sy : sx;
						m_height = m_aspectRatio * (m_width = s * m_widthOriginal);
					}
					else if (m_sizeType == sizeType::SIZE_ORIGINAL)
					{
						m_width = m_widthOriginal;
						m_height = m_heightOriginal;
					}
				}

				if (m_allignmentType == allignmentType::ALLIGN_TOPLEFT)
					m_left = m_top = 0;
				else if (m_allignmentType == allignmentType::ALLIGN_TOPCENTER)
				{
					m_left = (rect.Width() - m_width) / 2;
					m_top = 0;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_TOPRIGHT)
				{
					m_left = rect.Width() - m_width;
					m_top = 0;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_MIDDLELEFT)
				{
					m_left = 0;
					m_top = (rect.Height() - m_height) / 2;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_MIDDLECENTER)
				{
					m_left = (rect.Width() - m_width) / 2;
					m_top = (rect.Height() - m_height) / 2;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_MIDDLERIGHT)
				{
					m_left = rect.Width() - m_width;
					m_top = (rect.Height() - m_height) / 2;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_BOTTOMLEFT)
				{
					m_left = 0;
					m_top = rect.Height() - m_height;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_BOTTOMCENTER)
				{
					m_left = (rect.Width() - m_width) / 2;
					m_top = rect.Height() - m_height;
				}
				else if (m_allignmentType == allignmentType::ALLIGN_BOTTOMRIGHT)
				{
					m_left = rect.Width() - m_width;
					m_top = rect.Height() - m_height;
				}
			}
			/* else if (m_zoomAtPt.x < 0) { m_left += m_panOffset.x; m_top += m_panOffset.y; } // PAN action.
			else if (m_zoomFactor > 1e-6)                                                   // ZOOM action.
			{
				ScreenToClient(&m_zoomAtPt);
				if ((dx = (m_zoomAtPt.x - m_left)) < 1e-6) { m_zoomAtPt.x = (LONG)m_left; dx = 0; }
				else if (m_zoomAtPt.x > m_left + m_width - 1e-6) { m_zoomAtPt.x = (LONG)(m_left + (dx = m_width)); }
				if ((dy = (m_zoomAtPt.y - m_top)) < 1e-6) { m_zoomAtPt.y = (LONG)m_top; dy = 0; }
				else if (m_zoomAtPt.y > m_top + m_height - 1e-6) { m_zoomAtPt.y = (LONG)(m_top + (dy = m_height)); }

				w0 = m_width * m_zoomFactor; h0 = m_height * m_zoomFactor;
				if (w0 >= m_zoomMin && w0 <= m_zoomMax && h0 >= m_zoomMin && h0 <= m_zoomMax) // "ZOOM OUT" rectangle can't have a side smaller than m_ZoomMin pixels, "ZOOM iN" can't have a side greater than m_zoomMax pixels.
				{
					dx *= (w0 / m_width); dy *= (h0 / m_height);
					m_left = m_zoomAtPt.x - dx; m_top = m_zoomAtPt.y - dy; m_height = m_aspectRatio * (m_width = w0);
					GetParent()->SendMessage(WM_APP + 1, 12345, 0); // Send message to parent window to signalize ZOOM action event.
				}
			}*/

			m_isImageShown = (graphics.DrawImage(m_pBmp, (int)(m_left + 1e-6), (int)(m_top + 1e-6), (int)(m_width + 1e-6), (int)(m_height + 1e-6)) == Status::Ok);
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY); // Copy a portion of the in-memory device context to the painting device context.
			dcMem.SelectObject(oldBmp);
			bmpMem.DeleteObject();
			dcMem.DeleteDC();
		}
		else
		{
			GetClientRect(rect);
			pDC->FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
			m_isImageShown = FALSE;
		}
		ReleaseDC(pDC);
		m_zoomAtPt.SetPoint(-1, -1);
	}
}
