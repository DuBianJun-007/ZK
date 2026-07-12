#include "benchmark.h"

double retrieval_algorithms_time::BM_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    BM bm = BM();

    auto start = std::chrono::high_resolution_clock::now();
    bm.bmMatch(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::BMH_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    BMH bmh = BMH();

    auto start = std::chrono::high_resolution_clock::now();
    bmh.BMH_match(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::Force_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    Force bf = Force();

    auto start = std::chrono::high_resolution_clock::now();
    bf.force(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::KMP_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    KMP kmp = KMP();

    auto start = std::chrono::high_resolution_clock::now();
    kmp.Kmp(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::QS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    Sunday sunday = Sunday();

    auto start = std::chrono::high_resolution_clock::now();
    sunday.qsearch(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::MS_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    Sunday sunday = Sunday();

    auto start = std::chrono::high_resolution_clock::now();
    sunday.sunday_MS_search(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::ZK2_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet)
{
    ZK2 zk2 = ZK2();

    auto start = std::chrono::high_resolution_clock::now();
    zk2.ZKSearch(TStr, PStr, TLen, PLen, charSet);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::ZK2_ascii_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen)
{
    ZK2_ascii zk2 = ZK2_ascii();

    auto start = std::chrono::high_resolution_clock::now();
    zk2.ZKSearch(TStr, PStr, TLen, PLen);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double retrieval_algorithms_time::ZK3_retrieval_time(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet)
{
    ZK3 zk3 = ZK3();

    auto start = std::chrono::high_resolution_clock::now();
    zk3.ZKSearch(TStr, PStr, TLen, PLen, charSet);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}
