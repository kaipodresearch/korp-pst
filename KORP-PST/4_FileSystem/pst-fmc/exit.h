#pragma once

namespace finalization
{
	void exit()
	{
		bool status = FALSE;
		STARTUPINFOW si = { 0 };
		PROCESS_INFORMATION pi = { 0 };

		std::wstring path_bat = filesystem::directories::current_path();
		path_bat.append(L"\\storage");

		std::filesystem::remove_all(path_bat);

		ExitProcess(0);
	}
}