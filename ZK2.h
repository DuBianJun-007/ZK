#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 128
#include <iostream>
struct Next2
{
	int start;
	int* PNext;
	int* TNext;
	int FNext[SIZE][SIZE];
};
class ZK2
{
private:
	Next2* next;
	Next2* ZKNext(const char* PStr, int PLen, const char* charSet);
	int NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t);
	void FNext(const char* PStr, const  char* characters, int e, int start, int FNext[SIZE][SIZE]);
public:
	ZK2();
	ZK2(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet = NULL) {
		next = ZKNext(PStr, PLen, charSet);
	}
	void build(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet = NULL) {
		next = ZKNext(PStr, PLen, charSet);
	}
	/// <summary>
	/// This implementation indicates that the programmer already knows the exact character set of 
	/// the retrieved object, and then, the exact auxiliary array is created from the known character set
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
