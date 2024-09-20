#include "Assembler.h"

Assembler::Assembler(string file)
	: parsingFile(file), outputFile("")
{
	symbolTable = new SymbolTable();
	parser = new Parser(parsingFile);
	code = new Code(symbolTable);

	outputFile = parsingFile.substr(0, parsingFile.find(".")) + ".hack";
}

Assembler::~Assembler()
{
	delete symbolTable;
	delete parser;
	delete code;
}

void Assembler::FirstPass()
{
	int romAddress = 0;

	while (parser->HasMoreLines())
	{
		parser->Advance();
		InstructionType type = parser->GetInstructionType();
		if (type == InstructionType::A_COMMAND || type == InstructionType::C_COMMAND)
		{
			romAddress++;
		}
		else if (type == InstructionType::L_COMMAND)
		{
			string symbol = parser->Symbol();
			symbolTable->AddEntry(symbol, romAddress);
		}
	}

	parser->Reset();
}

void Assembler::Assemble()
{
	ofstream ofs(outputFile);
	string outputLine("");

	while (parser->HasMoreLines())
	{
		parser->Advance();
		InstructionType type = parser->GetInstructionType();
		if (type == InstructionType::A_COMMAND)
		{
			string symbol = parser->Symbol();
			outputLine = "0" + code->ConvertToBinary(symbol) + '\n';
		}
		else if (type == InstructionType::C_COMMAND)
		{
			string dest = parser->Dest();
			string comp = parser->Comp();
			string jump = parser->Jump();
			outputLine = "111" + code->Comp(comp) + code->Dest(dest) + code->Jump(jump) + '\n';
		}
		else if (type == InstructionType::L_COMMAND)
		{
			string symbol = parser->Symbol();
		}
		ofs << outputLine;
		outputLine.clear();	
	}
}
