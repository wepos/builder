/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buildlist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:54:20 by fnancy            #+#    #+#             */
/*   Updated: 2020/01/21 17:34:17 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "file_handling.h"
#include <unistd.h>
#include "build.h"
#include <vector>

#define NAME_SET		"/settings"
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

class Parser
{
private:
	std::vector<buildlist>		links;
	std::vector<std::string>	get_setting_words();
	std::vector<std::string>	get_blocks();
	void						bzero_node(buildlist *node);
	int							check_syntax(std::string& str, char *sp);
	int 						check_keywords(char *str);
	int							fill_node(char *str, buildlist *node, int res);
	int							parse_blocks(std::vector<std::string>& block, buildlist *node);

public:
    std::vector<buildlist>		get_links();
	void						parse_file();
};
