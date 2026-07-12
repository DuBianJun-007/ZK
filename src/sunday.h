#pragma once

typedef struct pattern_scan_element {
    int loc;
    char c;
} PAT;


class Sunday
{
public:
    Sunday();
    ~Sunday();
    int sunday_MS_search(const char* text, const char* pstr, int TLen, int PLen); // MS
    int qsearch(const char* text, const char* pstr, int TLen, int PLen);          // QS
private:
    int optimal_pcmp(const void* pat1, const void* pat2);
    void build_TD1(const char* pstr, int PLen);
    void build_TD2(const char* pstr, PAT* pattern, int PLen);
    int matchshift(const char* pstr, PAT* pattern, int ploc, int lshift, int PLen);

    static const int MAXPAT = 20000;
    static const int ASCII = 256;
    float* Freq;
    PAT* pattern;
    int* TD2;
    int* TD1;
};
