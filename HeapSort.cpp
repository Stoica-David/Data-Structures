#include<iostream>
#include<fstream>
#include<vector>
void ReadInput(std::vector<int>& vector, std::ifstream& inputFile)
{
	int nrElements, element;
	inputFile >> nrElements;
	for (int index = 0; index < nrElements; index++)
	{
		inputFile >> element;
		vector.push_back(element);
	}
}
void MaxHeap(std::vector<int>& heap, int index, int size)
{
	int left = (2 * index) + 1;
	int right = (2 * index) + 2;
	int maxIndex = index;
	if (left < size && heap[left] > heap[maxIndex])
	{
		maxIndex = left;
	}
	if (right < size && heap[right] > heap[maxIndex])
	{
		maxIndex = right;
	}
	if (maxIndex != index)
	{
		std::swap(heap[index], heap[maxIndex]);
		MaxHeap(heap, maxIndex, size);
	}
}
void BuildMaxHeap(std::vector<int>& heap)
{
	for (int index = (heap.size() / 2) - 1; index >= 0; index--)
	{
		MaxHeap(heap, index, heap.size());
	}
}
void HeapSort(std::vector<int>& vector)
{
	BuildMaxHeap(vector);
	int size = vector.size();
	for (int index = vector.size() - 1; index >= 1; index--)
	{
		std::swap(vector[index], vector[0]);
		size--;
		MaxHeap(vector, 0, size);
	}
}
int main()
{
	std::vector<int> vector; std::ifstream inputFile("Input.in");
	ReadInput(vector, inputFile);
	HeapSort(vector);
	std::cout << "Sorted vector = ";
	for (int index = 0; index < vector.size(); index++)
	{
		std::cout << vector[index] << " ";
	}
	inputFile.close();
	return 0;
}