#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
void ReadInput(std::set<int>& ascending, std::set<int>& descending, std::ifstream& inputFile, int& nrOperations)
{
	int nrElements, current, previous; bool foundMax = false;
	inputFile >> nrElements;
	inputFile >> previous;
	ascending.insert(previous);
	while (--nrElements)
	{
		inputFile >> current;
		if (previous < current)
			ascending.insert(current);
		if (previous >= current)
			descending.insert(current);
		previous = current;
	}
	inputFile >> nrOperations;
}
bool Insert(std::set<int>& ascending, std::set<int>& descending, int element)
{
	if ((ascending.find(element) == ascending.end()) && (descending.find(element) == descending.end()))
	{
		ascending.insert(element);
		return true;
	}
	else if ((ascending.find(element) != ascending.end()) && (descending.find(element) == descending.end()))
	{
		descending.insert(element);
		return true;
	}
	else
	{
		return false;
	}
}
void PrintBSequence(const std::set<int>& ascending, const std::set<int>& descending)
{
	for (int current : ascending)
	{
		std::cout << current << " ";
	}
	for (int current : descending)
	{
		std::cout << current << " ";
	}
	std::cout << std::endl;
}
void KOperations(std::set<int>& ascending, std::set<int>& descending, int nrOperations)
{
	int element;
	std::cout << "Initial sequence: ";
	PrintBSequence(ascending, descending);
	while (nrOperations)
	{
		std::cout << "\nEnter an element: ";
		std::cin >> element;
		bool inserted = Insert(ascending, descending, element);
		if (inserted)
		{
			std::cout << "The element was inserted!\n";
			std::cout << "New sequence: ";
			PrintBSequence(ascending, descending);
		}
		else
		{
			std::cout << "The element could not be inserted!\n";
		}
		nrOperations--;
	}
}
int main()
{
	std::ifstream inputFile("Input.in"); std::set<int> ascending, descending; int nrOperations;
	ReadInput(ascending, descending, inputFile, nrOperations);
	KOperations(ascending, descending, nrOperations);
	return 0;
}