#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>     
#include <fstream>
#include <cmath>
#include "Page.h"
#pragma once



class Operations
{
public:
	Operations();
	int height;
	int level;
	int pages;
	int rootAddress;
	int address_dist;
	int record_dist;
	int sizeOfNumbers;
	int addRecord(int, Page*, int*,int,int);
	int split(int, Page*, int*, int,int);
	int compensation(int, Page*, int*, int,int);
	int loadBlocks(int, int, Page*);
	int loadPage(char*,Page*);
	int loadPageA(Page*,int);
	int printPages(int, int,int);
	void updatePage(int, Page *);
	void loadInfo();
	void saveInfo(int, int);
	void saveRecord(int, int *,int);
	void printRecords(int,int,int);
	void printRecord(int);
	bool keyExists(int);


};