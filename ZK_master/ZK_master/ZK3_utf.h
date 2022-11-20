#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
struct Next3_utf
{
	int start, max, min;
	int* PNext;
	int* TNext;
	int*** FNext;
	int* hash;
};
class ZK3_utf
{
private:
	Next3_utf* next;
	Next3_utf* ZKNext(const char* PStr, int PLen, const char* charSet);
	int NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t);
	void FNext(const char* PStr, const  char* characters, int e, int start, Next3_utf* next);
public:
	ZK3_utf();
	ZK3_utf(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet = NULL) {
		next = ZKNext(PStr, PLen, charSet);
	}
	void build(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet = NULL) {
		next = ZKNext(PStr, PLen, charSet);
	}
	/// <summary>
	/// This implementation applies to any character set and requires the programmer to pass in the character set of the retrieved object
	/// </summary>
	/// <param name="TStr">the target text</param>
	/// <param name="PStr">the pattern text</param>
	/// <param name="TLen">Length of the target text</param>
	/// <param name="PLen">Length of the pattern text</param>
	/// <param name="charSet">character set, if NULL is filled, the character set is automatically obtained based on the pattern text</param>
	/// <returns>
	/// Returns the index of the pattern text in the target text, or 0 if none exists
	/// </returns>
	int ZKSearch(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet = NULL);
};

