#include "parser_buildlist.h"
#include "build.h"
#include "arr.h"
#include "speed_test.h"
#include <time.h>
#include <stdio.h>

using namespace std;

t_param parse_param(int argc, char **argv)
{
	t_param param;
	bzero(&param, sizeof(t_param));
	if (argc == 1)
		return (param);
	int i = 0;
	while (++i < argc)
	{
		if (strcmp(argv[i], "-re") == 0)
			param.re = true;
		else if (strcmp(argv[i], "-clear") == 0 || strcmp(argv[i], "-c") == 0) 
			param.clear = true;
		else if (strcmp(argv[i], "-show") == 0 || strcmp(argv[i], "-s") == 0)
			param.show = true;
		else
			error_processing(WRONG_KEY, argv[i]);
	}
	return (param);
}

int main(int argc, char **argv)
{
	Parser parser;
	t_param pr = parse_param(argc, argv);
	parser.parse_file();
	std::vector<buildlist> tasks = parser.get_links();

	for (const auto& task : tasks)
	{
		Builder builder(task, pr);
		builder.make();
	}
	return 0;
}
