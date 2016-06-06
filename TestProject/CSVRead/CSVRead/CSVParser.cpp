#include "stdafx.h"
#include "CSVParser.h"


CCSVParser::CCSVParser(string _strPath)
: m_strPath(_strPath)
{
}

CCSVParser::~CCSVParser()
{
	CloseFile();
}

bool CCSVParser::LoadFile()
{
	m_tFile.open(m_strPath, ios::in);

	if (m_tFile.fail())
		return false;

	return true;
}

void CCSVParser::ReadLine()
{
	string strLine;
	m_vecString.clear();

	while (getline(m_tFile, strLine, ','))
		m_vecString.push_back(strLine);
}

void CCSVParser::CloseFile()
{
	m_tFile.close();
	m_tFile.seekg(ios::beg);
	m_vecString.clear();
}

string CCSVParser::GetString(int _iIdx)
{
	return m_vecString[_iIdx];
}

int CCSVParser::GetInt(int _iIdx)
{
	string strTmp = m_vecString[_iIdx];

	if ("" == strTmp || strTmp.empty())
		return -1;

	return atoi(strTmp.c_str());
}

float CCSVParser::GetFloat(int _iIdx)
{
	string strTmp = m_vecString[_iIdx];

	if ("" == strTmp || strTmp.empty())
		return -1;

	return (float)(atof(strTmp.c_str()));
}

