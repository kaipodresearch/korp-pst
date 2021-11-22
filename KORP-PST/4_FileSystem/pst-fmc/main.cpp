#include "essential.h"
#include "resource.h"
#include "formated_print.h"
#include "help.h"
#include "filesystem.h"
#include "attribute.h"
#include "console.h"
#include "rdp.h"
#include "transfer.h"
#include "exit.h"
#include "file_manager.h"
#include "init.h"


int wmain(int argc, const wchar_t* argv[])
{
	// This function will configure the app icon
	init::app_icon();

	if (argc > 1) 
	{
		// Here we pass arguments of the program to the dispatcher
		// in order to initialize file manager and parse the commands
		init::dispathcer(argv[1], argv[2]);
	}
	else
	{
		// Here we print what is going wrong with the program
		print::output::get_last_error(GetLastError());
	}

	return 0;
}