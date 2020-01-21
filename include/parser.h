/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:54:20 by fnancy            #+#    #+#             */
/*   Updated: 2020/01/21 13:13:35 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include <unistd.h>
#include "file_handling.h"

#define NAME_SET	"/settings"

#define	SOURCE			"SOURCE"
#define	COMPILED_FILES	"COMPILED_FILES"
#define	IGNORE_FILE		"IGNORE_FILE"
#define	INCLUDES_DIR	"INCLUDES_DIR"
#define	COMPILER_OBJ	"COMPILER_OBJ"
#define	COMPILER_PR		"COMPILER_PR"
#define	OUTPUT_DIR		"OUTPUT_DIR"

enum	Keys{
	SOURCE_I = 0, COMPILED_FILES_I = 1, IGNORE_FILE_I = 2, INCLUDES_DIR_I = 3,
	COMPILER_OBJ_I = 4, COMPILER_PR_I = 5, OUTPUT_DIR_I = 6
};

using namespace std;

struct buildlist
{
	std::string name;
	std::string sources;
	std::string inclides;
	std::string compiler;
	std::string fl_file;
	std::string fl_program;
	std::string out_dir;
	std::vector<string> src_files;
	std::vector<string> src_ignore_files;
	std::vector<string> inc_files;
	std::vector<string> inc_ignore_files;
};


class Parser
{
private:
	std::vector<buildlist>		links;
	std::vector<std::string>	get_setting_words();
	std::vector<string>			get_blocks();
	int 						check_keywords(char *str);
	int							fill_node(char *str, buildlist *node, int res);
	int							parse_blocks(std::vector<string>& block, buildlist *node);

public:
    std::vector<buildlist>		get_links();
	void						parse_file();
};
