#include "build.h"

void 	Builder::make()
{
	make_param();
	for (const auto& [key, val] : src)
	{
		if (!obj.count(key) && val.type == TYPE_FILE::DIRICTORY)
			fh.make_dir(object + key, MOD);
		if ((!obj.count(key) && val.type != TYPE_FILE::DIRICTORY))
			make_task(key, val);
		else if ((val.type != TYPE_FILE::DIRICTORY) && obj.at(key).mtime < val.mtime)
			make_task(key, val);
	}
	if (fl)
		make_program();
}

void	Builder::make_param()
{
	if (param.re)
		fh.rm_rf(OBJ, param.show);
	else if (param.clear)
	{
		fh.rm_rf(OBJ, param.show);
		exit(0);
	}
}

void	Builder::make_program()
{
	if (out_dir.size())
		fh.change_dir(out_dir);
	std::string comand = prog_compile + ' ';
	for (const auto& [key, val] : src)
		if (val.type == TYPE_FILE::REGULAR)
			comand += work_space + '/' + object + key + ".o ";
	if (system(comand.c_str()) == -1)
		error_processing(SYSERROR, comand);
	if (param.show)
	{
		std::cout << "\n\n" << prog_compile << " " << includes << std::endl;
		for (const auto& [key, val] : src)
			if (val.type == TYPE_FILE::REGULAR)
				std::cout << '\t' << work_space + '/' + object + key + ".o" << std::endl;
	}
	if (out_dir.size())
		fh.change_dir(work_space);
}

void	Builder::make_task(const std::string& key, const f_info& val)
{
	fl = true;
	std::string objpath; 
	objpath.resize(KBIT);
	objpath = work_space + "/" + object + std::string(begin(key), begin(key) + val.path);
	fh.change_dir(objpath);
	std::string tmp = file_compile + work_space + "/" + key + val.extens + includes;
	if (system(tmp.c_str()) == -1)
		error_processing(SYSERROR, tmp);
	if (param.show)
		std::cout << file_compile + work_space + "/" + key + val.extens + "\n\t" + includes + "\n" << std::endl;
	fh.change_dir(work_space);
}
