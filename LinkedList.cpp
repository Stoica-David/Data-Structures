#include<iostream>
#include<stdlib.h>
struct node
{
	int info;
	node* prev = nullptr, * next = nullptr;
};

struct List
{
	node* head = nullptr, * tail = nullptr;
	int nrOfElements = 0;
	void push_front(int key)
	{
		node* newNode = new node;
		newNode->info = key;
		newNode->next = this->head;
		if (this->head != nullptr)
		{
			this->head->prev = newNode;
		}
		else
		{
			this->tail = newNode;
		}
		this->head = newNode;
		nrOfElements++;
	}
	void push_back(int key)
	{
		node* newNode = new node;
		newNode->info = key;
		newNode->prev = this->tail;
		if (this->tail != nullptr)
		{
			this->tail->next = newNode;
		}
		else
		{
			this->head = newNode;
		}
		this->tail = newNode;
		nrOfElements++;
	}
	void pop_front()
	{
		if (nrOfElements == 0)
		{
			std::cout << "The list is already empty!\n";
			return;
		}
		node* aux = this->head;
		this->head = this->head->next;
		if (this->head != nullptr)
		{
			this->head->prev = nullptr;
		}
		delete aux;
		nrOfElements--;
	}
	void pop_back()
	{
		if (nrOfElements == 0)
		{
			std::cout << "The list is already empty!\n";
			return;
		}
		node* aux = this->tail;
		this->tail = this->tail->prev;
		if (this->tail != nullptr)
		{
			this->tail->next = nullptr;
		}
		delete aux;
		nrOfElements--;
	}
	node* find(int key)
	{
		if (nrOfElements == 0)
		{
			return nullptr;
		}
		node* current = this->head;
		while (current != nullptr && current->info != key)
		{
			current = current->next;
		}
		return current;
	}
	void erase(node* Node)
	{
		if (Node->prev != nullptr)
		{
			Node->prev->next = Node->next;
		}
		else
		{
			this->head = Node->next;
		}
		if (Node->next != nullptr)
		{
			Node->next->prev = Node->prev;
		}
		else
		{
			this->tail = Node->prev;
		}
		nrOfElements--;
		delete Node;
	}
	void remove(int key)
	{
		if (nrOfElements == 0)
		{
			std::cout << "The list is already empty!\n";
			return;
		}
		while (this->head != nullptr && this->head->info == key)
		{
			node* aux = this->head;
			this->head = this->head->next;
			delete aux;
			nrOfElements--;
		}
		if (this->head == nullptr)
			return;
		node* current = this->head;
		while (current->next != nullptr)
		{
			if (current->next->info == key)
			{
				node* Node = current->next;
				current->next = current->next->next;
				delete Node;
				nrOfElements--;
			}
			else
			{
				current = current->next;
			}
		}
	}
	void insert(node* Node, int key)
	{
		if (Node == nullptr)
		{
			std::cout << "There is no such value in the list!\n";
			return;
		}
		if (Node == this->head)
		{
			push_front(key);
			return;
		}
		node* newNode = new node;
		newNode->info = key;
		Node->prev->next = newNode;
		newNode->next = Node;
		newNode->prev = Node->prev;
		Node->prev = newNode;
		nrOfElements++;
	}
	bool empty()
	{
		return this->head == nullptr;
	}
	void clear()
	{
		if (nrOfElements == 0)
		{
			return;
		}
		node* current = this->head;
		while (current != nullptr)
		{
			this->head = this->head->next;
			if (this->head != nullptr)
			{
				this->head->prev = nullptr;
			}
			delete current;
			current = this->head;
			nrOfElements--;
		}
	}
	void print()
	{
		node* current = this->head;
		std::cout << "L = ";
		if (current == nullptr)
		{
			std::cout << "Nil\n";
			return;
		}
		while (current != nullptr)
		{
			std::cout << current->info << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
	int size()
	{
		return this->nrOfElements;
	}
};
bool palindrom(List L)
{
	if (L.nrOfElements == 0)
	{
		return 0;
	}
	int tmp = L.nrOfElements / 2;
	node* front = L.head; node* back = L.tail;
	while (tmp)
	{
		if (front->info != back->info)
			return 0;
		front = front->next;
		back = back->prev;
		tmp--;
	}
	return 1;
}
int compare(List& L1, List& L2)
{
	node* L1_current = L1.head; node* L2_current = L2.head;
	if (L1.head == nullptr || L2.head == nullptr)
		return 0;
	if (L1.nrOfElements != L2.nrOfElements)
		return 0;
	while (L1_current != nullptr && L2_current != nullptr)
	{
		if (L1_current->info != L2_current->info)
			return 0;
		L1_current = L1_current->next;
		L2_current = L2_current->next;
	}
	return 1;
}
int main()
{
	List L; int option = 1, key, optionNumber = 0;
	std::cout << "Options:\n" << "(0) - exit\n(1) - push_front\n(2) - push_back\n(3) - pop_front\n(4) - pop back\n(5) - find\n(6) - erase\n(7) - remove\n(8) - insert\n(9) - empty\n(10) - clear\n(11) - print\n(12) - size\n(13) - palindrom\n(14) - compare\n\n";
	while (option)
	{
		if (optionNumber == 5)
		{
			optionNumber = 0;
			system("PAUSE");
			system("CLS");
			std::cout << "Options:\n" << "(0) - exit\n(1) - push_front\n(2) - push_back\n(3) - pop_front\n(4) - pop back\n(5) - find\n(6) - erase\n(7) - remove\n(8) - insert\n(9) - empty\n(10) - clear\n(11) - print\n(12) - size\n(13) - palindrom\n(14) - compare\n\n";
		}
		std::cout << "Enter your option: ";
		std::cin >> option;
		switch (option)
		{
		case 0:
		{
			std::cout << "Thanks for using our menu!\n";
			break;
		}
		case 1:
		{
			std::cout << "Enter a value: ";
			std::cin >> key;
			L.push_front(key);
			break;
		}
		case 2:
		{
			std::cout << "Enter a value: ";
			std::cin >> key;
			L.push_back(key);
			break;
		}
		case 3:
		{
			L.pop_front();
			break;
		}
		case 4:
		{
			L.pop_back();
			break;
		}
		case 5:
		{
			std::cout << "Enter a value: ";
			std::cin >> key;
			node* Node = L.find(key);
			if (Node != nullptr)
			{
				std::cout << "The list contains this value!\n";
			}
			else if (L.nrOfElements != 0)
			{
				std::cout << "The list doesn't contain this value!\n";
			}
			else
			{
				std::cout << "The list is empty!\n";
			}
			break;
		}
		case 6:
		{
			std::cout << "Enter a value: ";
			std::cin >> key;
			if (L.find(key) != nullptr)
				L.erase(L.find(key));
			break;
		}
		case 7:
		{
			std::cout << "Enter a value: ";
			std::cin >> key;
			L.remove(key);
			break;
		}
		case 8:
		{
			int secondKey;
			std::cout << "Enter a value: ";
			std::cin >> key;
			std::cout << "Enter the value that should be after the new value after insertion: ";
			std::cin >> secondKey;
			L.insert(L.find(secondKey), key);
			break;
		}
		case 9:
		{
			if (L.empty())
			{
				std::cout << "The list is empty!\n";
			}
			else
			{
				std::cout << "The list is not empty!\n";
			}
			break;
		}
		case 10:
		{
			if (L.nrOfElements == 0)
				std::cout << "The list is already empty!\n";
			L.clear();
			break;
		}
		case 11:
		{
			L.print();
			break;
		}
		case 12:
		{
			std::cout << "The size of the list is " << L.size() << "!\n";
			break;
		}
		case 13:
		{
			if (palindrom(L) != 0)
			{
				std::cout << "The given list is a palindrom!\n";
			}
			else
			{
				std::cout << "The given list is not a palindrom!\n";
			}
			break;
		}
		case 14:
		{
			List L2; int nrOfNodes;
			std::cout << "Give the number of nodes of the second list: ";
			std::cin >> nrOfNodes;
			std::cout << "Enter the values from the list: ";
			for (int i = 0; i < nrOfNodes; i++)
			{
				std::cin >> key;
				L2.push_back(key);
			}
			if (compare(L, L2))
			{
				std::cout << "The two lists are identical!\n";
			}
			else
			{
				std::cout << "The two lists are not identical!\n";
			}
			L2.clear();
			break;
		}
		default:
		{
			std::cout << "This option is not valid, enter a new one!\n";
			option = 1;
			break;
		}
		}
		optionNumber++;
	}
	L.clear();
	return 0;
}