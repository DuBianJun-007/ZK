#include "ZK2.h"

int ZK2::ZKSearch(const char* TStr, const char* PStr, int TLen, int PLen, const char* charSet) {
	if (!TStr || !PStr) return 0;
	next = ZKNext(PStr, PLen, charSet);
	if (!next) return 0;
	int start = next->start, Ti = 0, Pi,n = 0;
	int* PNext = next->PNext, * TNext = next->TNext;
	int temp = TLen - PLen + 1;
	int lastLast = PLen - 2, last = PLen - 1;

	//printf("\nPStr: ");
	//for (int i = 0; i < PLen; i++) {
	//	printf("%c", PStr[i]);
	//}
	//printf("\n");
	//printf("Next2 Structure:\n");
	//printf("start: %d\n", next->start);
	//printf("\n PLen: %d PNext: \n", PLen);
	//if (next->PNext) {
	//	for (int i = 0; i < PLen; i++) {
	//		printf("%d ", next->PNext[i]);
	//	}
	//	printf("\n");
	//}
	//printf("\n PLen: %d TNext: \n", TLen);
	//if (next->TNext) {
	//	for (int i = 0; i < PLen; i++) {
	//		printf("%d ", next->TNext[i]);
	//	}
	//	printf("\n TNext end! \n");
	//}
	//printf("\nFNext:\n");
	//for (int i = 0; i < SIZE; i++) {
	//	for (int j = 0; j < SIZE; j++) {
	//		printf("%d ", next->FNext[i][j]);
	//	}
	//	printf("\n");
	//}


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
			//printf("\n 1:%c  2:%c   next->FNext: %d \n", TStr[Ti + lastLast], TStr[Ti + last], next->FNext[TStr[Ti + lastLast]][TStr[Ti + last]]);
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
Next2* ZK2::ZKNext(const char* PStr, int PLen, const char* charSet) {
	int  temp, P, Start, i, t = 1, num = 0, e = 0, TStart = 2;
	char F;
	bool characterBool = false;
	int chars[SIZE];
	int charactersJudge[SIZE];
	char* characters;
	Next2* next = new Next2;
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
		if ((temp = ++chars[PStr[i]]) >= num) {
			num = temp;
			next->start = i;
			F = PStr[i];
		}
	}
	FNext(PStr, characters, e, PLen, next->FNext);
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
int ZK2::NextStart(int Index[], int Distance[], int Sequence[], int& TStart, int num, int t) {
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
void ZK2::FNext(const char* PStr, const char* characters, int e, int PLen, int FNext[SIZE][SIZE]) {
	for (int j = 0; j < e; j++) {
		int len = PStr[0] == characters[j] ? PLen - 1 : PLen;
		for (int i = 0; i < e; i++)
			FNext[characters[i]][characters[j]] = len;
	}
	for (int i = 0; i <= PLen - 3; i++)
		FNext[PStr[i]][PStr[i + 1]] = PLen - 2 - i;
}

ZK2::ZK2()
{

}
