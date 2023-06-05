#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<stack>
class Node
{
public:
	int value;
	Node* left, * right, * parent;
	Node()
	{
		this->value = -1;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	Node(int value)
	{
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};
class BTree
{
public:
	Node* root;
	BTree()
	{
		this->root = nullptr;
	}
	~BTree()
	{
		delete this->root;
	}
	Node* find(Node* node, int key)
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			if (current->value == key)
			{
				return current;
			}
			nodesQueue.pop();
			if (current->left != nullptr)
				nodesQueue.push(current->left);
			if (current->right != nullptr)
				nodesQueue.push(current->right);
		}
		return nullptr;
	}
	int Height(Node* node)
	{
		if (node == nullptr)
			return 0;
		int leftTree = 0, rightTree = 0;
		if (node->left != nullptr)
			leftTree = Height(node->left);
		if (node->right != nullptr)
			rightTree = Height(node->right);
		return 1 + std::max(leftTree, rightTree);
	}
	void RSD(Node* node)
	{
		if (node != nullptr)
		{
			std::cout << node->value << " ";
			RSD(node->left);
			RSD(node->right);
		}
	}
	void SRD(Node* node)
	{
		if (node != nullptr)
		{
			SRD(node->left);
			std::cout << node->value << " ";
			SRD(node->right);
		}
	}
	void SDR(Node* node)
	{
		if (node != nullptr)
		{
			SDR(node->left);
			SDR(node->right);
			std::cout << node->value << " ";
		}
	}
	void LevelOrder()
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			std::cout << current->value << " ";
			nodesQueue.pop();
			if (current->left != nullptr)
				nodesQueue.push(current->left);
			if (current->right != nullptr)
				nodesQueue.push(current->right);
		}
		std::cout << std::endl;
	}
	void PrintLeafs()
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			if (current->left == nullptr && current->right == nullptr)
			{
				std::cout << current->value << " ";
			}
			nodesQueue.pop();
			if (current->left != nullptr)
				nodesQueue.push(current->left);
			if (current->right != nullptr)
				nodesQueue.push(current->right);
		}
		std::cout << std::endl;
	}
	bool IsEqualTo(const BTree& newTree)
	{
		std::queue<Node*>nodesQueue1, nodesQueue2;
		nodesQueue1.push(this->root);
		nodesQueue2.push(newTree.root);
		while (!nodesQueue1.empty() || !nodesQueue2.empty())
		{
			Node* current1 = nodesQueue1.front();
			Node* current2 = nodesQueue2.front();
			if (current1->value != current2->value)
				return false;
			nodesQueue1.pop();
			nodesQueue2.pop();
			if (current1->left != nullptr)
				nodesQueue1.push(current1->left);
			if (current1->right != nullptr)
				nodesQueue1.push(current1->right);
			if (current2->left != nullptr)
				nodesQueue2.push(current2->left);
			if (current2->right != nullptr)
				nodesQueue2.push(current2->right);
		}
		return nodesQueue1.empty() && nodesQueue2.empty();
	}
	bool IsComplete()
	{
		std::queue<Node*> nodesQueue;
		nodesQueue.push(this->root);
		bool hole = false;
		while (!nodesQueue.empty())
		{
			Node* current = nodesQueue.front();
			if (current->left == nullptr || current->right == nullptr)
				hole = true;
			nodesQueue.pop();
			if (current->left != nullptr)
			{
				if (hole == true)
					return false;
				nodesQueue.push(current->left);
			}
			if (current->right != nullptr)
			{
				if (hole == true)
					return false;
				nodesQueue.push(current->right);
			}
		}
		return true;
	}
	int Depth(Node* node)
	{
		if (node == this->root || node == nullptr)
			return 0;
		return 1 + Depth(node->parent);
	}
};
Node* Insert(const std::vector<int>& levelOrder, int index, int size)
{
	if (index < size)
	{
		if (levelOrder[index] != -1)
		{
			Node* root = new Node(levelOrder[index]);
			root->left = Insert(levelOrder, 2 * index + 1, size);
			if (root->left != nullptr)
				root->left->parent = root;
			root->right = Insert(levelOrder, 2 * index + 2, size);
			if (root->right != nullptr)
				root->right->parent = root;
			return root;
		}
	}
	return nullptr;
}
void ReadLevelOrder(std::vector<int>& levelOrder, std::ifstream& inputFile)
{
	int nrNodes, value;
	inputFile >> nrNodes;
	for (int index = 0; index < nrNodes; index++)
	{
		inputFile >> value;
		levelOrder.push_back(value);
	}
}
int main()
{
	BTree myTree; std::vector<int> levelOrder; int index = 1; Node* node = new Node, * newNode = new Node;
	std::ifstream inputFile("Input.in");
	ReadLevelOrder(levelOrder, inputFile);
	myTree.root = Insert(levelOrder, 0, levelOrder.size());
	int option = 1, key, nrNodes, nrOption = 1;
	do
	{
		if (nrOption % 5 == 1)
		{
			if (nrOption != 1)
			{
				system("PAUSE");
				system("CLS");
			}
			std::cout << "Options:\n(0) - Exit\n(1) - Height of a tree\n(2) - Traversals\n(3) - Print the leafs\n(4) - Compare two trees\n(5) - Check if a tree is complete\n(6) - Depth of a node\n\n";
		}
		std::cout << "Enter your option: ";
		std::cin >> option;
		switch (option)
		{
		case 0:
		{
			std::cout << "Thanks for using my menu!\n";
			break;
		}
		case 1:
		{
			std::cout << "Enter a key: ";
			std::cin >> key;
			newNode = myTree.find(myTree.root, key);
			if (newNode == nullptr)
			{
				std::cout << "There is not any node with the given key!\n";
			}
			else
			{
				std::cout << "The height of the tree that has " << key << " as the root is " << myTree.Height(newNode) << "!\n";
			}
			break;
		}
		case 2:
		{
			do
			{
				std::cout << "Enter an option (1 - RSD, 2 - SRD, 3 - SDR, 4 - level order):";
				std::cin >> key;
			} while (!(key >= 1 && key <= 4));
			switch (key)
			{
			case 1:
			{
				std::cout << "RSD = ";
				myTree.RSD(myTree.root);
				std::cout << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "SRD = ";
				myTree.SRD(myTree.root);
				std::cout << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "SDR = ";
				myTree.SDR(myTree.root);
				std::cout << std::endl;
				break;
			}
			case 4:
			{
				std::cout << "Level order = ";
				myTree.LevelOrder();
				break;
			}
			}
			break;
		}
		case 3:
		{
			std::cout << "Leafs = ";
			myTree.PrintLeafs();
			break;
		}
		case 4:
		{
			BTree newTree; std::vector<int> levelOrder2;
			std::cout << "Number of nodes of the new tree: ";
			std::cin >> nrNodes;
			std::cout << "Give the level order of the new tree: ";
			for (int index = 0; index < nrNodes; index++)
			{
				std::cin >> key;
				levelOrder2.push_back(key);
			}
			newTree.root = Insert(levelOrder2, 0, levelOrder2.size());
			if (myTree.IsEqualTo(newTree))
				std::cout << "The two trees are identical!\n";
			else
				std::cout << "The two trees are not identical!\n";
			break;
		}
		case 5:
		{
			if (myTree.IsComplete())
				std::cout << "The tree is complete!\n";
			else
				std::cout << "The tree is not complete!\n";
			break;
		}
		case 6:
		{
			std::cout << "Give a key: ";
			std::cin >> key;
			node = myTree.find(myTree.root, key);
			if (node == nullptr)
			{
				std::cout << "There is not any node with the given key!\n";
			}
			else
			{
				std::cout << "The depth of the node number " << key << " is " << myTree.Depth(node) << "!\n";
			}
		}
		}
		nrOption++;
	} while (option);
	delete newNode;
	delete node;
	inputFile.close();
	return 0;
}