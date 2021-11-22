#pragma once

namespace init
{
	void app_icon()
	{
		LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	}

	bool configure(std::wstring arg_target_address)
	{
		g_RootDrive = L"C:\\";
		g_CurrentPath = L"\\\\" + arg_target_address;
		g_ShareName = L"\\C$";
		g_CurrentPath.append(g_ShareName);

		g_SystemModifiablePath = L"\\";
		g_CurrentPath.append(g_SystemModifiablePath);

		return true;
	}

	bool connection(std::wstring arg_current_path, std::wstring arg_file_name)
	{
		if (filesystem::files::create_file(arg_current_path, arg_file_name))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool dispathcer(std::wstring arg_target_address, std::wstring arg_username)
	{
		// We work with path in this program frequently
		// here we configure default path to work with it
		// We will work with a path like \\\\TARGET Address\C$\

		configure(arg_target_address);

		// Here we check we have a reliable connection with target machine 
		// if we have connection, we run interactive menu to parse commands
		// If \\IP\C$\pst-test.txt created we can deduce we have a reliable connection with the machine
		if (connection(g_CurrentPath, L"pst-test.txt"))
		{
			if (GetLastError() != 0)
			{
				// If we haven't a reliable connection with remote machine
				// these messages will show to the user.
				print::output::error(L"[-] ", L"Connection to remote PC with CIFS is failed.");
				print::output::error(L"[-] ", L"Maybe CIFS (share folder) isn't enabled.");
				print::output::ok(L"[+] ", L"Program has been finished, Bye!");
				system("PAUSE");
				return false;
			}
			else
			{
				print::output::ok(L"[+] ", L"You have connected to remote machine with CIFS successfully.");
				// Here we delete the file we created for connection test
				filesystem::files::del(g_CurrentPath, L"pst-test.txt");
				// Here we call main function of the file manager to run commands
				file_manager::interactive_parser(arg_target_address, arg_username);
				return true;
			}
		}
		else
		{
			print::output::error(L"[-] ", L"Connection to remote PC with CIFS is failed.");
			print::output::error(L"[-] ", L"Maybe CIFS (share folder) isn't enabled.");
			print::output::ok(L"[+] ", L"Program has been finished, Bye!");
			system("PAUSE");
			return false;
		}
		return true;
	}
}