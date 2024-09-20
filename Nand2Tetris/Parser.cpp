#include "Parser.h"

Parser::Parser(string file)
	: parsingFile(file), curLineIndex(0), curLine(""), maxLineIndex(0), curInstructionType(InstructionType::INVALID_COMMAND)
{
	ifstream fileStream(parsingFile);
	string line;
	if (fileStream.is_open())
	{
		while (getline(fileStream, line))
		{
			lines.push_back(line);
		}
		maxLineIndex = lines.size();
	}
	else
	{
		cout << "Error: Unable to open file: " << parsingFile << endl;
	}
	fileStream.close();
}

Parser::~Parser()
{
	lines.clear();
}

bool Parser::HasMoreLines()
{
	return curLineIndex < maxLineIndex;
}

void Parser::Advance()
{
	if (HasMoreLines() == false)
	{
		cerr << "Error: No more lines to parse" << endl;
		return;
	}

	curLine = lines[curLineIndex];
	curLine.erase(remove_if(curLine.begin(), curLine.end(), [](unsigned char x) {return isspace(x); }), curLine.end());

	size_t pos = curLine.find("//");
	if (pos != string::npos)
	{
		curLine = curLine.substr(0, pos);
	}

	curLineIndex++;
}

InstructionType Parser::GetInstructionType()
{
	if (curLine.empty())
	{
		curInstructionType = InstructionType::INVALID_COMMAND;
	}
	else if (curLine[0] == '\\')
	{
		curInstructionType = InstructionType::COMMENT_COMAND;
	}
	else if (curLine[0] == '@')
	{
		curInstructionType = InstructionType::A_COMMAND;
	}
	else if (curLine[0] == '(')
	{
		curInstructionType = InstructionType::L_COMMAND;
	}
	else
	{
		curInstructionType = InstructionType::C_COMMAND;
	}

	return curInstructionType;
}

string Parser::Symbol()
{	
	string res("");
	if (curInstructionType == InstructionType::A_COMMAND)
	{
		res = curLine.substr(1);
	}
	else if (curInstructionType == InstructionType::L_COMMAND)
	{
		size_t pos1 = curLine.find("(");
		size_t pos2 = curLine.find(")");
		res = curLine.substr(pos1 + 1, pos2 - pos1 - 1);
	}
	else
	{
		cerr << "Error: Invalid instruction type" << endl;
	}
	return res;
}

string Parser::Dest()
{
	if (curInstructionType != InstructionType::C_COMMAND)
	{
		cerr << "Error: Invalid instruction type" << endl;
		return "";
	}

	size_t pos = curLine.find("=");
	return (pos == string::npos) ? "" : curLine.substr(0, pos);
}

string Parser::Comp()
{
	if (curInstructionType != InstructionType::C_COMMAND)
	{
		cerr << "Error: Invalid instruction type" << endl;
		return "";
	}

	size_t pos1 = curLine.find("=");
	size_t pos2 = curLine.find(";");
	return (pos1 == string::npos) ? curLine.substr(0, pos2) : curLine.substr(pos1 + 1, pos2 - pos1 - 1);
}

string Parser::Jump()
{
	if (curInstructionType != InstructionType::C_COMMAND)
	{
		cerr << "Error: Invalid instruction type" << endl;
		return "";
	}

	size_t pos = curLine.find(";");
	return (pos == string::npos) ? "" : curLine.substr(pos + 1);
}

void Parser::Reset()
{
	curLineIndex = 0;
	curLine = "";
	curInstructionType = InstructionType::INVALID_COMMAND;
}


