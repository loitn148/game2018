#define _CRT_SECURE_NO_WARNINGS
#include "WriteLog.h"
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>



CWriteLog* CWriteLog::m_Instrance = NULL;

CWriteLog::CWriteLog()
{
}

void CWriteLog::Write(string szlog)
{
	fstream f;
	f.open(FileName, ios::app);
	if (f.is_open())
	{
		using namespace std::chrono;

		duration<int, std::ratio<60 * 60 * 24> > one_day(1);

		system_clock::time_point today = system_clock::now();

		time_t tt;

		tt = system_clock::to_time_t(today);
		string time(ctime(&tt));
		time.erase(time.length() - 1);
		f << time;
		f << ": " << szlog << endl;
		f.close();
	}
}

CWriteLog* CWriteLog::GetInstrance()
{
	if (m_Instrance == NULL)
	{
		m_Instrance = new CWriteLog();
	}
	return m_Instrance;
}

CWriteLog::~CWriteLog()
{
}
