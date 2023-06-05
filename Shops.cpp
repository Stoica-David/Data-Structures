#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
void MostExclusiveShop(std::unordered_map<std::string, std::vector<unsigned int>>& productsMap)
{
	std::ifstream inputFile("Intrare.in");
	std::string product;
	unsigned int nrShops, nrProducts;
	inputFile >> nrShops;
	for (unsigned int shopIndex = 0; shopIndex < nrShops; shopIndex++)
	{
		inputFile >> nrProducts;
		for (unsigned int productIndex = 0; productIndex < nrProducts; productIndex++)
		{
			inputFile >> product;
			productsMap[product].push_back(shopIndex);
		}
	}
	std::vector<std::vector<std::string>> exclusiveProducts;
	exclusiveProducts.resize(nrShops);
	for (std::pair<std::string, std::vector<unsigned int>> currentProduct : productsMap)
	{
		if (currentProduct.second.size() == 1)
			exclusiveProducts[currentProduct.second[0]].push_back(currentProduct.first);
	}
	unsigned int maxShopIndex = 0;
	for (unsigned int shopIndex = 0; shopIndex < nrShops; shopIndex++)
	{
		if (exclusiveProducts[shopIndex].size() > exclusiveProducts[maxShopIndex].size())
			maxShopIndex = shopIndex;
	}
	std::cout << "The shop with the most exclusive products is the shop number " << maxShopIndex << "!\n";
	std::cout << "The exclusive products: ";
	for (std::string currentProduct : exclusiveProducts[maxShopIndex])
	{
		std::cout << currentProduct << " ";
	}
	inputFile.close();
}
int main()
{
	std::unordered_map<std::string, std::vector<unsigned int>> productsMap;
	MostExclusiveShop(productsMap);
	return 0;
}