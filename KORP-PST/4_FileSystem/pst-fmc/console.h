#pragma once

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define WFILE WIDE1(__FILE__)

/* Standard error macro for reporting API errors */
#define APIERRORW(arg_success, api){if(!(arg_success)) wprintf(L"%ws:Error %d from %ws on line %d\n", WFILE, GetLastError(), api, __LINE__);}

namespace console
{
	void clear(HANDLE arg_handle_console)
	{
		COORD coordination_screen = { 0, 0 };
		BOOL success;
		DWORD chars_written;
		CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
		DWORD dw_ConsoleSize;

		success = GetConsoleScreenBufferInfo(arg_handle_console, &console_screen_buffer_info);
		APIERRORW(success, L"GetConsoleScreenBufferInfo");
		dw_ConsoleSize = console_screen_buffer_info.dwSize.X * console_screen_buffer_info.dwSize.Y;

		/* fill the entire screen with blanks */
		success = FillConsoleOutputCharacter(arg_handle_console, (wchar_t)' ', dw_ConsoleSize, coordination_screen, &chars_written);
		APIERRORW(success, L"FillConsoleOutputCharacter");

		/* get the current text attribute */
		success = GetConsoleScreenBufferInfo(arg_handle_console, &console_screen_buffer_info);
		APIERRORW(success, L"ConsoleScreenBufferInfo");

		/* now set the buffer's attributes accordingly */
		success = FillConsoleOutputAttribute(arg_handle_console, console_screen_buffer_info.wAttributes, dw_ConsoleSize, coordination_screen, &chars_written);
		APIERRORW(success, L"FillConsoleOutputAttribute");

		/* put the cursor at (0, 0) */
		success = SetConsoleCursorPosition(arg_handle_console, coordination_screen);
		APIERRORW(success, L"SetConsoleCursorPosition");
	}

	bool execute_command(std::wstring arg_target_address)
	{
		STARTUPINFOW startup_info = { 0 };
		PROCESS_INFORMATION process_information = { 0 };
		startup_info.cb = sizeof(startup_info);

		std::wstring full_command = L"PsExec.exe -nobanner \\\\";
		full_command.append(arg_target_address);
		full_command.append(L" cmd.exe");

		if (!CreateProcessW(NULL, const_cast<LPWSTR>(full_command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_information))
		{
			print::output::error(L"[-]", L"ERROR: PsExec failed.");
			return false;
		}
		else
		{
			// Wait until child process exits.
			WaitForSingleObject(process_information.hProcess, INFINITE);

			// Close process and thread handles. 
			CloseHandle(process_information.hProcess);
			CloseHandle(process_information.hThread);
		}

		return true;
	}

	void dispatcher(std::wstring arg_target_address)
	{
		std::wstring commands;
		std::getline(std::wcin, commands);

		if (commands.empty())
		{
			execute_command(arg_target_address);
		}
		else if (commands.find(L"--local") != std::wstring::npos)
		{
			execute_command(arg_target_address);
		}
		else if (commands.find(L"--ip") != std::wstring::npos)
		{
			std::wstring remote_ip;
			std::wcout << "\n\tEnter Remote Machine Address: ";
			std::getline(std::wcin, remote_ip);
			execute_command(remote_ip);
		}
		else
		{
			print::output::break_line();
			print::output::error(L"[-]", L" [Wrong] Usage: console --local / --ip [ADDRESS].");
			print::output::break_line();
		}
	}
}