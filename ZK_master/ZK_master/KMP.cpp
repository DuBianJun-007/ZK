#include "KMP.h"
int* KMP::getNext(const char* PStr,int PLen)
{
	int* next = new int[PLen],c = 0, d = -1;
	next[0] = -1;
	while (c < PLen - 1)
		if (d == -1 || PStr[c] == PStr[d]) {
			c++; d++;
			next[c] = (PStr[c] != PStr[d] ? d : next[d]);
		}else
			d = next[d];
	return next;
}

int KMP::Kmp(const char* TStr, const char* PStr, int TLen, int PLen)
{
	int* next = getNext(PStr,PLen);
	int c = 0, d = 0, n = 0;
	while (c != TLen)
	{
		while (c < TLen && d < PLen) {
			if (d == -1 || TStr[c] == PStr[d]) {
				c++; d++;
			}
			else {
				d = next[d];
			}
		}
		if (d == PLen)
		{
			c = c - d + 1;
			d = 0;
			n++;
			//return c - d;
		}
		else
			break;
	}
	delete next;
	return n;
}
