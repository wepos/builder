#include "build.h"

void 	Builder::make()
{
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

void	Builder::make_program()
{
	if (out_dir.size())
		fh.change_dir(out_dir);
	std::string comand = prog_compile;
	for (const auto& [key, val] : obj)
		comand += back + object + key + val.extens + ' ';
	system(comand.c_str());
	if (param.show)
		std::cout << prog_compile << std::endl;
		for (const auto& [key, val] : obj)
			std::cout << '\t' << back + object + key + val.extens << std::endl;
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
	system((file_compile + work_space + "/" + key + val.extens + includes).c_str());
	if (param.show)
		std::cout << file_compile + work_space + "/" + key + val.extens + "\n\t" + includes + "\n" << std::endl;
	fh.change_dir(work_space);
}