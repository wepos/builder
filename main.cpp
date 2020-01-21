#include "file_handling.h"
#include "build.h"
#include "arr.h"
#include "speed_test.h"
#include <time.h>
#include <stdio.h>


using namespace std;

int main()
{
	File_handling h;
	Array ar;
	Speed sp;
	string file("../");
	char pwd[1024];
	getcwd(pwd, 1024);
	string includes;
	h.get_paths_files("42sh/Libft/includes", pwd, includes);
	Builder bd(pwd, includes);

	sp.init_point();
	bd.set_buildlist();
	bd.make();
	sp.print_mksec("");


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
