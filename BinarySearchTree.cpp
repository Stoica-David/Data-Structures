#include<iostream>
#include<fstream>
#include<queue>
struct Node
{
	int key;
	Node* left, * right, * parent;
	Node()
	{
		this->key = -1;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	Node(int key)
	{
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};
struct SearchTree
{
	Node* root;
	SearchTree()
	{
		this->root = nullptr;
	}
	void Insert(int key)
	{
		if (Find(key) != nullptr)
		{
			std::cout << "There already is a node with this key!\n";
			return;
		}
		if (this->root == nullptr)
		{
			root = new Node(key);
			return;
		}
		Node* current = root;
		while (current != nullptr)
		{
			if (current->key > key)
			{
				if (current->left != nullptr)
				{
					current = current->left;
				}
				else
				{
					current->left = new Node(key);
					current->left->parent = current;
					return;
				}
			}
			else
			{
				if (current->right != nullptr)
				{
					current = current->right;
				}
				else
				{
					current->right = new Node(key);
					current->right->parent = current;
					return;
				}
			}
		}
	}
	Node* Max(Node* x)
	{
		Node* current = x;
		while (current->right != nullptr)
		{
			current = current->right;
		}
		return current;
	}
	Node* Min(Node* x)
	{
		Node* current = x;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}
	Node* Successor(Node* x)
	{
		Node* current = x;
		if (x->right != nullptr)
		{
			current = Min(current->right);
		}
		else
		{
			current = x->parent;
			while (current != nullptr && x == current->right)
			{
				x = current;
				current = current->parent;
			}
		}
		return current;
	}
	Node* Predecessor(Node* x)
	{
		Node* current = x;
		if (x->left != nullptr)
		{
			current = Max(current->left);
		}
		else
		{
			current = x->parent;
			while (current != nullptr && x == current->left)
			{
				x = current;
				current = current->parent;
			}
		}
		return current;
	}
	Node* Find(int key)
	{
		Node* current = this->root;
		while (current != nullptr && current->key != key)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return current;
	}
	void Transplant(Node* erased, Node* successor)
	{
		if (erased->parent == nullptr)
		{
			this->root = successor;
		}
		else
		{
			if (erased == erased->parent->left)
			{
				erased->parent->left = successor;
			}
			else
			{
				erased->parent->right = successor;
			}
		}
		if (successor != nullptr)
		{
			successor->parent = erased->parent;
		}
	}
	void Delete(int key)
	{
		if (Find(key) == nullptr)
		{
			std::cout << "There is not a node to erase with the given key!\n";
			return;
		}
		else
		{
			Erase(Find(key));
		}
	}
	void Erase(Node* toErase)
	{
		if (toErase == nullptr)
		{
			std::cout << "There is not a node to erase!\n";
			return;
		}
		if (toErase->left == nullptr)
		{
			Transplant(toErase, toErase->right);
		}
		else
		{
			if (toErase->right == nullptr)
			{
				Transplant(toErase, toErase->left);
			}
			else
			{
				Node* successor = Successor(toErase);
				if (successor != toErase->right)
				{
					Transplant(successor, successor->right);
					successor->right = toErase->right;
					toErase->right->parent = successor;
				}
				Transplant(toErase, successor);
				successor->left = toErase->left;
				toErase->left->parent = successor;
			}
		}
		delete toErase;
	}
	void RSD(Node* node)
	{
		if (node != nullptr)
		{
			std::cout << node->key << " ";
			RSD(node->left);
			RSD(node->right);
		}
	}
	void SRD(Node* node)
	{
		if (node != nullptr)
		{
			SRD(node->left);
			std::cout << node->key << " ";
			SRD(node->right);
		}
	}
	void SDR(Node* node)
	{
		if (node != nullptr)
		{
			SDR(node->left);
			SDR(node->right);
			std::cout << node->key << " ";
		}
	}
	void LevelOrder()
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			std::cout << current->key << " ";
			nodesQueue.pop();
			if (current->left != nullptr)
				nodesQueue.push(current->left);
			if (current->right != nullptr)
				nodesQueue.push(current->right);
		}
		std::cout << std::endl;
	}
	void Print(int option)
	{
		if (this->root == nullptr)
		{
			std::cout << "The tree is empty!\n";
			return;
		}
		switch (option)
		{
		case 0:
		{
			std::cout << "RSD = ";
			RSD(this->root);
			break;
		}
		case 1:
		{
			std::cout << "SRD = ";
			SRD(this->root);
			break;
		}
		case 2:
		{
			std::cout << "SDR = ";
			SDR(this->root);
			break;
		}
		case 3:
		{
			std::cout << "Level order = ";
			LevelOrder();
			break;
		}
		default:
		{
			std::cout << "That is not a valid option!\n";
		}
		}
	}
	void Construct(const std::vector<int>& keysVector)
	{
		int index = 0;
		while (index < keysVector.size())
		{
			Insert(keysVector[index]);
			index++;
		}
	}
	bool Empty()
	{
		return this->root == nullptr;
	}
	void Clear()
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			if (current->left != nullptr)
				nodesQueue.push(current->left);
			if (current->right != nullptr)
				nodesQueue.push(current->right);
			delete current;
		}
	}
};
int main()
{
	SearchTree MyTree;
	int option = 1, nrOption = 1, key, deleteType, traversal, nrKeys;
	std::cout << "Options: (0) - Exit\n(1) - Insert\n(2) - Erase\n(3) - Print min\n(4) - Print max\n(5) - Print successor\n(6) - Print predecessor\n(7) - Print tree\n(8) - Search an element\n(9) - Construct\n\n";
	while (option)
	{
		if (nrOption % 5 == 0)
		{
			system("PAUSE");
			system("CLS");
			std::cout << "Options: (0) - Exit\n(1) - Insert\n(2) - Erase\n(3) - Print min\n(4) - Print max\n(5) - Print successor\n(6) - Print predecessor\n(7) - Print tree\n(8) - Search an element\n(9) - Construct\n\n";
		}
		std::cout << "Enter your option: ";
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
			MyTree.Insert(key);
			break;
		}
		case 2:
		{
			std::cout << "Delete options:\n(0) - Delete a key\n(1) - Erase a node\n\n";
			std::cout << "Enter your delete option: ";
			std::cin >> deleteType;
			std::cout << "Enter a key: ";
			std::cin >> key;
			if (deleteType == 0)
			{
				MyTree.Delete(key);
			}
			else if (deleteType == 1)
			{
				if (MyTree.Find(key) != nullptr)
				{
					MyTree.Erase(MyTree.Find(key));
				}
				else
				{
					std::cout << "There is not a node with the given key!\n";
				}
			}
			else
			{
				std::cout << "Delete option not valid!\n";
			}
			break;
		}
		case 3:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is empty!\n";
			}
			else
			{
				std::cout << "The min value is " << MyTree.Min(MyTree.root)->key << "!\n";
			}
			break;
		}
		case 4:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is empty!\n";
			}
			else
			{
				std::cout << "The max value is " << MyTree.Max(MyTree.root)->key << "!\n";
			}
			break;
		}
		case 5:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is empty!\n";
			}
			else if (MyTree.root->left == nullptr && MyTree.root->right == nullptr)
			{
				std::cout << "There is only one node in the tree!\n";
			}
			else
			{
				std::cout << "Enter a key: ";
				std::cin >> key;
				if (MyTree.Find(key) != nullptr)
				{
					if (MyTree.Find(key) != MyTree.Max(MyTree.root))
					{
						std::cout << "The successor of the given node is " << MyTree.Successor(MyTree.Find(key))->key << "!\n";
					}
					else
					{
						std::cout << "The given has no successor!\n";
					}
				}
				else
				{
					std::cout << "There is not a node with the given key!\n";
				}
			}
			break;
		}
		case 6:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is empty!\n";
			}
			else if (MyTree.root->left == nullptr && MyTree.root->right == nullptr)
			{
				std::cout << "There is only one node in the tree!\n";
			}
			else
			{
				std::cout << "Enter a key: ";
				std::cin >> key;
				if (MyTree.Find(key) != nullptr)
				{
					if (MyTree.Find(key) != MyTree.Min(MyTree.root))
					{
						std::cout << "The predecessor of the given node is " << MyTree.Predecessor(MyTree.Find(key))->key << "!\n";
					}
					else
					{
						std::cout << "The given node has no predecessor!\n";
					}
				}
				else
				{
					std::cout << "There is not a node with the given key!\n";
				}
			}
			break;
		}
		case 7:
		{
			std::cout << "\Traversal numbers:\n(0) - RSD\n(1) - SRD\n(2) - SDR\n(3) - Level Order\n\n";
			std::cout << "Enter a traversal number: ";
			std::cin >> traversal;
			MyTree.Print(traversal);
			std::cout << std::endl;
			break;
		}
		case 8:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			if (MyTree.Find(key) == nullptr)
			{
				std::cout << "There is not a node with the given key!\n";
			}
			else
			{
				std::cout << "There is a node with the given key!\n";
			}
			break;
		}
		case 9:
		{
			std::cout << "Enter the nr of keys: ";
			std::cin >> nrKeys;
			std::vector<int> keysVector;
			std::cout << "Enter the vector of keys: ";
			for (int index = 0; index < nrKeys; index++)
			{
				std::cin >> key;
				keysVector.push_back(key);
			}
			MyTree.Construct(keysVector);
			break;
		}
		default:
		{
			std::cout << "Enter a valid option!\n";
			option = 1;
		}
		}
		nrOption++;
	}
	return 0;
}