#include "file_handling.h"
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
		else if (strcmp(argv[i], "-clearall") == 0 || strcmp(argv[i], "-ca") == 0)
			param.ca = true;
		else if (strcmp(argv[i], "-show") == 0 || strcmp(argv[i], "-s") == 0)
			param.show = true;
		else
			error_processing(WRONG_KEY, argv[i]);
	}
	return (param);
}

// int main(int argc, char **argv)
int main()
{
	t_param pr;
	buildlist bl;

	pr.show = true;

	bl.sources = "42sh/Libft/srcs";
	bl.includes = "42sh/Libft/includes";
	bl.src_ignore_files.insert("ft_strlen.s");
	bl.compile_obj = "gcc -g -c";
	bl.compile_program = "ar rc libft.a";
	bl.out_dir = "lib/";

	Builder build(bl, pr);
	build.make();

	// pr = parser_argv(argc, argv);
	// if (argc == 0)
	// {
	// 	// vector<buildlist> tasks = Parser();
	// 	for (const auto& task : tasks)
	// 	{
	// 		Builder bild(task, pr);
	// 	}

	// }




	// std::vector<std::string> vec;
	// sp.init_point();
	// for (int i = 0; i < 100000; ++i)
	// {
	// 	chdir("../../../");
	// 	// cout << getcwd(pwd, 100) << endl;
	// 	chdir("/Users/gdaemoni/Desktop/build");
	// 	// cout << getcwd(pwd, 100) << endl;
	// }
	// sp.print_mksec("");
{	
	// sp.init_point();
	// map<string, f_info> m;
	// h.get_recursion_finfo_dir(file, m, 's');
	// for (const auto& [key, val] : m) {

	// 	unsigned long n = val.mtime;
	// 	cout << key << " time = "
	// 	<< n << "   "
	// 	<< " type = " << val.type << endl;
	// }
	// cout << m.size() << endl;
	// sp.print_mksec("dp  ");
}

	// for(auto st: vec){
	// 	printf("%s\n", st.c_str());
	// }
}
