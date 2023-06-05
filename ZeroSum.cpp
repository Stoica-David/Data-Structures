#include<iostream>
#include<fstream>
#include<unordered_map>
void ReadVector(std::vector<int>& A, std::ifstream& inputFile)
{
	int nrElements, element;
	inputFile >> nrElements;
	for (int index = 0; index < nrElements; index++)
	{
		inputFile >> element;
		A.push_back(element);
	}
}
void Sums(const std::vector<int>& A, const std::vector<int>& B, const std::vector<int>& C, const std::vector<int>& D)
{
	std::unordered_map<int, std::pair<int, int>> sums;
	for (int index1 = 0; index1 < A.size(); index1++)
	{
		for (int index2 = 0; index2 < B.size(); index2++)
		{
			sums[A[index1] + B[index2]] = { index1, index2 };
		}
	}
	int sum = 0, nrSum = 1;
	for (int index1 = 0; index1 < C.size(); index1++)
	{
		for (int index2 = 0; index2 < D.size(); index2++)
		{
			sum = C[index1] + D[index2];
			if (sums.find(-sum) != sums.end())
			{
				std::cout << nrSum << ". ";
				std::cout << "A[" << sums.find(-sum)->second.first << "] + B[" << sums.find(-sum)->second.second << "] + C[" << index1 << "] + D[" << index2 << "] = 0" << std::endl;
				nrSum++;
			}
		}
	}
}
int main()
{
	std::vector<int> A, B, C, D;
	std::ifstream inputFile("Intrare.in");
	ReadVector(A, inputFile);
	ReadVector(B, inputFile);
	ReadVector(C, inputFile);
	ReadVector(D, inputFile);
	Sums(A, B, C, D);
	inputFile.close();
	return 0;
}