#include<iostream>
#include<fstream>
#include<string>
#include<stack>
void Citire(std::string& pharantesis, std::ifstream& inputFile)
{
	inputFile >> pharantesis;
	inputFile.close();
}
void Parantezare(const std::string& pharantesis)
{
	std::stack<char> stackPharantesis;
	for (char character : pharantesis)
	{
		if (character == '{')
		{
			if (!stackPharantesis.empty() && (stackPharantesis.top() == '[' || stackPharantesis.top() == '('))
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackPharantesis.push(character);
		}
		if (character == '}')
		{
			if (stackPharantesis.empty() || stackPharantesis.top() != '{')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackPharantesis.pop();
		}
		if (character == '[')
		{
			if (!stackPharantesis.empty() && stackPharantesis.top() == '(')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackPharantesis.push(character);
		}
		if (character == ']')
		{
			if (stackPharantesis.empty() || stackPharantesis.top() != '[')
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackPharantesis.pop();
		}
		if (character == '(')
		{
			stackPharantesis.push(character);
		}
		if (character == ')')
		{
			if (stackPharantesis.empty())
			{
				std::cout << "The given pharantesis are not valid!\n";
				return;
			}
			stackPharantesis.pop();
		}
	}
	if (stackPharantesis.empty())
	{
		std::cout << "The given pharantesis are valid!\n";
	}
	else
	{
		std::cout << "The given pharantesis are not valid!\n";
	}
}
int main()
{
	std::string pharantesis;
	std::ifstream inputFile("Intrare.in");
	Citire(pharantesis, inputFile);
	Parantezare(pharantesis);
	return 0;
}