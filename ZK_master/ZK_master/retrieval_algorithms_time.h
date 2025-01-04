#pragma once

#include <windows.h>
#include "BM.h"
#include "BMH.h"
#include "Force.h"
#include "KMP.h"
#include "Sunday.h"
#include "ZK2.h"
#include "ZK2_ascii.h"
#include "ZK3.h"
#include "ZK2_utf.h"
#include "ZK3_utf.h"


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