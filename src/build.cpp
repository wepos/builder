#include "build.h"

void	Builder::set_buildlist()
{
	build.sources = "42sh/Libft/srcs";
	build.src_ignore_files.insert("ft_strlen.s");
	build.includes = "42sh/Libft/includes";
	build.compile_obj = "-g -c -J4";
	build.compile_program = "ar rc libft.a";
	filecompile = build.compile_obj + " ";
	progcompile = build.compile_program + " ";
	build.out_dir = "lib/";
}

void Builder::make()
{
	std::string object(OBJ);
	fh.get_recursion_finfo_dir(build.sources, build.src_ignore_files, src, 's');
	src[build.sources] = {"", 0, 0, TYPE_FILE::DIRICTORY};
	fh.get_recursion_finfo_dir(object + build.sources, build.src_ignore_files, obj, 'o');
	
	for (const auto& [key, val] : src)
	{
		if (!obj.count(key) && val.type == TYPE_FILE::DIRICTORY)
			fh.make_dir(std::string(OBJ) + key, MOD);
		if ((!obj.count(key) && val.type != TYPE_FILE::DIRICTORY))
			make_task(key, val);
		else if ((val.type != TYPE_FILE::DIRICTORY) && obj.at(key).mtime < val.mtime)
			make_task(key, val);
	}
	if (fl)
		make_program();
}

void	Builder::make_program()
{
	std::string back("");
	if (build.out_dir.size())
	{
		back = "../";
		fh.make_dir(build.out_dir, MOD);		// 
		fh.change_dir(build.out_dir);
	}
	for (const auto& [key, val] : src)
	{
		if (val.type == TYPE_FILE::REGULAR)
			progcompile += back + OBJ + key + ".o ";
	}
	std::cout << progcompile << std::endl;
	system(progcompile.c_str());
	if (build.out_dir.size())
		fh.change_dir(work_space);
}

void	Builder::make_task(const std::string& key, const f_info& val)
{
	fl = 1;
	std::string objpath; 
	objpath.resize(1024);
	objpath = work_space + "/" + OBJ + std::string(begin(key), begin(key) + val.path);
	fh.change_dir(objpath);
	std::cout << filecompile + work_space + "/" + key + val.extens + "\n" + includes + "\n" << std::endl;
	system((filecompile + work_space + "/" + key + val.extens + "\t" + includes).c_str());
	fh.change_dir(work_space);
}