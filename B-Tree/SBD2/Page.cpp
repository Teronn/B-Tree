#include "Page.h"
Page::Page()
{
	
}

Page::~Page() {
	vector<int>().swap(keys);
	vector<int>().swap(records);
	if (childPage != nullptr)
		delete childPage;
}

Page::Page(int keyCount) 
	:keysCountMax(keyCount)
{

}



