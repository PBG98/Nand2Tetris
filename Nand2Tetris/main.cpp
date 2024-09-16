#include "Headers.h"
#include "Utility.h"

int main(void)
{
	Utility util;
	
	string parsingFile = util.GetParsingFilePath();


	cout << parsingFile << endl;
	
	return 0;	
}

