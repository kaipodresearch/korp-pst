#pragma once

namespace rdp
{
	wchar_t* get_this_path(wchar_t* dest, DWORD destSize)
	{
		if (!dest) return NULL;
		if (MAX_PATH > destSize) return NULL;

		DWORD length = GetModuleFileNameW(NULL, dest, destSize);
		PathRemoveFileSpecW(dest);
		return dest;
	}


	void connect(std::wstring arg_target_address)
	{
		bool status_bat = FALSE;
		STARTUPINFOW si_bat;
		PROCESS_INFORMATION pi_bat;

		ZeroMemory(&si_bat, sizeof(si_bat));
		si_bat.cb = sizeof(si_bat);
		ZeroMemory(&pi_bat, sizeof(pi_bat));

		wchar_t exe_path[MAX_PATH];
		get_this_path(exe_path, MAX_PATH);

		wchar_t path_bat[MAX_PATH] = { 0 };

		wcscpy_s(path_bat, exe_path);
		wcscat_s(path_bat, L"\\storage\\PTHrdp.bat");

		LPWSTR final_bat_path = _wcsdup(path_bat);

		// Execute requirement batch file
		status_bat = CreateProcessW(NULL, final_bat_path, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si_bat, &pi_bat);

		if (status_bat)
		{
			WaitForSingleObject(pi_bat.hProcess, INFINITE);
			CloseHandle(pi_bat.hProcess);
			CloseHandle(pi_bat.hThread);

			bool status_rdp = FALSE;
			STARTUPINFOW si_rdp;
			PROCESS_INFORMATION pi_rdp;

			ZeroMemory(&si_rdp, sizeof(si_rdp));
			si_rdp.cb = sizeof(si_rdp);
			ZeroMemory(&pi_rdp, sizeof(pi_rdp));

			std::wstring command_rdp = L"mstsc /v:";
			command_rdp.append(arg_target_address);
			command_rdp.append(L" /restrictedadmin");
			LPWSTR remote_desktop = _wcsdup(command_rdp.c_str());

			// Execute requirement batch file
			status_rdp = CreateProcessW(NULL, remote_desktop, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si_rdp, &pi_rdp);

			if (status_rdp)
			{
				WaitForSingleObject(pi_rdp.hProcess, INFINITE);
				CloseHandle(pi_rdp.hProcess);
				CloseHandle(pi_rdp.hThread);
			}
			else
			{
				print::output::error(L"[-]", L" Korp-PST failed to connect with RDP.");
			}
		}
	}
}