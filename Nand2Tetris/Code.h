#pragma once
#include "Headers.h"
#include <bitset>

class SymbolTable;

class Code
{
public:
	Code(SymbolTable* symbolTable);
	~Code();

	void destMapInit();
	void compMapInit();
	void jumpMapInit();

	string Dest(string mnemonic);
	string Comp(string mnemonic);
	string Jump(string mnemonic);
	string ConvertToBinary(string symbol);

private:
	map<string, string> destMap;
	map<string, string> compMap;
	map<string, string> jumpMap;

	SymbolTable* symbolTable;
};

