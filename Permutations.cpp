#include<iostream>
#include<fstream>
#include<unordered_set>
#include<string>
void ReadStrings(std::string& firstString, std::string& secondString)
{
	std::ifstream inputFile("Intrare.in");
	inputFile >> firstString >> secondString;
	inputFile.close();
}
bool Verify(std::string firstString, std::string& secondString)
{
	if (firstString.size() != secondString.size())
		return false;
	std::unordered_set<char> charSet;
	for (char character : firstString)
	{
		charSet.insert(character);
	}
	for (char character : secondString)
	{
		if (charSet.find(character) == charSet.end())
			return false;
		charSet.erase(character);
	}
	if (!charSet.empty())
		return false;
	return true;
}
int main()
{
	std::string firstString, secondString;
	ReadStrings(firstString, secondString);
	if (Verify(firstString, secondString))
	{
		std::cout << "The second string is a permutation of the first one!\n";
	}
	else
	{
		std::cout << "The second string is not a permutation of the first one!\n";
	}
	return 0;
}