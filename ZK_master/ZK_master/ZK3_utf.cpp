#include "ZK3_utf.h"
int ZK3_utf::ZKSearch(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet) {
	if (!TStr || !PStr) return 0;
	next = ZKNext(PStr, PLen, charSet);
	if (!next) return 0;
	int start = next->start, Ti = next->start, Pi = next->start, Len, first;
	int* PNext = next->PNext, * TNext = next->TNext;
	int lastLastLast = PLen - 3, lastLast = PLen - 2, last = PLen - 1;
	int right = TLen - PLen + 1,n = 0;
	while (Ti < right) {
		for (Pi = start; Pi != -1 && TStr[Ti + Pi] == PStr[Pi]; Pi = PNext[Pi]);
		if (Pi == -1) {
			//delete[]next->TNext;
			//delete[]next->PNext;
			//delete next;
			//return Ti;
			n++;
			Ti++;
			continue;
		}
		if (Pi == start) {
			Ti += next->FNext[next->hash[TStr[Ti + lastLastLast] - next->min]]
				[next->hash[TStr[Ti + lastLast] - next->min]]
			[next->hash[TStr[Ti + last] - next->min]];
		} else {
			Ti += TNext[Pi];
		}
	}
	delete[]next->TNext;
	delete[]next->PNext;
	delete next;
	return n;
}
Next3_utf* ZK3_utf::ZKNext(const char* PStr, int PLen, const char* charSet) {
	Next3_utf* next = new Next3_utf;
	next->max = INT_MIN;
	next->min = INT_MAX;
	if (!charSet)
	{
		for (int i = 0; i < PLen; i++) {
			if (PStr[i] > next->max) next->max = PStr[i];
			if (PStr[i] < next->min) next->min = PStr[i];
		}
	}
	else {
		for (int i = 0; i < strlen(charSet); i++) {
			if (charSet[i] > next->max) next->max = charSet[i];
			if (charSet[i] < next->min) next->min = charSet[i];
		}
	}
	int  temp, P, Start, i, t = 1, num = 0, e = 0, TStart = 2, SIZE = next->max - next->min + 1;;
	char F;
	bool characterBool = false;
	int* chars = new int[SIZE];
	int* charactersJudge = new int[SIZE];
	char* characters;
	next->hash = new int[SIZE];
	next->PNext = new int[PLen], next->TNext = new int[PLen];
	int* Sequence = new int[PLen];
	if (!Sequence || !next || !next->PNext || !next->TNext) return NULL;
	for (int i = 0; i < SIZE; i++) {
		charactersJudge[i] = 0;
		chars[i] = 0;
	}
	if (charSet) {
		characterBool = true;
		e = strlen(charSet);
		characters = new char[e + 1];
		if (!characters) return NULL;
		strcpy(characters, charSet);
	}
	else
		characters = new char[SIZE + 1];
	if (!characters) return NULL;
	for (i = 0; i < PLen; i++) {
		Sequence[i] = 0;
		if (!characterBool && charactersJudge[PStr[i]] == 0) {
			charactersJudge[PStr[i]] = 1;
			characters[e++] = PStr[i];
		}
		if ((temp = ++chars[PStr[i] - next->min]) >= num) {
			num = temp;
			next->start = i;
			F = PStr[i];
		}
	}
	FNext(PStr, characters, e, PLen,next);
	if (num <= 1) {
		next->start = PLen - 1;
		for (int i = 0; i < PLen; i++) {
			next->TNext[i] = PLen;
			next->PNext[i] = i - 1;
		}
		delete[]characters;
		delete[]Sequence;
		return next;
	}
	int* Index = new int[num + 1], * Distance = new int[num];
	if (!Index || !Distance) return NULL;
	P = i = next->start;
	Index[t] = i;
	Sequence[i] = 1;
	for (t++, i--; t <= num; i--) {
		if (PStr[i] == F) {
			Index[t] = i;
			Distance[t - 1] = Index[t - 1] - i;
			Sequence[i] = 1;
			P = next->PNext[P] = i;
			t++;
		}
	}
	next->TNext[Index[2]] = Index[1] - Index[2];
	for (t = 3; t <= num; t++) {
		if (TStart != num + 1)
			Start = NextStart(Index, Distance, Sequence, TStart, num, t);
		next->TNext[Index[t]] = Start;
	}
	if (TStart != num + 1)
		Start = NextStart(Index, Distance, Sequence, TStart, num, num + 1);
	for (i = PLen - 1; i >= 0; i--) {
		if (!Sequence[i]) {
			next->PNext[P] = i;
			P = i;
			next->TNext[i] = Start;
		}
	}
	next->PNext[P] = -1;
	delete[]characters;
	delete[]Index;
	delete[]Distance;
	delete[]Sequence;
	return next;
}
int ZK3_utf::NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t) {
	int SSP, OSP, T;
	for (T = TStart; T <= num; T++) {
		for (OSP = 1, SSP = Index[T]; OSP <= t - 2 && 0 <= (SSP -= Distance[OSP]); OSP++) {
			if (SSP >= 0 && Sequence[SSP] != 1) {
				OSP = -1;
				break;
			}
		}
		if (OSP != -1) return Index[1] - Index[TStart = T];
	}
	TStart = T;
	return Index[1] + 1;
}
void ZK3_utf::FNext(const char* PStr, const char* characters, int e, int PLen, Next3_utf* next) {
	next->FNext = new int** [e];
	for (int i = 0; i < e; i++)
	{
		next->hash[characters[i] - next->min] = i;
		next->FNext[i] = new int* [e];
		for (int j = 0; j < e; j++)
			next->FNext[i][j] = new int[e];
	}
	for (int k = 0; k < e; k++)
		for (int j = 0; j < e; j++) {
			int len = PStr[0] == characters[j] && PStr[1] == characters[k] ? PLen - 2 : PStr[0] == characters[k] ? PLen - 1 : PLen;
			for (int i = 0; i < e; i++)
				next->FNext[next->hash[characters[i] - next->min]][next->hash[characters[j] - next->min]][next->hash[characters[k] - next->min]] = len;
		}
	for (int i = 0; i <= PLen - 4; i++)
		next->FNext[next->hash[PStr[i] - next->min]][next->hash[PStr[i + 1] - next->min]][next->hash[PStr[i + 2] - next->min]] = PLen - 3 - i;
}

ZK3_utf::ZK3_utf()
{
}
