#include "errors_handling.h"

static void error_processing(const int code, const std::string& message)
{
	switch (code)
	{
		case FAIL_DIR:
			std::cout << RED << "Failed to create directory: " << message << std::endl;
			exit(1);
		case OPEN_FILE:
			std::cout << RED << "Failed to open file " << message << std::endl;
			exit(2);
	}
}
