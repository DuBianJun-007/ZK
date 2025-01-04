#pragma once
#define CHAR_SIZE   128
class BMH {
public:
    int* GenerateBC(const char* pat, int pLen);
    int BMH_match(const char* str, const char* pat,int ,int);
};