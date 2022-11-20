#include "Force.h"
int Force::force(const char* TStr, const char* PStr, int TLen, int PLen)
{
	int c = 0, d = 0,n = 0;
	while (c != TLen) {
		while (c < TLen && d < PLen) {
			if (TStr[c] == PStr[d]) {
				c++; d++;
			}
			else {
				c = c - d + 1;
				d = 0;
			}
		}
		if (d == PLen) {
			c = c - d + 1;
			d = 0;
			n++;
			//return c - d;
		}
		else
			break;
	}
	return n;
}
