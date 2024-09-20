#pragma once
#include "Headers.h"
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

class Assembler
{
public:
	Assembler(string file);
	~Assembler();

	void FirstPass();
	void Assemble();

private:
	SymbolTable* symbolTable;
	Parser* parser;
	Code* code;
	string parsingFile;
	string outputFile;
};

