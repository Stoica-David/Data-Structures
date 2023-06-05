#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<queue>
void ReadVectors(std::vector<std::vector<int>>& vectors, std::ifstream& inputFile)
{
	int nrVectors, vectorSize, element; std::vector<int> currentVector;
	inputFile >> nrVectors;
	while (nrVectors)
	{
		inputFile >> vectorSize;
		while (vectorSize)
		{
			inputFile >> element;
			currentVector.push_back(element);
			vectorSize--;
		}
		vectors.push_back(currentVector);
		currentVector.clear();
		nrVectors--;
	}
}
struct compStruct
{
	bool operator()(const std::tuple<int, int, int>& tuple1, const std::tuple<int, int, int>& tuple2)
	{
		return std::get<0>(tuple1) > std::get<0>(tuple2);
	}
};
std::vector<int> MergeVectors(const std::vector<std::vector<int>>& vectors)
{
	std::vector<int> sortedVector;
	std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, compStruct> numbersQueue;
	for (int vectorIndex = 0; vectorIndex < vectors.size(); vectorIndex++)
	{
		numbersQueue.push({ vectors[vectorIndex][0], vectorIndex, 0 });
	}
	while (!numbersQueue.empty())
	{
		std::tuple<int, int, int> current = numbersQueue.top();
		sortedVector.push_back(std::get<0>(current));
		numbersQueue.pop();
		if (vectors[std::get<1>(current)].size() > std::get<2>(current) + 1)
		{
			numbersQueue.push({ vectors[std::get<1>(current)][std::get<2>(current) + 1], std::get<1>(current), std::get<2>(current) + 1 });
		}
	}
	return sortedVector;
}
int main()
{
	std::vector<std::vector<int>> vectors; std::ifstream inputFile("Input.in"); std::vector<int> sortedVector;
	ReadVectors(vectors, inputFile);
	sortedVector = MergeVectors(vectors);
	std::cout << "Final vector: ";
	for (int current : sortedVector)
	{
		std::cout << current << " ";
	}
	std::cout << std::endl;
	inputFile.close();
	return 0;
}