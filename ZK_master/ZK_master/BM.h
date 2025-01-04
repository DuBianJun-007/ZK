#pragma once

class BM
{
public:
	BM();
	~BM();
	int bmMatch(const char* text, const char* pat, int TLen, int PLen);
private:
	int* getBc(const char* pattern, int PLen);
	int* suffixes(const char* pat, int PLen);
	int* getGs(const char* pat, int PLen);
};

