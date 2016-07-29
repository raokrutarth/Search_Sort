#include "ExternalSearch.h"
#include <fstream>
// do binary search.
	// get file length using seekg or similar.
	// start at halfway and the input is sorted.
	// if the value you are searching for is smaller/larger than halfway.
	// go halfway of the left/right of original halfwaypoint.
	// warning: going to halfway might put the pointer in the middle of the line,
	// sols: move backwards till a '/n' and move one step front.
bool extern_search(string fileName, string toFind)
{
	ifstream inpFile(fileName);
	if(inpFile.is_open() )
	{
		string line;
		getline(inpFile, line); //for first line   
	    	if(line == toFind)
	    		return true;	
		inpFile.seekg (0, ios_base::end);
	    long length = inpFile.tellg();
	    inpFile.seekg(0, ios_base::beg);
	    long offset = length;
	    //inpFile.seekg (length/2);
	    //cout << length << endl;
	    while(offset > 0)
	    {
	    	long curr = inpFile.tellg();	    	
	    	getline(inpFile, line); 
	    	getline(inpFile, line);   
	    	if(line == toFind)
	    		return true;	   
		    //cout << "line visited = " << line << " offset = " << offset << endl;		    
			offset /=2;			
		    if(line.compare(toFind) < 0)
		    {
		    	inpFile.seekg (curr + offset);
		    }		   		
		    else
		    {
		    	if( (curr-offset) >= 0)
		    		inpFile.seekg(curr - offset);
		    	else
		    		inpFile.seekg(0);
		    }		        
	    }
	    return false;
	}
}