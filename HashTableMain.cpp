#include<iostream>
#include<fstream>
#include "HashTable.h"
int main()
{
	std::ifstream inputFile("Intrare.in");
	unsigned int nrElements; int key, value;
	HashTable myHashTable;
	inputFile >> nrElements;
	for (int index = 0; index < nrElements; index++)
	{
		inputFile >> key >> value;
		myHashTable.insert({ key, value });
	}
	unsigned int option, optionNumber = 0;
	std::cout << "Options:\n(0) - exit\n(1) - insert\n(2) - erase\n(3) - find\n(4) - print table\n\n";
	do
	{
		if (optionNumber != 0 && optionNumber % 5 == 0)
		{
			system("PAUSE");
			system("CLS");
			std::cout << "Options:\n(0) - exit\n(1) - insert\n(2) - erase\n(3) - find\n(4) - print table\n\n";
		}
		std::cout << "Enter your option: ";
		std::cin >> option;
		switch (option)
		{
		case 0:
		{
			std::cout << "Thanks for using our menu!\n";
			break;
		}
		case 1:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			std::cout << "Enter a value: ";
			std::cin >> value;
			myHashTable.insert({ key, value });
			break;
		}
		case 2:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			myHashTable.erase(key);
			break;
		}
		case 3:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			if (myHashTable.find(key) != myHashTable.end())
			{
				std::cout << "The element with they key " << key << " is stored in the table!\n";
			}
			else
			{
				std::cout << "The element with they key " << key << " is not stored in the table!\n";
			}
			break;
		}
		case 4:
		{
			myHashTable.print();
			break;
		}
		default:
		{
			std::cout << "The option is not valid! Choose another option!\n";
			option = 1;
			break;
		}
		}
	} while (option != 0);
	inputFile.close();
	return 0;
}