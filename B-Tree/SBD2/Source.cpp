#include <iostream>
#include <vector>
#include <stdlib.h>

#include <cstdlib>
#include <ctime>
#include "Page.h"
#include "Operations.h"
#pragma once


using namespace std;

int main() {
	srand(time(NULL));
	Operations oper;
	Page* page = new Page;
	int table2[5] = { 4 , 2 ,3 ,4 ,5 };
	int c = 0;
	float x;
	float y;
	int number;
	int * table = new int[oper.sizeOfNumbers];
	// eksperyment nr.1

	/*float tablica[10000];
	ofstream wynik("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/wynik.txt");

	for (int i = 1; i < 7; )
	{
		c = rand() % 100000 + 1;
		if (oper.keyExists(c) == false) {
			oper.loadBlocks(oper.height, c, page);
			oper.addRecord(c, page, table, oper.height, 0);
			oper.loadInfo();
			x = (float)i;
			y = (2.0 * oper.level * oper.pages);
			
			i++;
			wynik << (float)(x / y) << " ";

		}
		
	}
	cout << "level " << oper.level << " i pages " << oper.pages;
	wynik.close();

	*/

	char var = 0;
	int key;
	while (var != 'q') {
		cin >> var;
		//
		if (var == 'n')
		{
			
			cout << "Podaj wartoœæ klucza, a potem rekordy" << endl;
			cin >> key;


			for (int i = 0; i < oper.sizeOfNumbers; i++)
			{
				cin >> number;
				table[i] = number;
			}

			if (oper.keyExists(key) == true)
			{
				cout << "Klucz istnieje ju¿." << endl;;
				
			}
			else {
				oper.loadBlocks(oper.height, key, page);
				oper.addRecord(key, page, table, oper.height, 0);
				cout << "Dodano pomyslnie." << endl;
			}
		}
		if (var == 's')
		{
			oper.printPages(oper.height, oper.rootAddress,0);
			
		}
		if (var == 'd')
		{
			oper.printRecords(oper.height, oper.rootAddress, 0);
		}
		if (var == 'b')
		{
			cout << "Wpisz wartosc klucza szukanego";
			cin >> key;
			oper.printRecord(key);
		}
		if (var == 'x') {
			cout << "Zmiana ilosci liczb w zbiorze rekordu" << endl;
			cin >> number;
			if (number > 0) {
				int currentVar;
				int currentRest;
				oper.saveInfo(1, 1);
				oper.saveInfo(2, 1);
				oper.saveInfo(3, oper.level);
				oper.saveInfo(4, 1);
				oper.saveInfo(5, 1);
				oper.saveInfo(6, number);
				oper.saveInfo(7, 1);
				oper.loadInfo();
				int bytes = 8 * (2 * oper.level * 3 + 4);// 2*level*3+1+3
				char *update = new char[bytes];
				for (int i = 0; i < bytes; i++)
					update[i] = 48;
				cout << "Wpisz klucz i potem rekody" << endl;
				cin >> key;
				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[7 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[15 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[23 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				for (int i = 0; i < 1; i++)
				{
					currentVar = key;
					for (int j = 0; j < 8; j++)
					{
						currentRest = currentVar % 10;
						currentVar = currentVar / 10;
						update[31 + 8 * i - j] = currentRest + 48;
						if (currentVar == 0)
							break;
					}
				}


				for (int i = 0; i <1; i++)
				{
					currentVar = 1;
					for (int j = 0; j < 8; j++)
					{
						currentRest = currentVar % 10;
						currentVar = currentVar / 10;
						update[31 + (2 * oper.level * 8) + 8 * i - j] = currentRest + 48;
						if (currentVar == 0)
							break;
					}
				}




				// gotowa tablica do zamiany

				ofstream file("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btree.txt", ios::out | ios::in | ios::binary | ios::trunc);
				file.write(update, bytes);
				file.close();
				delete[]update;
				int * newUpdate = new int[oper.sizeOfNumbers];
				for (int i = 0; i < oper.sizeOfNumbers; i++) {
					cin >> newUpdate[i];
				}
				ofstream file2("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/records.txt", ios::out | ios::in | ios::binary | ios::trunc);
				file2.close();
				oper.saveRecord(1, newUpdate, oper.sizeOfNumbers);
				delete[]newUpdate;
				cout << "Zmieniono" << endl;
			}
			else
			{
				cout << "Nieprawidlowy format" << endl;
			}
		}
		if (var == 'c') {
			cout << "Zmiana stopnia" << endl;
			cin >> number;
			if (number > 0) {
				int currentVar;
				int currentRest;
				oper.saveInfo(1, 1);
				oper.saveInfo(2, 1);
				oper.saveInfo(3, number);
				oper.saveInfo(4, 1);
				oper.saveInfo(5, 1);
				oper.saveInfo(6, oper.sizeOfNumbers);
				oper.saveInfo(7, 1);
				oper.loadInfo();
				int bytes = 8 * (2 * oper.level * 3 + 4);// 2*level*3+1+3
				char *update = new char[bytes];
				for (int i = 0; i < bytes; i++)
					update[i] = 48;
				cout << "Wpisz klucz i potem rekody" << endl;
				cin >> key;
				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[7 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[15 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				currentVar = 1;

				for (int i = 0; i < 8; i++)
				{
					currentRest = currentVar % 10;
					currentVar = currentVar / 10;
					update[23 - i] = currentRest + 48;
					if (currentVar == 0)
						break;
				}

				for (int i = 0; i < 1; i++)
				{
					currentVar = key;
					for (int j = 0; j < 8; j++)
					{
						currentRest = currentVar % 10;
						currentVar = currentVar / 10;
						update[31 + 8 * i - j] = currentRest + 48;
						if (currentVar == 0)
							break;
					}
				}


				for (int i = 0; i < 1; i++)
				{
					currentVar = 1;
					for (int j = 0; j < 8; j++)
					{
						currentRest = currentVar % 10;
						currentVar = currentVar / 10;
						update[31 + (2 * oper.level * 8) + 8 * i - j] = currentRest + 48;
						if (currentVar == 0)
							break;
					}
				}




				// gotowa tablica do zamiany

				ofstream file("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/btree.txt", ios::out | ios::in | ios::binary | ios::trunc);
				file.write(update, bytes);
				file.close();
				delete[]update;
				int * newUpdate = new int[oper.sizeOfNumbers];
				for (int i = 0; i < oper.sizeOfNumbers; i++) {
					cin >> newUpdate[i];
				}
				ofstream file2("C:/Users/SYLWESTER/source/repos/SBD2/SBD2/records.txt", ios::out | ios::in | ios::binary | ios::trunc);
				file2.close();
				oper.saveRecord(1, newUpdate, oper.sizeOfNumbers);
				delete[]newUpdate;
				cout << "Zmieniono" << endl;
			}
			else
			{
				cout << "Nieprawidlowy format" << endl;
			}
		}
		if (var == 'r') {
			int random;
			int * tab = new int[oper.sizeOfNumbers];
			for (int i = 0; i < oper.sizeOfNumbers;i++) {
				tab[i] = 1;
			}

			cout << "Wpisz liczbe losowa";
			cin >> random;
			for (int i = 0; i < random;i++ )
			{
				c = rand() % 100000 + 1;
				if (oper.keyExists(c) == false) {
					oper.loadBlocks(oper.height, c, page);
					oper.addRecord(c, page, tab, oper.height, 0);
					oper.loadInfo();

				}

			}
			delete[]tab;

		}
		if (var == 'o') {
			cout << "Stopien: " << oper.level << endl;
			cout << "Wysokosc aktualna: " << oper.height << endl;
			cout << "Liczba kluczy: " << oper.address_dist << endl;
			cout << "Stron: " << oper.pages << endl;
			cout << "Ilosc liczb w zbiorze: " << oper.sizeOfNumbers << endl;
			x = (float)oper.address_dist;
			y = (2.0 * oper.level * oper.pages);
			cout << "Zajetosc: ";
			cout << (float)(x / y) << " ";

		}
	}
	

	delete page;
	delete[]table;

	return 0;
}