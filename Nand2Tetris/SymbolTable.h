#pragma once
#include "Headers.h"

class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();

	void AddEntry(string symbol, int address);
	bool Contains(string symbol);
	int GetAddress(string symbol);
	int GetNextAvailableAddress();
private:
	unordered_map<string, int> symbolTable;
	int nextAvailableAddress;

};