#include <iostream>
#include <string>
#include <memory.h>
#include "ExternalSort.h"
#include "ExternalSearch.h"
#include <sys/time.h>

using namespace std;


int main(int argc, const char* argv[])
{
	if(argv[1] == string("1")) // Run P4 Part 1
	{
			//struct timeval tp;
			//gettimeofday(&tp, NULL);
			//long int ms = tp.tv_sec * 1000 + tp.tv_usec/1000;
		int n = argc;
		if(n != 6)
			cout << "incorrect no. of arguments passed" << endl;
		else
			extern_sort(argv[2], argv[3], argv[5],atoi(argv[4]));  //(inp file, output file, chunk dir, chunk size)
					//gettimeofday(&tp, NULL);
					//long int ms2 = tp.tv_sec * 1000 + tp.tv_usec/1000;
					//cout << "time taken to extern_sort = " << ms2-ms << endl;
	}
	else if(argv[1] == string("2"))
	{

		int n = argc;
		cout << "part 2" << " n = " << n << endl;
		for(int i = 3; i < n; i++)
		{
			if(extern_search(argv[2], argv[i]) )
				cout << "found" << endl;
			else
				cout << "missing" << endl;
		}
			
	}
	return 0;
}