#pragma once


namespace attribute
{
	BOOL get_last_write_time_directory(HANDLE arg_file, LPWSTR arg_string, DWORD arg_size)
	{
		FILETIME create_time, access_time, write_time;
		SYSTEMTIME utc, local;
		DWORD status;

		// Retrieve the file times for the file.
		if (!GetFileTime(arg_file, &create_time, &access_time, &write_time))
		{
			return FALSE;
		}

		// Convert the last-write time to local time.
		FileTimeToSystemTime(&write_time, &utc);
		SystemTimeToTzSpecificLocalTime(NULL, &utc, &local);

		// Build a string showing the date and time.
		status = StringCchPrintfW(arg_string, arg_size, L"%02d/%02d/%d %02d:%02d", local.wMonth, local.wDay, local.wYear, local.wHour, local.wMinute);

		if (S_OK == status)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL get_last_write_time(HANDLE arg_file, LPWSTR arg_string, DWORD arg_size)
	{
		FILETIME create_time, access_time, write_time;
		SYSTEMTIME utc, local;
		DWORD status;

		// Retrieve the file times for the file.
		if (!GetFileTime(arg_file, &create_time, &access_time, &write_time))
		{
			return FALSE;
		}

		// Convert the last-write time to local time.
		FileTimeToSystemTime(&write_time, &utc);
		SystemTimeToTzSpecificLocalTime(NULL, &utc, &local);

		// Build a string showing the date and time.
		status = StringCchPrintfW(arg_string, arg_size, L"%02d/%02d/%d %02d:%02d", local.wMonth, local.wDay, local.wYear, local.wHour, local.wMinute);

		if (S_OK == status)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	bool last_access(std::wstring arg_current_path, std::wstring arg_file_name)
	{
		HANDLE handle_file;
		std::wstring path;
		wchar_t buffer[MAX_PATH];

		path = arg_current_path + arg_file_name;
		handle_file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (handle_file == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		if (get_last_write_time(handle_file, buffer, MAX_PATH))
		{
			wprintf(L"\n\t\t");
			print::output::ok(L"Last Accessed: \t", buffer);
			CloseHandle(handle_file);
			return true;
		}

		CloseHandle(handle_file);
		return false;
	}

	bool directory_last_access(std::wstring arg_target_address, std::wstring arg_path)
	{
		HANDLE handle_file;
		wchar_t buffer_last_access_time[MAX_PATH];
		std::wstring path_directory;

		path_directory = L"\\\\" + arg_target_address + g_ShareName + arg_path;

		handle_file = CreateFileW(path_directory.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

		if (handle_file == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		if (get_last_write_time_directory(handle_file, buffer_last_access_time, MAX_PATH))
		{
			wprintf(L"\n\t\t");
			print::output::ok(L"Last Accessed: \t", buffer_last_access_time);
			CloseHandle(handle_file);
			return true;
		}

		CloseHandle(handle_file);
		return false;
	}

	bool create_time(std::wstring arg_current_path, std::wstring arg_file_name)
	{
		HANDLE handle_file;
		FILETIME create_time;
		SYSTEMTIME utc_time;

		std::wstring path = arg_current_path + arg_file_name;
		handle_file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (handle_file == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		if (!GetFileTime(handle_file, &create_time, NULL, NULL))
		{
			return false;
		}
		else
		{
			FileTimeToSystemTime(&create_time, &utc_time);
			wprintf(L"\t\t");
			print::output::ok(L"Created Time: \t");
			wprintf(L"%02d/%02d/%d %02d:%02d\n", utc_time.wDay, utc_time.wMonth, utc_time.wYear, utc_time.wHour, utc_time.wMinute);
			CloseHandle(handle_file);
			return true;
		}
	}

	bool owner(std::wstring arg_current_path, std::wstring arg_file_name)
	{
		PSECURITY_DESCRIPTOR security_descriptor = NULL;
		DWORD return_code = 0;
		PSID sid_owner = NULL;
		HANDLE handle_file;

		BOOL return_bool = TRUE;
		LPWSTR account_name = NULL;
		LPWSTR domain_name = NULL;
		DWORD account_name_dword = 1;
		DWORD domain_name_dword = 1;
		SID_NAME_USE enu_Use = SidTypeUnknown;

		std::wstring path = arg_current_path + arg_file_name;

		handle_file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		return_code = GetSecurityInfo(handle_file, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &sid_owner, NULL, NULL, NULL, &security_descriptor);

		if (handle_file == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		return_code = GetSecurityInfo(handle_file, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &sid_owner, NULL, NULL, NULL, &security_descriptor);
		if (return_code != ERROR_SUCCESS)
		{
			return false;
		}

		return_bool = LookupAccountSidW(NULL, sid_owner, account_name, (LPDWORD)&account_name_dword, domain_name, (LPDWORD)&account_name_dword, &enu_Use);

		account_name = (LPWSTR)GlobalAlloc(GMEM_FIXED, account_name_dword);
		if (account_name == NULL)
		{
			return false;
		}

		domain_name = (LPWSTR)GlobalAlloc(GMEM_FIXED, domain_name_dword);
		if (domain_name == NULL)
		{
			return false;
		}

		return_bool = LookupAccountSidW(NULL, sid_owner, account_name, (LPDWORD)&account_name_dword, domain_name, (LPDWORD)&account_name_dword, &enu_Use);
		if (return_bool == FALSE)
		{
			return false;
		}
		else if (return_bool == TRUE)
		{
			wprintf(L"\t\t");
			print::output::ok(L"Account Owner: ", account_name);
			CloseHandle(handle_file);
			return true;
		}

		CloseHandle(handle_file);
		return false;
	}

	void show(std::wstring arg_target_address, std::wstring arg_format, std::wstring arg_path)
	{
		std::vector<std::wstring> splited_path;
		splited_path = filesystem::directories::spliter(arg_path);

		// Absolute path 
		if (arg_path.find(L":") != std::wstring::npos)
		{
			std::wstring path = L"\\\\" + arg_target_address + g_ShareName + splited_path.at(1);
			if (arg_format == L"-f")
			{
				print::output::break_line();
				print::output::ok(L"\tGet Attribute: ", splited_path.at(2) + splited_path.at(3));
				last_access(path, splited_path.at(2) + splited_path.at(3));
				create_time(path, splited_path.at(2) + splited_path.at(3));
				owner(path, splited_path.at(2) + splited_path.at(3));
				print::output::break_line();

			}
			else if (arg_format == L"-d")
			{
				print::output::break_line();
				print::output::ok(L"\tGet Attribute: ", splited_path.at(1));
				directory_last_access(arg_target_address, splited_path.at(1));
				print::output::break_line();
			}
			else
			{
				print::output::break_line();
				print::output::error(L"[-] ", L"You have used wrong format or path.");
				print::output::ok(L"[+] ", L"Usage: show -f / -d [path]");
				print::output::break_line();
			}
		}
		// Relative path
		else
		{
			if (arg_format == L"-f")
			{
				print::output::break_line();
				print::output::ok(L"\tGet Attribute: ", arg_path);
				last_access(g_CurrentPath, arg_path);
				create_time(g_CurrentPath, arg_path);
				owner(g_CurrentPath, arg_path);
				print::output::break_line();

			}
			else if (arg_format == L"-d")
			{
				print::output::break_line();
				print::output::ok(L"\tGet Attribute: ", splited_path.at(1));
				directory_last_access(arg_target_address, splited_path.at(1));
				print::output::break_line();
			}
			else
			{
				print::output::error(L"\n[-] ", L"You have used wrong format or path.");
				print::output::ok(L"[+] ", L"Usage: show -f / -d [path]\n");
			}
		}
	}

	BOOL set_timestamp_relative(std::wstring arg_path, std::wstring arg_file_name, int arg_year, int arg_month, int ard_day)
	{
		HANDLE handle_file;
		FILETIME file_time;
		SYSTEMTIME system_time;

		std::wstring path_directory = arg_path;
		path_directory.append(arg_file_name);


		handle_file = CreateFileW(path_directory.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		GetSystemTime(&system_time);
		system_time.wYear = arg_year;
		system_time.wMonth = arg_month;
		system_time.wDay = ard_day;

		// Converts the current system time to file time format
		SystemTimeToFileTime(&system_time, &file_time);

		if (SetFileTime(handle_file, &file_time, &file_time, &file_time))
		{
			CloseHandle(handle_file);
			return true;
		}
		else
		{
			return false;
		}
		CloseHandle(handle_file);
	}

	BOOL set_timestamp_absloute(std::wstring arg_computer_name, std::wstring arg_file_path, std::wstring arg_file_name, int arg_year, int arg_month, int ard_day)
	{
		HANDLE handle_file;
		FILETIME file_time;
		SYSTEMTIME system_time;

		std::wstring path = L"\\\\";
		path.append(arg_computer_name);
		path.append(g_ShareName);
		path.append(arg_file_path);
		path.append(arg_file_name);

		handle_file = CreateFileW(path.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		GetSystemTime(&system_time);							// Gets the current system time
		system_time.wYear = arg_year;
		system_time.wMonth = arg_month;
		system_time.wDay = ard_day;

		SystemTimeToFileTime(&system_time, &file_time);		// Converts the current system time to file time format

		if (SetFileTime(handle_file, &file_time, &file_time, &file_time))
		{
			CloseHandle(handle_file);
			return true;
		}
		else
		{
			return false;
		}
		CloseHandle(handle_file);
	}

	void set_file_timestamp(std::wstring arg_target_address, std::wstring arg_path)
	{
		int year = 0;
		int month = 0;
		int day = 0;

		std::wcout << L"\n\t";
		print::unformated::cyan(L"Please input date for timestamp:");

		std::wcout << L"\t\tYear: ";
		std::wcin >> year;

		std::wcout << L"\t\tMonth: ";
		std::wcin >> month;

		std::wcout << L"\t\tDay: ";
		std::wcin >> day;

		if (year != 0 && month != 0 && day != 0)
		{
			std::vector<std::wstring> splited_path;
			splited_path = filesystem::directories::spliter(arg_path);

			if (arg_path.find(L":") != std::wstring::npos)
			{
				set_timestamp_absloute(arg_target_address, splited_path.at(1), splited_path.at(2) + splited_path.at(3), year, month, day);
			}
			else
			{
				set_timestamp_relative(g_CurrentPath, arg_path, year, month, day);
			}

			std::wcout << L"\n\t";
			print::output::ok(L"[+]", L" File timestamp has been changed successfully.\n\n");
		}
		else
		{
			std::wcout << L"\n\t";
			print::output::error(L"[-]", L" USAGE: File [Year] [Month] [Day]\n");
			print::output::error(L"[-]", L" I.E. Sample.txt 1994 4 4\n");
		}
	}


	BOOL set_directory_timestamp_absloute(std::wstring arg_computer_name, std::wstring arg_file_path, int arg_year, int arg_month, int ard_day)
	{
		HANDLE handle_file;
		FILETIME file_time;
		SYSTEMTIME system_time;

		std::wstring path_directory = L"\\\\";
		path_directory.append(arg_computer_name);
		path_directory.append(g_ShareName);
		path_directory.append(arg_file_path);

		handle_file = CreateFileW(path_directory.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

		GetSystemTime(&system_time);
		system_time.wYear = arg_year;
		system_time.wMonth = arg_month;
		system_time.wDay = ard_day;

		SystemTimeToFileTime(&system_time, &file_time);

		if (SetFileTime(handle_file, &file_time, &file_time, &file_time))
		{
			CloseHandle(handle_file);
			return true;
		}
		else
		{
			return false;
		}
		CloseHandle(handle_file);
	}

	BOOL set_directory_timestamp_relative(std::wstring arg_path, std::wstring arg_file_name, int arg_year, int arg_month, int ard_day)
	{
		HANDLE handle_file;
		FILETIME file_time;
		SYSTEMTIME system_time;

		std::wstring path = arg_path;
		path.append(arg_file_name);

		handle_file = CreateFileW(path.c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

		GetSystemTime(&system_time);
		system_time.wYear = arg_year;
		system_time.wMonth = arg_month;
		system_time.wDay = ard_day;

		SystemTimeToFileTime(&system_time, &file_time);

		if (SetFileTime(handle_file, &file_time, &file_time, &file_time))
		{
			CloseHandle(handle_file);
			return true;
		}
		else
		{
			return false;
		}
		CloseHandle(handle_file);
	}

	void set_directory_timestamp(std::wstring arg_target_address, std::wstring arg_path)
	{
		int year = 0;
		int month = 0;
		int day = 0;

		std::wcout << L"\n\t";
		print::unformated::cyan(L"Please input date for timestamp:");

		std::wcout << L"\t\tYear: ";
		std::wcin >> year;

		std::wcout << L"\t\tMonth: ";
		std::wcin >> month;

		std::wcout << L"\t\tDay: ";
		std::wcin >> day;

		if (year != 0 && month != 0 && day != 0)
		{
			std::vector<std::wstring> splited_path;
			splited_path = filesystem::directories::spliter(arg_path);

			if (arg_path.find(L":") != std::wstring::npos)
			{
				set_directory_timestamp_absloute(arg_target_address, splited_path.at(1), year, month, day);
			}
			else
			{
				set_directory_timestamp_relative(g_CurrentPath, arg_path, year, month, day);
			}

			std::wcout << L"\n\t";
			print::output::ok(L"[+]", L" Directory timestamp has been changed successfully.\n\n");
		}
		else
		{
			std::wcout << L"\n\t";
			print::output::error(L"[-]", L" USAGE: File [Year] [Month] [Day]\n");
			print::output::error(L"[-]", L" I.E. Sample 1994 4 4\n");
		}
	}

	void set(std::wstring arg_target_address, std::wstring arg_format, std::wstring arg_path)
	{
		std::vector<std::wstring> splited_path;
		splited_path = filesystem::directories::spliter(arg_path);

		if (arg_format == L"-f")
		{
			print::output::break_line();
			print::output::ok(L"\tSet Attribute: ", arg_path);
			set_file_timestamp(arg_target_address, arg_path);
			print::output::break_line();

		}
		else if (arg_format == L"-d")
		{
			print::output::break_line();
			print::output::ok(L"\tSet Attribute: ", splited_path.at(1));
			set_directory_timestamp(arg_target_address, arg_path);
			print::output::break_line();
		}
		else
		{
			print::output::error(L"\n[-] ", L"You have used wrong format or path.");
			print::output::ok(L"[+] ", L"Usage: set -f / -d [path]\n");
		}
	}
}