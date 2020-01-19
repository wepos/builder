#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Array {
public:
	void	print_arr(char **arr){
		for (int i = 0; arr[i]; i++){
			printf("%s ", arr[i]);
		}
	}
	void	printnl_arr(char **arr){
		for (int i = 0; arr[i]; i++){
			printf("%s\n", arr[i]);
		}
	}
	void	print_vec(vector<string> arr){
		for (int i = 0; i < arr.size(); i++){
			printf("%s ", arr[i].c_str());
		}
	}
	void	print_vec(vector<int> arr){
		for (int i = 0; i < arr.size(); i++){
			printf("%d ", arr[i]);
		}
	}
	void	println_vec(vector<string> arr){
		for (int i = 0; i < arr.size(); i++){
			printf("%s\n", arr[i].c_str());
		}
	}
	void	println_vec(vector<int> arr){
		for (int i = 0; i < arr.size(); i++){
			printf("%d\n", arr[i]);
		}
	}
	char* 	get_rand_str(int len){
		char *str = (char*)malloc(sizeof(char) * len + 1);

		for (int i = 0; i < len; i++){
			str[i] = (char)get_print_ch();
		}
		str[len] = '\0';
		return (str);
	}
	char* 	get_rand_str(int len, int minlen){
		int strlen = (rand() % len) + minlen;
		char *str = (char*)malloc(sizeof(char) * strlen + 1);

		for (int i = 0; i < strlen; i++){
			str[i] = (char)get_print_ch();
		}
		str[len] = '\0';
		return (str);
	}
	char** 	get_rand_arr_str(int quant, int strlen){
		char **arr = (char**)malloc(sizeof(char*) * quant + 1);

		for (int i = 0; i < quant; i++){
			arr[i] = get_rand_str(strlen);
		}
		arr[quant] = NULL;
		return (arr);
	}
	char** 	get_rand_arr_str(int quant, int strlen, int minlen){
		char **arr = (char**)malloc(sizeof(char*) * quant + 1);

		for (int i = 0; i < quant; i++){
			arr[i] = get_rand_str(strlen, minlen);
		}
		arr[quant] = NULL;
		return (arr);
	}
	string	get_rand_string(int strlen){
		string str;

		for (int i = 0; i < strlen; i++){
			str.push_back((char)get_print_ch());
		}
		return (str);
	}
	string	get_rand_string(int strlen, int minlen){
		string str;
		int len = (rand() % (strlen - minlen)) + minlen;

		for (int i = 0; i < len; i++){
			str.push_back((char)get_print_ch());
		}
		return (str);
	}
	vector<string> get_rand_string_arr(int quant, int strlen){
		vector<string> arr;

		for (int i = 0; i < quant; i++){
			arr.push_back(get_rand_string(strlen));
		}
		return (arr);
	}
	vector<string> get_rand_string_arr(int quant, int strlen, int minlen){
		vector<string> arr;

		for (int i = 0; i < quant; i++){
			arr.push_back(get_rand_string(strlen, minlen));
		}
		return (arr);
	}

	map<string, string> get_rand_string_map(int quant, int strlen, int minlen){
		map<string, string> m;

		for (int i = 0; i < quant; i++){
			m[get_rand_string(strlen, minlen)] = get_rand_string(strlen, minlen);
		}
		return (m);
	}
	
	int			*get_rang_int(int quant, int max){
		int *arr = (int*)malloc(sizeof(int) * quant);

		for (int i = 0; i < quant; i++){
			arr[i] = rand() % max;
		}
		return (arr);
	}
	vector<int>	get_rand_int_vec(int quant, int max){
		vector<int> arr;

		for (int i = 0; i < quant; i++){
			arr.push_back(rand() % max);
		}
		return (arr);
	}
private:
	int		get_print_ch(){
		int r = (rand() % (122 - 31)) + 31;
		if (r < 97 && r > 90)
			r = (rand() % (122 - 97)) + 97;
		return (r);
	}
};


