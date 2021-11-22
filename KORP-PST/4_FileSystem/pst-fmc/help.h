#pragma once

namespace pst
{
	void help()
	{
		std::wstring help_message = FM_FULL;
		help_message.append(L" supports following commands:\n");
		
		print::output::break_line();
		print::unformated::cyan(help_message);
		print::output::banner(L"********", L"***********");
		print::output::banner(L"COMMANDS", L"DESCRIPTION");
		print::output::banner(L"********", L"***********");
		print::output::break_line();

		print::output::info(L"help\t\t\t\t", L"show help menu");
		print::output::info(L"cls\t\t\t\t", L"clears console output");
		print::output::info(L"dir\t\t\t\t", L"show directory contents");
		print::output::info(L"cd\t\t\t\t", L"change current working directory");
		print::output::info(L"mk\t\t\t\t", L"make files and directories on file system");
		print::output::info(L"del\t\t\t\t", L"delete files and directories on the file system");
		print::output::info(L"console\t\t\t\t", L"execute PsExec with CMD in fm environment");
		print::output::info(L"rdp\t\t\t\t", L"make a rdp connection with the remote machine");
		print::output::info(L"show\t\t\t\t", L"view timestamp of a file/directory");
		print::output::info(L"set\t\t\t\t", L"set timestamp of a file/directory to a customized time");
		print::output::info(L"download\t\t\t", L"download files from remote machine");
		print::output::info(L"upload\t\t\t\t", L"upload files to remote machine");
		print::output::info(L"version\t\t\t\t", L"show current version of the program");
		print::output::info(L"exit\t\t\t\t", L"exit the program");
		print::output::break_line();
	}

	void version()
	{
		print::output::break_line();
		print::unformated::cyan(L"File Manager Program Information:");

		print::output::break_line();
		print::output::info(L"Name:\t\t\t", FM);
		print::output::info(L"Version:\t\t", FM_VERSION);
		print::output::info(L"Developer:\t\t", FM_AUTHOR);
		print::output::info(L"Architecture:\t\t", FM_ARCH);
		print::output::break_line();
	}
}