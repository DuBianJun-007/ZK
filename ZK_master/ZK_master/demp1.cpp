#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <vector>
#include <direct.h>  
#include <stdio.h> 
#include "BM.h"
#include "BMH.h"
#include "Force.h"
#include "KMP.h"
#include "Sunday.h"
#include "ZK2.h"
#include "ZK3.h"
#include "ZK2_utf.h"
#include "ZK3_utf.h"
#include "retrieval_algorithms_time.h"
using namespace std;

int PLen, TLen;
const char* TStr = "tctactttactcccttctttcacaagatggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgacggggactaccctgtactccgaccggagagatgatcggtattctcgtttacaaagaaggtttacttgtatgactgagagagttttcttgtggtttcgtttatcgttttcttgtggtttcgtttatcgtttctaaaccgaacagtcaatggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgacttcggattttcaccaataatatttggtttctaaaccgaacagtcaattcggatccgaaccctacaaatccttcatacaaatatcaaacaatatacaaattatattctgtatttttcaccaataatatttgatttcagtgatcagaaaatattgaaagtgtggttttggaaataatatctaattgaatatcacattgtacgttgttatcaatcaatcatctactaaaggggtgtagaagttgtaatcacttaggaatgggctagaatgatgaggatggatccatgtatgcatgaattgctcctagtcttagatatattttgcataatgatcaaactccttgatttttcagtgttactcccttctttcaaaggggtgtagaagttgtaatcacttaggaatgggctagaatgatgaggatggatccatgtatgcatgaattgctcctagtcttagatatattttgcataatgatcaaactccttgatttttcagtgacaagaggggactaccctgtactccgaccggagagatgatcggagtttttgattgatacacatctactttactcccttctttcacaagaggggactaccctgtactccgaccggagagatgatcggagtttttgattgatacacatcaaaagccgcctgttttcttgtggtttcgtttatcgtttctaaaccgaacagtaagtctttcctccgaattgctggtgagcggatcgcagacctgttagtgtaaaactgatcaggtctgttataatccccaagcgtttggtggttctccgacccagcattcaaaacaacggcgcatactcgatttcagccctaggtttataattaatttgacgtgatgcattgcatactcgattatctagatatcctagaactactttcccataattgaaattggtaagcacagacttacctgcttccggctggtcggcgtcgatcgatttgtttagcccatcgtcgatcgatttttgttgatctgcgtcgatcgattgcagtatggaagtgtcgatcgatttgtccgtcgattcgtcgctcgatgtctccgtcatcttgtcgatcgatgctcggccgaacttgtgttcctcttcttaagttcctgtgtcagtaaggaaagaagaaaaacttttaaataaacagtaagtaaaatctagactatattctaaacttaatctaatggcaataagaaagagtccctggcaacgccgccaaatttgatatcactcaaattaccctaaggagtgactttactctcttaaataagaggttcagctgtagtacttagggatcgaatccacaaagactctaagattacacaatagattgtatagtcttcgaaataaagctagataggtaagttttaaacagtaaattaaatggtgagcaagtcagttgctcgattgatttgatttgaggttgttaacagaaggaaaggtagctagattcatgtattatctcaggttcgacaagtatgcaagttaattagggtttttactattcatagttctgaactcaaactttaggtttaatcgaatcaattaccttcaactggatctcggatcatgaactatcgatcgatgatcataagaaagtgtcgatcgattattcagtagaatatcgatcgatgcacctttcacaatatcgaccaatacaacgatagttgcgtcgaacgatattgcttccagcgagccttaagatcggctcaattcggatccgaaccctacaaatccttcatacaaatatcaaacaatatacaaattatattctgtatttttcaccaataatatttgagcaaaaatacaaaatcgtcaaacgagcaaaatcaaaagccgcctagcaaaaatacaaaatcgtcaaacgagcaaaagtttttgattgatacacatcaaaagccgcctagcaaaaatacaaaatcgtcaaacgagcaaaa";
const char* PStr = "tggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgac";
string TStrTemp;
string temp;
int MatchCnt[9];
vector<string> rs;
BM bm = BM();
BMH bmh = BMH();
Force bf = Force();
KMP	kmp = KMP();
Sunday sunday = Sunday();
ZK2	zk2 = ZK2();
ZK3	zk3 = ZK3();
ZK2_ascii zk2_ascii = ZK2_ascii();
ZK2_utf	zk2_utf = ZK2_utf();
ZK3_utf	zk3_utf = ZK3_utf();
retrieval_algorithms_time rat = retrieval_algorithms_time();

void  randomTStr(int CharsetSet_start, int CharsetSet_end, int Length) {
	srand((unsigned int)time(NULL));
	int range = CharsetSet_end - CharsetSet_start + 1;
	for (int i = 0; i < Length; i++)//Target string generation
	{
		int r = rand() % range + CharsetSet_start;
		TStrTemp += (char)r;
	}
	TStr = TStrTemp.c_str();
}

const char* itoa(int val)
{
	static char result[sizeof(int) << 3 + 2];
	unsigned int tempval = val;
	if (val < 0) tempval = -val;
	int i = sizeof(int) << 3 + 1;
	do {
		result[i] = "0123456789"[tempval % 10];
		tempval /= 10; --i;
	} while (tempval);
	if (val < 0) result[i--] = '-';
	return &result[i + 1];
}

void read(string Path) {
	const char* path = Path.c_str();
	ifstream infile;
	infile.open(path);
	if (!infile)
	{
		cout << "infile failed to open" << endl;
		exit(1);
	}
	while (!infile.eof())
	{
		infile >> temp;
		TStrTemp += temp;
	}
	infile.close();
}

/// <summary>
/// The gene file (multiple files) is read, build TStr
/// </summary>
void  geneTStr() {
	char* c = NULL;
	char filename_body[10];
	for (int i = 1; i <= 18; i++)
	{
		string filename = _getcwd(c, NULL);
		filename = filename.substr(0, filename.find_last_of("'\\'"));
		filename = filename + "\\gene_data\\chr";
		memset(filename_body, 0, sizeof(filename_body));		//Copy character
		filename += itoa(i);
		string filename_tail = ".fna";
		filename += filename_tail;
		cout << filename << endl;
		read(filename);
	}
	TStr = TStrTemp.c_str();
}

/// <summary>
/// words (single file) read, build TStr
/// </summary>
void wordsTStr() {
	char* c = NULL;
	char filename_body[10];
	string filename = _getcwd(c, NULL);
	filename = filename.substr(0, filename.find_last_of("'\\'"));
	filename = filename + "\\words";
	memset(filename_body, 0, sizeof(filename_body));		//Copy character
	string filename_tail = ".txt";
	filename += filename_tail;
	cout << "file path:   " << filename << endl;
	read(filename);

	TStr = TStrTemp.c_str();
}


int main() {
	FILE* file = fopen("DNA.txt", "r");
	if (file == NULL) {
		perror("Failed to open file");
		return EXIT_FAILURE;
	}

	// Move the file pointer to the end of the file
	fseek(file, 0, SEEK_END);
	// Get the size of the file
	long fileSize = ftell(file);
	// Move the file pointer back to the beginning of the file
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the file content plus a null terminator
	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL) {
		perror("Failed to allocate memory");
		fclose(file);
		return EXIT_FAILURE;
	}

	// Read the file into the buffer
	fread(buffer, 1, fileSize, file);
	// Null-terminate the string
	buffer[fileSize] = '\0';

	// Close the file
	fclose(file);

	// Use the buffer as a const char* TStr
	TStr = buffer;



	/// <summary>
	/// Algorithm running function
	/// </summary>
	/// <param name="cnt1">the length of the pattern string</param>
	/// <param name="cnt2">Randomly generates the length of the target string</param>

	//const char charSet_default[128] = {
	//0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	//16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	//' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	//'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	//'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	//'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	//'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	//'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 127 
	//};
	const char charSet_default[5] = { 'a','c','g', 'n', 't' };

	//const char charSet_default[256] = {
	//0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	//16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	//' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	//'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	//'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	//'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	//'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	//'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 127,
	//128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
	//144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	//160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
	//176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
	//192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
	//208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
	//224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
	//240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
	//};

	int TLen = strlen(TStr);
	int PLen = strlen(PStr);

	cout << "TLen: " << TLen << "      " << "PLen: " << PLen << endl;
	cout << endl << "Program running";
	MatchCnt[0] = bm.bmMatch(TStr, PStr, TLen, PLen);				cout << ".";
	MatchCnt[1] = bmh.BMH_match(TStr, PStr, TLen, PLen);			cout << ".";
	MatchCnt[2] = bf.force(TStr, PStr, TLen, PLen);					cout << ".";
	MatchCnt[3] = kmp.Kmp(TStr, PStr, TLen, PLen);					cout << ".";
	MatchCnt[4] = sunday.qsearch(TStr, PStr, TLen, PLen);			cout << ".";
	MatchCnt[5] = sunday.sunday_MS_search(TStr, PStr, TLen, PLen);  cout << ".";
	MatchCnt[6] = zk2.ZKSearch(TStr, PStr, TLen, PLen, charSet_default);	cout << ".";
	//MatchCnt[7] = zk3.ZKSearch(TStr, PStr, TLen, PLen, charSet_default);    cout << ".";
	MatchCnt[8] = zk2_ascii.ZKSearch(TStr, PStr, TLen, PLen);		cout << ".";
	cout << endl << endl;

	cout << "Time of algorithm BM:        " << rat.BM_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[0] << endl;
	cout << "Time of algorithm BMH:       " << rat.BMH_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[1] << endl;
	cout << "Time of algorithm Force:     " << rat.Force_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[2] << endl;
	cout << "Time of algorithm KMP:       " << rat.KMP_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "   Number of successful matches: " << MatchCnt[3] << endl;
	cout << "Time of algorithm QS:        " << rat.QS_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[4] << endl;
	cout << "Time of algorithm MS:        " << rat.MS_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[5] << endl;
	cout << "Time of algorithm ZK2:       " << rat.ZK2_retrieval_time(TStr, PStr, TLen, PLen, charSet_default) << " ms" << "    Number of successful matches: " << MatchCnt[6] << endl;
	//cout << "Time of algorithm ZK3:       " << rat.ZK3_retrieval_time(TStr, PStr, TLen, PLen, charSet_default) << " ms" << "    Number of successful matches: " << MatchCnt[7] << endl;
	cout << "Time of algorithm ZK2_ascii: " << rat.ZK2_ascii_retrieval_time(TStr, PStr, TLen, PLen) << " ms" << "    Number of successful matches: " << MatchCnt[8] << endl;

	cout << endl << "===================================================================================================================" << endl;

	return 0;
}

