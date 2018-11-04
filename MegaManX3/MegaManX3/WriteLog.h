#pragma once
#include<iostream>
#include<fstream>

using namespace std;

#define FileName "TraceLog.txt"

class CWriteLog
{
	static CWriteLog* m_Instrance;
	CWriteLog();
public:
	static CWriteLog* GetInstrance();
	void Write(string szlog);
	~CWriteLog();
};

