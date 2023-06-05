#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
class Node
{
public:
	char value;
	Node* left, * right, * parent;
	Node()
	{
		this->value = '\0';
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	Node(char value)
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
};
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
bool Characters(const std::string& expression)
{
	char validCharacters[18] = "0123456789+-*/^()";
	for (char character : expression)
	{
		if (!strchr(validCharacters, character) && !isblank(character))
			return false;
	}
	return true;
}
bool Paranthesis(const std::string& expression)
{
	std::stack<char> paranthesisStack;
	for (char character : expression)
	{
		if (character == '(')
		{
			paranthesisStack.push(character);
		}
		else if (character == ')')
		{
			if (paranthesisStack.empty())
			{
				return false;
			}
			paranthesisStack.pop();
		}
	}
	return paranthesisStack.empty();
}
int Priority(const char& character)
{
	if (character == '(')
		return 0;
	if (character == '+' || character == '-')
		return 1;
	if (character == '*' || character == '/')
		return 2;
	if (character == '^')
		return 3;
}
std::string Polish(const std::string& expression)
{
	std::string polishNotation = {}; std::stack<char> operatorStack = {};
	for (char character : expression)
	{
		if (isblank(character))
		{
			continue;
		}
		if (isalnum(character) && !isalpha(character))
		{
			polishNotation.push_back(character);
		}
		else
		{
			if (character == '(')
			{
				operatorStack.push(character);
			}
			else
			{
				if (character == ')')
				{
					while (!operatorStack.empty() && operatorStack.top() != '(')
					{
						polishNotation.push_back(operatorStack.top());
						operatorStack.pop();
					}
					if (!operatorStack.empty())
						operatorStack.pop();
				}
				else
				{
					while (!operatorStack.empty() && Priority(character) <= Priority(operatorStack.top()))
					{
						polishNotation.push_back(operatorStack.top());
						operatorStack.pop();
					}
					operatorStack.push(character);
				}
			}
		}
	}
	while (!operatorStack.empty())
	{
		polishNotation.push_back(operatorStack.top());
		operatorStack.pop();
	}
	return polishNotation;
}
void ReadInput(std::string& expression, std::ifstream& inputFile)
{
	inputFile >> expression;
}
Node* TreeConstruction(const std::string& polishNotation, int index, int size)
{
	std::stack<Node*> nodesStack;
	for (char character : polishNotation)
	{
		if (isdigit(character))
		{
			Node* newNode = new Node(character);
			nodesStack.push(newNode);
		}
		else if (!isdigit(character))
		{
			Node* newNode = new Node(character);
			if (!nodesStack.empty())
			{
				newNode->right = nodesStack.top();
				if (newNode->right != nullptr)
					newNode->right->parent = newNode;
				nodesStack.pop();
			}
			if (!nodesStack.empty())
			{
				newNode->left = nodesStack.top();
				if (newNode->left != nullptr)
					newNode->left->parent = newNode;
				nodesStack.pop();
			}
			nodesStack.push(newNode);
		}
	}
	return nodesStack.top();
}
int main()
{
	BTree polishTree; std::string expression;
	std::ifstream inputFile("Input.in");
	ReadInput(expression, inputFile);
	expression = Polish(expression);
	std::cout << "Polish notation: ";
	std::cout << expression << std::endl << std::endl;
	polishTree.root = TreeConstruction(expression, 0, expression.size());
	std::cout << "The level order traversal for the polishTree is: ";
	polishTree.LevelOrder();
	inputFile.close();
	return 0;
}