#include<iostream>
#include<unordered_map>
unsigned int SortTriple(unsigned int first, unsigned int second, unsigned int third)
{
	unsigned int number = 0;
	if (first > second)
		std::swap(first, second);
	if (first > third)
		std::swap(first, third);
	if (second > third)
		std::swap(second, third);
	number = first * 100 + second * 10 + third;
	return number;
}
void NrThrows(std::unordered_map<unsigned int, unsigned int>& triplesMap)
{
	unsigned int nrThrows, first, second, third, sortedTriple;
	std::cin >> nrThrows;
	for (int i = 0; i < nrThrows; i++)
	{
		std::cin >> first >> second >> third;
		sortedTriple = SortTriple(first, second, third);
		triplesMap[sortedTriple]++;
	}
	for (std::pair<unsigned int, unsigned int> currentTriple : triplesMap)
	{
		if (currentTriple.second == 1)
		{
			std::cout << "The triple {" << currentTriple.first / 100 % 10 << ", " << currentTriple.first / 10 % 10 << ", " << currentTriple.first % 10 << "} has been thrown " << currentTriple.second << " time!\n";
		}
		else
		{
			std::cout << "The triple {" << currentTriple.first / 100 % 10 << ", " << currentTriple.first / 10 % 10 << ", " << currentTriple.first % 10 << "} has been thrown " << currentTriple.second << " times!\n";
		}
	}
	std::cout << std::endl;
}
int main()
{
	std::unordered_map<unsigned int, unsigned int> triplesMap;
	NrThrows(triplesMap);
	return 0;
}