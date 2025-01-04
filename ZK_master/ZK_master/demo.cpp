//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <windows.h>
//#include <vector>
//#include <direct.h>  
//#include <stdio.h> 
//#include "BM.h"
//#include "BMH.h"
//#include "Force.h"
//#include "KMP.h"
//#include "Sunday.h"
//#include "ZK2.h"
//#include "ZK3.h"
//#include "ZK2_utf.h"
//#include "ZK3_utf.h"
//#include "retrieval_algorithms_time.h"
//using namespace std;
//
//int PLen, TLen;
//const char* TStr;
//const char* PStr;
//string TStrTemp;
//string temp;
//int MatchCnt[9];
//vector<string> rs;
//BM bm = BM();
//BMH bmh = BMH();
//Force bf = Force();
//KMP	kmp = KMP();
//Sunday sunday = Sunday();
//ZK2	zk2 = ZK2();
//ZK3	zk3 = ZK3();
//ZK2_ascii zk2_ascii = ZK2_ascii();
//ZK2_utf	zk2_utf = ZK2_utf();
//ZK3_utf	zk3_utf = ZK3_utf();
//retrieval_algorithms_time rat = retrieval_algorithms_time();
//
//void  randomTStr(int CharsetSet_start, int CharsetSet_end, int Length) {
//	srand((unsigned int)time(NULL));
//	int range = CharsetSet_end - CharsetSet_start + 1;
//	for (int i = 0; i < Length; i++)//Target string generation
//	{
//		int r = rand() % range + CharsetSet_start;
//		TStrTemp += (char)r;
//	}
//	TStr = TStrTemp.c_str();
//}
//
//const char* itoa(int val)
//{
//	static char result[sizeof(int) << 3 + 2];
//	unsigned int tempval = val;
//	if (val < 0) tempval = -val;
//	int i = sizeof(int) << 3 + 1;
//	do {
//		result[i] = "0123456789"[tempval % 10];
//		tempval /= 10; --i;
//	} while (tempval);
//	if (val < 0) result[i--] = '-';
//	return &result[i + 1];
//}
//
//void read(string Path) {
//	const char* path = Path.c_str();
//	ifstream infile;
//	infile.open(path);
//	if (!infile)
//	{
//		cout << "infile failed to open" << endl;
//		exit(1);
//	}
//	while (!infile.eof())
//	{
//		infile >> temp;
//		TStrTemp += temp;
//	}
//	infile.close();
//}
//
///// <summary>
///// The gene file (multiple files) is read, build TStr
///// </summary>
//void  geneTStr() {
//	char* c = NULL;
//	char filename_body[10];
//	for (int i = 1; i <= 18; i++)
//	{
//		string filename = _getcwd(c, NULL);
//		filename = filename.substr(0, filename.find_last_of("'\\'"));
//		filename = filename + "\\gene_data\\chr";
//		memset(filename_body, 0, sizeof(filename_body));		//Copy character
//		filename += itoa(i);
//		string filename_tail = ".fna";
//		filename += filename_tail;
//		cout << filename << endl;
//		read(filename);
//	}
//	TStr = TStrTemp.c_str();
//}
//
///// <summary>
///// words (single file) read, build TStr
///// </summary>
//void wordsTStr() {
//	char* c = NULL;
//	char filename_body[10];
//	string filename = _getcwd(c, NULL);
//	filename = filename.substr(0, filename.find_last_of("'\\'"));
//	filename = filename + "\\words";
//	memset(filename_body, 0, sizeof(filename_body));		//Copy character
//	string filename_tail = ".txt";
//	filename += filename_tail;
//	cout << "file path:   " << filename << endl;
//	read(filename);
//
//	TStr = TStrTemp.c_str();
//}
//void Runthealgorithm(int cnt, const char* charSet) {
//	string d = TStrTemp.substr(rand() % TStrTemp.length(), cnt);
//	PStr = d.c_str();
//	TLen = TStrTemp.length();
//	PLen = d.length();
//	cout << "TLen: " << TLen << "      " << "PLen: " << PLen << endl;
//	cout << endl << "Program running";
//	MatchCnt[0] = bm.bmMatch(TStr, PStr, TLen, PLen);				cout << ".";
//	MatchCnt[1] = bmh.BMH_match(TStr, PStr, TLen, PLen);			cout << ".";
//	MatchCnt[2] = bf.force(TStr, PStr, TLen, PLen);					cout << ".";
//	MatchCnt[3] = kmp.Kmp(TStr, PStr, TLen, PLen);					cout << ".";
//	MatchCnt[4] = sunday.qsearch(TStr, PStr, TLen, PLen);			cout << ".";
//	MatchCnt[5] = sunday.sunday_MS_search(TStr, PStr, TLen, PLen);  cout << ".";
//	MatchCnt[6] = zk2.ZKSearch(TStr, PStr, TLen, PLen, charSet);	cout << ".";
//	MatchCnt[7] = zk3.ZKSearch(TStr, PStr, TLen, PLen, charSet);    cout << ".";
//	MatchCnt[8] = zk2_ascii.ZKSearch(TStr, PStr, TLen, PLen);		cout << ".";
//	cout << endl << endl;
//
//	cout << "Time of algorithm BM:        " << rat.BM_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[0] << endl;
//	cout << "Time of algorithm BMH:       " << rat.BMH_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[1] << endl;
//	cout << "Time of algorithm Force:     " << rat.Force_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[2] << endl;
//	cout << "Time of algorithm KMP:       " << rat.KMP_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "   Number of successful matches: " << MatchCnt[3] << endl;
//	cout << "Time of algorithm QS:        " << rat.QS_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[4] << endl;
//	cout << "Time of algorithm MS:        " << rat.MS_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[5] << endl;
//	cout << "Time of algorithm ZK2:       " << rat.ZK2_retrieval_time(TStr, PStr, TLen, PLen, charSet) << " ms" << "    Number of successful matches: " << MatchCnt[6] << endl;
//	cout << "Time of algorithm ZK3:       " << rat.ZK3_retrieval_time(TStr, PStr, TLen, PLen, charSet) << " ms" << "    Number of successful matches: " << MatchCnt[7] << endl;
//	cout << "Time of algorithm ZK2_ascii: " << rat.ZK2_ascii_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[8] << endl;
//
//	cout << endl << "===================================================================================================================" << endl;
//}
//
//int main() {
//	/// <summary>
//	/// Algorithm running function
//	/// </summary>
//	/// <param name="cnt1">the length of the pattern string</param>
//	/// <param name="cnt2">Randomly generates the length of the target string</param>
//	int cnt1, cnt2;
//	cout << "Please enter the length of the pattern string" << endl;
//	cin >> cnt1;
//
//	cout << "Please enter the length of the target string" << endl;
//	cin >> cnt2;
//	if (cnt2 < cnt1) {
//		cout << "The TLen needs to be greater than the PLen!" << endl;
//		exit(1);
//	}
//
//	const char* charSet_default = "abcdefghijklmnopqrstuvwxyz";
//	//The default character set is a - z
//	randomTStr('a', 'z', cnt2);
//	Runthealgorithm(cnt1, charSet_default);
//
//	// Character set of the words file
//	const char* charSet = "!&'_-,./0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	wordsTStr();
//	Runthealgorithm(cnt1, charSet);
//
//	// The gene file character set is a - z
//	const char* charSet_gene = "!&'_-,./0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	geneTStr();
//	Runthealgorithm(cnt1, charSet_gene);
//
//	return 0;
//}
//
