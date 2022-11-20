#include "BM.h"
#define max(a,b)            (((a) > (b)) ? (a) : (b))
int BM::bmMatch(const char* text, const char* pat, int TLen, int PLen)
{
	int* bc = getBc(pat, PLen);
	int* gs = getGs(pat, PLen);
	int patAt = 0, n = 0;
	int cmp;
	const int PATLASTID = PLen - 1, patLen = PLen, textLen = TLen;
	int t1, t2;
	while (patAt + patLen <= textLen)
	{
		for (cmp = PATLASTID; cmp >= 0 && pat[cmp] == text[patAt + cmp]; --cmp);
		if (cmp == -1) {
			//delete[] bc;
			//delete[] gs;
			//return patAt;
			patAt++;
			n++;
		}
		else {
			//patAt += max(gs[cmp], cmp - bc[text[patAt + cmp]]);
			t1 = gs[cmp];
			t2 = cmp - bc[text[patAt + cmp]];
			patAt += t1 > t2 ? t1 : t2;
		}
	}
	delete[] bc;
	delete[] gs;
	return n;
}
int* BM::getBc(const char* pattern, int PLen) {
	int* bc = new int[256];
	int len = PLen;
	for (int i = 0; i < 256; ++i)
		bc[i] = -1;
	for (int i = 0; i < len; ++i) {
		bc[pattern[i]] = i;
	}
	return bc;
}
int* BM::suffixes(const char* pat, int PLen)
{
	const int len = PLen;
	int num;
	int* suff = new int[len];
	suff[len - 1] = len;
	for (int i = len - 2; i >= 0; --i)
	{
		for (num = 0; num <= i && pat[i - num] == pat[len - num - 1]; ++num);
		suff[i] = num;
	}
	return suff;
}
int* BM::getGs(const char* pat, int PLen)
{
	const int len = PLen;
	const int lastIndex = len - 1;
	int* suffix = suffixes(pat, PLen);
	int* gs = new int[len];
	for (int i = 0; i < len; ++i)
		gs[i] = len;
	for (int i = lastIndex; i >= 0; --i)
	{
		if (suffix[i] == i + 1)
		{
			for (int j = 0; j < lastIndex - i; ++j)
			{
				if (gs[j] == len)
					gs[j] = lastIndex - i;
			}
		}
	}
	for (int i = 0; i < lastIndex; ++i)
	{
		gs[lastIndex - suffix[i]] = lastIndex - i;
	}
	delete[] suffix;
	return gs;
}
BM::BM()
{
}

BM::~BM()
{
}