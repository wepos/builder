#include "parser_buildlist.h"

std::vector<buildlist>		Parser::get_links()
{
	return (links);
}

std::vector<std::string>	Parser::get_setting_words()
{
	std::string					path;
	File_handling				fh;
	char						buf[10000];

	getcwd(buf, sizeof(buf));
	path.append(buf);
	path.append(NAME_SET);
	return (fh.get_lines(path, '\n'));
}

void						Parser::bzero_node(buildlist *node)
{
	node->sources.clear();
	node->src_files.clear();
	node->src_ignore_files.clear();
	node->includes.clear();
	node->compile_obj.clear();
	node->compile_program.clear();
	node->out_dir.clear();
}

int							Parser::check_syntax(std::string& str, char *sp)
{
	str.append(sp);
	if (strchr(str.c_str(), ';'))
	{
		str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
		return (0);	
	}
	else//errrrooooooorrrrr
	{

	}
	return (1);
}

int 						Parser::check_keywords(char *str)
{
	std::string			astr;

	astr.append(str);
	std::remove(astr.begin(), astr.end(), '\t');
	astr.erase(std::remove(astr.begin(), astr.end(), ' '), astr.end());
	if (strcmp(astr.c_str(), SOURCE) == 0)
		return (SOURCE_I);
	else if (strcmp(astr.c_str(), COMPILED_FILES) == 0)
		return (COMPILED_FILES_I);
	else if (strcmp(astr.c_str(), IGNORE_FILE) == 0)
		return (IGNORE_FILE_I);
	else if (strcmp(astr.c_str(), INCLUDES_DIR) == 0)
		return (INCLUDES_DIR_I);
	else if (strcmp(astr.c_str(), COMPILER_OBJ) == 0)
		return (COMPILER_OBJ_I);
	else if (strcmp(astr.c_str(), COMPILER_PR) == 0)
		return (COMPILER_PR_I);
	else if (strcmp(astr.c_str(), OUTPUT_DIR) == 0)
		return (OUTPUT_DIR_I);
	return (-1);
}

int							Parser::fill_node(char *str, buildlist *node, int res)
{
	char	*spl;

	switch (res)
	{
		case SOURCE_I:
			node->sources.append(str);
			break;
		case COMPILED_FILES_I:
			spl = strtok(str, " ");
			while (spl != NULL)
			{
				node->src_files.insert(node->src_files.begin(), spl);
				spl = strtok(NULL, " ");
			}
			break;
		case IGNORE_FILE_I:
			spl = strtok(str, " ");
			while (spl != NULL)
			{
				node->src_ignore_files.insert(spl);
				spl = strtok(NULL, " ");
			}
			break;
		case INCLUDES_DIR_I:
			node->includes.append(str);
			break;
		case COMPILER_OBJ_I:
			node->compile_obj.append(str);
			break;
		case COMPILER_PR_I:
			node->compile_program.append(str);
			break;
		case OUTPUT_DIR_I:
			node->out_dir.append(str);
			break;
	}
	return (1);
}

int							Parser::parse_blocks(std::vector<std::string>& block, buildlist *node)
{
	char				*spl;
	std::string			str;
	int					res;

	for (size_t i = 0; i < block.size(); i++)
	{
		spl = strtok((char *)block[i].c_str(), "=");
		res = check_keywords(spl);
		if (res != -1)
		{
			spl = strtok(NULL, "=");
			check_syntax(str, spl);
			fill_node((char *)str.c_str(), node, res);
			str.clear();
		}
		else///errrroooorrrr key not fouund
		{
			
		}
		
	}
	return (1);
}

void						Parser::parse_file()
{
	std::vector<std::string>	words;
	std::vector<std::string>	block;
	buildlist					node;

	words = get_setting_words();	
	for (size_t i = 0; i < words.size(); i++)
	{
		if (strcmp(words[i].c_str(), "{") == 0)
		{
			while (strcmp(words[++i].c_str(), "}") != 0 && i < words.size())
				block.push_back(words[i]);
			bzero_node(&node);
			parse_blocks(block, &node);
			links.insert(links.end(), node);
			block.clear();
		}
	}
}

// int		main()
// {
// 	Parser	parser_buildlist;

// 	parser_buildlist.parse_file();
// 	printf("HUT");
// 	return (1);
// }
