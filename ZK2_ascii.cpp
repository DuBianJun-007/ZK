#include "ZK2_ascii.h"
int ZK2_ascii::ZKSearch(const char* TStr, const char* PStr, int TLen, int PLen) {
	if (!TStr || !PStr) return 0;
	next = ZKNext(PStr, PLen);
	if (!next) return 0;
	int start = next->start, Ti = 0, Pi, n = 0;
	int* PNext = next->PNext, * TNext = next->TNext;
	int temp = TLen - PLen + 1;
	int lastLast = PLen - 2, last = PLen - 1;
	while (Ti < temp) {
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
		//Ti += max(next->FNext[TStr[Ti + lastLast]][TStr[Ti + last]], TNext[Pi]);
		if (Pi == start) {
			Ti += next->FNext[TStr[Ti + lastLast]][TStr[Ti + last]];
		}
		else {
			Ti += TNext[Pi];
		}
	}
	delete[]next->TNext;
	delete[]next->PNext;
	delete next;
	return n;
}
Next2_ascii* ZK2_ascii::ZKNext(const char* PStr, int PLen) {
	int  temp, P, Start, i, t = 1, num = 0, e = 0, TStart = 2;
	char F;
	int chars[SIZE];
	memset(chars, 0, sizeof(chars));
	Next2_ascii* next = new Next2_ascii;
	next->PNext = new int[PLen], next->TNext = new int[PLen];
	int* Sequence = new int[PLen];
	if (!Sequence || !next || !next->PNext || !next->TNext) return NULL;
	for (i = 0; i < PLen; i++) {
		Sequence[i] = 0;
		if ((temp = ++chars[PStr[i]]) >= num) {
			num = temp;
			next->start = i;
			F = PStr[i];
		}
	}
	FNext(PStr, PLen, next->FNext);
	if (num <= 1) {
		next->start = PLen - 1;
		for (int i = 0; i < PLen; i++) {
			next->TNext[i] = PLen;
			next->PNext[i] = i - 1;
		}
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
	delete[]Index;
	delete[]Distance;
	delete[]Sequence;
	return next;
}
int ZK2_ascii::NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t) {
	int SSP, OSP, T;
	for (T = TStart; T <= num; T++) {
		for (OSP = 1, SSP = Index[T]; OSP <= t - 2 && 0 <= (SSP -= Distance[OSP]); OSP++) {
			//if (SSP >= 0 && PStr[SSP] != F) {
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
void ZK2_ascii::FNext(const char* PStr, int PLen, int FNext[SIZE][SIZE]) {
	for (int j = 0; j < SIZE; j++) {
		int len = PStr[0] == j ? PLen - 1 : PLen;
		for (int i = 0; i < SIZE; i++)
			FNext[i][j] = len;
	}
	for (int i = 0; i <= PLen - 3; i++)
		FNext[PStr[i]][PStr[i + 1]] = PLen - 2 - i;
}

ZK2_ascii::ZK2_ascii()
{
}
