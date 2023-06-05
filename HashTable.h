#pragma once
#include<iostream>
#include<list>
class HashTable
{
private:
	int nrElements, dimension;
	std::list<std::pair<int, int>>* table;
public:
	HashTable();
	HashTable(int);
	HashTable(const HashTable&);
	~HashTable();
	float loadFactor();
	void rehash();
	unsigned int hash(int);
	void insert(std::pair<int, int>);
	void erase(int);
	std::pair<int, int>* find(int);
	void print();
	std::pair<int, int>* end();
};