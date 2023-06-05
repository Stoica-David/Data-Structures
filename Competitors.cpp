#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
struct hashPair
{
	int operator() (std::pair<std::string, std::string> pair) const
	{
		return std::hash<std::string>() (pair.first);
	}
};
void ReadParticipants(std::unordered_map<std::pair<std::string, std::string>, int, hashPair>& map)
{
	std::string firstName, lastName;
	std::ifstream inputFile("Intrare.in");
	int nrContests, nrParticipants;
	inputFile >> nrContests;
	while (nrContests)
	{
		while (inputFile >> firstName >> lastName)
		{
			map[{firstName, lastName}]++;
		}
		nrContests--;
	}
	inputFile.close();
}
int main()
{
	std::unordered_map<std::pair<std::string, std::string>, int, hashPair> map;
	ReadParticipants(map);
	std::cout << "The participants that attended multiple events are:\n";
	for (std::pair<std::pair<std::string, std::string>, int> pair : map)
	{
		if (pair.second > 1)
			std::cout << pair.first.first << " " << pair.first.second << "(" << pair.second << ")" << "\n";
	}
	return 0;
}