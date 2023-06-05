#include<iostream>
#include<vector>
#include<map>
void ListCreation(std::map<std::pair<int, int>, std::string>& waitingList)
{
	std::string option = ""; int admissionGrade, SATGrade;
	while (1)
	{
		std::cout << "Enter a candidate (Press E to exit): ";
		std::cin >> option;
		if (option == "E")
			break;
		std::cin >> admissionGrade >> SATGrade;
		std::pair<std::pair<int, int>, std::string> currentCandidate = std::make_pair(std::make_pair(admissionGrade, SATGrade), option);
		waitingList.insert(currentCandidate);
	}
}
void Candidates(std::map<std::pair<int, int>, std::string>& waitingList)
{
	int index = 0; bool foundIonescu = false;
	for (auto currentCandidate = waitingList.rbegin(); currentCandidate != waitingList.rend(); currentCandidate++)
	{
		if (index < 3)
			std::cout << "Candidate: " << (*currentCandidate).second << "\tAdmission Grade: " << (*currentCandidate).first.first << "\tSAT Grade: " << (*currentCandidate).first.second << "\n";
		if ((*currentCandidate).second == "Ionescu")
			foundIonescu = true;
		index++;
	}
	if (foundIonescu)
	{
		std::cout << "There is a candidate named Ionescu on the list!\n";
	}
	else
	{
		std::cout << "There is not a candidate named Ionescu on the list!\n";
	}
}
int main()
{
	std::map<std::pair<int, int>, std::string> waitingList;
	ListCreation(waitingList);
	Candidates(waitingList);
	return 0;
}