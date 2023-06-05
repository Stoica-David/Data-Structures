#include<iostream>
#include "HashTable.h"
HashTable::HashTable() :nrElements(0), dimension(8)
{
	this->table = new std::list<std::pair<int, int>>[this->dimension];
}
HashTable::HashTable(int x)
{
	this->dimension = x;
	this->nrElements = 0;
	this->table = new std::list<std::pair<int, int>>[this->dimension];
}
HashTable::HashTable(const HashTable& ht)
{
	this->nrElements = ht.nrElements;
	this->dimension = ht.dimension;
	this->table = new std::list<std::pair<int, int>>[this->dimension];
	for (int i = 0; i < this->dimension; i++)
	{
		this->table[i] = ht.table[i];
	}
}
HashTable::~HashTable()
{
	delete[] this->table;
}
float HashTable::loadFactor()
{
	return (float)((float)this->nrElements / (float)this->dimension);
}
void HashTable::rehash()
{
	this->dimension *= 2;
	std::list<std::pair<int, int>>* newTable;
	newTable = new std::list<std::pair<int, int>>[this->dimension];
	for (int index = 0; index < this->dimension / 2; index++)
	{
		std::list<std::pair<int, int>>::iterator it;
		for (it = this->table[index].begin(); it != this->table[index].end(); it++)
		{
			newTable[hash(it->first)].push_front(*it);
		}
	}
	delete[] this->table;
	this->table = new std::list<std::pair<int, int>>[this->dimension];
	for (int index = 0; index < this->dimension; index++)
	{
		this->table[index] = newTable[index];
	}
	delete[] newTable;
}
unsigned HashTable::hash(int key)
{
	return (unsigned int)(key % this->dimension);
}
void HashTable::insert(std::pair<int, int> insertedPair)
{
	if (find(insertedPair.first))
		return;
	this->nrElements++;
	if (loadFactor() == 1.0)
	{
		rehash();
	}
	this->table[hash(insertedPair.first)].push_front(insertedPair);
}
void HashTable::erase(int key)
{
	if (find(key) == nullptr)
		return;
	nrElements--;
	unsigned int index = hash(key);
	std::list<std::pair<int, int>>::iterator it;
	for (it = this->table[index].begin(); it != this->table[index].end(); it++)
	{
		if (it->first == key)
		{
			this->table[index].erase(it);
			break;
		}
	}
}
std::pair<int, int>* HashTable::find(int key)
{
	std::list<std::pair<int, int>>::iterator it;
	std::pair<int, int> pPair = { 0,0 };
	unsigned int index = hash(key);
	for (it = this->table[index].begin(); it != this->table[index].end(); it++)
	{
		if (it->first == key)
			pPair = *it;
	}
	if (pPair.first != 0 && pPair.second != 0)
		return &pPair;
	else
		return nullptr;
}
void HashTable::print()
{
	std::list < std::pair<int, int>>::iterator it;
	for (int index = 0; index < this->dimension; index++)
	{
		for (it = this->table[index].begin(); it != this->table[index].end(); it++)
		{
			std::cout << it->first << " " << it->second << std::endl;
		}
	}
	std::cout << std::endl;
}
std::pair<int, int>* HashTable::end()
{
	return nullptr;
}