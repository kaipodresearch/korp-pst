#pragma once

namespace file_manager
{
	void interactive_parser(std::wstring arg_target_address, std::wstring arg_username)
	{
		std::wstring commands;
		print::output::ok(L"[+] ", L"You have been logged into " + arg_target_address);
		print::output::ok(L"You are currently at c:\\", L"\n");

		// cmd is a function that show machine address and the current directory
		// that the file manager can work with that
		print::output::cmd(arg_target_address, g_SystemModifiablePath, FM_CMD);

		// commands store the commands the user enter into the program
		// based on these command we execute tasks.
		while (std::wcin >> commands)
		{
			// Transform will changes commands characters to the lower cases.
			std::transform(commands.begin(), commands.end(), commands.begin(), ::tolower);

			if (commands == L"help" || commands == L"?")
			{
				// Help command show information about commands that file manager supports.
				pst::help();
			}
			else if (commands == L"version")
			{
				// version will show information about the file manager
				pst::version();
			}
			else if (commands == L"cd")
			{
				// change will used for directory change and path traverse.
				filesystem::directories::change(arg_target_address, arg_username);
			}
			else if (commands == L"dir")
			{
				// list will show directory contents
				filesystem::directories::list(arg_target_address);
			}
			else if (commands == L"del")
			{
				// del used for delete a directory or file on the current working directory or absolute path
				filesystem::directories::del(arg_target_address);
			}
			else if (commands == L"mk")
			{
				// mk used for create a directory or file on the current working directory or absolute path
				filesystem::directories::make(arg_target_address);
			}
			else if (commands == L"show")
			{
				// show used to watch file and directory attributes
				std::wstring format, path;
				std::wcin >> format >> path;
				attribute::show(arg_target_address, format, path);
			}
			else if (commands == L"set")
			{
				// set used to change file and directory attribute
				std::wstring format, path;
				std::wcin >> format >> path;
				attribute::set(arg_target_address, format, path);
			}
			else if (commands == L"console")
			{
				// console used to trigger cmd.exe on remote machine
				console::dispatcher(arg_target_address);
			}
			else if (commands == L"rdp")
			{
				// rdp make a remote desktop connection with the machine we have connected to.
				rdp::connect(arg_target_address);
			}
			else if (commands == L"download")
			{
				// download used to transfer a file from target machine to the machine our program is executing on that.
				transfer::download::disptacher(arg_target_address);
			}
			else if (commands == L"upload")
			{
				// upload used to transfer a file from host machine to target machine
				transfer::upload::disptacher(arg_target_address);
			}
			else if (commands == L"cls")
			{
				// cls clear console screen
				console::clear(GetStdHandle(STD_OUTPUT_HANDLE));
			}
			else if (commands == L"exit")
			{
				// exit used to quit the program and also cleans content in storage directory
				finalization::exit();
			}
			else
			{
				print::output::error(L"[-] ", L"The command isn't supported.");
			}
			print::output::cmd(arg_target_address, g_SystemModifiablePath, FM_CMD);
		}
	}
}