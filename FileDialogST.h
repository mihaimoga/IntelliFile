//
//	Class:		CFileDialogST
//
//	Author:		Davide Calabro'		davide_calabro@yahoo.com
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE 5$ (FIVE U.S. DOLLARS) TO THE AUTHOR:
//
//		Davide Calabro'
//		P.O. Box 65
//		21019 Somma Lombardo (VA)
//		Italy
//
#ifndef _FILEDIALOGST_H_
#define _FILEDIALOGST_H_

#include <Shlobj.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Uncomment following line if you are using this class outside the DLL
#define _FILEDIALOGST_NODLL_

#ifndef _FILEDIALOGST_NODLL_
#ifndef	_CMLHTDLL_NOLIB_
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib, "CmlHTud.lib")
		#else
			#pragma comment(lib, "CmlHTd.lib")
		#endif
		#else
		#ifdef _UNICODE
			#pragma comment(lib, "CmlHTu.lib")
		#else
			#pragma comment(lib, "CmlHT.lib")
		#endif
	#endif
#endif

	#ifdef	_CMLHTDLL_BUILDDLL_
		#define	FILEDIALOGST_EXPORT	__declspec(dllexport)
	#else
		#define	FILEDIALOGST_EXPORT	__declspec(dllimport)
	#endif

#else
		#define	FILEDIALOGST_EXPORT
#endif

class FILEDIALOGST_EXPORT	CFileDialogST  
{
public:
	CFileDialogST(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
	CFileDialogST();
	virtual ~CFileDialogST();

	virtual int DoModal();

	CString GetPathName() const;
	CString GetFileName() const;
	CString GetFileTitle() const;
	CString GetFileExt() const;
	CString GetFileDir() const;
	CString GetFileDrive() const;

	POSITION GetStartPosition() const;
	CString GetNextPathName(POSITION& pos) const;

	BOOL GetReadOnlyPref() const;

	int SelectFolder(LPCTSTR lpszTitle = NULL, LPCTSTR lpszStartPath = NULL, UINT ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS, CWnd* pParentWnd = NULL);
	CString GetSelectedFolder() const;

	static short GetVersionI()		{return 13;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.3");}

private:
/*
// commented by - Stefan-Mihai MOGA
#if (_WIN32_WINNT < 0x0500)
	struct OPENFILENAMEEX : public OPENFILENAME 
	{ 
		void*	pvReserved;
		DWORD	dwReserved;
		DWORD	FlagsEx;
	};
#endif
*/

public:
/*
// commented by - Stefan-Mihai MOGA
#if (_WIN32_WINNT >= 0x0500)
	OPENFILENAME	m_ofn;
#else
	OPENFILENAMEEX	m_ofn;
#endif
*/
	OPENFILENAME	m_ofn;
	BOOL			m_bOpenFileDialog;

private:
	static int __stdcall BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	TCHAR			m_szFile[MAX_PATH];
	TCHAR			m_szFileTitle[MAX_PATH];
	TCHAR			m_szSelectedFolder[MAX_PATH];
};

#endif 
