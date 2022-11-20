#include "BMH.h"
#include<iostream>
int* BMH::GenerateBC(const char* pat, int pLen)
{
    int* bc = (int*)malloc(CHAR_SIZE * sizeof(int));
    if (bc == NULL)  return NULL;
    memset(bc, -1, CHAR_SIZE * sizeof(int));
    for (int i = 0; i < pLen; ++i) {
        int ascii = (int)pat[i];
        bc[ascii] = i;
    }
    return bc;
}

int BMH::BMH_match(const char* str, const char* pat, int sLen, int pLen)
{
    if (str == NULL || pat == NULL)
        return NULL;

    int* bc = GenerateBC(pat, pLen);
    if (bc == NULL)
        return NULL;

    int i = 0, j = pLen - 1, n = 0;
    while (i <= sLen - pLen) {
        for (j = pLen - 1; j >= 0; --j) {
            if (str[i + j] != pat[j])
                break;
        }
        if (j < 0) {
            i++;
            n++;
            continue;
            //free(bc);  
            //return i;
        }
        j = pLen - 1;
        if (bc[(int)str[i + j]] < j) {
            i += j - bc[(int)str[i + j]];
        }
        else {
            i++;
        }
    }
    free(bc);
    return n;
}
