#include "SymbolTable.h"

SymbolTable::SymbolTable()
	: nextAvailableAddress(16)
{
	symbolTable.emplace("SP", 0);
	symbolTable.emplace("LCL", 1);
	symbolTable.emplace("ARG", 2);
	symbolTable.emplace("THIS", 3);
	symbolTable.emplace("THAT", 4);
	symbolTable.emplace("R0", 0);
	symbolTable.emplace("R1", 1);
	symbolTable.emplace("R2", 2);
	symbolTable.emplace("R3", 3);
	symbolTable.emplace("R4", 4);
	symbolTable.emplace("R5", 5);
	symbolTable.emplace("R6", 6);
	symbolTable.emplace("R7", 7);
	symbolTable.emplace("R8", 8);
	symbolTable.emplace("R9", 9);
	symbolTable.emplace("R10", 10);
	symbolTable.emplace("R11", 11);
	symbolTable.emplace("R12", 12);
	symbolTable.emplace("R13", 13);
	symbolTable.emplace("R14", 14);
	symbolTable.emplace("R15", 15);
	symbolTable.emplace("SCREEN", 16384);
	symbolTable.emplace("KBD", 24576);
}

SymbolTable::~SymbolTable()
{
	symbolTable.clear();
}

void SymbolTable::AddEntry(string symbol, int address)
{
	symbolTable.emplace(symbol, address);
}

bool SymbolTable::Contains(string symbol)
{
	if (symbolTable.find(symbol) != symbolTable.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SymbolTable::GetAddress(string symbol)
{
	return symbolTable[symbol];
}

int SymbolTable::GetNextAvailableAddress()
{
	return nextAvailableAddress++;
}
