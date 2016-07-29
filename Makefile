all:
	g++ -ggdb -O3 -o program ExternalSort.cpp ExternalSearch.cpp main.cpp ExternalSort.h ExternalSearch.h -std=c++11
clean: 
	$(RM) program 