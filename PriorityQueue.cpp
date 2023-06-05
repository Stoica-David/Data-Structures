#include<iostream>
#include<vector>
struct PriorityQueue
{
	std::vector<int> data;
	void insert(int key)
	{
		data.push_back(0);
		increaseKey(data.size() - 1, key);
	}
	void extractMax()
	{
		if (data.size() == 0)
		{
			return;
		}
		data[0] = data[data.size() - 1];
		data.pop_back();
		maxHeapfy(0);
	}
	int maxElement()
	{
		if (data.size() == 0)
			return -1;
		return data[0];
	}
	void increaseKey(int index, int value)
	{
		if (value > data[index])
		{
			data[index] = value;
			int p = (index - 1) / 2;
			while (index > 0 && data[p] < value)
			{
				data[index] = data[p];
				index = p;
				p = (index - 1) / 2;
			}
			data[index] = value;
		}
	}
	void maxHeapfy(int index)
	{
		int left = (2 * index) + 1;
		int right = (2 * index) + 2;
		int maxIndex = index;
		if (left < data.size() && data[left] > data[maxIndex])
		{
			maxIndex = left;
		}
		if (right < data.size() && data[right] > data[maxIndex])
		{
			maxIndex = right;
		}
		if (maxIndex != index)
		{
			std::swap(data[index], data[maxIndex]);
			maxHeapfy(maxIndex);
		}
	}
	void buildMaxHeap()
	{
		for (int index = (data.size() / 2) - 1; index >= 0; index--)
		{
			maxHeapfy(index);
		}
	}
	void print()
	{
		for (int element : data)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
};
int main()
{
	PriorityQueue myQueue; int option = 0, nrOption = 1, key;
	std::cout << "Options: (0) - Exit\n(1) - Insert a key\n(2) - Extract max key\n(3) - Print max key\n(4) - Print\n(5) - Build max heap\n";
	do
	{
		if (nrOption % 5 == 0)
		{
			system("PAUSE");
			system("CLS");
			std::cout << "Options: (0) - Exit\n(1) - Insert a key\n(2) - Extract max key\n(3) - Print max key\n(4) - Print\n\n";
		}
		std::cout << "Enter an option: ";
		std::cin >> option;
		switch (option)
		{
		case 0:
		{
			std::cout << "Bye!\n";
			break;
		}
		case 1:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			myQueue.insert(key);
			break;
		}
		case 2:
		{
			myQueue.extractMax();
			break;
		}
		case 3:
		{
			int maxElement = myQueue.maxElement();
			if (maxElement == -1)
				std::cout << "The queue is empty!\n";
			else
				std::cout << "The max key is " << myQueue.maxElement() << " !\n";
			break;
		}
		case 4:
		{
			std::cout << "The queue = ";
			myQueue.print();
			break;
		}
		case 5:
		{
			myQueue.buildMaxHeap();
			break;
		}
		default:
		{
			std::cout << "Enter a valid option!\n";
			option = 1;
			break;
		}
		}
	} while (option);
	return 0;
}