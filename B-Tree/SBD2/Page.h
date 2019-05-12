#include <iostream>
#include <vector>
#include <stdlib.h>
#pragma once

using namespace std;


class Page
{
public:
	int keysCount;
	int keysCountMax;
	int role;
	int height;
	Page(int);
	Page();
	~Page();
	vector<int> keys;
	vector<int> records;
	vector<int> children;
	Page * parentPage;
	Page * leftNeighbour;
	Page * rightNeighbour;
	Page * childPage;

};