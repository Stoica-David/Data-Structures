#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
void ReadInput(std::string& text, std::ifstream& inputFile)
{
	std::map<std::string, int> wordsMap;
	while (!inputFile.eof())
	{
		inputFile >> text;
		int index = text.size() - 1;
		while (index < text.size() && !isalnum(text[index]))
		{
			text.pop_back();
			index--;
		}
		if (isupper(text[0]))
			text[0] = tolower(text[0]);
		wordsMap[text] ++;
	}
	for (std::pair<std::string, int> currentWord : wordsMap)
	{
		std::cout << currentWord.first << "(" << currentWord.second << ")\n";
	}
}
int main()
{
	std::string text;
	std::ifstream inputFile("Input.in");
	ReadInput(text, inputFile);
	inputFile.close();
	return 0;
}