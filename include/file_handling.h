#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>


#define RED "\033[31m" 	// red color message

enum ERRORS {	 		// error code
	OK,
	FAIL_DIR,
	FAIL_OPEN_FILE,
	BAD_IFSTREAM,
	FAIL_OPEN_DIR,
	UNKNOWN_TYPE
};

enum TYPE_FILE {
	FIFO,
	CHARTER,
	DIRICTORY,
	BLOK,
	REGULAR,
	LINK,
	SOCKET,
	NO_ACCESS
};
				/* Return enum TYPE_FILE */
TYPE_FILE		get_filetype(mode_t mode);
				/* print error code and message. concludes program */
static void 	error_processing(const int code, const std::string& message);

struct	type_fiel
{

};

class File_handling
{
public:
	/* 
		openmode:
			app    = 0x01 стремиться к концу потока перед каждой записи
			ate    = 0x02 открыть в двоичном режиме
			binary = 0x04 открыть для чтения
			in     = 0x08 открыть для записи
			out    = 0x10 Удалите содержимое потока при открытии
			trunc  = 0x20 стремиться к концу поток сразу после открытой
	*/
	void	write_in_file(	const std::string& file,
							const std::string& data,
							const unsigned int openmode) const;

	void	write_in_file(	const std::string& file,
							const std::map<std::string, std::string>& data,
							const std::string& delim,
							const unsigned int openmode) const;
	/*
		unsafe function.
		does not obstruct the input flow.
		the stream to be closed after use.
	*/
	std::ofstream of_stream_file(	const std::string& file,
									unsigned int openmode) const;


	/*
		unsafe function.
		does not obstruct the input flow.
		the stream to be closed after use.
	*/
	std::ifstream if_stream_file(const std::string& file) const;

	/* return vector words min time 3691775 mks for 134.3MB*/
	std::vector<std::string> get_words(const std::string& file) const;
	
	/* return vector lines min time 3157604 mks for 134.MB*/
	std::vector<std::string> get_lines(	const std::string& file,
										const char delim) const;

	/*
		unsafe function.
		does not obstruct the input flow.
		the stream to be closed after use.
	*/
	FILE* get_c_stream(const std::string& file) const;
	
	/* return vector lines min time 209025 mks for 134.MB WIN!!! */
	std::vector<std::string> get_lines_c_str(	const std::string& file,
												const char delim) const;

	/*
		unsafe function.
		does not obstruct the input flow.
		the DIR to be closed after use.
	*/
	DIR		*open_dir(const std::string& path) const;
	bool 	tray_open_dir(const std::string& path) const;


	std::vector<std::string> get_files_dir(const std::string& dir) const;
	/*HOME dir 437193 mks */
	void	 get_recursion_files_dir(	const std::string& path,
										std::vector<std::string>& vec) const;


	std::map<std::string, struct stat> get_fstat_dir(const std::string& path) const;

	void get_fstat_dir(	const std::string& path,
						std::map<std::string, struct stat>& m) const;

	/*HOME dir 540085 mks */
	void 	get_recursion_fstat_dir(	const std::string& path,
										std::map<std::string, struct stat>& map) const;

private:
	inline bool	is_dots(char *name) const;
};

