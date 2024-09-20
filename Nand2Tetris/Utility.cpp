#include "Utility.h"

string Utility::GetParsingFilePath()
{
	cout << "Input asm file name : ";
	string inputFileName("");
	cin >> inputFileName;

	string curDir("");
	char szCurDir[1024]{ 0, };
	if (_getcwd(szCurDir, sizeof(szCurDir)) != NULL)
	{
		curDir = szCurDir;
	}
	else
	{
		cerr << "Error getting current working directory" << endl;
	}

	string res = curDir + "\\" + inputFileName;

	return res;
}
