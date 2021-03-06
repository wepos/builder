#include "file_handling.h"


void print_err_message(
	const std::string& err,
	const std::string& message="")
{
	std::cout << RED << err << ": " << message << std::endl;
}

void error_processing(
	const int code,
	const std::string& message="")
{
	switch (code)
	{
		case OK:
			return ;
		case FAIL_DIR:
			print_err_message("Failed to create directory", message); break;
		case FAIL_OPEN_FILE:
			print_err_message("Failed to open file", message); break;
		case BAD_IFSTREAM:
			print_err_message("Bad file stream", message); break;
		case FAIL_OPEN_DIR:
			print_err_message("Failed to open directory", message); break;
		case UNKNOWN_TYPE:
			print_err_message("unknown type"); break;
		case MAKE_DIR:
			print_err_message("Failed make directory", message); break;
		case CHANGE_DIR:
			print_err_message("Fail directory change", message); break;
		case LSTAT:
			print_err_message("It was not possible to obtain information about the file", message); break;
		case WRONG_KEY:
			print_err_message("Wrong key", message); break;
		case SYSERROR:
			print_err_message("Couldn't execute the command", message); break;
	}
	std::cout << RED << "ERROR CODE " << code << std::endl;
	exit(code);
}

TYPE_FILE	File_handling::get_filetype(
	mode_t mode) const
{
	mode &= S_IFMT;
	switch (mode)
	{
		case S_IFIFO:
			return (FIFO);
		case S_IFCHR:
			return (CHARTER);
		case S_IFDIR:
			return (DIRICTORY);
		case S_IFBLK:
			return (BLOK);
		case S_IFREG:
			return (REGULAR);
		case S_IFLNK:
			return (LINK);
		case S_IFSOCK:
			return (SOCKET);
		default:
			return (NO_ACCESS);
	}
}

std::ofstream File_handling::of_stream_file(
	const std::string& file,
	unsigned int openmode) const
{
	std::ofstream res;

	res.open(file, openmode);
	if (!res.is_open())
		error_processing(FAIL_OPEN_FILE, file);
	return res;
}

void	File_handling::write_in_file(
	const std::string& file,
	const std::string& data,
	const unsigned int openmode) const 
{
	std::ofstream fout = of_stream_file(file, openmode);
	fout << data;
	fout.close();
}

void	File_handling::write_in_file(	
	const std::string& file,
	const std::map<std::string, std::string>& data,
	const std::string& delim,
	const unsigned int openmode) const
{
	std::ofstream fout = of_stream_file(file, openmode);
	for(const auto& [key, val] : data) {
		fout << key << delim << val << std::endl;
	}
}


std::ifstream File_handling::if_stream_file(
	const std::string& file) const 
{
	std::ifstream res;
	res.open(file);
	if (!res.is_open())
		error_processing(FAIL_OPEN_FILE, file);
	return res;
}

std::vector<std::string> File_handling::get_words(
	const std::string& file) const
{
	std::ifstream f = if_stream_file(file);
	std::istream_iterator<std::string> begin(f), end;
	std::vector<std::string> res(begin, end);
	f.close();
	return res;
}

std::vector<std::string> File_handling::get_lines(
	const std::string& file,
	const char delim) const
{
	std::ifstream f = if_stream_file(file);
	std::vector<std::string> res;
	for(std::string str; getline(f, str, delim); res.push_back(str));
	f.close();
	return (res);
}

FILE* 	File_handling::get_c_stream(
	const std::string& file) const
{
	FILE *stream = fopen(file.c_str(), "r");
	if (stream == 0)
		error_processing(FAIL_OPEN_FILE, file);
	return (stream);
}

std::vector<std::string> File_handling::get_lines_c_str(
	const std::string& file) const
{
	FILE *stream = get_c_stream(file);
	size_t len = 0;
	char *line = 0;
	ssize_t nread;
	std::vector<std::string> res;
	while ((nread = getline(&line, &len, stream)) != -1) {
		std::string s(line, len);
		res.push_back(s);
	}
	fclose(stream);
	return (res);
}


DIR		*File_handling::open_dir(
	const std::string& path) const
{
	DIR	*dir = opendir(path.c_str());

	if (!dir)
		error_processing(FAIL_OPEN_DIR, path);
	return (dir);
}

inline bool	File_handling::is_dots(char *name) const  {
	if (!strcmp(name, ".") || !strcmp(name, ".."))
		return (true);
	return (false);
}

std::vector<std::string> File_handling::get_files_dir(
	const std::string& path) const
{
	DIR	*dir = open_dir(path.c_str());
	struct dirent *entry;
	std::vector<std::string> res;
	int c = 0;
	while ((entry = readdir(dir)) != 0)
	{
		if (++c < 3)
			continue ;
		std::string name_dir(entry->d_name);
		res.push_back(name_dir);
	}
	closedir(dir);
	return (res);
}

void	File_handling::get_paths_files(
	const std::string& path,
	const std::string& worc_space,
	std::string& paths) const
{
	DIR				*dir = open_dir(path.c_str());
	struct dirent 	*entry;
	struct stat		st;
	int c = 0;
	if (!paths.size())
		paths = std::string(" -I") + worc_space + '/' + path + '\t' ;
	while ((entry = readdir(dir)) != 0)
	{
		if (++c < 3)
			continue ;
		std::string tmp(path + '/' + entry->d_name);
		lstat(tmp.c_str(), &st);
		if (get_filetype(st.st_mode) == TYPE_FILE::DIRICTORY)
		{
			get_paths_files(tmp, worc_space, paths);
			paths += std::string(" -I") + worc_space + '/' + tmp + '\t';
		}
	}
	closedir(dir);
}


void 	File_handling::get_recursion_files_dir(
	const std::string& path,
	std::vector<std::string>&vec) const
{
	DIR				*dir = open_dir(path.c_str());
	struct dirent 	*entry;
	struct stat		st;

	while ((entry = readdir(dir)) != 0)
	{
		if (is_dots(entry->d_name))
			continue ;
		std::string tmp(path + '/' + entry->d_name);
		lstat(tmp.c_str(), &st);
		if (get_filetype(st.st_mode) == TYPE_FILE::DIRICTORY && try_open_dir(tmp))
			get_recursion_files_dir(tmp, vec);
		vec.push_back(tmp);
	}
	closedir(dir);
}

std::map<std::string, struct stat> File_handling::get_fstat_dir(
	const std::string& path) const
{
	DIR				*dir = open_dir(path);
	struct dirent	*entry;
	struct stat		st;
	std::map<std::string, struct stat> res;
	int c = 0;
	const size_t size_st= sizeof(struct stat);

	while ((entry = readdir(dir)))
	{
		if (++c < 3)
			continue ;

		std::string tmp(path + "/" + entry->d_name);
		struct stat		cpy;
		lstat(tmp.c_str(), &st);
		res[tmp] = *(struct stat*)memmove(&cpy, &st, size_st);
	}
	closedir(dir);
	return (res);
}

void 	File_handling::get_fstat_dir(
	const std::string& path,
	std::map<std::string, struct stat>& m) const
{
	DIR				*dir = open_dir(path);
	struct dirent	*entry;
	struct stat		st;
	int c = 0;
	const size_t size_st= sizeof(struct stat);

	while ((entry = readdir(dir)))
	{
		if (++c < 3)
			continue ;

		std::string tmp(path + "/" + entry->d_name);
		struct stat		cpy;
		lstat(tmp.c_str(), &st);
		m[tmp] = *(struct stat*)memmove(&cpy, &st, size_st);
	}
	closedir(dir);
}

bool 	File_handling::try_open_dir(
	const std::string& path) const
{
	DIR	*dir = opendir(path.c_str());

	if (!dir)
		return (false);
	closedir(dir);
	return (true);
}

void	File_handling::get_recursion_fstat_dir(
	const std::string& path,
	std::map<std::string, struct stat>& map) const
{
	DIR				*dir = opendir(path.c_str());
	if (dir == 0)
		return ;
	struct dirent	*entry;
	struct stat		st;
	const size_t 	size_st = sizeof(struct stat);

	while ((entry = readdir(dir)))
	{
		if (is_dots(entry->d_name))
			continue ;
		std::string tmp(path + "/" + entry->d_name);
		struct stat		cpy;
		lstat(tmp.c_str(), &st);
		if (get_filetype(st.st_mode) == TYPE_FILE::DIRICTORY && try_open_dir(tmp))
			get_recursion_fstat_dir(tmp, map);
		map[tmp] = *(struct stat*)memmove(&cpy, &st, size_st);
	}
	closedir(dir);
}

void	File_handling::get_recursion_finfo_dir(
	const std::string& path,
	const std::set<std::string>& ignore,
	std::map<std::string, f_info>& map,
	char fl) const
{
	DIR	*dir;
	if (!(dir = opendir(path.c_str())))
		return ;
	struct dirent	*entry;
	struct stat		st;
	TYPE_FILE		t;
	int c = 0;
	while ((entry = readdir(dir)))
	{
		if (++c < 3)
			continue ;
		if (fl == 's'
			&& ignore.find(std::string(entry->d_name)) != ignore.end())
				continue ;
		std::string tmp(path + "/" + entry->d_name);
		lstat(tmp.c_str(), &st);
		if ((t = get_filetype(st.st_mode)) == TYPE_FILE::DIRICTORY && try_open_dir(tmp))
			get_recursion_finfo_dir(tmp, ignore, map, fl);
		if (fl == 's')
			set_map(map, tmp, &st, t);
		else
			set_map_o(map, tmp, &st, t);
	}
	closedir(dir);
}

inline bool	drop(const std::set<std::string>& ignore, const char *name_file)
{
	if (ignore.count(std::string(name_file)))
		return (true);
	return (false);
}

void	File_handling::set_map_o(
	std::map<std::string, f_info>& map,
	const std::string& file,
	struct stat* st,
	TYPE_FILE type) const
{
	f_info	val;
	int		dot;
	int		slash = file.find('/') + 1;
	if ((dot = file.find_last_of('.', file.size())) == -1)
	{
		val.type = TYPE_FILE::DIRICTORY;
		map[std::string(file.begin() + slash, file.end())] = val;
		return ;
	}
	val.extens = std::string(file.begin() + dot, file.end());
	val.mtime = st->st_mtimespec.tv_sec;
	val.type = type;
	val.path = file.find_last_of('/', file.size());
	map[std::string(file.begin() + slash, file.begin() + dot)] = val;	
}

void 	File_handling::set_map(
	std::map<std::string, f_info>& map,
	const std::string& file,
	struct stat* st,
	TYPE_FILE type) const
{
	f_info	val;
	int		dot;
	if ((dot = file.find_last_of('.', file.size())) == -1)
	{
		val.type = TYPE_FILE::DIRICTORY;
		map[file] = val;
		return ;
	}
	val.extens = std::string(file.begin() + dot, file.end());
	val.mtime = st->st_mtimespec.tv_sec;
	val.type = type;
	val.path = file.find_last_of('/', file.size());
	map[std::string(file.begin(), file.begin() + dot)] = val;
}

void	 File_handling::make_dir(
	const std::string& name,
	const mode_t mode) const
{
	if (try_open_dir(name))
		return ;
	std::string cpy = name;
	char *ptr = strtok((char*)cpy.c_str(), "/");;
	char d[KBIT];
	bzero(d, KBIT);
	int n = 0, c = 0;
	while(ptr != NULL)
	{
		int len = strlen(ptr);
		memmove(d + n, ptr, len);
		d[len + n] = '/';
		if (mkdir(d, mode) != -1)
			++c;
		n += len + 1;
		ptr = strtok(NULL, "/");
	}
	if (!c)
		error_processing(MAKE_DIR, d);
}

void	File_handling::change_dir(
	const std::string& path) const
{
	if (chdir(path.c_str()) == -1)
		error_processing(CHANGE_DIR, path);
}

void		File_handling::get_finfo(
	const std::vector<std::string>& src_files,
	const std::set<std::string>& ignore,
	std::map<std::string, f_info>& map) const
{
	struct stat		st;

	for (const auto& file : src_files)
	{
		if (ignore.find(file) != end(ignore))
			continue ;
		if (lstat(file.c_str(), &st) == -1)
			error_processing(LSTAT, file);
		set_map(map, file, &st, TYPE_FILE::REGULAR);
	}
}

void		File_handling::get_finfo_o(
	const std::vector<std::string>& src_files,
	const std::string& obj,
	std::map<std::string, f_info>& map) const
{
	struct stat		st;
	
	for (const auto& file : src_files)
	{
		if (lstat((obj + file).c_str(), &st) == -1)
			continue ;
		set_map_o(map, file, &st, TYPE_FILE::REGULAR);
	}
}
void	File_handling::rm_rf(
	const char *dir,
	bool show) const
{
	std::string cmd;

	cmd += std::string("rm -rf ") + dir;
	if (system(cmd.c_str()))
		error_processing(SYSERROR, cmd);
	if (show)
		std::cout << cmd << std::endl;
}