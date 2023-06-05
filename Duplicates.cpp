#include<iostream>
#include<fstream>
#include<unordered_set>
#include<unordered_map>
void ReadNumbers(std::vector<float>& numbers, unsigned int& distance)
{
	std::ifstream inputFile("Intrare.in");
	inputFile >> distance;
	float element;
	while (inputFile >> element)
	{
		numbers.push_back(element);
	}
	inputFile.close();
}
void Duplicates(const std::vector<float>& numbers, unsigned int distance)
{
	std::unordered_set<float> alreadyUsed;
	std::unordered_map<float, int> lastIndex;
	unsigned int currentPosition = 1; bool duplicateExists = false;
	std::cout << "Elements that are close duplicates in the vector: ";
	for (float element : numbers)
	{
		if (lastIndex[element] > 0 && currentPosition - lastIndex[element] <= distance && alreadyUsed.find(element) == alreadyUsed.end())
		{
			std::cout << element << " ";
			alreadyUsed.insert(element);
			duplicateExists = true;
		}
		else
		{
			lastIndex[element] = currentPosition;
		}
		currentPosition++;
	}
	std::cout << std::endl;
	if (!duplicateExists)
		std::cout << "There are no numbers that are close duplicates in the vector!\n";
}
int main()
{
	std::vector<float> numbers; unsigned int distance;
	ReadNumbers(numbers, distance);
	Duplicates(numbers, distance);
	return 0;
}