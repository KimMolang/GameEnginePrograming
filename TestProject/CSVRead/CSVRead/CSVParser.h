#pragma once


#include <fstream>

class CCSVParser
{
public : // about File
	bool LoadFile();
	void ReadLine();
	void CloseFile();

public : // about Sell
	string	GetString(int _iIdx);
	int		GetInt(int _iIdx);
	float	GetFloat(int _iIdx);


public :
	explicit CCSVParser(string _strPath);
	~CCSVParser();

private:
	string				m_strPath;
	fstream				m_tFile;
	vector<string>		m_vecString;
};

