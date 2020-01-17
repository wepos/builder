#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Search {
	
public:
	int 	linearSearch(char *word, char **array) {
		for (int i = 0; array[i] != NULL; i++)
			if (strcmp(word, array[i]) == 0)
				return i;
		return -1;
	}
	int 	binsearch(char *str, char *arr[], int len)
	{
		int min = 0, max = len -1, cmp, ind;
		while (min <= max) {
			ind = (min + max) / 2;
			cmp = strcmp(str, arr[ind]);
			if (cmp > 0) {
				min = ind + 1;
			}
			else if (cmp < 0) {
				max = ind - 1;
			}
			else {
				return (ind);
			}
		}
		return -1;
	}
	void	sort_vec_puz(vector<int>& arr){
		if (arr.size() <= 1)
			return ;
		int fl = 1;
		while(fl) {
			fl = 0;
			for (int i = 0; i + 1 < arr.size(); i++){
				if (arr[i] > arr[i + 1]){
					swap(arr[i], arr[i + 1]);
					fl = 1;
				}
			}
		}
	}
	void	sort_vec_puz(vector<string>& arr){
		if (arr.size() <= 1)
			return ;
		int fl = 1;
		while(fl) {
			fl = 0;
			for (int i = 0; i + 1 < arr.size(); i++){
				if (strcmp(arr[i].c_str(), arr[i + 1].c_str()) > 0){
					swap(arr[i], arr[i + 1]);
					fl = 1;
				}
			}
		}
	}
	void	q_sort(vector<string>& arr) {
		
	}
	
	
private:
	void	swap(int& x, int& y){
		int tmp;

		tmp = x;
		x = y;
		y = tmp;
	}
	void	swap(string& x, string& y){
		string tmp;

		tmp = x;
		x = y;
		y = tmp;
	}
};
