#pragma once

namespace transfer
{
	std::vector<std::wstring> spliter(std::wstring arg_path)
	{
		std::vector<std::wstring> splited_path;

		wchar_t drive[MAX_PATH];
		wchar_t file_name[MAX_PATH];
		wchar_t file_extension[MAX_PATH];
		wchar_t directory[MAX_PATH];

		_wsplitpath(arg_path.c_str(), drive, directory, file_name, file_extension);

		splited_path.push_back(drive);
		splited_path.push_back(directory);
		splited_path.push_back(file_name);
		splited_path.push_back(file_extension);

		return splited_path;
	}

	bool copy_file(std::wstring arg_source, std::wstring arg_destination)
	{
		if (CopyFileW(arg_source.c_str(), arg_destination.c_str(), FALSE))
			return true;
		else
			return false;
	}

	namespace download
	{
		void path(std::wstring arg_target_address, std::wstring arg_source_path, std::wstring arg_destination_path)
		{
			if (arg_source_path.find(L":"))
			{
				std::vector<std::wstring> splited_path = spliter(arg_source_path);

				std::wstring full_path_source = L"\\\\";
				full_path_source.append(arg_target_address);
				full_path_source.append(g_ShareName);
				full_path_source.append(L"\\");
				full_path_source.append(splited_path.at(1));
				full_path_source.append(splited_path.at(2));
				full_path_source.append(splited_path.at(3));

				if (copy_file(full_path_source, arg_destination_path))
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::ok(L"File Downloaded: ", full_path_source);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::error(L"File not Downloaded: ", full_path_source);
					print::output::break_line();
				}

			}
			else
			{
				std::wstring source_path = L"\\\\";
				source_path.append(arg_target_address);
				source_path.append(L"\\C$\\");
				source_path.append(g_SystemModifiablePath);
				source_path.append(arg_source_path);

				if (copy_file(source_path, arg_destination_path))
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::ok(L"File Downloaded: ", source_path);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::error(L"File not Downloaded: ", source_path);
					print::output::break_line();
				}
			}
		}

		void disptacher(std::wstring arg_target_address)
		{
			std::wstring source_path;
			std::wstring destination_path;
			std::wcin >> source_path >> destination_path;
			path(arg_target_address, source_path, destination_path);
		}
	}

	namespace upload
	{
		void path(std::wstring arg_target_address, std::wstring arg_source_path, std::wstring arg_destination_path)
		{
			if (arg_destination_path.find(L":"))
			{
				std::vector<std::wstring> splited_path = spliter(arg_destination_path);

				std::wstring full_path_source = L"\\\\";
				full_path_source.append(arg_target_address);
				full_path_source.append(g_ShareName);
				full_path_source.append(L"\\");
				full_path_source.append(splited_path.at(1));
				full_path_source.append(splited_path.at(2));
				full_path_source.append(splited_path.at(3));

				if (copy_file(arg_source_path, full_path_source))
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::ok(L"File Uploaded: ", arg_source_path);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::error(L"File not Uploaded: ", arg_source_path);
					print::output::break_line();
				}

			}
			else
			{
				std::wstring destination_path = L"\\\\";
				destination_path.append(arg_target_address);
				destination_path.append(L"\\C$\\");
				destination_path.append(g_SystemModifiablePath);
				destination_path.append(arg_destination_path);

				if (copy_file(arg_source_path, destination_path))
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::ok(L"File Uploaded: ", arg_source_path);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::indent(L"\t");
					print::output::error(L"File not Uploaded: ", arg_source_path);
					print::output::break_line();
				}
			}
		}

		void disptacher(std::wstring arg_target_address)
		{
			std::wstring source_path;
			std::wstring destination_path;
			std::wcin >> source_path >> destination_path;
			path(arg_target_address, source_path, destination_path);
		}
	}
}