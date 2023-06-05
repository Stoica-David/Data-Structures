#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<limits.h>
struct hashPair
{
	int operator() (std::pair<int, int> pair) const
	{
		return std::hash<int>() (pair.first);
	}
};
void MinMaxSquare(std::unordered_map<std::pair<int, int>, int, hashPair>& squares, bool maxSquare)
{
	std::ifstream inputFile("Intrare.in");
	int nrSquares, x, y, l;
	inputFile >> nrSquares;
	for (int i = 0; i < nrSquares; i++)
	{
		inputFile >> x >> y >> l;
		if (maxSquare == true && (squares[{x, y}] == 0 || squares[{x, y}] < l))
			squares[{x, y}] = l;
		if (maxSquare == false && (squares[{x, y}] == 0 || squares[{x, y}] > l))
			squares[{x, y}] = l;
	}
	std::pair<int, int> center;
	inputFile >> center.first >> center.second;
	std::cout << "The given point is (" << center.first << ", " << center.second << ")\n\n";
	if (maxSquare == true)
	{
		if (squares.find(center) != squares.end())
		{
			std::cout << "The max square centered in the given point has the length of " << squares.find(center)->second;
		}
		else
		{
			std::cout << "There is no square centered in the given point!\n";
		}
	}
	else
	{
		if (squares.find(center) != squares.end())
		{
			std::cout << "The min square centered in the given point has the length of " << squares.find(center)->second;
		}
		else
		{
			std::cout << "There is no square centered in the given point!\n";
		}
	}
	inputFile.close();
}
int main()
{
	std::unordered_map<std::pair<int, int>, int, hashPair> squares; bool maxSquare = true; std::string choice;
	std::cout << "Choose max or min: ";
	std::cin >> choice;
	if (choice == "max")
		maxSquare = true;
	else
		maxSquare = false;
	MinMaxSquare(squares, maxSquare);
	return 0;
}