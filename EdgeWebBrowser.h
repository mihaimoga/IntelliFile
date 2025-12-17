/* Copyright (C) 2022-2026 Stefan-Mihai MOGA
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

#pragma once

#include <EventToken.h>
#include <functional>
#include <map>

struct ICoreWebView2Environment;
struct ICoreWebView2Controller;

struct CWebBrowserImpl;
class CView;

/**
 * @class CWebBrowser
 * @brief MFC window class that hosts a Microsoft Edge WebView2 browser control.
 *
 * Provides navigation, script execution, printing, and event/callback support for embedding
 * a modern web browser in an MFC application.
 */
class CWebBrowser : public CWnd
{
public:
	/**
	 * @enum CallbackType
	 * @brief Types of asynchronous events for which callbacks can be registered.
	 */
	enum class CallbackType
	{
		CreationCompleted,      ///< WebView2 creation finished
		NavigationCompleted,    ///< Navigation to a URL finished
		TitleChanged,           ///< Document title changed
	};

	/// Callback function type for asynchronous events.
	using CallbackFunc = std::function<void()>;
	/// Callback function type for text selection results.
	using TextSelectionFunc = std::function<void(CString const&)>;

public:
	/**
	 * @brief Constructor. Initializes the browser control.
	 */
	CWebBrowser();

	/**
	 * @brief Destructor. Cleans up resources.
	 */
	virtual ~CWebBrowser();

	/**
	 * @brief Creates the browser window and initializes WebView2 synchronously.
	 * @param lpszClassName Window class name.
	 * @param lpszWindowName Window name.
	 * @param dwStyle Window style.
	 * @param rect Initial window rectangle.
	 * @param pParentWnd Parent window pointer.
	 * @param nID Control ID.
	 * @param pContext Optional creation context.
	 * @return TRUE if successful, FALSE otherwise.
	 */
	virtual BOOL Create(
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID,
		CCreateContext* = NULL) override;

	/**
	 * @brief Asynchronously creates the browser window and initializes WebView2.
	 * @param dwStyle Window style.
	 * @param rect Initial window rectangle.
	 * @param pParentWnd Parent window pointer.
	 * @param nID Control ID.
	 * @param onCreated Callback invoked when creation is complete.
	 * @return TRUE if successful, FALSE otherwise.
	 */
	BOOL CreateAsync(
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID,
		CallbackFunc onCreated);

	/**
	 * @brief Registers a callback for a specific browser event.
	 * @param type Callback type.
	 * @param callback Function to call on event.
	 */
	void RegisterCallback(CallbackType const type, CallbackFunc callback);

	/**
	 * @brief Gets the bounds of the browser control.
	 * @return RECT structure with bounds.
	 */
	RECT GetBounds();

	/**
	 * @brief Sets the bounds (width and height) of the browser control.
	 * @param width New width.
	 * @param height New height.
	 */
	void SetBounds(LONG const width, LONG const height) { Resize(width, height); }

	/**
	 * @brief Resizes the browser control.
	 * @param width New width.
	 * @param height New height.
	 */
	void Resize(LONG const width, LONG const height);

	/**
	 * @brief Gets the current URL loaded in the browser.
	 * @return Current URL as CString.
	 */
	CString GetLocationURL();

	/**
	 * @brief Navigates to a URL and invokes a callback upon completion.
	 * @param url URL to navigate to.
	 * @param onComplete Callback to invoke when navigation completes.
	 */
	void Navigate(CString const& url, CallbackFunc onComplete);

	/**
	 * @brief Navigates to a URL using HTTP POST with custom content and headers.
	 * @param url Target URL.
	 * @param content POST data.
	 * @param headers HTTP headers.
	 * @param onComplete Callback to invoke when navigation completes.
	 */
	void NavigatePost(CString const& url, CString const& content, CString const& headers, CallbackFunc onComplete = nullptr);

	/**
	 * @brief Navigates back in the browser history if possible.
	 */
	void GoBack();

	/**
	 * @brief Navigates forward in the browser history if possible.
	 */
	void GoForward();

	/**
	 * @brief Reloads the current page.
	 */
	void Reload();

	/**
	 * @brief Stops the current navigation or page load.
	 */
	void Stop();

	/**
	 * @brief Checks if a navigation is currently in progress.
	 * @return true if navigating, false otherwise.
	 */
	bool IsNavigating() const { return m_isNavigating; }

	/**
	 * @brief Disables JavaScript popups and default script dialogs.
	 */
	void DisablePopups();

	/**
	 * @brief Prints the current document using the browser's print dialog.
	 */
	void PrintDocument();

	/**
	 * @brief Gets the current document title.
	 * @return Document title as CString.
	 */
	CString GetTitle() const { return m_strTitle; }

	/**
	 * @brief Sets the parent MFC view for the browser control.
	 * @param pViewParent Pointer to parent view.
	 */
	void SetParentView(CView* pViewParent) { m_pViewParent = pViewParent; }

	/**
	 * @brief Checks if the WebView2 control has been created.
	 * @return true if created, false otherwise.
	 */
	bool IsWebViewCreated() const;

	/**
	 * @brief Gets the currently selected text in the browser and invokes a callback with the result.
	 * @param callback Function to receive the selected text.
	 */
	void GetSelectedText(TextSelectionFunc callback);

	/**
	 * @brief Executes JavaScript code in the context of the current page.
	 * @param code JavaScript code to execute.
	 */
	void ExecuteScript(CString const& code);

	/**
	 * @brief Shows the print UI for the current document.
	 * @param systemDialog If true, shows the system print dialog; otherwise, shows the browser print dialog.
	 */
	void ShowPrintUI(bool const systemDialog);

	/**
	 * @brief Prints the current page to a PDF file.
	 * @param landscape If true, prints in landscape orientation.
	 * @param callback Callback to invoke with the result and file path.
	 */
	void PrintToPDF(bool const landscape, std::function<void(bool, CString)> callback);

	/**
	 * @brief Checks if a PrintToPDF operation is in progress.
	 * @return true if printing to PDF, false otherwise.
	 */
	bool IsPrintToPdfInProgress() const { return m_printToPdfInProgress; }

protected:
	DECLARE_DYNCREATE(CWebBrowser)
	DECLARE_MESSAGE_MAP()

private:
	CWebBrowserImpl* m_pImpl; ///< Internal implementation details (WebView2 COM pointers)
	std::map<CallbackType, CallbackFunc> m_callbacks; ///< Registered event callbacks

	EventRegistrationToken m_navigationCompletedToken = {};
	EventRegistrationToken m_navigationStartingToken = {};
	EventRegistrationToken m_documentTitleChangedToken = {};

	bool m_isNavigating = false; ///< True if navigation is in progress
	CView* m_pViewParent = nullptr; ///< Parent MFC view
	CString m_strTitle; ///< Current document title
	bool m_printToPdfInProgress = false; ///< True if PrintToPDF is running

private:
	/**
	 * @brief Runs a callback asynchronously on the UI thread.
	 * @param callback Callback function to run.
	 */
	void RunAsync(CallbackFunc callback);

	/**
	 * @brief Closes and releases all WebView and related resources.
	 */
	void CloseWebView();

	/**
	 * @brief Registers event handlers for navigation and title changes.
	 */
	void RegisterEventHandlers();

	/**
	 * @brief Resizes the WebView to fit the client area of the window.
	 */
	void ResizeToClientArea();

	/**
	 * @brief Navigates the browser to the specified URL.
	 * @param url URL to navigate to.
	 */
	void NavigateTo(CString url);

	/**
	 * @brief Normalizes a URL, adding protocol if missing.
	 * @param url Input URL.
	 * @return Normalized URL.
	 */
	CString NormalizeUrl(CString url);

	/**
	 * @brief Gets the install path for WebView2 or Edge.
	 * @return Install path as CString.
	 */
	static CString GetInstallPath();

	/**
	 * @brief Gets the install path from the registry.
	 * @param searchWebView If true, searches for WebView2; otherwise, searches for Edge.
	 * @return Install path as CString.
	 */
	static CString GetInstallPathFromRegistry(bool const searchWebView = true);

	/**
	 * @brief Gets the install path from disk.
	 * @param searchWebView If true, searches for WebView2; otherwise, searches for Edge.
	 * @return Install path as CString.
	 */
	static CString GetInstallPathFromDisk(bool const searchWebView = true);

	/**
	 * @brief Gets the user data folder for WebView2.
	 * @return User data folder as CString.
	 */
	static CString GetUserDataFolder();

	/**
	 * @brief Initializes the WebView2 environment and starts browser creation.
	 */
	void InitializeWebView();

	/**
	 * @brief Callback for when the WebView2 environment is created.
	 * @param result HRESULT result.
	 * @param environment Pointer to the created environment.
	 * @return HRESULT
	 */
	HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);

	/**
	 * @brief Callback for when the WebView2 controller is created.
	 * @param result HRESULT result.
	 * @param controller Pointer to the created controller.
	 * @return HRESULT
	 */
	HRESULT OnCreateWebViewControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);

	/**
	 * @brief Registers and returns the window class name for the browser host.
	 * @return Window class name.
	 */
	static PCTSTR GetWindowClass();

	/**
	 * @brief Static window procedure for the browser host window.
	 * @param hWnd Window handle.
	 * @param message Message ID.
	 * @param wParam WPARAM.
	 * @param lParam LPARAM.
	 * @return LRESULT
	 */
	static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief Handles window messages for the browser host window.
	 * @param hWnd Window handle.
	 * @param message Message ID.
	 * @param wParam WPARAM.
	 * @param lParam LPARAM.
	 * @param result Pointer to LRESULT for output.
	 * @return true if message was handled, false otherwise.
	 */
	bool HandleWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result);

	/**
	 * @brief Creates the host window for the browser control.
	 * @param lpszClassName Window class name.
	 * @param lpszWindowName Window name.
	 * @param dwStyle Window style.
	 * @param rect Initial window rectangle.
	 * @param pParentWnd Parent window pointer.
	 * @param nID Control ID.
	 * @return TRUE if successful, FALSE otherwise.
	 */
	BOOL CreateHostWindow(
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd,
		UINT nID);
};
