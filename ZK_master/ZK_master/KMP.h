#pragma once
class KMP
{
public:
	int* getNext(const char* PStr,int len);
	int Kmp(const char* TStr, const char* PStr, int TLen, int PLen);
};
