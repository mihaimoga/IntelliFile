# AGENTS.md — Developer & AI Agent Guidelines for IntelliFile

This document provides architectural context, development guidelines, build instructions, and coding standards for AI agents and developers working on the **IntelliFile** codebase.

---

## 1. Project Overview

**IntelliFile** is a fast, lightweight, dual-pane Win32 file manager written in C++ using the Microsoft Foundation Classes (MFC), Win32 API, and the Standard Template Library (STL). It is licensed under the **GNU General Public License v3.0 (GPLv3)**.

### Key Capabilities
- Dual-pane file management (navigation, copy, move, delete, rename, search).
- Multi-format file viewing and editing:
  - Text files with syntax highlighting via **Scintilla** and **Lexilla**.
  - Binary/Hex files via **HexCtrl** (C++20 module-based hex editor).
  - Web/HTML preview using **Microsoft Edge WebView2**.
  - Rich text, image, and audio previews.
  - Base64 encode/decode utilities.
- Auto-updating mechanism via **genUp4win**.

---

## 2. Repository & Solution Structure

The solution `IntelliFile.sln` contains the following projects:

| Project | Location | Language / Standard | Role |
|---|---|---|---|
| **IntelliFile** | `IntelliFile.vcxproj` | C++ Latest (`stdcpplatest`), C Latest (`stdclatest`) | Main MFC application executable. Uses static MFC linking and Unicode character set. |
| **Scintilla** | `scintilla\win32\Scintilla.vcxproj` | C++17 (`stdcpp17`) | Scintilla source code editing control. |
| **Lexilla** | `lexilla\src\Lexilla.vcxproj` | C++17 | Lexer library providing syntax highlighting for Scintilla. |
| **genUp4win** | `genUp4win\genUp4win.vcxproj` | C++ Latest (`stdcpplatest`) | Application auto-updater executable. |
| **Setup** | `Setup\Setup.vdproj` | Visual Studio Installer | Windows installer setup project. |

### Core Architecture & Key Files

- **Application Entry & Framework:**
  - `IntelliFile.h` / `IntelliFile.cpp`: Application class `CIntelliFileApp` initializing MFC, OLE, and common controls.
  - `MainFrame.h` / `MainFrame.cpp`: Main frame window class `CMainFrame`, managing ribbon/toolbar, status bar, and dual view panes.
  - `stdafx.h` / `stdafx.cpp`: Precompiled header including MFC, Win32 SDK headers, and WIL.
  - `Resource.h` / `IntelliFile.rc` / `res/IntelliFile.rc2`: Windows resource definitions (menus, dialogs, ribbons, icons, bitmaps).

- **File Views & Listing:**
  - `FileView.h` / `FileView.cpp`: Pane view hosting the file list controls.
  - `FileList.h` / `FileList.cpp`: File and directory enumeration and management.
  - `MFCListView.h` / `MFCListView.cpp`: Custom MFC list view implementation.
  - `SortListCtrl.h` / `SortListCtrl.cpp`: Multi-column sortable list control.

- **Integrated Viewers & Dialogs:**
  - `ViewTextFileDlg.h` / `ViewTextFileDlg.cpp`: Text file viewer using Scintilla with syntax highlighting.
  - `ViewBinaryFileDlg.h` / `ViewBinaryFileDlg.cpp`: Binary file viewer using HexCtrl.
  - `ViewImageFileDlg.h` / `ViewImageFileDlg.cpp`: Image viewer.
  - `ViewAudioFileDlg.h` / `ViewAudioFileDlg.cpp`: Audio preview dialog.
  - `ViewRichFileDlg.h` / `ViewRichFileDlg.cpp`: Rich text (RTF) viewer.
  - `WebBrowserDlg.h` / `WebBrowserDlg.cpp`: Edge WebView2 browser preview.
  - `SearchFileDlg.h` / `SearchFileDlg.cpp`: Multi-threaded full-text file search dialog.
  - `SelectFileDlg.h` / `SelectFileDlg.cpp`: File pattern and attribute selection.
  - `Base64Dlg.h` / `Base64Dlg.cpp`: Base64 encode/decode dialog.
  - `ChangeDriveDlg.h`, `NewFolderDlg.h`, `QuickAccessDlg.h`, `CheckForUpdatesDlg.h`: Utility dialogs.

- **Third-Party & Modular Subsystems:**
  - `HexCtrl/`: Modern C++20 module-based hex editor control (`.ixx` files).
  - `base64.h` / `base64.cpp`: René Nyffenegger's Base64 codec.
  - `FolderDlg.h` / `FolderDlg.cpp`, `FilteredFolderDlg.h` / `FilteredFolderDlg.cpp`: Folder selection dialogs.
  - `HLinkCtrl.h`, `sinstance.h`, `VersionInfo.h`, `WndResizer.h`: PJ Naughter & Mizan Rahman MFC helper utilities.

- **NuGet Dependencies (`packages.config`):**
  - `Microsoft.Web.WebView2`
  - `Microsoft.Windows.ImplementationLibrary` (WIL)

---

## 3. Build & Configuration Instructions

### Prerequisites
- Microsoft Visual Studio 2022 (v143/v145 platform toolset) with:
  - C++ MFC for v143/v145 build tools (x86 & x64)
  - C++ Modules component
  - Windows 10/11 SDK (10.0+)
- NuGet package manager (packages restored automatically during build).

### Build Configurations & Targets
- Supported Configurations: `Debug`, `Release`
- Supported Platforms: `x64`, `Win32`, `ARM64`

### Command-Line Build
```powershell
# Build entire solution for x64 Debug
msbuild IntelliFile.sln /p:Configuration=Debug /p:Platform=x64

# Build entire solution for x64 Release
msbuild IntelliFile.sln /p:Configuration=Release /p:Platform=x64

# Build main IntelliFile project only
msbuild IntelliFile.vcxproj /p:Configuration=Debug /p:Platform=x64
```

---

## 4. Coding Standards & Conventions

All contributions and agent edits must strictly adhere to the project conventions established in `CONTRIBUTING.md`:

### 4.1. Indentation & Spacing
- **Tabs over Spaces**: Always use **tabs** (tab width = 4 spaces) for indentation, never spaces.
- **Operator Spacing**: Always leave one space before and after binary and ternary operators:
  ```cpp
  // Good:
  if (a == 10 && b == 42)

  // Bad:
  if (a==10&&b==42)
  ```
- **Loop Semicolons**: Leave one space after semicolons in `for` statements:
  ```cpp
  // Good:
  for (int i = 0; i != 10; ++i)
  ```
- **Parentheses Spacing**:
  - Do NOT place a space between a function name and `(`: `foo(arg);` (Good) vs `foo (arg);` (Bad).
  - DO place one space between keywords and `(`: `if (condition)`, `while (running)`.

### 4.2. Braces & Structure
- **Allman Style for Multi-line Blocks**: Opening curly braces on their own newline:
  ```cpp
  void MyClass::method1()
  {
	  if (aCondition)
	  {
		  // Do something
	  }
  }
  ```
- **One-line methods in headers**: In `.h` files, single-line method bodies may be placed inline:
  ```cpp
  int getCount() const { return _count; }
  ```
- **Switch Indentation**:
  ```cpp
  switch (test)
  {
	  case 1:
	  {
		  // Do something
		  break;
	  }
	  default:
		  // Do something else
  }
  ```

### 4.3. Naming Conventions
- **Classes**: PascalCase (e.g., `CMainFrame`, `CFileView`).
- **Methods & Parameters**: camelCase (e.g., `refreshView()`, `filePath`).
- **Member Variables**: Prefix with an underscore `_` (e.g., `_publicAttribute`, `_pPrivateAttribute`).
- **Descriptive Names**: Avoid single-letter or cryptic variable names; avoid magic numbers (use constants or enums).

### 4.4. Modern C++ Best Practices
- **Brace Initialization**: Prefer uniform curly brace initialization: `MyClass instance{10.4};`.
- **String Checks**: Use `.empty()` or MFC `.IsEmpty()` rather than comparing against `""`.
- **C++ Casts**: Use `static_cast`, `reinterpret_cast`, or `dynamic_cast`; avoid C-style casts `(int)x`.
- **Logical Operators**: Use `!`, `&&`, `||` instead of `not`, `and`, `or`.
- **Increment**: Prefer pre-increment `++i` over post-increment `i++`.
- **Memory & Pointers**:
  - Prefer references over raw pointers.
  - Prefer automatic (stack) variables over heap allocation.
  - Use `std::unique_ptr` for exclusive ownership; avoid `std::shared_ptr` unless shared ownership is explicitly required.
- **Header Discipline**: Never place `using namespace` directives in header files.
- **Comments**: Use C++ single-line comments `//`; avoid block comments `/* ... */`.

---

## 5. Agent Guidelines & Workflow Rules

When working on this repository, AI agents must follow these operational rules:

1. **Context & File Discovery:**
   - Always read and inspect existing files before making edits to preserve local formatting and logic.
   - Respect precompiled header inclusion (`#include "stdafx.h"` must remain the first non-comment line in `.cpp` files).

2. **Resource & ID Management:**
   - When adding dialogs, commands, or UI elements, check `Resource.h` for existing command ID ranges to prevent ID collisions.
   - Keep MFC message maps (`BEGIN_MESSAGE_MAP` / `END_MESSAGE_MAP`) and class declarations (`afx_msg void On...()`) strictly in sync.

3. **Build Verification:**
   - Run a solution build after making changes to ensure zero compiler and linker errors.
   - Address root causes of warnings or compilation failures rather than suppressing them.

4. **Minimal & Focused Edits:**
   - Make compact, targeted modifications without indiscriminate reformatting or whitespace churn.
   - Ensure all new and modified code adheres to the tab-indentation and naming conventions outlined above.
