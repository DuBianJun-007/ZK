#pragma once

#include <chrono>
#include "bm.h"
#include "bmh.h"
#include "force.h"
#include "kmp.h"
#include "sunday.h"
#include "zk2.h"
#include "zk2_ascii.h"
#include "zk3.h"
#include "zk2_utf.h"
#include "zk3_utf.h"


/// <summary>
/// Use high-precision timing methods to obtain the actual retrieval time of the algorithm
/// </summary>
class retrieval_algorithms_time
{
public:
    retrieval_algorithms_time() {};

    double BM_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double BMH_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double Force_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double KMP_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double QS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double MS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double ZK2_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet);
    double ZK2_ascii_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen);
    double ZK3_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet);
};
