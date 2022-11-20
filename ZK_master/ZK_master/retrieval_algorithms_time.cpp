#include "retrieval_algorithms_time.h"

double retrieval_algorithms_time::BM_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	BM	bm = BM();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	bm.bmMatch(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::BMH_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	BMH	bmh = BMH();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	bmh.BMH_match(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::Force_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	Force bf = Force();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	bf.force(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::KMP_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	KMP	kmp = KMP();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	kmp.Kmp(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::QS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	Sunday sunday = Sunday();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	sunday.qsearch(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::MS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	Sunday sunday = Sunday();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	sunday.sunday_MS_search(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::ZK2_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet)
{
	ZK2	zk2 = ZK2();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	zk2.ZKSearch(TStr, PStr, TLen, PLen, charSet);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::ZK2_ascii_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
	ZK2_ascii	zk2 = ZK2_ascii();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	zk2.ZKSearch(TStr, PStr, TLen, PLen);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}

double retrieval_algorithms_time::ZK3_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet)
{
	ZK3	zk3 = ZK3();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//start time

	// retrieval body
	zk3.ZKSearch(TStr, PStr, TLen, PLen, charSet);

	QueryPerformanceCounter(&nEndTime);//end time
	return (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;
}
