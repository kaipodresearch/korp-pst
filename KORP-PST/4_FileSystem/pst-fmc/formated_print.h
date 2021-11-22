#pragma once


enum class color_range : uint16_t {
	grey
	, blue
	, green
	, cyan
	, red
	, magenta
	, yellow
	, white
	, on_blue
	, on_red
	, on_magenta
	, on_grey
	, on_green
	, on_cyan
	, on_yellow
	, on_white
	, reset = 0xFF
};

namespace colored_cout_impl
{
	uint16_t get_color_code(const color_range arg_color)
	{
		switch (arg_color)
		{
		case color_range::grey:         return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		case color_range::blue:         return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		case color_range::green:        return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		case color_range::cyan:         return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		case color_range::red:          return FOREGROUND_RED | FOREGROUND_INTENSITY;
		case color_range::magenta:      return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		case color_range::yellow:       return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		case color_range::white:        return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		case color_range::on_blue:      return BACKGROUND_BLUE; //| BACKGROUND_INTENSITY
		case color_range::on_red:       return BACKGROUND_RED;  //| BACKGROUND_INTENSITY
		case color_range::on_magenta:   return BACKGROUND_BLUE | BACKGROUND_RED;  //| BACKGROUND_INTENSITY
		case color_range::on_grey:      return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		case color_range::on_green:     return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		case color_range::on_cyan:      return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		case color_range::on_yellow:    return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
		case color_range::on_white:     return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
		case color_range::reset:
		default: break;
		}
		return static_cast<uint16_t>(color_range::reset);
	}

	uint16_t get_console_attr()
	{
		CONSOLE_SCREEN_BUFFER_INFO buffer_info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
		return buffer_info.wAttributes;
	}

	void set_console_attr(const uint16_t attr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
	}
}

template <typename type>
type& operator<<(type& arg_ostream, const color_range arg_color)
{
	static const uint16_t initial_attributes = colored_cout_impl::get_color_code(color_range::grey);
	static uint16_t background = initial_attributes & 0x00F0;
	static uint16_t foreground = initial_attributes & 0x000F;
	if (arg_color == color_range::reset)
	{
		arg_ostream.flush();
		colored_cout_impl::set_console_attr(initial_attributes);
		background = initial_attributes & 0x00F0;
		foreground = initial_attributes & 0x000F;
	}
	else
	{
		uint16_t set = 0;
		const uint16_t color_code = colored_cout_impl::get_color_code(arg_color);
		if (color_code & 0x00F0)
		{
			background = color_code;
			set = background | foreground;
		}
		else if (color_code & 0x000F)
		{
			foreground = color_code;
			set = background | foreground;
		}
		arg_ostream.flush();
		colored_cout_impl::set_console_attr(set);
	}
	return arg_ostream;
}


namespace print
{
	namespace formated
	{
		void red(std::wstring arg_caption)
		{
			std::wcout << color_range::red << L"\t[" << arg_caption << L"]" << color_range::reset << L"\n";
		}

		void blue(std::wstring arg_caption)
		{
			std::wcout << color_range::blue << L"\t[" << arg_caption << L"]" << color_range::reset << L"\n";
		}

		void yellow(std::wstring arg_caption)
		{
			std::wcout << color_range::yellow << L"\t[" << arg_caption << L"]" << color_range::reset << L"\n";
		}
	}

	namespace unformated
	{
		void red(std::wstring arg_caption)
		{
			std::wcout << color_range::red << L"\t" << arg_caption << color_range::reset << L"\n";
		}

		void blue(std::wstring arg_caption)
		{
			std::wcout << color_range::blue << L"\t" << arg_caption << color_range::reset << L"\n";
		}

		void yellow(std::wstring arg_caption)
		{
			std::wcout << color_range::yellow << L"\t" << arg_caption << color_range::reset << L"\n";
		}

		void cyan(std::wstring arg_caption)
		{
			std::wcout << color_range::cyan << L"\t" << arg_caption << color_range::reset << L"\n";
		}
	}

	namespace output
	{
		void error(std::wstring arg_format, std::wstring arg_message)
		{
			std::wcout << color_range::red << arg_format << color_range::reset << arg_message << L"\n";
		}

		void ok(std::wstring arg_format, std::wstring arg_message)
		{
			std::wcout << color_range::yellow << arg_format << color_range::reset << arg_message << L"\n";
		}
		
		void ok(std::wstring arg_format)
		{
			std::wcout << color_range::yellow << arg_format << color_range::reset;
		}

		void get_last_error(const DWORD arg_error_code)
		{
			wchar_t error_description[256];
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, arg_error_code, 0, error_description, 255, NULL);

			if (GetLastError() != 0)
			{
				error(L"\t[-]", std::wstring(error_description));
			}
			else
			{
				ok(L"\t[+]", std::wstring(error_description));
			}
		}

		void cmd(std::wstring arg_target_address, std::wstring arg_path, std::wstring arg_logo)
		{
			arg_path.erase(arg_path.size() - 1);
			std::wcout << color_range::red << arg_target_address << L" [" << arg_path << L"] " << color_range::cyan << arg_logo << color_range::reset;
		}

		void banner(std::wstring arg_text, std::wstring arg_caption)
		{
			std::wcout << "\t" << color_range::yellow << arg_text << "\t\t\t" << arg_caption << color_range::reset << L"\n";
		}

		void info(std::wstring arg_text, std::wstring arg_caption)
		{
			std::wcout << "\t" << color_range::green << arg_text << color_range::reset << arg_caption << color_range::cyan << L"\n" << color_range::reset;
		}

		void indent(std::wstring arg_indention)
		{
			std::wcout << arg_indention;
		}

		void break_line()
		{
			std::cout << std::endl;
		}
	}
}