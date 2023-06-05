#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
void BucketSort(std::vector<float>& myVector)
{
	std::ifstream inputFile("Intrare.in"); float element; int nrOfElements;
	inputFile >> nrOfElements;
	for (int index = 0; index < nrOfElements; index++)
	{
		inputFile >> element;
		myVector.push_back(element);
	}
	std::vector<std::list<float>> buckets(nrOfElements); std::list<int> currentBucket; int currentIndex = 0;
	for (float number : myVector)
	{
		buckets[floor(number * 10)].push_front(number);
	}
	myVector.clear();
	for (std::list<float> list : buckets)
	{
		list.sort();
		for (float number : list)
		{
			if (number != 1)
				myVector.push_back(number);
		}
	}
	inputFile.close();
}
int main()
{
	std::vector<float> myVector;
	BucketSort(myVector);
	for (float element : myVector)
	{
		std::cout << element << " ";
	}
	return 0;
}