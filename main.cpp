#include "file_handling.h"

#include "arr.h"
#include "speed_test.h"
#include <time.h>
#include <stdio.h>

#include <string.h>

using namespace std;

#define OBJ "object/"
#define MOD (mode_t)0777


struct file_c
{
	std::string	path;
	long 		mtime;	// last data modification nsec
	std::string get_filename()
	{
		
	}
};


struct buildlist
{
	std::string name;
	std::string sources;
	std::vector<string> src_files;
	std::vector<string> src_ignore_files;
	std::string inclides;
	std::vector<string> inc_files;
	std::vector<string> inc_ignore_files;
	std::string compiler;
	std::string fl_file;
	std::string fl_program;
	std::string out_dir;

};



class Builder
{
	buildlist build;
	File_handling fh;
	std::map<std::string, f_info> src;
	std::map<std::string, f_info> obj;
	std::vector<string> task;
	std::string filecompile;
	std::string progcompile;
	
public:
	void set_buildlist()
	{
		bzero(&build, sizeof(buildlist));
		build.name = "libft.a";
		build.sources = "42sh/sources";
		build.inclides = "42sh/Libft/includes";
		build.compiler = "gcc";
		build.fl_file = "-g";
		build.fl_program = "ar rc lib";
		filecompile = build.compiler + " " + build.fl_file + " ";
		progcompile = build.compiler + " " + build.fl_program + " ";
	}

	void make_task()
	{
		std::string object(OBJ);
		fh.get_recursion_finfo_dir(build.sources, src, 's');
		fh.get_recursion_finfo_dir(object + build.sources, obj, 'o');
		
		for (const auto& [key, val] : src)
		{
			if (!obj.count(key) && val.type == TYPE_FILE::DIRICTORY)
				fh.make_dir(std::string(OBJ) + key, MOD); 		// обработать ошибку когда вернет ноль
			if ((!obj.count(key) && val.type != TYPE_FILE::DIRICTORY))
				add_task(key, val);
			else if (obj.at(key).mtime < val.mtime)
				add_task(key, val);
		}
		for (const auto& t : task) {
			cout << t << endl;
		}
		task.size();
	}
private:
	void	add_task(const std::string& key, const f_info& val)
	{
		task.push_back(std::string(filecompile + key + val.extens));
	}
};


int main()
{
	File_handling h;
	Array ar;
	Speed sp;
	string file("../");
	Builder bd;

	// sp.init_point();
	// bd.set_buildlist();
	// bd.make_task();
	// sp.print_mksec("");

	// std::vector<std::string> vec;
{	
	sp.init_point();
	map<string, f_info> m;
	h.get_recursion_finfo_dir(file, m, 's');
	// for (const auto& [key, val] : m) {

	// 	unsigned long n = val.mtime;
	// 	cout << key << " time = "
	// 	<< n << "   "
	// 	<< " type = " << val.type << endl;
	// }
	cout << m.size() << endl;
	sp.print_mksec("dp  ");
}

	// for(auto st: vec){
	// 	printf("%s\n", st.c_str());
	// }
}