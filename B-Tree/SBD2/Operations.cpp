#include "Operations.h"

Operations::Operations()
{
	loadInfo();
	pages = 1;
}

/*
int Operations::findRecord(int x,Page pagex) {

	Page * pagePointer = nullptr;

	for (int i = 0; i < pagex.keys.size(); i++)
	{
		
		if (pagex.keys[i] == x)
			return pagex.records[i];
		else if (pagex.keys[i] > x)
		{
			if (pagex.pages[i] == NULL)
				return -1;
			else return findRecord(x, pagex.pages[i][0]);
		}
	}



	return -1;
	// Nie znaleziono

}

Page Operations::findPage(int x, Page pagex)
{
	for (int i = 0; i < pagex.keys.size(); i++)
	{
		if (pagex.keys[i] > x)
		{
			if (pagex.pages[i] == NULL)
				return pagex;
			else return findPage( x, pagex.pages[i][0]);
		}
	}
	return pagex;
}

int Operations::addRecord(int x, Page pagex, int * r) {

	if (findRecord(x, pagex) != -1)
		return -1;

	// Wejdü na odpowiednia strone

	Page * pointer = NULL;
	pointer = &findPage(x, pagex);



	// Sprawdz czy odpowiednia ilosc elementow

	if ((*pointer).keysCount < (*pointer).keysCountMax)
	{
		for (int i = 0; i < (*pointer).keys.size(); i++)
		{
			if ((*pointer).keys[i] > x)
			{
				(*pointer).keys.insert((*pointer).keys.begin() + i, x);
				// TODO - rekordy wstaw
				return 1;

			}
		}
		(*pointer).keys.push_back(x);
		return 1;
	} else	if ((*pointer).role = 0)
		//Czy jest rootem
	{
		// Zwiekszenie wysokosci drzewa o 1 - rozszczepienie i utworzenie nowych stron
	}

	// Przepe≥nienie - kompensacja

	

	Page * parentPointer = (*pointer).parentPage;

	int tmpx = 0;
	int flag = 0;
	for (; tmpx < (*parentPointer).keysCountMax; tmpx++)
	{
		if ((*parentPointer).keys[tmpx] > x)
		{
			flag = 1;
			break;
		}
		
	}
	if (flag = 0)
		tmpx = (*parentPointer).keysCountMax;

	// Jesli ma tylko prawego sasiada

	if (tmpx == 0)
	{
		if ((*parentPointer).pages[tmpx + 1]->keysCount < (*parentPointer).pages[tmpx + 1]->keysCountMax)
		{

			// REKORDY TODO

			int tmpkey = (*parentPointer).keys[0];
			(*parentPointer).keys[0] = (*pointer).keys[(*parentPointer).keysCountMax - 1];
			(*pointer).keys.pop_back;
			(*parentPointer).pages[tmpx + 1]->keys.insert((*parentPointer).pages[tmpx + 1]->keys.begin(), tmpkey);
			int tmps = 0;
			int flag2 = 0;
			for (; tmps < (*pointer).keysCountMax; tmps++)
			{
				if ((*pointer).keys[tmps] > x)
				{
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 1)
			{
				(*pointer).keys.insert((*pointer).keys.begin() + tmps, x);


			}
			else (*pointer).keys.push_back(x);
		

		}

		//Trzeba dokonac rozszczepienia
	}





}


int Operations::addRecord(int x, Page * pagex, int *r) {
	int status;

	status = findRecord(x, *pagex);

	if (status != -1) 
		return -1;

	Page targetPage = findPage(x, *pagex);
	
	status = newRecord(x, &targetPage,r);

	if (status == -1)
		status = compensation(x, &targetPage, r);
	else return 1;
	if (status == -1)
		return split(x, &targetPage, r);
	else return 1;




	return 0;
}

int Operations::newRecord(int x, Page * pagex, int *r)
{
	if (pagex->keysCount == pagex->keysCountMax)
		return -1;

	for (int i = 0; i < pagex->keysCount; i++)
	{
		if (pagex->keys[i] > x) {
			pagex->keys.insert(pagex->keys.begin() + i, x);
			//rekordy
			pagex->keysCount++;
			return 1;
			
		}
	}

	pagex->keys.push_back(x);
	pagex->keysCount++;
	return 1;
}

int Operations::compensation(int x, Page * pagex, int *r)
{
	if (pagex->role == 1)
		return -1;

	// Okreúl jakich ma sasiadow  - czy lewy, czy prawy (preferuj lewego)

	Page * parentNode = pagex->parentPage;
	
	int i;
	int tmpFlag = 0;

	for (i = 0; i < parentNode->keysCount; i++)
	{
		if (parentNode->keys[i] > x)
		{
			tmpFlag = 1;
			break;
		}
	}

	if (tmpFlag != 1)
		i++;

	// Jeúli ma tylko prawego sπsiada
	if (i == 0) {
		if (parentNode->pages[1][0].keysCount == parentNode->pages[1][0].keysCountMax)
			return -1;

		// dokonaj prawej kompensacji

		int tmp = pagex->keys.pop_back;
		pagex->keysCount--;

		tmpFlag = 0;

		for (int j = 0; j < pagex->keysCount;j++)
		{
			if (pagex->keys[j] > x)
			{
				tmpFlag = 1;
				pagex->keys.insert(pagex->keys.begin() + j, x);
				pagex->keysCount++;
				break;
			}


		}

		if (tmpFlag = 0) {
			pagex->keys.push_back(x);
			pagex->keysCount++;
		}

		tmpFlag = parentNode->keys[0];
		parentNode->keys[0] = tmp;
		parentNode->pages[1]->keys.insert(parentNode->pages[1]->keys.begin(), tmpFlag);
		parentNode->pages[1]->keysCount++;

		return 1;
	}

	if (i > 0 && i < parentNode->keysCount)
	{
		int neighFlag = 0;
		if (parentNode->pages[i + 1][0].keysCount == parentNode->pages[i + 1][0].keysCountMax)
			neighFlag = 1;
		if (neighFlag == 1 && parentNode->pages[i - 1][0].keysCount == parentNode->pages[i - 1][0].keysCountMax)
			return -1;
		
		if (neighFlag == 0)
		{
			int tmp = pagex->keys.pop_back;
			pagex->keysCount--;

			tmpFlag = 0;

			for (int j = 0; j < pagex->keysCount; j++)
			{
				if (pagex->keys[j] > x)
				{
					tmpFlag = 1;
					pagex->keys.insert(pagex->keys.begin() + j, x);
					pagex->keysCount++;
					break;
				}


			}

			if (tmpFlag = 0) {
				pagex->keys.push_back(x);
				pagex->keysCount++;
			}

			tmpFlag = parentNode->keys[i];
			parentNode->keys[i] = tmp;
			parentNode->pages[i+1]->keys.insert(parentNode->pages[i+1]->keys.begin(), tmpFlag);
			parentNode->pages[i+1]->keysCount++;

			return 1;

		}
		if (neighFlag == 1) {
			int tmp = pagex->keys[0];
			pagex->keys.erase(pagex->keys.begin);
			pagex->keysCount--;

			tmpFlag = 0;

			for (int j = 0; j < pagex->keysCount; j++)
			{
				if (pagex->keys[j] > x)
				{
					tmpFlag = 1;
					pagex->keys.insert(pagex->keys.begin() + j, x);
					pagex->keysCount++;
					break;
				}


			}
			if (tmpFlag = 0) {
				pagex->keys.push_back(x);
				pagex->keysCount++;
			}

			tmpFlag = parentNode->keys[i];
			parentNode->keys[i] = tmp;
			parentNode->pages[i - 1]->keys.push_back(tmpFlag);
			parentNode->pages[i - 1]->keysCount++;

			return 1;
		}

	}

	if (i == parentNode->keysCount)
	{
		int tmp = pagex->keys[0];
		pagex->keys.erase(pagex->keys.begin);
		pagex->keysCount--;

		tmpFlag = 0;

		for (int j = 0; j < pagex->keysCount; j++)
		{
			if (pagex->keys[j] > x)
			{
				tmpFlag = 1;
				pagex->keys.insert(pagex->keys.begin() + j, x);
				pagex->keysCount++;
				break;
			}


		}
		if (tmpFlag = 0) {
			pagex->keys.push_back(x);
			pagex->keysCount++;
		}

		tmpFlag = parentNode->keys[i];
		parentNode->keys[i] = tmp;
		parentNode->pages[i - 1]->keys.push_back(tmpFlag);
		parentNode->pages[i - 1]->keysCount++;

		return 1;
	}
}

int Operations::split(int x, Page * pagex, int *r) {

}

int Operations::addRecord(int x, Page * pagex, int * r, Page * heritedPage) {


}

*/

void Operations::loadInfo() {
	std::ifstream is("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btreeinfo.txt");
	char buf[56];
	
	do {
		is.read(buf, sizeof(buf));

		height = 0;

		for (int i = 0; i < 8; i++)
		{
			height += (buf[7 - i] - 48) * pow(10, i);
		}

		rootAddress = 0;


		for (int i = 0; i < 8; i++)
		{
			rootAddress += (buf[15 - i] - 48) * pow(10, i);
		}

		level = 0;


		for (int i = 0; i < 8; i++)
		{
			level += (buf[23 - i] - 48) * pow(10, i);
		}

		address_dist = 0;


		for (int i = 0; i < 8; i++)
		{
			address_dist += (buf[31 - i] - 48) * pow(10, i);
		}

		record_dist = 0;


		for (int i = 0; i < 8; i++)
		{
			record_dist += (buf[39 - i] - 48) * pow(10, i);
		}

		sizeOfNumbers = 0;


		for (int i = 0; i < 8; i++)
		{
			sizeOfNumbers += (buf[47 - i] - 48) * pow(10, i);
		}
		pages = 0;

		for (int i = 0; i < 8; i++)
		{
			pages += (buf[55 - i] - 48) * pow(10, i);
		}
	} while (is);
	is.close();
}

void Operations::saveInfo(int option, int number)
{

	int currentRest = 0;
	int currentVar = 0;
	currentVar = number;

	char numberToChange[8];
	for (int i = 0; i < 8; i++)
		numberToChange[i] = 48;
	for (int i = 0; i < 8; i++)
	{
		currentRest = currentVar % 10;
		currentVar = currentVar / 10;
		numberToChange[7 - i] = currentRest + 48;
		if (currentVar == 0)
			break;
	}

	ofstream file("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btreeinfo.txt", ios::out | ios::in | ios::binary);
	file.seekp((option - 1) * 8, ios::beg);
	file.write(numberToChange, 8);
	file.close();


}

void Operations::saveRecord(int rec, int *tab,int size) {

	char * newTab = new char[(size + 1) * 8];
	for (int i = 0; i < (size + 1) * 8; i++)
		newTab[i] = 48;
	int currentRest = 0;
	int currentVar = 0;
	currentVar = rec;
	for (int i = 0; i < 8; i++)
	{
		currentRest = currentVar % 10;
		currentVar = currentVar / 10;
		newTab[7 - i] = currentRest + 48;
		if (currentVar == 0)
			break;
	}

	for (int i = 0; i < size; i++) {
		currentVar = (*(tab+i));
		for (int j = 0; j < 8; j++)
		{
			currentRest = currentVar % 10;
			currentVar = currentVar / 10;
			newTab[15 +(i*8) - j] = currentRest + 48;
			if (currentVar == 0)
				break;
		}
	}

	ofstream file("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/records.txt", ios::out | ios::in | ios::binary);
	file.seekp((rec - 1) * (size + 1)*8, ios::beg);
	file.write(newTab, (size+1)*8);
	file.close();

	delete []newTab;

}

int Operations::loadPageA(Page * page, int address) {
	std::ifstream is("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btree.txt");
	int bytes = 8 * (6 * level + 4);
	char * buf= new char[bytes];
	Page* tmp = new Page;
	do {
		is.read(buf, bytes);
		loadPage(buf, tmp);
		if ((*tmp).role == address)
			break;

	} while (is);
	is.close();
	*page = *tmp;

	delete tmp;
	delete[]buf;
	return 1;
}

int Operations::loadPage(char* bytes,Page * page)
{
	int var = 0;
	int tmp = 0;
	Page newPage;
	newPage.keysCountMax = 2*level;
	newPage.leftNeighbour = nullptr;
	newPage.rightNeighbour = nullptr;
	newPage.parentPage = nullptr;
	newPage.childPage = nullptr;

	// Wysokosc
	

	for (int i = 0; i < 8; i++)
	{
		tmp += (bytes[7-i]-48) * pow(10, i);
	}
	
	newPage.height = tmp;

	tmp = 0;

	// Liczba kluczy

	for (int i = 0; i < 8; i++)
	{
		tmp += (bytes[15 - i] - 48) * pow(10, i);
	}

	newPage.keysCount = tmp;
	

	tmp = 0;

	// Adres strony

	for (int i = 0; i < 8; i++)
	{
		tmp += (bytes[23 - i] - 48) * pow(10, i);
	}

	newPage.role = tmp;

	tmp = 0;

	// Klucze

	for (int i = 0; i < newPage.keysCount; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tmp += (bytes[31 + 8*i - j] - 48) * pow(10, j);
		}
		
		newPage.keys.push_back(tmp);
		
		tmp = 0;
	}

	// Adresy rekordÛw 
	tmp = 0;

	for (int i = 0; i < newPage.keysCount; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tmp += (bytes[31 + (2*level*8) + 8 * i - j] - 48) * pow(10, j);
		}
		
		newPage.records.push_back(tmp);
		
		tmp = 0;
	}


// Adresy dzieci

	tmp = 0;

for (int i = 0; i < newPage.keysCount+1; i++)
{
	for (int j = 0; j < 8; j++)
	{
		tmp += (bytes[31+ (4 * level * 8) + 8 * i - j] - 48) * pow(10, j);
	}
	
		newPage.children.push_back(tmp);
	
	tmp = 0;
}

*page = newPage;

return 1;
}

int Operations::loadBlocks(int t, int x, Page * page) {
	std::ifstream is("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btree.txt");
	int bytes = 8 * (6 * level + 4);
	char *buf = new char[bytes];
	int tier = 1;
	int j = 0;
	int flag = 0;
	Page* tmp = new Page;
	/*do {
		is.read(buf, sizeof(buf));
		loadPage(buf, tmp);
		
		if (tier > 1 && tier == (*tmp).height)
		{
			if (add == (*tmp).role)
			{
				(*page).childPage = tmp;
				tier++;
				*page = *tmp;

			}


		}

		if ((*tmp).height == 1) {
			*page = *tmp;
			tier++;
			for (int i = 0; i < page->keysCount; i++)
			{
				if (x < page->keys[i])
				{
					add = page->children[i];
					tmpVar++;
					kex++;
					break;


				}

			}
			if (tmpVar != 1)
			{
				add = page->children[page->keysCount];
				tmpVar = 0;
				lNeigh = page->children[page->keysCount - 1];
			}
		}

		if (tier == t && kex > 0)
			break;



	} while (is);
	*/
	loadPageA(tmp, rootAddress);
	//cout << (*tmp).keys[0] << "<- sprawdzenie Roota" << endl;
	for (int i = 1; i < t; i++)
	{
		for (j = 0; j < (*tmp).keysCount; j++)
		{
			if (x < (*tmp).keys[j])
			{
				(*tmp).childPage = new Page;
				loadPageA((*tmp).childPage, (*tmp).children[j]);
				(*(*tmp).childPage).parentPage = tmp;
				tmp = (*tmp).childPage;
				
				flag++;
				break;
			}

		}
		if (flag == 0)
		{
			(*tmp).childPage = new Page;
			loadPageA((*tmp).childPage, (*tmp).children[(*tmp).keysCount]);
			(*(*tmp).childPage).parentPage = tmp;
			tmp = (*tmp).childPage;
		}
		flag = 0;
		j = 0;
	}

	*page = *tmp;
	cout << (*page).keys[0] << "<- sprawdzenie" << endl;
	delete tmp;
	delete[]buf;
	return 1;
}

int Operations::printPages(int depth, int address, int keys)
{
	Page * tmp = new Page;
	loadPageA(tmp,address);

	int k = 0;

	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}
	cout << "> ";
	for (int i = 0; i < (*tmp).keysCount; i++)
	{
		cout << (*tmp).keys[i] << "  ";
	}
	cout << endl;

	for (int i = 0; i < (*tmp).keysCount + 1; i++)
	{
		if (((*tmp).children[i])!=0)
		{
			printPages(depth + 1, (*tmp).children[i],k);
		}
	}

	delete tmp;

	return k;
}

void Operations::updatePage(int address, Page * page)
{
	int bytes = 8*(2 * level * 3 + 4);// 2*level*3+1+3
	char *update = new char[bytes];
	
	int currentVar = 0;
	int currentRest = 0;
	
	for (int i = 0; i < bytes; i++)
		update[i] = 48;
		
	currentVar = (*page).height;

	for (int i = 0; i < 8; i++)
	{
		currentRest = currentVar % 10;
		currentVar = currentVar / 10;
		update[7 - i] = currentRest + 48;
		if (currentVar == 0)
			break;
	}

	currentVar = (*page).keysCount;

	for (int i = 0; i < 8; i++)
	{
		currentRest = currentVar % 10;
		currentVar = currentVar / 10;
		update[15 - i] = currentRest + 48;
		if (currentVar == 0)
			break;
	}

	currentVar = (*page).role;

	for (int i = 0; i < 8; i++)
	{
		currentRest = currentVar % 10;
		currentVar = currentVar / 10;
		update[23 - i] = currentRest + 48;
		if (currentVar == 0)
			break;
	}

	for (int i = 0; i < (*page).keysCount; i++)
	{
		currentVar = (*page).keys[i];
		for (int j = 0; j < 8; j++)
		{
			currentRest = currentVar % 10;
			currentVar = currentVar / 10;
			update[31 + 8 * i - j] = currentRest + 48;
			if (currentVar == 0)
				break;
		}
	}


	for (int i = 0; i < (*page).keysCount; i++)
	{
		currentVar = (*page).records[i];
		for (int j = 0; j < 8; j++)
		{
			currentRest = currentVar % 10;
			currentVar = currentVar / 10;
			update[31 + (2*level*8) + 8 * i - j] = currentRest + 48;
			if (currentVar == 0)
				break;
		}
	}


	for (int i = 0; i < (*page).keysCount + 1; i++)
	{
		currentVar = (*page).children[i];
		for (int j = 0; j < 8; j++)
		{
			currentRest = currentVar % 10;
			currentVar = currentVar / 10;
			update[31 + (4*level*8) + 8 * i - j] = currentRest + 48;
			if (currentVar == 0)
				break;
		}
	}

	// gotowa tablica do zamiany

	ofstream file("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btree.txt", ios::out | ios::in | ios::binary);
	file.seekp((address - 1) * bytes, ios::beg);
	file.write(update, bytes);
	file.close();
	delete[]update;

}

int Operations::addRecord(int x, Page * page, int * tab, int t, int pocketAddress)
{
	Page * currentPage = new Page;
	*currentPage = *page;
	cout << "Dodaje" << endl;




	if ((*currentPage).keysCount < (*currentPage).keysCountMax)
	{
		int i = 0;
		int flag = 0;
		for (; i < (*currentPage).keysCount; i++)
		{
			if ((*currentPage).keys[i] > x)
			{
				(*currentPage).keys.insert((*currentPage).keys.begin() + i, x);
				(*currentPage).records.insert((*currentPage).records.begin() + i, ++record_dist);
				saveRecord(record_dist, tab, sizeOfNumbers);
				saveInfo(5, record_dist);
				(*currentPage).children.insert((*currentPage).children.begin() + i+1, pocketAddress);
				(*currentPage).keysCount++;
				flag++;
				break;
			}
		}

		if (flag == 0)
		{
			(*currentPage).records.push_back(++record_dist);
			saveRecord(record_dist, tab, sizeOfNumbers);
			saveInfo(5, record_dist);
			(*currentPage).keys.push_back(x);
			(*currentPage).children.push_back(pocketAddress);
			(*currentPage).keysCount++;

		}

		//printPages(level, rootAddress);
		//cout << "Dodaje w tym momencie x = " << x << endl;


		updatePage((*currentPage).role, currentPage);
		//cout << "Udalo sie!" << endl;
		return 1;
	}



	//cout << "Wykonam kompensacje" << endl;
	return compensation(x,page,tab,t,pocketAddress);
}

int Operations::compensation(int x, Page * page, int * tab, int t, int pocketAddress) {

	Page * tmp = new Page;
	Page * tmp2 = new Page;

	// Kompensacja na roocie jest niemoøliwa
	if ((*page).role == rootAddress)
	{
		cout << "To jest root - wiec wykonam splita" << endl;
		return split(x, page, tab, t,pocketAddress);
	}
	//cout << "..." << endl;

	// jesli nie ma sasiada lewego

	int i = 0;
	if ((*(*page).parentPage).children[0] == (*page).role)
	{
		loadPageA(tmp, (*(*page).parentPage).children[1]);

		//cout << "Kompensacja na pierwszym elemencie" << endl;
		// TODO dzis
		if ((*tmp).keysCount == (*tmp).keysCountMax)
		{
			//cout << "Niestety split" << endl;
			return split(x, page, tab, t, pocketAddress);
		}

		int d = 0;
		int statusFlag = 0;
		int flag = 0;


		for (; d < (*page).keysCount; d++)
		{
			if ((*page).keys[d] > x)
			{
				(*page).keys.insert((*page).keys.begin() + d, x);
				(*page).records.insert((*page).records.begin() + d, ++record_dist);
				saveRecord(record_dist, tab, sizeOfNumbers);
				saveInfo(5, record_dist);
				(*page).keysCount++;
				(*page).children.insert((*page).children.begin() + d + 1, pocketAddress);
				flag++;
				break;
			}


		}


		if (flag == 0)
		{
			(*page).keys.push_back(x);
			(*page).records.push_back(++record_dist);
			(*page).children.push_back(pocketAddress);
			saveRecord(record_dist, tab, sizeOfNumbers);
			saveInfo(5, record_dist);
			(*page).keysCount++;
		}


		(*tmp).keys.insert((*tmp).keys.begin(), (*(*page).parentPage).keys[0]);
		(*tmp).records.insert((*tmp).records.begin(), (*(*page).parentPage).records[0]);
		(*tmp).children.insert((*tmp).children.begin(), (*page).children[(*page).keysCount]);
		(*tmp).keysCount++;

		(*(*page).parentPage).keys[0] = (*page).keys[(*page).keysCount-1];
		(*(*page).parentPage).records[0] = (*page).records[(*page).keysCount-1];


		(*page).keys.pop_back();
		(*page).records.pop_back();
		(*page).children.pop_back();
		(*page).keysCount--;

		//printPages(level, rootAddress);
		//cout << "Dodaje w tym momencie x = " << x << endl;

		updatePage((*page).role, page);
		updatePage((*tmp).role, tmp);
		updatePage((*(*page).parentPage).role, (*page).parentPage);

	}
	else if ((*(*page).parentPage).children[(*(*page).parentPage).keysCount] == (*page).role)
	{
		loadPageA(tmp, (*(*page).parentPage).children[(*(*page).parentPage).keysCount-1]);

		//cout << "Kompensacja na prawym granicznym" << endl;

		// TODO dzis
		if ((*tmp).keysCount == (*tmp).keysCountMax)
			return split(x, page, tab, t, pocketAddress);

		int d = 0;
		int statusFlag = 0;
		int flag = 0;


		for (; d < (*page).keysCount; d++)
		{
			if ((*page).keys[d] > x)
			{
				(*page).keys.insert((*page).keys.begin() + d, x);
				(*page).records.insert((*page).records.begin() + d, ++record_dist);
				saveRecord(record_dist, tab, sizeOfNumbers);
				saveInfo(5, record_dist);
				(*page).keysCount++;
				(*page).children.insert((*page).children.begin() + d + 1, pocketAddress);
				flag++;
				break;
			}


		}


		if (flag == 0)
		{
			(*page).keys.push_back(x);
			(*page).records.push_back(++record_dist);
			(*page).children.push_back(pocketAddress);
			saveRecord(record_dist, tab, sizeOfNumbers);
			saveInfo(5, record_dist);
			(*page).keysCount++;
		}

		(*tmp).keys.push_back((*(*page).parentPage).keys[(*(*page).parentPage).keysCount-1]);
		(*tmp).records.push_back((*(*page).parentPage).records[(*(*page).parentPage).keysCount - 1]);
		(*tmp).children.push_back((*page).children[0]);
		(*tmp).keysCount++;

		(*(*page).parentPage).keys[(*(*page).parentPage).keysCount - 1] = (*page).keys[0];
		(*(*page).parentPage).records[(*(*page).parentPage).keysCount - 1] = (*page).records[0];

		(*page).keys.erase((*page).keys.begin());
		(*page).records.erase((*page).records.begin());
		(*page).children.erase((*page).children.begin());
		(*page).keysCount--;

		//printPages(level, rootAddress);
		//cout << "Dodaje w tym momencie x = " << x << endl;

		updatePage((*page).role, page);
		updatePage((*tmp).role, tmp);
		updatePage((*(*page).parentPage).role,(*page).parentPage);


	}
	else
	{
	cout << "Kompensacja na srodkowym prawym" << endl;
	int tempo = 1;
	for (; tempo < (*(*page).parentPage).keysCount; tempo++)
	{
		if (x < (*(*page).parentPage).keys[tempo])
			break;
	}
	//cout << "Kompensacja na srodkowym prawym3" << endl;
	loadPageA(tmp, (*(*page).parentPage).children[tempo-1]);
	if ((*tmp).keysCount == (*tmp).keysCountMax)
	{
		//cout << "Kompensacja na srodkowym prawym2" << endl;
		//cout << "tempo jest rowne:" << tempo << endl;
		cout << (*(*page).parentPage).keysCount << endl;
		//printPages(level, rootAddress);
		//cout << "Dodaje w tym momencie x = " << x << endl;
		loadPageA(tmp, (*(*page).parentPage).children[tempo+1]);
		//cout << "Kompensacja na srodkowym prawym4" << endl;
		if ((*tmp).keysCount == (*tmp).keysCountMax)
			return split(x, page, tab, t, pocketAddress);


		int d = 0;
		int statusFlag = 0;
		int flag = 0;

		//cout << "Kompensacja na srodkowym prawym" << endl;

		for (; d < (*page).keysCount; d++)
		{
			if ((*page).keys[d] > x)
			{
				(*page).keys.insert((*page).keys.begin() + d, x);
				(*page).records.insert((*page).records.begin() + d, ++record_dist);
				saveRecord(record_dist, tab, sizeOfNumbers);
				saveInfo(5, record_dist);
				(*page).keysCount++;
				(*page).children.insert((*page).children.begin() + d + 1, pocketAddress);
				flag++;
				break;
			}


		}

		//cout << "." << endl;
		if (flag == 0)
		{
			(*page).keys.push_back(x);
			(*page).records.push_back(++record_dist);
			(*page).children.push_back(pocketAddress);
			saveRecord(record_dist, tab, sizeOfNumbers);
			saveInfo(5, record_dist);
			(*page).keysCount++;
		}
		//cout << "." << endl;

		(*tmp).keys.insert((*tmp).keys.begin(), (*(*page).parentPage).keys[tempo]);
		(*tmp).records.insert((*tmp).records.begin(), (*(*page).parentPage).records[tempo]);
		(*tmp).children.insert((*tmp).children.begin(), (*page).children[(*page).keysCount]);
		(*tmp).keysCount++;
		//cout << "." << endl;
		(*(*page).parentPage).keys[tempo] = (*page).keys[(*page).keysCount-1];
		(*(*page).parentPage).records[tempo] = (*page).records[(*page).keysCount-1];

		//cout << "." << endl;
		(*page).keys.pop_back();
		(*page).records.pop_back();
		(*page).children.pop_back();
		(*page).keysCount--;
		//cout << "." << endl;
		updatePage((*page).role, page);
		updatePage((*tmp).role, tmp);
		updatePage((*(*page).parentPage).role, (*page).parentPage);


	}
	else
	{

		int d = 0;
		int statusFlag = 0;
		int flag = 0;

		//cout << "Kompensacja na srodkowym lewym" << endl;
		for (; d < (*page).keysCount; d++)
		{
			if ((*page).keys[d] > x)
			{
				(*page).keys.insert((*page).keys.begin() + d, x);
				(*page).records.insert((*page).records.begin() + d, ++record_dist);
				saveRecord(record_dist, tab, sizeOfNumbers);
				saveInfo(5, record_dist);
				(*page).keysCount++;
				(*page).children.insert((*page).children.begin() + d + 1, pocketAddress);
				flag++;
				break;
			}


		}


		if (flag == 0)
		{
			(*page).keys.push_back(x);
			(*page).records.push_back(++record_dist);
			(*page).children.push_back(pocketAddress);
			saveRecord(record_dist, tab, sizeOfNumbers);
			saveInfo(5, record_dist);
			(*page).keysCount++;
		}

		(*tmp).keys.push_back((*(*page).parentPage).keys[tempo-1]);
		(*tmp).records.push_back((*(*page).parentPage).records[tempo - 1]);
		(*tmp).children.push_back((*page).children[0]);
		(*tmp).keysCount++;

		(*(*page).parentPage).keys[tempo - 1] = (*page).keys[0];
		(*(*page).parentPage).records[tempo - 1] = (*page).records[0];

		(*page).keys.erase((*page).keys.begin());
		(*page).records.erase((*page).records.begin());
		(*page).children.erase((*page).children.begin());
		(*page).keysCount--;

		updatePage((*page).role, page);
		updatePage((*tmp).role, tmp);
		updatePage((*(*page).parentPage).role, (*page).parentPage);
	}


	}

	delete tmp;
	delete tmp2;
	return 1;
}

int Operations::split(int x, Page * page, int * tab, int t, int pocketAddress) {

	// Rozszczepienie na roocie jest inne
	/*if (t == 1 && height == 1)
	{
		Page * newRoot = new Page;
		Page * newPage = new Page;


		int i = 0;
		int statusFlag = 0;
		int flag = 0;


		for (; i < (*page).keysCount; i++)
		{
			if ((*page).keys[i] > x)
			{
				(*page).keys.insert((*page).keys.begin() + i, x);
				(*page).records.insert((*page).records.begin() + i, ++record_dist);
				(*page).keysCount++;
				flag++;
				break;
			}


		}


		if (flag == 0)
		{
			(*page).keys.push_back(x);
			(*page).keysCount++;
		}
		(*newRoot).keysCount = 1;
		(*newRoot).height = 1;
		(*newRoot).role = 1;
		(*newRoot).keysCountMax = (*page).keysCountMax;
		(*newRoot).keys.push_back((*page).keys[(*page).keysCountMax / 2]);
		(*newRoot).records.push_back((*page).records[(*page).keysCountMax / 2]);
		(*newRoot).children.push_back(2);
		(*newRoot).children.push_back(3);

		(*newPage).keysCount = 0;
		(*newPage).role = 3;
		(*newPage).height = 2;
		(*newPage).keysCountMax = (*page).keysCountMax;

		for (int k = 0; k < (*page).keysCountMax / 2; k++)
		{
			(*newPage).keys.push_back((*page).keys[(*page).keysCountMax / 2 + 1 + k]);
			(*newPage).records.push_back((*page).records[(*page).keysCountMax / 2 + 1 + k]);
			(*newPage).children.push_back(0);
			(*newPage).keysCount++;
		}

		(*newPage).children.push_back(0);


		(*page).role = 2;
		(*page).height = 2;


		for (int k = 0; k < (*page).keysCountMax / 2+1; k++)
		{
			(*page).keys.pop_back();
			(*page).records.pop_back();
			(*page).keysCount--;
		}

		updatePage(1, newRoot);
		updatePage(2, page);
		updatePage(3, newPage);


			delete newRoot;
			delete newPage;
			return -1;

	}
	*/
Page * tmpPage = new Page;


int d = 0;
int statusFlag = 0;
int flag = 0;

for (; d < (*page).keysCount; d++)
{
	if ((*page).keys[d] > x)
	{
		(*page).keys.insert((*page).keys.begin() + d, x);
		(*page).records.insert((*page).records.begin() + d, ++record_dist);
		saveRecord(record_dist, tab, sizeOfNumbers);
		saveInfo(5, record_dist);
		(*page).keysCount++;
		(*page).children.insert((*page).children.begin() + d + 1, pocketAddress);
		flag++;
		break;
	}


}
//cout << "Split" << endl;

if (flag == 0)
{
	(*page).keys.push_back(x);
	(*page).records.push_back(++record_dist);
	(*page).children.push_back(pocketAddress);
	saveRecord(record_dist, tab, sizeOfNumbers);
	saveInfo(5, record_dist);
	(*page).keysCount++;
}

(*tmpPage).keysCount = 0;
for (int i = (*page).keysCount / 2 + 1; i < (*page).keysCount; i++)
{
	(*tmpPage).keys.push_back((*page).keys[i]);
	(*tmpPage).records.push_back((*page).records[i]);
	(*tmpPage).children.push_back((*page).children[i]);
	(*tmpPage).keysCount++;
}
(*tmpPage).children.push_back((*page).children[(*page).keysCount]);
(*tmpPage).role = ++address_dist;
saveInfo(4, address_dist);
(*tmpPage).keysCountMax = 2 * level;

int varTmp = (*page).keys[(*page).keysCount / 2];
int varRec = (*page).records[(*page).keysCount / 2];

for (int i = (*page).keysCount / 2 + 1; i > 0; i--) {
	(*page).keys.pop_back();
	(*page).records.pop_back();
	(*page).children.pop_back();
	(*page).keysCount--;
}

//printPages(level, rootAddress);
//cout << "Dodaje w tym momencie x = " << x << endl;
pages++;
updatePage((*page).role, page);
updatePage((*tmpPage).role, tmpPage);

if (rootAddress == (*page).role)
{
	Page * newRoot = new Page;
	(*newRoot).keys.push_back(varTmp);
	(*newRoot).records.push_back(varRec);
	(*newRoot).children.push_back((*page).role);
	(*newRoot).children.push_back((*tmpPage).role);
	(*newRoot).role = ++address_dist;
	saveInfo(2, address_dist);
	saveInfo(1, ++height);
	saveInfo(4, address_dist);
	rootAddress = address_dist;
	(*newRoot).keysCount = 1;
	(*newRoot).keysCountMax = 2 * level;

	//printPages(level, rootAddress);
	//cout << "Dodaje w tym momencie x = " << x << endl;
	pages++;
	saveInfo(7,pages);
	updatePage((*newRoot).role, newRoot);

	cout << "Rootujemy po splicie" << endl;
	delete newRoot;
	delete tmpPage;
	return 1;
}
else
{
	//cout << "Dodajemy po splicie" << endl;
	return addRecord(varTmp, (*page).parentPage, tab, height, (*tmpPage).role);

}



}

bool Operations::keyExists(int key) {

	Page * page = new Page;
	loadBlocks(height, key, page);
	do {
		for (int i = 0; i < (*page).keysCount; i++)
		{
			if (key == (*page).keys[i])
				return true;
		}

		if ((*page).parentPage != nullptr)
			page = (*page).parentPage;
		else break;
		
	} while (true);

	if ((*page).parentPage == nullptr)
		return false;
	delete page;
}

void Operations::printRecord(int key) {
	Page * page = new Page;
	loadBlocks(height, key, page);
	do {
		for (int i = 0; i < (*page).keysCount; i++)
		{
			if (key == (*page).keys[i])
			{
				int * record = new int[sizeOfNumbers];
				int currentRecord;
				int currentKey;
				int destinationKey = (*page).records[i];
					std::ifstream is("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/records.txt");
					char * buf = new char[(sizeOfNumbers+1)*8];
					do {
						is.read(buf, (sizeOfNumbers + 1) * 8);

						currentKey = 0;

						for (int k = 0; k < 8; k++)
						{
							currentKey += (buf[7 - k] - 48) * pow(10, k);
						}

						if (currentKey == destinationKey) {

							cout << "Dla klucza " << key << " rekody to ";
							for (int w = 0; w < sizeOfNumbers; w++)
							{
								currentRecord = 0;
								for (int e = 0; e < 8; e++)
								{
									currentRecord += (buf[15 + (w*8) - e] - 48) * pow(10, e);
								}

								cout << currentRecord << " ";
							}

							cout << endl;

							break;
						}


					} while (is);
					is.close();

					delete[]record;
					delete[]buf;
				return;

			}
		}

		if ((*page).parentPage != nullptr)
			page = (*page).parentPage;
		else break;

	} while (true);

	if ((*page).parentPage == nullptr)
	{

		std::cout << "Klucz nie istnieje." << endl;
		return;
	}
	delete page;
}

void Operations::printRecords(int depth, int address, int keys) {
	Page * tmp = new Page;
	loadPageA(tmp, address);

	int k = 0;

	for (int i = 0; i < (*tmp).keysCount; i++)
	{
		std::cout << "Klucz: " << (*tmp).keys[i] << " - ";
		int * record = new int[sizeOfNumbers];
		int currentRecord;
		int currentKey;
		int destinationKey = (*tmp).records[i];
		std::ifstream is("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/records.txt");
		char * buf = new char[(sizeOfNumbers + 1) * 8];
		do {
			is.read(buf, (sizeOfNumbers + 1) * 8);

			currentKey = 0;

			for (int k = 0; k < 8; k++)
			{
				currentKey += (buf[7 - k] - 48) * pow(10, k);
			}

			if (currentKey == destinationKey) {

				for (int w = 0; w < sizeOfNumbers; w++)
				{
					currentRecord = 0;
					for (int e = 0; e < 8; e++)
					{
						currentRecord += (buf[15 + (w * 8) - e] - 48) * pow(10, e);
					}

					cout << currentRecord << " ";
				}

				cout << endl;

				break;
			}


		} while (is);
		is.close();

		delete[]record;
		delete[]buf;
		

	}
	

	for (int i = 0; i < (*tmp).keysCount + 1; i++)
	{
		if (((*tmp).children[i]) != 0)
		{
			printRecords(depth + 1, (*tmp).children[i], k);
		}
	}

	delete tmp;


}