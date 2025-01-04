#pragma once
typedef struct pattern_scan_element {
	int loc;
	char c;
}PAT;


class Sunday
{
public:
	Sunday();
	~Sunday();
	int sunday_MS_search(const char* text, const char* pstr, int TLen, int PLen); // MS
	int qsearch(const char* text, const char* pstr, int TLen, int PLen); //QS
private:
	int optimal_pcmp(const void* pat1, const void* pat2);
	void build_TD1(const char* pstr, int PLen);
	void build_TD2(const char* pstr, PAT* pattern, int PLen);
	int matchshift(const char* pstr, PAT* pattern, int ploc, int lshift, int PLen);
private:
	const int MAXPAT = 20000;
	const int ASCII = 256;
	float *Freq = new float[ASCII];
	PAT *pattern = new PAT[MAXPAT];
	int *TD2 = new int[MAXPAT];
	int *TD1 = new int[ASCII];
};

