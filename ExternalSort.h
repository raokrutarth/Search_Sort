#include <iostream>
#include <string>

using namespace std;

void extern_sort(string in_fname, string out_fname, string chunk_location, int chunk_size);

// Pick your favorite n*log(n) sorting algorithm here!		
void sort(string chunk[]); 

// Write a temporary chunk file
void write_chunk(string fileName, int numItems);

string getFnum(int a);

void msort(string chunk[], int n, int low, int high) ;
void merger(string chunk[], int n, int first, int mid, int last);

// Merges the k temporary files
void k_merge(string chunk_location, string out_fname, int num_chunks);
