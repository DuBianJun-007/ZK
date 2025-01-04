#include "Sunday.h"
#include <algorithm>
#include <iostream>
int* MinShift;
using namespace std;
int* getMinShift(const char* pstr, int PLen) {
	int* MinShift = new int[PLen];
	int j, i;
	for (i = 0; i < PLen; ++i) {
		for (j = i - 1; j >= 0; --j) {
			if (pstr[j] == pstr[i]) break;
		}
		MinShift[i] = i - j;
	}
	return MinShift;
}
int pcmp(const void* pat1, const void* pat2) {
	int dsh = MinShift[((PAT*)pat2)->loc] - MinShift[((PAT*)pat1)->loc];
	return (dsh ? dsh : (((PAT*)pat2)->loc - ((PAT*)pat1)->loc));
}
int Sunday::optimal_pcmp(const void* pat1, const void* pat2) {
	float fx = Freq[((PAT*)pat1)->c] - Freq[((PAT*)pat2)->c];
	return (fx ? (fx > 0 ? 1 : -1) : (((PAT*)pat2)->loc - ((PAT*)pat1)->loc));
}
void order_pattern(const char* pstr, int PLen, PAT* pattern) {
	PAT* pat = pattern;
	MinShift = getMinShift(pstr, PLen);
	for (int i = 0; i <= PLen; i++, ++pstr, ++pat) {
		pat->loc = i;
		pat->c = *pstr;
	}
	qsort(pattern, PLen, sizeof(PAT), pcmp);
}

void Sunday::build_TD1(const char* pstr, int PLen) {
	int i;
	const char* p;
	for (i = 0; i < ASCII; i++)
		TD1[i] = PLen + 1;
	for (p = pstr; *p; p++)
		TD1[*p] = PLen - (p - pstr);
}

void Sunday::build_TD2(const char* pstr, PAT* pattern, int PLen) {
	int lshift, i, ploc;
	TD2[0] = lshift = 1;
	const char* p = pstr;
	for (ploc = 1; ploc < PLen; ++ploc) {
		lshift = matchshift(p, pattern, ploc, lshift, PLen);
		TD2[ploc] = lshift;
	}
	for (ploc = 0; ploc < PLen; ++ploc) {
		lshift = TD2[ploc];
		while (lshift < PLen) {
			i = (pattern[ploc].loc - lshift);
			if (i < 0 || pattern[ploc].c != p[i])break;
			++lshift;
			lshift = matchshift(p, pattern, ploc, lshift, PLen);
		}
		TD2[ploc] = lshift;
	}
}

int Sunday::matchshift(const char* pstr, PAT* pattern, int ploc, int lshift, int PLen) {
	PAT* pat;
	int j;
	for (; lshift < PLen; ++lshift) {
		pat = pattern + ploc;
		while (--pat >= pattern) {
			if ((j = (pat->loc - lshift)) < 0)continue;
			if (pat->c != pstr[j]) break;
		}
		if (pat < pattern)break;
	}
	return lshift;
}

int Sunday::sunday_MS_search(const char* text, const char* pstr, int TLen, int PLen) {
	order_pattern(pstr, PLen, pattern);
	build_TD1(pstr, PLen);
	build_TD2(pstr, pattern, PLen);
	PAT* p;
	const char* tx = text;
	int d1, d2, n = 0;
	const char* t = text - 1;
	while (tx + PLen <= text + TLen) {
		for (p = pattern; p->c; ++p) {
			if (p->c != *(tx + (p->loc))) break;
		}
		if (p->c == 0) {
			tx += 1;
			n++;
			continue;
			//return (tx - text); 
		}
		d1 = TD1[*(tx + PLen)];
		d2 = TD2[p - pattern];
		tx += d1 > d2 ? d1 : d2;
	}

	return n;
}

int Sunday::qsearch(const char* text, const char* pstr, int TLen, int PLen) {
	build_TD1(pstr, PLen);
	const char* p;
	const char* t, * tx = text;
	int n = 0;
	while (tx + PLen <= text + TLen) {
		for (p = pstr, t = tx; *p; ++p, ++t) {
			if (*p != *t) break;
		}
		if (*p == 0) {
			tx += 1;
			n++;
			continue;
			//return (tx - text); 
		}
		tx += TD1[*(tx + PLen)];
	}
	return n;
}
Sunday::Sunday()
{
}

Sunday::~Sunday()
{
}