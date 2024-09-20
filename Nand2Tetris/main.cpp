#include "Headers.h"
#include "Utility.h"
#include "Assembler.h"

int main(void)
{
	Utility util;

	string parsingFile = util.GetParsingFilePath();

	Assembler assembler(parsingFile);

	assembler.FirstPass();
	assembler.Assemble();

	return 0;
}

