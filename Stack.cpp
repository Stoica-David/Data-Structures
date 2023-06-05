#include <iostream>
#include<fstream>
#include<queue>
struct stack
{
	std::queue<char> Q1, Q2;
	void push(char paranthesis)
	{
		Q1.push(paranthesis);
	}
	void pop()
	{
		while (Q1.size() > 1)
		{
			Q2.push(Q1.front());
			Q1.pop();
		}
		Q1.pop();
		while (Q2.size())
		{
			Q1.push(Q2.front());
			Q2.pop();
		}
	}
};
void Validation(stack& stackParanthesis, std::ifstream& inputFile)
{
	std::string pharantesis;
	inputFile >> pharantesis;
	for (char character : pharantesis)
	{
		if (character == '{')
		{
			if (!stackParanthesis.Q1.empty() && (stackParanthesis.Q1.back() == '[' || stackParanthesis.Q1.back() == '('))
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackParanthesis.push(character);
		}
		if (character == '}')
		{
			if (stackParanthesis.Q1.empty() || stackParanthesis.Q1.back() != '{')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackParanthesis.pop();
		}
		if (character == '[')
		{
			if (!stackParanthesis.Q1.empty() && stackParanthesis.Q1.back() == '(')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackParanthesis.push(character);
		}
		if (character == ']')
		{
			if (stackParanthesis.Q1.empty() || stackParanthesis.Q1.back() != '[')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackParanthesis.pop();
		}
		if (character == '(')
		{
			stackParanthesis.push(character);
		}
		if (character == ')')
		{
			if (stackParanthesis.Q1.empty())
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackParanthesis.pop();
		}
	}
	if (stackParanthesis.Q1.empty())
	{
		std::cout << "The given pharantesis are valid!\n";
	}
	else
	{
		std::cout << "The given pharantesis are not valid!\n";
	}
	inputFile.close();
}
int main()
{
	stack stackPharantesis; std::ifstream inputFile("Intrare.in");
	Validation(stackPharantesis, inputFile);
	return 0;
}