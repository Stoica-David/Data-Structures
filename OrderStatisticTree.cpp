#include<iostream>
#include<fstream>
#include<string>
#include<vector>
struct Node
{
	std::string name;
	int grade, nrNodes;
	bool color;
	Node* left, * right, * parent;
	Node()
	{
		this->name = "";
		this->grade = -1;
		this->nrNodes = 1;
		this->color = false;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	Node(std::string name, int grade, bool color, Node* left, Node* right, Node* parent)
	{
		this->name = name;
		this->grade = grade;
		this->color = color;
		this->nrNodes = 1;
		this->left = left;
		this->right = right;
		this->parent = parent;
	}
};
struct ARN
{
	Node* root, * nil;
	ARN()
	{
		this->root = nullptr;
		this->nil = new Node;
		this->nil->nrNodes = 0;
	}
	int NrNodes(Node* current) {
		if (current == nullptr || current == this->nil)
		{
			return 0;
		}
		else
		{
			return 1 + NrNodes(current->left) + NrNodes(current->right);
		}
	}
	void Insert(const std::string& name, int grade)
	{
		if (this->root == nullptr)
		{
			root = new Node(name, grade, false, this->nil, this->nil, this->nil);
			return;
		}
		Node* current = root;
		while (current != this->nil)
		{
			if (current->grade == grade)
			{
				if (current->name < name)
				{
					if (current->left != this->nil)
					{
						current->nrNodes++;
						current = current->left;
					}
					else
					{
						current->left = new Node(name, grade, true, this->nil, this->nil, this->nil);
						current->left->parent = current;
						InsertRepare(current->left);
						return;
					}
				}
				else
				{
					if (current->right != this->nil)
					{
						current->nrNodes++;
						current = current->right;
					}
					else
					{
						current->right = new Node(name, grade, true, this->nil, this->nil, this->nil);
						current->right->parent = current;
						InsertRepare(current->right);
						return;
					}
				}
			}
			else if (current->grade > grade)
			{
				if (current->left != this->nil)
				{
					current->nrNodes++;
					current = current->left;
				}
				else
				{
					current->left = new Node(name, grade, true, this->nil, this->nil, this->nil);
					current->left->parent = current;
					InsertRepare(current->left);
					return;
				}
			}
			else
			{
				if (current->right != this->nil)
				{
					current->nrNodes++;
					current = current->right;
				}
				else
				{
					current->right = new Node(name, grade, true, this->nil, this->nil, this->nil);
					current->right->parent = current;
					InsertRepare(current->right);
					return;
				}
			}
		}
		current = current->parent;
	}
	void InsertRepare(Node* current)
	{
		while (current->parent->color == true)
		{
			if (current->parent == current->parent->parent->left)
			{
				Node* uncle = current->parent->parent->right;
				if (uncle->color == true)
				{
					current->parent->color = false;
					uncle->color = false;
					current->parent->parent->color = true;
					current = current->parent->parent;
				}
				else
				{
					if (current == current->parent->right)
					{
						current = current->parent;
						LeftRotation(current);
					}
					current->parent->color = false;
					current->parent->parent->color = true;
					RightRotation(current->parent->parent);
				}
			}
			else
			{
				Node* uncle = current->parent->parent->left;
				if (uncle->color == true)
				{
					current->parent->color = false;
					uncle->color = false;
					current->parent->parent->color = true;
					current = current->parent->parent;
				}
				else
				{
					if (current == current->parent->left)
					{
						current = current->parent;
						RightRotation(current);
					}
					current->parent->color = false;
					current->parent->parent->color = true;
					LeftRotation(current->parent->parent);
				}
			}
		}
		this->root->color = false;
	}
	Node* Max(Node* x)
	{
		Node* current = x;
		while (current->right != this->nil)
		{
			current = current->right;
		}
		return current;
	}
	Node* Min(Node* x)
	{
		Node* current = x;
		while (current->left != this->nil)
		{
			current = current->left;
		}
		return current;
	}
	Node* Successor(Node* x)
	{
		Node* current = x;
		if (x->right != this->nil)
		{
			current = Min(current->right);
		}
		else
		{
			current = x->parent;
			while (current != this->nil && x == current->right)
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
		if (x->left != this->nil)
		{
			current = Max(current->left);
		}
		else
		{
			current = x->parent;
			while (current != this->nil && x == current->left)
			{
				x = current;
				current = current->parent;
			}
		}
		return current;
	}
	Node* Find(std::string name, int grade)
	{
		Node* current = this->root;
		while (current != nullptr && current != this->nil)
		{
			if (current->grade == grade)
			{
				if (current->name == name)
				{
					return current;
				}
				else if (name > current->name)
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			else if (grade < current->grade)
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
		if (erased->parent == this->nil)
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
		successor->parent = erased->parent;
	}
	void Delete(std::string name, int grade)
	{
		if (Find(name, grade) == nullptr || Find(name, grade) == this->nil)
		{
			std::cout << "There is not a node to erase with the given key!\n";
			return;
		}
		else
		{
			Erase(Find(name, grade));
		}
	}
	void Erase(Node* toErase)
	{
		if (toErase == nullptr || toErase == this->nil)
		{
			std::cout << "There is not a node to erase!\n";
			return;
		}
		bool toEraseColor = toErase->color;
		Node* x;
		if (toErase->left == this->nil)
		{
			x = toErase->right;
			Transplant(toErase, x);
		}
		else
		{
			if (toErase->right == this->nil)
			{
				x = toErase->left;
				Transplant(toErase, x);
			}
			else
			{
				Node* successor = Successor(toErase);
				toEraseColor = successor->color;
				x = successor->right;
				if (successor->parent == toErase)
				{
					x->parent = successor;
				}
				else
				{
					Transplant(successor, x);
					successor->right = toErase->right;
					toErase->right->parent = successor;
				}
				Transplant(toErase, successor);
				successor->left = toErase->left;
				toErase->left->parent = successor;
				successor->color = toErase->color;
			}
		}
		delete toErase;
		if (toEraseColor == false)
			DeleteRepare(x);
	}
	void DeleteRepare(Node* current)
	{
		while (current != this->root && current->color == false)
		{
			if (current == current->parent->left)
			{
				Node* brother = current->parent->right;
				if (brother->color == true)
				{
					brother->color = false;
					brother->parent->color = true;
					LeftRotation(current->parent);
					brother = current->parent->right;
				}
				if (brother->left->color == false && brother->right->color == false)
				{
					brother->color = 0;
					current = current->parent;
				}
				else
				{
					if (brother->right->color == false)
					{
						brother->left->color = false;
						brother->color = true;
						RightRotation(brother);
						brother = current->parent->right;
					}
					brother->color = current->parent->color;
					current->parent->color = false;
					brother->right->color = false;
					LeftRotation(brother->parent);
					current = this->root;
				}
			}
			else
			{
				Node* brother = current->parent->left;
				if (brother->color == true)
				{
					brother->color = false;
					current->parent->color = true;
					RightRotation(current->parent);
					brother = current->parent->left;
				}
				if (brother->right->color == false && brother->left->color == false)
				{
					brother->color = true;
					current = current->parent;
				}
				else
				{
					if (brother->left->parent)
					{
						brother->right->color = false;
						brother->color = true;
						LeftRotation(brother);
						brother = current->parent->left;
					}
					brother->color = current->parent->color;
					current->parent->color = false;
					brother->left->color = false;
					RightRotation(current->parent);
					current = this->root;
				}
			}
		}
		current->color = 1;
	}
	void LeftRotation(Node* toRotate)
	{
		Node* child = toRotate->right;
		toRotate->right = child->left;
		if (child->left != this->nil)
		{
			child->left->parent = toRotate;
			child->left->nrNodes = NrNodes(child->left);
		}
		child->parent = toRotate->parent;
		if (toRotate->parent == this->nil)
		{
			this->root = child;
		}
		else
		{
			if (toRotate->parent->left == toRotate)
			{
				toRotate->parent->left = child;
			}
			else
			{
				toRotate->parent->right = child;
			}
		}
		child->left = toRotate;
		toRotate->parent = child;
		toRotate->nrNodes = NrNodes(toRotate);
		child->nrNodes = NrNodes(child);
	}
	void RightRotation(Node* toRotate)
	{
		Node* child = toRotate->left;
		toRotate->left = child->right;
		if (child->right != this->nil)
		{
			child->right->parent = toRotate;
			child->right->nrNodes = NrNodes(child->right);
		}
		child->parent = toRotate->parent;
		if (toRotate->parent == this->nil)
		{
			this->root = child;
		}
		else
		{
			if (toRotate->parent->right == toRotate)
			{
				toRotate->parent->right = child;
			}
			else
			{
				toRotate->parent->left = child;
			}
		}
		child->right = toRotate;
		toRotate->parent = child;
		toRotate->nrNodes = NrNodes(toRotate);
		child->nrNodes = NrNodes(child);
	}
	void DRS(Node* current)
	{
		if (current != this->nil)
		{
			DRS(current->right);
			std::cout << current->name << "-" << current->grade << "\n";
			DRS(current->left);
		}
	}
	Node* FindNStudent(int rank)
	{
		Node* current = this->root;
		while (current != this->nil)
		{
			int currentRank = current->right->nrNodes + 1;
			if (rank == currentRank)
			{
				return current;
			}
			else if (rank < currentRank)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
				rank -= currentRank;
			}
		}
		return current;
	}
	int FindRank(Node* current)
	{
		int rank = current->right->nrNodes + 1;
		while (current != this->root)
		{
			Node* parent = current->parent;
			if (current == parent->left)
			{
				rank = rank + parent->right->nrNodes + 1;
			}
			current = parent;
		}
		return rank;
	}
	Node* FindGrade(int grade)
	{
		Node* current = this->root;
		while (current != nullptr && current != this->nil)
		{
			if (current->grade == grade)
			{
				return current;
			}
			else if (grade < current->grade)
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
	int NrStudents(int begin, int end)
	{
		Node* node1 = FindGrade(begin);
		Node* node2 = FindGrade(end);
		if (node1 == nullptr || node1 == this->nil || node2 == nullptr || node2 == this->nil)
		{
			return 0;
		}
		int rank1 = FindRank(node1);
		int rank2 = FindRank(node2);
		return rank1 - rank2 + 1;
	}
};
void ReadInput(ARN& MyTree, std::ifstream& inputFile)
{
	int nrStudents;
	inputFile >> nrStudents;
	std::string name; int grade;
	while (nrStudents)
	{
		inputFile >> name >> grade;
		MyTree.Insert(name, grade);
		nrStudents--;
	}
}
int main()
{
	ARN MyTree; std::ifstream inputFile("Input.in");
	int option = 1, nrOption = 1, grade, rank, begin, end; std::string name;
	ReadInput(MyTree, inputFile);
	std::cout << "Options:\n(0) - Exit\n(1) - Show students\n(2) - Search a student\n(3) - Search the nth student\n(4) - Add a student\n(5) - Eliminate a student\n(6) - Number of students within a given range\n\n";
	while (option)
	{
		if (nrOption % 5 == 0)
		{
			system("PAUSE");
			system("CLS");
			std::cout << "Options:\n(0) - Exit\n(1) - Show students\n(2) - Search a student\n(3) - Search the nth student\n(4) - Add a student\n(5) - Eliminate a student\n(6) - Number of students within a given range\n\n";
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
			std::cout << "List:\n";
			MyTree.DRS(MyTree.root);
			std::cout << std::endl;
			break;
		}
		case 2:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is empty!\n";
			}
			else
			{
				std::cout << "Enter a name: ";
				std::cin >> name;
				std::cout << "Enter a grade: ";
				std::cin >> grade;
				if (MyTree.Find(name, grade) != MyTree.nil)
				{
					std::cout << "The given student is rank " << MyTree.FindRank(MyTree.Find(name, grade)) << "!\n";
				}
				else
				{
					std::cout << "The given student is not on the list!\n";
				}
			}
			break;
		}
		case 3:
		{
			std::cout << "Enter a rank: ";
			std::cin >> rank;
			if (MyTree.FindNStudent(rank) != MyTree.nil)
			{
				std::cout << "Rank " << rank << ": " << MyTree.FindNStudent(rank)->name << "-" << MyTree.FindNStudent(rank)->grade << "\n";
			}
			else
			{
				std::cout << "There is no student at the given rank!\n";
			}
			break;
		}
		case 4:
		{
			std::cout << "Enter a name: ";
			std::cin >> name;
			std::cout << "Enter a grade: ";
			std::cin >> grade;
			MyTree.Insert(name, grade);
			break;
		}
		case 5:
		{
			if (MyTree.root == nullptr)
			{
				std::cout << "The tree is already empty!\n";
			}
			else
			{
				std::cout << "Enter a name: ";
				std::cin >> name;
				std::cout << "Enter a grade: ";
				std::cin >> grade;
				MyTree.Delete(name, grade);
			}
			break;
		}
		case 6:
		{
			std::cout << "Enter a range of numbers(begin and end): ";
			std::cin >> begin >> end;
			int nrStudents = MyTree.NrStudents(begin, end);
			if (nrStudents)
			{
				std::cout << "The number of students in the given range is " << nrStudents << "!\n";
			}
			else if (nrStudents == 1)
			{
				std::cout << "There is only a student in the given interval!\n";
			}
			else
			{
				std::cout << "There are no students in the given interval!\n";
			}
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
	inputFile.close();
	return 0;
}