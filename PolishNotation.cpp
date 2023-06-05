#include<iostream>
#include<fstream>
#include<string>
#include<stack>
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
float Evaluation(const std::string& polishNotation)
{
	std::stack<float> number; float firstNumber, secondNumber, result;
	for (char character : polishNotation)
	{
		if (isalnum(character) && !isalpha(character))
		{
			number.push((int)(character - '0'));
		}
		else
		{
			if (number.size() < 2)
			{
				return -1;
			}
			firstNumber = number.top();
			number.pop();
			secondNumber = number.top();
			number.pop();
			switch (character)
			{
			case '+':
			{
				result = firstNumber + secondNumber;
				break;
			}
			case '-':
			{
				result = firstNumber - secondNumber;
				break;
			}
			case '*':
			{
				result = firstNumber * secondNumber;
				break;
			}
			case '/':
			{
				result = firstNumber / secondNumber;
				break;
			}
			case '^':
			{
				result = std::pow(firstNumber, secondNumber);
				break;
			}
			}
			number.push(result);
		}
	}
	return number.top();
}
void Output(std::string& expression, std::ifstream& inputFile)
{
	std::string polishNotation; int expressionNumber = 1;
	float result = 0;
	while (!inputFile.eof())
	{
		std::getline(inputFile, expression);
		std::cout << "Expression " << expressionNumber << ":\n";
		for (char character : expression)
		{
			if (!isblank(character))
				std::cout << character;
		}
		std::cout << std::endl;
		if (!Characters(expression))
		{
			std::cout << "There are invalid characters in the expression " << expressionNumber << "!\n";
			expressionNumber++;
			continue;
		}
		else if (!Paranthesis(expression))
		{
			std::cout << "The pharantesis from the expression are not valid!\n";
			expressionNumber++;
			continue;
		}
		polishNotation = Polish(expression);
		result = Evaluation(polishNotation);
		if (result == -1)
		{
			std::cout << "The number of operators is not valid!\n\n";
			expressionNumber++;
			continue;
		}
		std::cout << "Reverse Polish notation: " << polishNotation << std::endl;
		std::cout << "The value of the given expression is " << result << "!\n\n";
		expressionNumber++;
	}
	inputFile.close();
}
int main()
{
	std::string expression; std::ifstream inputFile("Intrare.in");
	Output(expression, inputFile);
	return 0;
}