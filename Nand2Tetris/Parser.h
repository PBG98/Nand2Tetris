#pragma once
#include "Headers.h"

class Parser
{
public:	
	Parser(string file);
	~Parser();
	bool HasMoreLines();
	void Advance();
	InstructionType GetInstructionType();
	string Symbol();
	string Dest();
	string Comp();
	string Jump();
	void Reset();
	
private:
	string parsingFile;
	vector<string> lines;
	size_t curLineIndex;
	size_t maxLineIndex;
	string curLine;
	InstructionType curInstructionType;
	 
};

