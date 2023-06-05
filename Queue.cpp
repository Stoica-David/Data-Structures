#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
struct node
{
	std::string info;
	node* next;
};
struct Queue
{
	node* head = nullptr, * tail = nullptr;
	int nrElem = 0;
	void push(std::string elem)
	{
		node* newNode = new node;
		newNode->info = elem;
		newNode->next = nullptr;
		if (this->tail != nullptr)
		{
			this->tail->next = newNode;
		}
		else
		{
			this->head = newNode;
		}
		this->tail = newNode;
		nrElem++;
	}
	void pop()
	{
		if (nrElem == 0)
		{
			std::cout << "The queue is already empty!\n";
			return;
		}
		node* aux = this->head;
		this->head = this->head->next;
		if (this->head == nullptr)
			this->tail = nullptr;
		delete aux;
		nrElem--;
	}
	std::string front()
	{
		if (this->head == nullptr)
		{
			std::cout << "The queue is empty!\n";
			return "\0";
		}
		return this->head->info;
	}
	std::string back()
	{
		if (this->tail == nullptr)
		{
			std::cout << "The queue is empty!\n";
			return "\0";
		}
		return this->tail->info;
	}
	bool empty()
	{
		return nrElem == 0;
	}
	void clear()
	{
		if (nrElem == 0)
		{
			std::cout << "The queue is already empty!\n";
			return;
		}
		node* current = this->head;
		while (current != nullptr)
		{
			this->head = this->head->next;
			delete current;
			current = this->head;
			nrElem--;
		}
		this->tail = nullptr;
	}
	int size()
	{
		return nrElem;
	}
};
void ListCreation(Queue& candidates, std::ifstream& inputFile, int& duration, int& nrCandidates)
{
	std::string name;
	inputFile >> duration >> nrCandidates;
	for (int index = 0; index < nrCandidates; index++)
	{
		inputFile >> name;
		candidates.push(name);
	}
	duration *= 60; int candidateDuration = 0;
	std::ofstream outputFile("Iesire.out");
	while (duration != 0)
	{
		if (candidates.empty())
		{
			outputFile << "The list for the second day is empty!\n";
			break;
		}
		srand(time(NULL));
		candidateDuration = rand() % 11;
		candidateDuration += 5;
		candidates.pop();
		duration -= candidateDuration;
	}
	outputFile << "List for the second day:\n";
	while (!candidates.empty())
	{
		outputFile << candidates.front() << "\n";
		candidates.pop();
	}
	inputFile.close();
	outputFile.close();
}
int main()
{
	int option = 1; std::string key; Queue candidates; std::ifstream inputFile("Intrare.in"); int duration, nrCandidates;
	ListCreation(candidates, inputFile, duration, nrCandidates);
	return 0;
}