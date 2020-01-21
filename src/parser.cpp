#include "parser.h"
#include "file_handling.h"
#include <sstream>

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

int 						Parser::check_keywords(char *str)
{
	std::string			astr;

	astr.append(str);
	std::remove(astr.begin(), astr.end(), '\t');
	astr.erase(std::remove(astr.begin(), astr.end(), ' '), astr.end());
	if (strcmp(astr.c_str(), NAME_LNK) == 0)
		return (NAME_LNK_I);
	else if (strcmp(astr.c_str(), FOLDER1) == 0)
		return (FOLDER1_I);
	else if (strcmp(astr.c_str(), IGNORE_FILE) == 0)
		return (IGNORE_INC_FILE_I);
	else if (strcmp(astr.c_str(), COMPILED_FILES) == 0)
		return (COMPILED_FILES_I);
	else if (strcmp(astr.c_str(), INCLUDES_DIR) == 0)
		return (INCLUDES_DIR_I);
	else if (strcmp(astr.c_str(), INCLUDES_FILE) == 0)
		return (INCLUDES_FILE_I);
	else if (strcmp(astr.c_str(), IGNORE_INC_FILE) == 0)
		return (IGNORE_INC_FILE_I);
	else if (strcmp(astr.c_str(), COMPILER) == 0)
		return (COMPILER_I);
	else if (strcmp(astr.c_str(), FLAGS_FIL) == 0)
		return (FLAGS_FIL_I);
	else if (strcmp(astr.c_str(), FLAGS_PR) == 0)
		return (FLAGS_PR_I);
	else if (strcmp(astr.c_str(), OUTPUT_DIR) == 0)
		return (OUTPUT_DIR_I);
	return (-1);
}

int							Parser::fill_node(char *str, buildlist *node, int res)
{
	char	*spl;

	switch (res)
	{
		case FOLDER1_I:
			node->sources.append(str);
			break;
	}
	return (1);
}

int							Parser::parse_blocks(std::vector<string>& block, buildlist *node)
{
	char				*spl;
	int					res;

	for (size_t i = 0; i < block.size(); i++)
	{
		spl = strtok((char *)block[i].c_str(), "=");
		res = check_keywords(spl);
		if (res != -1)
		{
			spl = strtok(NULL, "=");
			fill_node(spl, node, res);
		}
	}
	return (1);
}

void						Parser::parse_file()
{
	std::vector<std::string>	words;
	std::vector<string>			block;
	buildlist					node;

	words = get_setting_words();	
	for (size_t i = 0; i < words.size(); i++)
	{
		if (strcmp(words[i].c_str(), "{") == 0)
		{
			while (strcmp(words[++i].c_str(), "}") != 0 && i < words.size())
				block.push_back(words[i]);
			bzero(&node, sizeof(node));
			parse_blocks(block, &node);
			links.insert(links.end(), node);		
			block.clear();
		}
		else
			i++;	
	}
}

int		main()
{
	Parser	parser;

	parser.parse_file();
	printf("HUT");
	return (1);
}
