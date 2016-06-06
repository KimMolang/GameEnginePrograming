// CSVRead.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "CSVParser.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//CCSVParser*		pCSVParser = new CCSVParser(
	//	"D:/GameEngine/Project/Term/TestProject/CSVRead/CSV/Chapter_1/1-1.csv");
	CCSVParser*		pCSVParser = new CCSVParser("../CSV/Chapter_1/1-15.csv");
	
	if (pCSVParser->LoadFile())
	{
		pCSVParser->ReadLine();
		cout << pCSVParser->GetString(0) << endl;
	}

	delete pCSVParser;

	return 0;
}

