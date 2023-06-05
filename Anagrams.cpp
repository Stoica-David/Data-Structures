#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include<unordered_map>
#include<unordered_set>
std::string SortWord(const std::string& word)
{
	std::array<unsigned int, 26> characters = {};
	for (char character : word)
	{
		characters[(int)(character)-'a'] ++;
	}
	std::string sortedWord;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < characters[i]; j++)
		{
			sortedWord.push_back('a' + i);
		}
	}
	return sortedWord;
}
void Output(std::unordered_map<std::string, std::unordered_set<std::string>>& wordsMap)
{
	std::ifstream inputFile("Intrare.in");
	std::string word, sortedWord;
	while (!inputFile.eof())
	{
		inputFile >> word;
		sortedWord = SortWord(word);
		wordsMap[sortedWord].insert(word);
	}
	for (std::pair<std::string, std::unordered_set<std::string>> currentGroup : wordsMap)
	{
		std::cout << "{ ";
		for (std::string currentWord : currentGroup.second)
		{
			std::cout << currentWord << " ";
		}
		std::cout << "}\n";
	}
	inputFile.close();
}
int main()
{
	std::unordered_map<std::string, std::unordered_set<std::string>> wordsMap;
	Output(wordsMap);
	return 0;
}