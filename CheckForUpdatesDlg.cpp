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

// CheckForUpdatesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntelliFile.h"
#include "CheckForUpdatesDlg.h"

// Include genUp4win update checking library
#include "genUp4win/genUp4win.h"

// Link appropriate genUp4win library based on platform and configuration
#if _WIN64
#ifdef _DEBUG
#pragma comment(lib, "x64/Debug/genUp4win.lib")     // 64-bit Debug build
#else
#pragma comment(lib, "x64/Release/genUp4win.lib")   // 64-bit Release build
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "Debug/genUp4win.lib")         // 32-bit Debug build
#else
#pragma comment(lib, "Release/genUp4win.lib")       // 32-bit Release build
#endif
#endif

/**
 * @class CCheckForUpdatesDlg
 * @brief Dialog for checking application updates using genUp4win library.
 * 
 * This dialog:
 * - Displays a progress bar while checking for updates
 * - Shows status messages during the update check process
 * - Runs the update check in a background thread to avoid blocking UI
 * - Uses a timer to monitor thread completion
 * - Automatically closes when the check completes
 * - Triggers application exit if a new update is available
 * 
 * The genUp4win library handles:
 * - Downloading version information from the server
 * - Comparing current version with available version
 * - Downloading and launching the installer if an update is found
 */

// Enable dynamic creation of this dialog class
IMPLEMENT_DYNAMIC(CCheckForUpdatesDlg, CDialogEx)

/**
 * @brief Constructor for CCheckForUpdatesDlg.
 * 
 * Initializes all member variables:
 * - Thread ID and handle to zero/null
 * - Timer ID to zero
 * 
 * @param pParent Pointer to the parent window, or nullptr for no parent.
 */
CCheckForUpdatesDlg::CCheckForUpdatesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CheckForUpdatesDlg, pParent)
{
	// Initialize thread tracking variables
	m_nUpdateThreadID = 0;    // Thread ID will be set when thread is created
	m_hUpdateThread = nullptr; // Thread handle will be set when thread is created
	m_nTimerID = 0;           // Timer ID will be set in OnInitDialog
}

/**
 * @brief Destructor for CCheckForUpdatesDlg.
 * 
 * Cleans up resources. Thread cleanup is handled in OnCancel().
 */
CCheckForUpdatesDlg::~CCheckForUpdatesDlg()
{
}

/**
 * @brief Exchanges data between dialog controls and member variables.
 * 
 * Maps the following controls:
 * - IDC_STATUS: Status message label (m_ctrlStatusMessage)
 * - IDC_PROGRESS: Progress bar control (m_ctrlProgress)
 * 
 * @param pDX Pointer to the data exchange context.
 */
void CCheckForUpdatesDlg::DoDataExchange(CDataExchange* pDX)
{
	// Call base class data exchange
	CDialogEx::DoDataExchange(pDX);
	// Map status message label control
	DDX_Control(pDX, IDC_STATUS, m_ctrlStatusMessage);
	// Map progress bar control (shows marquee animation during update check)
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}

// Message map - connects Windows messages to handler functions
BEGIN_MESSAGE_MAP(CCheckForUpdatesDlg, CDialogEx)
	ON_WM_TIMER()  // Handle timer events for monitoring thread completion
END_MESSAGE_MAP()

// ===== Global variables for inter-thread communication =====

/**
 * @brief Global pointer to the active update dialog.
 * 
 * Used by the background thread to update UI elements (status message, progress bar).
 * Must be set before starting the update thread and cleared when dialog is destroyed.
 */
CCheckForUpdatesDlg* g_dlgCheckForUpdates = nullptr;

/**
 * @brief Callback function for genUp4win library to report status updates.
 * 
 * Called by the update checking library to report progress and status messages.
 * Updates the dialog's status label with the provided message.
 * 
 * This function is called from the background thread, so it must be thread-safe.
 * The UpdateWindow() call ensures immediate display of the message.
 * 
 * @param Unused status code parameter (reserved for future use).
 * @param strMessage Status message to display to the user.
 */
void UI_Callback(int, const std::wstring& strMessage)
{
	// Check if dialog still exists (may be null if dialog was closed)
	if (g_dlgCheckForUpdates != nullptr)
	{
		// Update status message label with new text
		g_dlgCheckForUpdates->m_ctrlStatusMessage.SetWindowText(strMessage.c_str());
		// Force immediate repaint to show the message
		g_dlgCheckForUpdates->m_ctrlStatusMessage.UpdateWindow();
	}
}

/**
 * @brief Flag indicating whether the update check thread is currently running.
 * 
 * Set to true when the thread starts, false when it completes.
 * Used by OnCancel() to wait for thread completion before closing dialog.
 * Used by OnTimer() to detect when to close the dialog automatically.
 */
bool g_bThreadRunning = false;

/**
 * @brief Flag indicating whether a new update was found.
 * 
 * Set to true by UpdateThreadProc if the genUp4win library finds an available update.
 * Checked by OnTimer() to determine if the application should exit (to allow installer to run).
 */
bool g_bNewUpdateFound = false;

/**
 * @brief Background thread function that performs the update check.
 * 
 * This function runs in a separate thread to avoid blocking the UI:
 * 1. Sets g_bThreadRunning to true
 * 2. Starts the progress bar marquee animation
 * 3. Gets the current executable path
 * 4. Calls CheckForUpdates() from genUp4win library
 * 5. Stops the progress bar animation
 * 6. Sets g_bThreadRunning to false
 * 7. Exits the thread
 * 
 * The CheckForUpdates() function:
 * - Downloads version information from APPLICATION_URL
 * - Compares with current version
 * - If update available, downloads and launches installer
 * - Reports status via UI_Callback
 * 
 * @param lpParam Pointer to thread parameters (unused, can be nullptr).
 * @return Thread exit code (always 0).
 */
DWORD WINAPI UpdateThreadProc(LPVOID lpParam)
{
	// Suppress compiler warning about unused parameter
	UNREFERENCED_PARAMETER(lpParam);

	// Signal that thread is running
	g_bThreadRunning = true;

	// Start progress bar marquee animation (continuous scrolling)
	if (g_dlgCheckForUpdates != nullptr)
	{
		// TRUE = enable marquee mode, 30 = animation speed in milliseconds
		g_dlgCheckForUpdates->m_ctrlProgress.SetMarquee(TRUE, 30);
	}

	// Get the full path to the current executable
	const DWORD nLength = 0x1000; // 4096 bytes (sufficient for MAX_PATH)
	TCHAR lpszFilePath[nLength] = { 0, };
	GetModuleFileName(nullptr, lpszFilePath, nLength);

	// Check for updates using genUp4win library
	// - lpszFilePath: Path to current executable (to read version info)
	// - APPLICATION_URL: Server URL containing version information
	// - UI_Callback: Function to call with status updates
	// Returns true if a new update was found and installer was launched
	g_bNewUpdateFound = CheckForUpdates(lpszFilePath, APPLICATION_URL, UI_Callback);

	// Stop progress bar animation
	if (g_dlgCheckForUpdates != nullptr)
	{
		// FALSE = disable marquee mode
		g_dlgCheckForUpdates->m_ctrlProgress.SetMarquee(FALSE, 30);
	}

	// Signal that thread has completed
	g_bThreadRunning = false;

	// Exit the thread cleanly
	::ExitThread(0);
	// Note: return statement is unreachable after ExitThread
	// return 0;
}

/**
 * @brief Initializes the update check dialog.
 * 
 * Performs the following initialization:
 * - Calls base class initialization
 * - In debug builds: Creates a config file with installer URL for testing
 * - Sets the global dialog pointer for thread communication
 * - Creates the background thread to perform the update check
 * - Starts a timer (100ms interval) to monitor thread completion
 * 
 * The timer is used to automatically close the dialog when the update
 * check completes, and to trigger application exit if an update is found.
 * 
 * @return TRUE to set focus to the first control, FALSE if focus was set manually.
 */
BOOL CCheckForUpdatesDlg::OnInitDialog()
{
	// Call base class initialization
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	// Debug builds: Create configuration file for update testing
	// This allows testing the update mechanism without deploying to a server
	const DWORD nLength = 0x1000; // 4096 bytes
	TCHAR lpszFilePath[nLength] = { 0, };
	// Get path to current executable
	GetModuleFileName(nullptr, lpszFilePath, nLength);
	// Write config file with installer URL next to the executable
	WriteConfigFile(lpszFilePath, INSTALLER_URL);
#endif

	// Set global pointer so background thread can access dialog controls
	g_dlgCheckForUpdates = this;

	// Create background thread to perform update check
	// This prevents UI blocking during network operations
	m_hUpdateThread = ::CreateThread(
		nullptr,                              // Default security attributes
		0,                                    // Default stack size
		(LPTHREAD_START_ROUTINE)UpdateThreadProc, // Thread function
		this,                                 // Thread parameter (dialog pointer)
		0,                                    // Start immediately (not suspended)
		&m_nUpdateThreadID);                  // Receives thread ID

	// Start timer to monitor thread completion (fires every 100ms)
	// Timer ID 0x1234 is used to identify our timer in OnTimer()
	m_nTimerID = SetTimer(0x1234, 100, nullptr);

	return TRUE;  // Let framework set focus to first control
}

/**
 * @brief Handles the Cancel button or ESC key press.
 * 
 * Waits for the update check thread to complete before closing the dialog.
 * This ensures the thread has finished its work and cleaned up resources
 * before the dialog is destroyed.
 * 
 * The function blocks (sleeps 1 second at a time) while g_bThreadRunning is true.
 * Once the thread completes, calls base class OnCancel() to close the dialog.
 */
void CCheckForUpdatesDlg::OnCancel()
{
	// Wait for background thread to complete before closing dialog
	// This prevents premature destruction of dialog while thread is still running
	while (g_bThreadRunning)
		Sleep(1000);  // Sleep 1 second and check again

	// Thread has completed - safe to close dialog
	CDialogEx::OnCancel();
}

/**
 * @brief Handles timer events to monitor update check completion.
 * 
 * Called every 100 milliseconds (as specified in SetTimer call).
 * 
 * When the background thread completes (g_bThreadRunning becomes false):
 * 1. Kills the timer (no longer needed)
 * 2. Closes the dialog automatically
 * 3. If an update was found (g_bNewUpdateFound is true):
 *    - Posts WM_QUIT message to exit the application
 *    - This allows the installer (launched by genUp4win) to run
 *    - The installer typically needs the application to exit before updating
 * 
 * @param nIDEvent The timer identifier.
 */
void CCheckForUpdatesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// Call base class timer handler first
	CDialogEx::OnTimer(nIDEvent);

	// Check if this is our timer event
	if (m_nTimerID == nIDEvent)
	{
		// Check if background thread has completed
		if (!g_bThreadRunning)
		{
			// Thread finished - clean up timer
			VERIFY(KillTimer(m_nTimerID));

			// Close the dialog automatically
			CDialogEx::OnCancel();

			// If a new update was found and installer was launched
			if (g_bNewUpdateFound)
			{
				// Exit the application to allow installer to update files
				// The installer cannot update files while they are in use
				PostQuitMessage(0);
			}
		}
	}
}
