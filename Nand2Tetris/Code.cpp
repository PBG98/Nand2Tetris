#include "Code.h"
#include "SymbolTable.h"

Code::Code(SymbolTable* symbolTable)
	: symbolTable(symbolTable)
{
	destMapInit();
	compMapInit();
	jumpMapInit();
}

Code::~Code()
{
	destMap.clear();
	compMap.clear();
	jumpMap.clear();
}

void Code::destMapInit()
{
	destMap.emplace("null", "000");
	destMap.emplace("M", "001");
	destMap.emplace("D", "010");
	destMap.emplace("MD", "011");
	destMap.emplace("A", "100");
	destMap.emplace("AM", "101");
	destMap.emplace("AD", "110");
	destMap.emplace("AMD", "111");
}

void Code::compMapInit()
{
	compMap.emplace("0", "0101010");
	compMap.emplace("1", "0111111");
	compMap.emplace("-1", "0111010");
	compMap.emplace("D", "0001100");
	compMap.emplace("A", "0110000");
	compMap.emplace("!D", "0001101");
	compMap.emplace("!A", "0110001");
	compMap.emplace("-D", "0001111");
	compMap.emplace("-A", "0110011");
	compMap.emplace("D+1", "0011111");
	compMap.emplace("A+1", "0110111");
	compMap.emplace("D-1", "0001110");
	compMap.emplace("A-1", "0110010");
	compMap.emplace("D+A", "0000010");
	compMap.emplace("D-A", "0010011");
	compMap.emplace("A-D", "0000111");
	compMap.emplace("D&A", "0000000");
	compMap.emplace("D|A", "0010101");
	compMap.emplace("M", "1110000");
	compMap.emplace("!M", "1110001");
	compMap.emplace("-M", "1110011");
	compMap.emplace("M+1", "1110111");
	compMap.emplace("M-1", "1110010");
	compMap.emplace("D+M", "1000010");
	compMap.emplace("D-M", "1010011");
	compMap.emplace("M-D", "1000111");
	compMap.emplace("D&M", "1000000");
	compMap.emplace("D|M", "1010101");
}

void Code::jumpMapInit()
{
	jumpMap.emplace("null", "000");
	jumpMap.emplace("JGT", "001");
	jumpMap.emplace("JEQ", "010");
	jumpMap.emplace("JGE", "011");
	jumpMap.emplace("JLT", "100");
	jumpMap.emplace("JNE", "101");
	jumpMap.emplace("JLE", "110");
	jumpMap.emplace("JMP", "111");
}

string Code::Dest(string mnemonic)
{
	if (mnemonic == "null" || mnemonic.empty())
	{
		mnemonic = "null";
	}
	return destMap[mnemonic];
}

string Code::Comp(string mnemonic)
{
	return compMap[mnemonic];
}

string Code::Jump(string mnemonic)
{
	if (mnemonic == "null" || mnemonic.empty())
	{
		mnemonic = "null";
	}
	return jumpMap[mnemonic];
}

string Code::ConvertToBinary(string symbol)
{
	string binary("");
	if (isdigit(symbol[0]))
	{
		int num = stoi(symbol);
		binary = bitset<15>(num).to_string();
	}
	else
	{
		if (symbolTable->Contains(symbol) == false)
		{
			symbolTable->AddEntry(symbol, symbolTable->GetNextAvailableAddress());
		}
		int	address = symbolTable->GetAddress(symbol);
		binary = bitset<15>(address).to_string();
	}

	return binary;
}


