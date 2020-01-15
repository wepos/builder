#include <iostream>

/*
	0 - OK
	1 - ошибка создания дирректории
	2 - ошибка открытия файла
*/

enum ERRORS {OK, FAIL_DIR, OPEN_FILE};

#define RED "\033[31m"

static void error_processing(const int code, const std::string& message)
