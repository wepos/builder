#include "file_handling.h"

#include "arr.h"
#include "speed_test.h"

using namespace std;




int main()
{
	File_handling h;
	Array ar;
	Speed sp;
	string file("../..");

	std::vector<std::string> vec;

{	
	map<string, struct stat> m;
	sp.init_point();
	h.get_fstat_dir(file, m);
	sp.print_mksec("end ");
	cout << m.size() << endl;
}
{	
	sp.init_point();
	map<string, struct stat> m = h.get_fstat_dir(file);
	sp.print_mksec("end = ");
}
{	
	map<string, struct stat> m;
	sp.init_point();
	h.get_fstat_dir(file, m);
	sp.print_mksec("end ");
}
{	
	map<string, struct stat> m;
	sp.init_point();
	h.get_fstat_dir(file, m);
	sp.print_mksec("end ");
}
	// for(auto st: vec){
	// 	printf("%s\n", st.c_str());
	// }
}