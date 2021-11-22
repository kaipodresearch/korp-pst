#pragma once

namespace filesystem
{
	namespace remove
	{
		void item(std::wstring arg_target_address, std::wstring arg_directory_path, std::wstring arg_file_name, std::wstring arg_file_extension)
		{
			std::wstring file_path;
			file_path.append(L"\\\\");
			file_path.append(arg_target_address);
			file_path.append(g_ShareName);
			file_path.append(arg_directory_path);
			file_path.append(arg_file_name);
			file_path.append(arg_file_extension);


			if (std::filesystem::remove(file_path))
			{
				print::output::break_line();
				print::output::ok(L"\t[+] Deleted:\t", arg_file_name + arg_file_extension);
				print::output::break_line();
			}
			else
			{
				print::output::break_line();
				print::output::error(L"\t[-] ~Deleted:\t", arg_file_name + arg_file_extension);
				print::output::break_line();
			}
		}

		void item(std::wstring arg_path)
		{
			std::wstring working_path = g_CurrentPath;

			if (arg_path.find(L".") != std::wstring::npos)
			{
				working_path.append(arg_path);

				if (std::filesystem::remove(working_path))
				{
					print::output::break_line();
					print::output::ok(L"\t[+] Deleted:\t", arg_path);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::error(L"\t[-] ~Deleted:\t", arg_path);
					print::output::break_line();
				}
			}
			else
			{
				arg_path.append(L"\\");
				working_path.append(arg_path);

				if (std::filesystem::remove(working_path))
				{
					print::output::break_line();
					print::output::ok(L"\t[+] Deleted:\t", arg_path);
					print::output::break_line();
				}
				else
				{
					print::output::break_line();
					print::output::error(L"\t[-] ~Deleted:\t", arg_path);
					print::output::break_line();
				}
			}
		}
	}

	namespace files
	{
		BOOL exist(std::wstring arg_path)
		{
			DWORD attribute = GetFileAttributesW(arg_path.c_str());

			return (attribute != INVALID_FILE_ATTRIBUTES && !(attribute & FILE_ATTRIBUTE_DIRECTORY));
		}


		bool del(std::wstring arg_path, std::wstring arg_file_name)
		{
			std::wstring file_path(arg_path);
			file_path.append(arg_file_name);

			if (DeleteFileW(file_path.c_str()))
				return true;
			else
				return false;
		}

		bool create_file(std::wstring arg_path, std::wstring arg_file_name)
		{
			SECURITY_ATTRIBUTES file_security_attribute;
			file_security_attribute.nLength = sizeof(file_security_attribute);
			file_security_attribute.lpSecurityDescriptor = NULL;
			file_security_attribute.bInheritHandle = FALSE;

			std::wstring file_path(arg_path);
			file_path.append(arg_file_name);

			if (!exist(file_path))
			{
				HANDLE handle_created_file = CreateFileW(file_path.c_str(), 0, 0, &file_security_attribute, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

				if (handle_created_file)
				{
					CloseHandle(handle_created_file);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				print::output::break_line();
				print::output::error(L"\t[-] File Exist:\t", arg_file_name);
				print::output::break_line();
				return false;
			}
			return false;
		}

		bool create_file(std::wstring arg_target_address, std::wstring arg_directory, std::wstring arg_file_name, std::wstring arg_file_extension)
		{
			SECURITY_ATTRIBUTES file_security_attribute;
			file_security_attribute.nLength = sizeof(file_security_attribute);
			file_security_attribute.lpSecurityDescriptor = NULL;
			file_security_attribute.bInheritHandle = FALSE;


			std::wstring file_path(L"\\\\");
			file_path.append(arg_target_address);
			file_path.append(g_ShareName);
			file_path.append(arg_directory);
			file_path.append(arg_file_name);
			file_path.append(arg_file_extension);

			//std::wcout << file_path << std::endl;
			if (!exist(file_path))
			{
				HANDLE handle_created_file = CreateFileW(file_path.c_str(), 0, 0, &file_security_attribute, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

				if (handle_created_file)
				{
					CloseHandle(handle_created_file);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				print::output::break_line();
				print::output::error(L"\t[-] File Exist:\t", arg_file_name);
				print::output::break_line();
				return false;
			}
			return false;
		}

		bool create_file(std::wstring arg_file_name)
		{
			SECURITY_ATTRIBUTES file_security_attribute;
			file_security_attribute.nLength = sizeof(file_security_attribute);
			file_security_attribute.lpSecurityDescriptor = NULL;
			file_security_attribute.bInheritHandle = FALSE;

			std::wstring file_path(g_CurrentPath);
			file_path.append(arg_file_name);

			if (!exist(file_path))
			{
				HANDLE handle_created_file = CreateFileW(file_path.c_str(), 0, 0, &file_security_attribute, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

				if (handle_created_file)
				{
					CloseHandle(handle_created_file);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				print::output::break_line();
				print::output::error(L"\t[-] File Exist:\t", arg_file_name);
				print::output::break_line();
				return false;
			}
			return false;
		}
	}

	namespace directories
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

		void del(std::wstring arg_target_address)
		{
			std::wstring dir_path;
			std::wcin >> dir_path;

			if (dir_path.find(L":") != std::wstring::npos)
			{
				if (!dir_path.empty() && dir_path.back() == L'\\')
				{
					dir_path.back() = L' ';
				}
				std::vector<std::wstring> splited_path = spliter(dir_path);
				
				filesystem::remove::item(arg_target_address, splited_path.at(1), splited_path.at(2), splited_path.at(3));
			}
			else
			{
				filesystem::remove::item(dir_path);
			}
		}

		bool absloute_path(std::wstring arg_root_drive, std::wstring arg_computer_name, std::wstring arg_directory)
		{
			g_RootDrive = arg_root_drive;
			g_RootDrive.append(L"\\");

			g_CurrentPath = L"\\\\";
			g_CurrentPath.append(arg_computer_name);

			g_ShareName = L"\\C$\\";
			g_CurrentPath.append(g_ShareName);

			g_SystemModifiablePath = arg_directory;
			g_CurrentPath.append(g_SystemModifiablePath);

			return true;
		}

		bool relative_path(std::wstring arg_directory)
		{
			g_SystemModifiablePath = arg_directory;
			g_CurrentPath.append(arg_directory);

			return true;
		}

		void change_reverse_path(std::wstring arg_root_drive, std::wstring arg_computer_name, std::wstring arg_directory)
		{
			g_RootDrive = arg_root_drive;
			g_RootDrive.append(L":\\");

			g_CurrentPath = L"\\\\";
			g_CurrentPath.append(arg_computer_name);

			g_ShareName = L"\\C$\\";
			g_CurrentPath.append(g_ShareName);

			g_SystemModifiablePath = arg_directory;
			g_CurrentPath.append(g_SystemModifiablePath);
		}

		bool reverse_path_traverse(std::wstring arg_computer_name)
		{
			std::wstring path_buffer;
			wchar_t drive[_MAX_DRIVE];
			wchar_t directory_main[_MAX_DIR], directory_temp[_MAX_DIR];
			wchar_t filename[_MAX_FNAME];
			wchar_t extension[_MAX_EXT];

			path_buffer = g_CurrentPath;

			_wsplitpath(path_buffer.c_str(), drive, directory_main, filename, extension);
			_wsplitpath(path_buffer.c_str(), drive, directory_temp, filename, extension);

			wchar_t* main_token = wcstok(directory_main, L"\\");
			int strings_counter = 0;

			while (main_token != NULL)
			{
				main_token = wcstok(NULL, L"\\");
				strings_counter++;
			}

			wchar_t* temp_token = wcstok(directory_temp, L"\\");
			int strings_counter_temp = strings_counter - 1;

			wchar_t final_modified_path[MAX_PATH];
			wcscpy_s(final_modified_path, L"\\\\");

			for (size_t i = 0; i < strings_counter_temp; i++)
			{
				wcscat(final_modified_path, temp_token);
				wcscat(final_modified_path, L"\\");
				temp_token = wcstok(NULL, L"\\");
			}

			wchar_t* token_base = NULL;
			wchar_t* token_dir = NULL;
			token_base = wcstok_s(final_modified_path, L"\\", &token_dir);

			wchar_t* token_root = NULL;
			wchar_t* token_directory = NULL;
			token_root = wcstok_s(token_dir, L"$", &token_directory);
			change_reverse_path(std::wstring(token_root), arg_computer_name, std::wstring(token_directory));

			return true;
		}

		void root_path(std::wstring arg_target_address)
		{
			g_RootDrive = L"C:\\";
			g_CurrentPath = L"\\\\";
			g_CurrentPath.append(arg_target_address);

			g_ShareName = L"\\C$";
			g_CurrentPath.append(g_ShareName);

			g_SystemModifiablePath = L"\\";
			g_CurrentPath.append(g_SystemModifiablePath);
		}

		void absloute_change(std::wstring arg_target_address, std::wstring arg_dir_path)
		{
			std::vector<std::wstring> splited_path = spliter(arg_dir_path);
			
			std::wstring working_path = L"\\\\";
			working_path.append(arg_target_address);
			working_path.append(L"\\C$");
			working_path.append(splited_path.at(1));

			if (std::filesystem::is_directory(working_path))
			{
				absloute_path(splited_path.at(0), arg_target_address, splited_path.at(1));
			}
			else
			{
				print::output::error(L"[-] Path Invalid: ", arg_dir_path);
			}
		}

		void relative_change(std::wstring arg_target_address, std::wstring arg_dir_path)
		{
			std::wstring relative_path_check = g_CurrentPath;
			relative_path_check.append(arg_dir_path);

			if (std::filesystem::is_directory(relative_path_check))
			{
				if (arg_dir_path == L"..")
				{
					reverse_path_traverse(arg_target_address);
				}
				else if (arg_dir_path == L"/")
				{
					root_path(arg_target_address);
				}
				else
				{
					relative_path(arg_dir_path);
				}
			}
			else
			{
				print::output::error(L"[-] Path Invalid: ", arg_dir_path);
			}
		}

		void change(std::wstring arg_target_address, std::wstring arg_username)
		{
			// Here we get absolute or relative path we wanted to change the path to it
			// and store the into the dir_path variable
			std::wstring dir_path;
			std::wcin >> dir_path;
			
			// We check the last character of the path has a backslash or not
			// if it hasn't backslash, we append it to the path
			// in order we have a standard path like c:\\something\

			if (!dir_path.empty() && dir_path.back() != L'\\')
			{
				dir_path.append(L"\\");
			}

			// we check the path has a colon or not, if it has a colon we can deduce
			// the user entered a absolute path otherwise user enter a relative path
			if (dir_path.find(L":") != std::wstring::npos)
			{
				// change directory to the absolute path
				absloute_change(arg_target_address, dir_path);
			}
			else
			{
				// change directory to the relative path
				relative_change(arg_target_address, dir_path);
			}
		}

		std::wstring current_path() 
		{
			wchar_t buffer[MAX_PATH] = { 0 };
			GetModuleFileName(NULL, buffer, MAX_PATH);
			std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
			return std::wstring(buffer).substr(0, pos);
		}

		void relative_list()
		{
			WIN32_FIND_DATAW find_data_32;
			wchar_t working_path[2048];

			wsprintfW(working_path, L"%ws\\*", g_CurrentPath.c_str());

			HANDLE handle_find = FindFirstFileW(working_path, &find_data_32);

			if (handle_find != INVALID_HANDLE_VALUE) 
			{
				print::output::banner(L"---------------", L"-----------");
				print::output::banner(L"Size (Byte)", L"File Name");
				print::output::banner(L"---------------", L"-----------");

				do 
				{
					ULONGLONG file_size = find_data_32.nFileSizeHigh;
					file_size <<= sizeof(find_data_32.nFileSizeHigh) * 8;
					file_size |= find_data_32.nFileSizeLow;
					std::wcout << L"\n\t" << file_size << L"\t\t\t\t" << find_data_32.cFileName;
				} while (FindNextFileW(handle_find, &find_data_32));

				std::wcout << L"\n\n";
				FindClose(handle_find);
			}
		}

		void list(std::wstring arg_target_address)
		{
			std::wstring dir_path;
			std::wcin >> dir_path;

			if (dir_path == L".")
			{
				relative_list();
			}
			else
			{
				std::vector<std::wstring> splited_path = spliter(dir_path);
				absloute_path(splited_path.at(1), arg_target_address, splited_path.at(2));
				relative_list();
			}
		}

		bool create_directory(std::wstring arg_target_address, std::wstring arg_path)
		{
			std::wstring target_path = L"\\\\";
			target_path.append(arg_target_address);
			target_path.append(g_ShareName);
			target_path.append(arg_path);

			if (std::filesystem::create_directory(target_path))
				return true;
			else
				return false;
		}

		bool create_directory(std::wstring arg_path)
		{
			std::wstring target_path = g_CurrentPath;
			target_path.append(arg_path);
			if (std::filesystem::create_directory(target_path))
				return true;
			else
				return false;
		}

		void make(std::wstring arg_target_address)
		{
			// Here we get absolute or relative path we wanted to change the path to it
			// and store the into the dir_path variable
			std::wstring item_path;
			std::wcin >> item_path;

			std::vector splited_path = spliter(item_path);

			// we check the path has a colon or not, if it has a colon we can deduce
			// the user entered a absolute path otherwise user enter a relative path
			if (item_path.find(L":") != std::wstring::npos)
			{
				if (item_path.find(L".") != std::wstring::npos)
				{
					if (filesystem::files::create_file(arg_target_address, splited_path.at(1), splited_path.at(2), splited_path.at(3)))
					{
						print::output::break_line();
						print::output::ok(L"\t[+] File Created:\t", splited_path.at(2) + splited_path.at(3));
						print::output::break_line();
					}
					else
					{
						print::output::break_line();
						print::output::error(L"\t[-] File ~Created:\t", splited_path.at(2) + splited_path.at(3));
						print::output::break_line();
					}
				}
				else
				{
					if (create_directory(arg_target_address, splited_path.at(1)))
					{
						print::output::break_line();
						print::output::ok(L"\t[+] Directory Created:\t", splited_path.at(1));
						print::output::break_line();
					}
					else
					{
						print::output::break_line();
						print::output::error(L"\t[-] Directory ~Created:\t", splited_path.at(1));
						print::output::break_line();
					}
				}
			}
			else
			{
				if (item_path.find(L".") != std::wstring::npos)
				{
					if (filesystem::files::create_file(item_path))
					{
						print::output::break_line();
						print::output::ok(L"\t[+] File Created:\t", item_path);
						print::output::break_line();
					}
					else
					{
						print::output::break_line();
						print::output::error(L"\t[-] File ~Created:\t", item_path);
						print::output::break_line();
					}
				}
				else
				{
					if (create_directory(item_path))
					{
						print::output::break_line();
						print::output::ok(L"\t[+] Directory Created:\t", item_path);
						print::output::break_line();
					}
					else
					{
						print::output::break_line();
						print::output::error(L"\t[-] Directory ~Created:\t", item_path);
						print::output::break_line();
					}
				}
			}
		}
	}
}