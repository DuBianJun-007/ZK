#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 128
#include <iostream>
struct Next2_ascii
{
	int start;
	int* PNext;
	int* TNext;
	int FNext[SIZE][SIZE];
};
class ZK2_ascii
{
private:
	Next2_ascii* next;
	Next2_ascii* ZKNext(const char* PStr, int PLen);
	int NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t);
	void FNext(const char* PStr, int start, int FNext[SIZE][SIZE]);
public:
	ZK2_ascii();
	ZK2_ascii(const char* TStr, const char* PStr, int TLen, int PLen) {
		next = ZKNext(PStr, PLen);
	}
	void build(const char* TStr, const char* PStr, int TLen, int PLen) {
		next = ZKNext(PStr, PLen);
	}
	/// <summary>
	/// This implementation builds auxiliary arrays through the ascii character set for retrieval
	/// </summary>
	/// <param name="TStr">the target text</param>
	/// <param name="PStr">the pattern text</param>
	/// <param name="TLen">Length of the target text</param>
	/// <param name="PLen">Length of the pattern text</param>
	/// <param name="charSet">character set, if NULL is filled, the character set is automatically obtained based on the pattern text</param>
	/// <returns>
	/// Returns the index of the pattern text in the target text, or 0 if none exists
	/// </returns>
	int ZKSearch(const char* TStr, const char* PStr, int TLen, int PLen);
};
