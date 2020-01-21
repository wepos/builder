#pragma once
#include "file_handling.h"
#include <time.h>
#include <stdio.h>

#define OBJ "object/"
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
	bool show;
};

class Builder
{
	buildlist build;
	File_handling fh;
	std::map<std::string, f_info> src;
	std::map<std::string, f_info> obj;
	std::vector<std::string> task;
	std::string filecompile;
	std::string progcompile;
	const std::string work_space;
	const std::string includes;
	int fl = 0;
	
public:
	Builder(const char *path, const std::string& inc)
	: work_space(path), includes(inc)
	{};

	void	set_buildlist();
	void	make();

private:
	void	make_program();
	void	make_task(	const std::string& key,
						const f_info& val);
};