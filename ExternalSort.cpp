#include "ExternalSort.h"
#include <fstream>
#include <ctime>
#include <sys/time.h>

void merger(string chunk[],  int first, int mid, int last)
{
	int left = first,  right = mid+1;
    if ( chunk[mid].compare(chunk[right]) <= 0 )
		return;
	while (left <= mid && right <= last)
	{  
		if ( chunk[left].compare(chunk[right]) <= 0 )
			left++;
        else
        {  
			string tmp = chunk[right];
			for(int i = 0, k = left + (right-left); i < (right-left); i++)
				chunk[k--] = chunk[k-1];
            chunk[left] = tmp;
            left++;  
            mid++;  
            right++;
        }
    }
}
void msort(string chunk[],  int low, int high) 
{
	if(low < high)
	{
		int center = (low + high)/2;
		msort(chunk,  low, center);
		msort(chunk,  center+1, high);
		merger(chunk,  low, center, high);
	}	
}
int partition( string a[], int l, int r) 
{
   int  i, j;
   cout << "l = " << l << " r = " << r << endl;
   string pivot, t;
   cout << "flag 1" << endl;
   pivot = a[l];
   cout << "flag 2" << endl;
   i = l; j = r+1;
   cout << "flag 3" << endl;	
   while( 1)
   {
   	cout << "flag 4" << endl;
   	do
   	{
   		++i;
   		cout << i << endl;
   	}  
   	while( a[i] <= pivot && i <= r );
   	cout << "flag 5" << endl;   	
   	do --j; while( a[j] > pivot );
   	
   	if( i >= j ) break;
   	t = a[i]; 
   	a[i] = a[j]; 
   	a[j] = t;
   	
   }
   t = a[l]; 
   a[l] = a[j]; 
   a[j] = t;
   
   return j;
}
void quickSort( string a[], int l, int r)
{
   int j;
   if( l < r ) 
   {
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }	
}

void extern_sort(string in_fname, string out_fname, string chunk_location, int chunk_size)
{
	string line;
	string chunk[chunk_size];
	int counter = 0;
	ifstream inpFile(in_fname);
	int chunk_n = 1;
	struct timeval tp;
	
	//cout << "before reading" << ms << endl;

	if ( inpFile.is_open() )
	{
		while ( getline(inpFile,line) )
		{			
			if(counter == chunk_size-1)
			{
				chunk[counter] = line;
					///gettimeofday(&tp, NULL);
					///long int ms = tp.tv_sec * 1000 + tp.tv_usec/1000;
				msort(chunk, 0, counter);
				//quickSort(chunk, 0, counter);
					///gettimeofday(&tp, NULL);
					///long int ms2 = tp.tv_sec * 1000 + tp.tv_usec/1000;
					///cout << "time taken to msort = " << ms2-ms << endl;
				ofstream myfile;
				myfile.open( chunk_location + getFnum(chunk_n++) );
				for(int t = 0; t <= counter; t++)
				{
					myfile << chunk[t]<< endl;
				}					
				myfile.close();
				counter = 0;
			}
			else
			{
				chunk[counter++] = line;
			}
		}		
		if(counter)//for incomplete chunk left from uneven chunk split
		{
			int remaining_ctr = counter-1;
			msort(chunk,  0, remaining_ctr-1);
			//quickSort(chunk, 0, remaining_ctr-1);
			ofstream myfile;
			myfile.open( chunk_location + getFnum(chunk_n++) );
			for(int i = 0; i < remaining_ctr; i++)
				myfile << chunk[i]<< endl;
			myfile.close();
		}
		inpFile.close();// done reading
		
		k_merge(chunk_location, out_fname, chunk_n); 
		
	}
	else 
		cout << "No file" << endl;
} 
string getFnum(int n)
{
	if(n <10)
		return "chunk0000" + to_string(n) ;
	else if (n < 100)
		return "chunk000" + to_string(n) ;
	else if (n < 1000)
		return "chunk00" + to_string(n) ;
	else if (n < 10000)
		return "chunk0" + to_string(n) ;
	else
		return "chunk" + to_string(n) ;
}

		// getline
		// read each pointer till newline
		// store an array of first lines where sizeof array = num chunks
		// find min form the array and retain index(=the chunk no.)
		// write min to output file. go to corresponding chunk using
		// index and fseek another line. put the newly obtained line in arr[index]
		// start finding min again.
string getMin( string arr[], int n, int &index)
{
	string min = "";
	for(int i= 0; i < n; i++)
		if(arr[i].size() != 0)
		{
			min = arr[i];
			break;
		}
	if(min == "")
	{
		index = -1;
		return min;
	}
	for(int i= 0; i < n; i++)
	{
		if( arr[i].compare(min) <=0 && arr[i].compare("") != 0)
		{
			min = arr[i];
			index = i;
		}	
	}
	return min;	
}
void k_merge(string chunk_location, string out_fname, int num_chunks)
{
	ifstream files[num_chunks];
	string curr_lines[num_chunks];
	ofstream myfile;
	myfile.open( out_fname );
	for(int i = 0; i < num_chunks; i++)
	{
		files[i].open(chunk_location + getFnum(i+1) );
		getline(files[i], curr_lines[i]);
	}
	string min;
	int index;
	min = getMin(curr_lines, num_chunks, index);
	while( index != -1)
	{
		myfile << min << endl;
		getline(files[index], curr_lines[index]); 
		min = getMin(curr_lines, num_chunks, index);
	}
	myfile.close();
	return;
}
