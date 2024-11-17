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
IntelliEdit. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

#pragma once

#include <EventToken.h>
#include <functional>
#include <map>

struct ICoreWebView2Environment;
struct ICoreWebView2Controller;

struct CWebBrowserImpl;
class CView;

class CWebBrowser : public CWnd
{
public:
	enum class CallbackType
	{
		CreationCompleted,
		NavigationCompleted,
		TitleChanged,
	};

	using CallbackFunc = std::function<void()>;
	using TextSelectionFunc = std::function<void(CString const&)>;

public:
	CWebBrowser();
	virtual ~CWebBrowser();

	virtual BOOL Create(
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID,
		CCreateContext* = NULL) override;

	BOOL CreateAsync(
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID,
		CallbackFunc onCreated);

	void RegisterCallback(CallbackType const type, CallbackFunc callback);

	RECT GetBounds();
	void SetBounds(LONG const width, LONG const height) { Resize(width, height); }
	void Resize(LONG const width, LONG const height);

	CString GetLocationURL();

	void Navigate(CString const& url, CallbackFunc onComplete);
	void NavigatePost(CString const& url, CString const& content, CString const& headers, CallbackFunc onComplete = nullptr);
	void GoBack();
	void GoForward();
	void Reload();
	void Stop();
	bool IsNavigating() const { return m_isNavigating; }
	void DisablePopups();

	void PrintDocument();
	CString GetTitle() const { return m_strTitle; }

	void SetParentView(CView* pViewParent) { m_pViewParent = pViewParent; }
	bool IsWebViewCreated() const;

	void GetSelectedText(TextSelectionFunc callback);
	void ExecuteScript(CString const& code);

	void ShowPrintUI(bool const systemDialog);
	void PrintToPDF(bool const landscape, std::function<void(bool, CString)> callback);
	bool IsPrintToPdfInProgress() const { return m_printToPdfInProgress; }

protected:
	DECLARE_DYNCREATE(CWebBrowser)
	DECLARE_MESSAGE_MAP()

private:
	CWebBrowserImpl* m_pImpl;
	std::map<CallbackType, CallbackFunc> m_callbacks;

	EventRegistrationToken m_navigationCompletedToken = {};
	EventRegistrationToken m_navigationStartingToken = {};
	EventRegistrationToken m_documentTitleChangedToken = {};

	bool m_isNavigating = false;
	CView* m_pViewParent = nullptr;
	CString m_strTitle;
	bool m_printToPdfInProgress = false;

private:
	void RunAsync(CallbackFunc callback);

	void CloseWebView();
	void RegisterEventHandlers();
	void ResizeToClientArea();
	void NavigateTo(CString url);
	CString NormalizeUrl(CString url);

	static CString GetInstallPath();
	static CString GetInstallPathFromRegistry(bool const searchWebView = true);
	static CString GetInstallPathFromDisk(bool const searchWebView = true);
	static CString GetUserDataFolder();

	void InitializeWebView();
	HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);
	HRESULT OnCreateWebViewControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);

	static PCTSTR GetWindowClass();
	static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool HandleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result);

	BOOL CreateHostWindow(
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID);
};
