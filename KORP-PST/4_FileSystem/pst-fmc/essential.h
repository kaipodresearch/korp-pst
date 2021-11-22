#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_WCSTOK

#include <windows.h>
#include <accctrl.h>
#include <aclapi.h>
#include <Shlwapi.h>
#include <strsafe.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <sstream>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "advapi32.lib")

// FMC Program Architecture Configuration
#if defined(_M_X64)
#define FM_ARCH L"x64"
#elif defined(_M_IX86)
#define FM_ARCH L"x86"
#endif

// FMC Version and Release Candidate Configuration
#define FM				L"KORP-PST Console File Manager"
#define FM_CMD			L" -> "
#define FM_VERSION		L"1.0.0"
#define FM_AUTHOR		L"Kaipod Offensive Research Team"
#define FM_FULL			FM L" " FM_VERSION L" (" FM_ARCH L")"


// Global file manager variables
std::wstring g_RootDrive;
std::wstring g_ShareName;
std::wstring g_CurrentPath;
std::wstring g_SystemModifiablePath;
std::wstring g_Commands;
std::wstring g_RemoteTarget;