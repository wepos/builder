#pragma once
#include <string>

#define RED "\033[31m" // red color message

enum ERRORS {	 		// error code
	OK,
	FAIL_DIR,
	FAIL_OPEN_FILE,
	BAD_IFSTREAM,
	FAIL_OPEN_DIR,
	UNKNOWN_TYPE,
	MAKE_DIR,
	CHANGE_DIR,
	LSTAT,
	WRONG_KEY,
	SYSERROR
};

void print_err_message(const std::string& err, const std::string& message="")
{
	std::cout << RED << err << ": " << message << std::endl;
}

void error_processing(const int code, const std::string& message="")
{
	switch (code)
	{
		case OK:
			return ;
		case FAIL_DIR:
			print_err_message("Failed to create directory", message); break;
		case FAIL_OPEN_FILE:
			print_err_message("Failed to open file", message); break;
		case BAD_IFSTREAM:
			print_err_message("Bad file stream", message); break;
		case FAIL_OPEN_DIR:
			print_err_message("Failed to open directory", message); break;
		case UNKNOWN_TYPE:
			print_err_message("unknown type"); break;
		case MAKE_DIR:
			print_err_message("Failed make directory", message); break;
		case CHANGE_DIR:
			print_err_message("Fail directory change", message); break;
		case LSTAT:
			print_err_message("It was not possible to obtain information about the file", message); break;
		case WRONG_KEY:
			print_err_message("Wrong key", message); break;
		case SYSERROR:
			print_err_message("Couldn't execute the command", message); break;
	}
	std::cout << RED << "ERROR CODE " << code << std::endl;
	exit(code);
}