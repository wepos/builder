#pragma once
#include "file_handling.h"
#include <time.h>
#include <stdio.h>

#define OBJ "objects/"
#define MOD (mode_t)0777

struct buildlist
{
	std::string sources;
	std::vector<std::string> src_files;
	std::set<std::string> src_ignore_files;
	std::string includes;
	std::string compile_obj;
	std::string compile_program;
	std::string out_dir;
};

struct t_param
{
	bool show;
	bool re;
	bool clear;
	bool ca;
};

class Builder
{
	std::map<std::string, f_info> src;
	std::map<std::string, f_info> obj;
	const std::string object;
	std::string back;
	std::string out_dir;
	std::string file_compile;
	std::string prog_compile;
	std::string work_space;
	std::string includes;
	t_param param;
	File_handling fh;
	bool fl = false;		// flag that changes the state if at least one file was recompiled
	
public:
	Builder(const buildlist& task, t_param& pr) : object(OBJ)
	{
		param = pr;
		src[task.sources] = {"", 0, 0, TYPE_FILE::DIRICTORY};
		if (task.sources.size())
			fh.get_recursion_finfo_dir(task.sources, task.src_ignore_files, src, 's');
		fh.get_finfo(task.src_files, task.src_ignore_files, src);
		fh.get_recursion_finfo_dir(object + task.sources, std::set<std::string>(), obj, 'o');
		fh.get_finfo_o(task.src_files, object, obj);
		back = "";
		out_dir = task.out_dir;
		if (out_dir.size()) // проверяем наличие директории
		{
			back = "../";
			fh.make_dir(out_dir, MOD);
		}
		char pwd[KBIT];
		getcwd(pwd, KBIT);
		work_space = pwd;
		if (task.includes.size())
			fh.get_paths_files(task.includes, work_space, includes);
		prog_compile = task.compile_program + " ";
		file_compile = task.compile_obj + " ";
	};

	void	make();

private:
	void	make_param();
	void	make_program();
	void	make_task(	const std::string& key,
						const f_info& val);
};