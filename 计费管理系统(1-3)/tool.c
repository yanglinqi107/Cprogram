#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<stdio.h>
void timeToString(time_t t, char* pBuf)
{
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}
