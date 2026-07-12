#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <filesystem>

#include "bm.h"
#include "bmh.h"
#include "force.h"
#include "kmp.h"
#include "sunday.h"
#include "zk2.h"
#include "zk3.h"
#include "zk2_utf.h"
#include "zk3_utf.h"
#include "benchmark.h"

using namespace std;

int PLen, TLen;
const char* TStr = nullptr;
const char* PStr = nullptr;

// Default embedded DNA test sequence and pattern (for quick verification)
const char* DEFAULT_PSTR = "tggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgac";

string TStrTemp;
string temp;
int MatchCnt[9];
vector<string> rs;

BM bm = BM();
BMH bmh = BMH();
Force bf = Force();
KMP kmp = KMP();
Sunday sunday = Sunday();
ZK2 zk2 = ZK2();
ZK3 zk3 = ZK3();
ZK2_ascii zk2_ascii = ZK2_ascii();
ZK2_utf zk2_utf = ZK2_utf();
ZK3_utf zk3_utf = ZK3_utf();
retrieval_algorithms_time rat = retrieval_algorithms_time();


/// Read entire file content into a string
string readFile(const string& filePath) {
    ifstream infile(filePath, ios::binary);
    if (!infile) {
        cerr << "Error: Failed to open file: " << filePath << endl;
        exit(1);
    }
    string content;
    // Get file size
    infile.seekg(0, ios::end);
    content.reserve(infile.tellg());
    infile.seekg(0, ios::beg);
    // Read entire file
    content.assign((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();
    return content;
}


/// Read multiple gene data files and concatenate them
string readGeneData(const string& geneDataDir) {
    string allContent;
    for (int i = 1; i <= 18; i++) {
        string filename = geneDataDir + "/chr" + to_string(i) + ".fna";
        cout << "Reading: " << filename << endl;
        string content = readFile(filename);
        // Remove FASTA header lines (lines starting with '>')
        string filtered;
        for (size_t pos = 0; pos < content.length(); ) {
            size_t lineEnd = content.find('\n', pos);
            if (lineEnd == string::npos) lineEnd = content.length();
            if (pos < content.length() && content[pos] != '>') {
                filtered.append(content, pos, lineEnd - pos);
            }
            pos = lineEnd + 1;
            if (pos >= content.length()) break;
        }
        allContent += filtered;
    }
    return allContent;
}


/// Run all algorithms on the given text and pattern
void runAllAlgorithms(const char* text, const char* pattern, int tLen, int pLen, const char* charSet = nullptr) {
    cout << endl;
    cout << "Text length:     " << tLen << endl;
    cout << "Pattern length:  " << pLen << endl;
    cout << endl << "Running algorithms..." << endl;

    MatchCnt[0] = bm.bmMatch(text, pattern, tLen, pLen);
    MatchCnt[1] = bmh.BMH_match(text, pattern, tLen, pLen);
    MatchCnt[2] = bf.force(text, pattern, tLen, pLen);
    MatchCnt[3] = kmp.Kmp(text, pattern, tLen, pLen);
    MatchCnt[4] = sunday.qsearch(text, pattern, tLen, pLen);
    MatchCnt[5] = sunday.sunday_MS_search(text, pattern, tLen, pLen);
    MatchCnt[6] = zk2.ZKSearch(text, pattern, tLen, pLen, charSet);
    MatchCnt[7] = zk2_ascii.ZKSearch(text, pattern, tLen, pLen);
    MatchCnt[8] = zk3.ZKSearch(text, pattern, tLen, pLen, charSet);

    cout << endl;
    cout << "===============================================================================" << endl;
    cout << "Algorithm             Time (ms)          Matches" << endl;
    cout << "===============================================================================" << endl;
    cout << "BM                    " << rat.BM_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[0] << endl;
    cout << "BMH                   " << rat.BMH_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[1] << endl;
    cout << "Brute-Force           " << rat.Force_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[2] << endl;
    cout << "KMP                   " << rat.KMP_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[3] << endl;
    cout << "Sunday (QS)           " << rat.QS_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[4] << endl;
    cout << "Sunday (MS)           " << rat.MS_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[5] << endl;
    cout << "ZK2                   " << rat.ZK2_retrieval_time(text, pattern, tLen, pLen, charSet) << " ms              " << MatchCnt[6] << endl;
    cout << "ZK2 (ASCII)           " << rat.ZK2_ascii_retrieval_time(text, pattern, tLen, pLen) << " ms              " << MatchCnt[7] << endl;
    cout << "ZK3                   " << rat.ZK3_retrieval_time(text, pattern, tLen, pLen, charSet) << " ms              " << MatchCnt[8] << endl;
    cout << "===============================================================================" << endl;
}


void printUsage(const char* progName) {
    cout << "Usage: " << progName << " [OPTIONS]" << endl;
    cout << endl;
    cout << "A Dual-Heuristic String Matching Algorithm Based on Structural Constraint Propagation" << endl;
    cout << "Benchmark and demonstration program" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "  --file <path>       Input text file path (required for file-based tests)" << endl;
    cout << "  --pattern <string>   Pattern string to search for (optional, default embedded)" << endl;
    cout << "  --gene-data <dir>   Directory containing chr1-18.fna gene data files" << endl;
    cout << "  --help              Show this help message" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  " << progName << " --file data/DNA.txt" << endl;
    cout << "  " << progName << " --file data/DNA.txt --pattern \"ACGTACGT\"" << endl;
    cout << "  " << progName << " --gene-data datasets/gene_data --pattern \"ACGTACGT\"" << endl;
    cout << endl;
    cout << "Note: Dataset files (DNA.txt, words.txt, chr*.fna) must be downloaded separately." << endl;
    cout << "See datasets/README.md for download instructions." << endl;
}


int main(int argc, char* argv[]) {
    string inputFile;
    string geneDataDir;
    string patternStr;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
        }
        else if (arg == "--file" && i + 1 < argc) {
            inputFile = argv[++i];
        }
        else if (arg == "--gene-data" && i + 1 < argc) {
            geneDataDir = argv[++i];
        }
        else if (arg == "--pattern" && i + 1 < argc) {
            patternStr = argv[++i];
        }
    }

    // Determine text source
    if (!geneDataDir.empty()) {
        // Read gene data from directory
        cout << "Loading gene data from: " << geneDataDir << endl;
        TStrTemp = readGeneData(geneDataDir);
        TStr = TStrTemp.c_str();
    }
    else if (!inputFile.empty()) {
        // Read from single file
        cout << "Loading text from: " << inputFile << endl;
        TStrTemp = readFile(inputFile);
        TStr = TStrTemp.c_str();
    }
    else {
        // No file specified — use embedded DNA sequence for quick verification
        cout << "No input file specified. Using embedded DNA test sequence for verification." << endl;
        cout << "Use --help for usage information." << endl;

        const char* EMBEDDED_TSTR =
            "tctactttactcccttctttcacaagatggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgacggggactaccctgtactccgaccggagagatgatcggtattctcgtttacaaagaaggtttacttgtatgactgagagagttttcttgtggtttcgtttatcgttttcttgtggtttcgtttatcgtttctaaaccgaacagtcaatggagctgaagacgacgttagtgtttaattaaacacgtgtttaatttatgaaaagaaaatttcttaaaaatacactaactaattttcatgtgttaataaaatacacaaactatttttggatctccgacttcggattttcaccaataatatttggtttctaaaccgaacagtcaattcggatccgaaccctacaaatccttcatacaaatatcaaacaatatacaaattatattctgtatttttcaccaataatatttgatttcagtgatcagaaaatattgaaagtgtggttttggaaataatatctaattgaatatcacattgtacgttgttatcaatcaatcatctactaaaggggtgtagaagttgtaatcacttaggaatgggctagaatgatgaggatggatccatgtatgcatgaattgctcctagtcttagatatattttgcataatgatcaaactccttgatttttcagtgttactcccttctttcaaaggggtgtagaagttgtaatcacttaggaatgggctagaatgatgaggatggatccatgtatgcatgaattgctcctagtcttagatatattttgcataatgatcaaactccttgatttttcagtgacaagaggggactaccctgtactccgaccggagagatgatcggagtttttgattgatacacatctactttactcccttctttcacaagaggggactaccctgtactccgaccggagagatgatcggagtttttgattgatacacatcaaaagccgcctgttttcttgtggtttcgtttatcgtttctaaaccgaacagtaagtctttcctccgaattgctggtgagcggatcgcagacctgttagtgtaaaactgatcaggtctgttataatccccaagcgtttggtggttctccgacccagcattcaaaacaacggcgcatactcgatttcagccctaggtttataattaatttgacgtgatgcattgcatactcgattatctagatatcctagaactactttcccataattgaaattggtaagcacagacttacctgcttccggctggtcggcgtcgatcgatttgtttagcccatcgtcgatcgatttttgttgatctgcgtcgatcgattgcagtatggaagtgtcgatcgatttgtccgtcgattcgtcgctcgatgtctccgtcatcttgtcgatcgatgctcggccgaacttgtgttcctcttcttaagttcctgtgtcagtaaggaaagaagaaaaacttttaaataaacagtaagtaaaatctagactatattctaaacttaatctaatggcaataagaaagagtccctggcaacgccgccaaatttgatatcactcaaattaccctaaggagtgactttactctcttaaataagaggttcagctgtagtacttagggatcgaatccacaaagactctaagattacacaatagattgtatagtcttcgaaataaagctagataggtaagttttaaacagtaaattaaatggtgagcaagtcagttgctcgattgatttgatttgaggttgttaacagaaggaaaggtagctagattcatgtattatctcaggttcgacaagtatgcaagttaattagggtttttactattcatagttctgaactcaaactttaggtttaatcgaatcaattaccttcaactggatctcggatcatgaactatcgatcgatgatcataagaaagtgtcgatcgattattcagtagaatatcgatcgatgcacctttcacaatatcgaccaatacaacgatagttgcgtcgaacgatattgcttccagcgagccttaagatcggctcaattcggatccgaaccctacaaatccttcatacaaatatcaaacaatatacaaattatattctgtatttttcaccaataatatttgagcaaaaatacaaaatcgtcaaacgagcaaaatcaaaagccgcctagcaaaaatacaaaatcgtcaaacgagcaaaagtttttgattgatacacatcaaaagccgcctagcaaaaatacaaaatcgtcaaacgagcaaaa";

        PStr = patternStr.empty() ? DEFAULT_PSTR : patternStr.c_str();
        TStr = EMBEDDED_TSTR;
        int tLen = strlen(TStr);
        int pLen = strlen(PStr);

        const char charSet_default[5] = { 'a','c','g', 'n', 't' };
        runAllAlgorithms(TStr, PStr, tLen, pLen, charSet_default);
        return 0;
    }

    // Set pattern (default or user-specified)
    PStr = patternStr.empty() ? DEFAULT_PSTR : patternStr.c_str();

    int tLen = TStrTemp.length();
    int pLen = strlen(PStr);

    // Use appropriate character set based on input
    const char dnaCharSet[5] = { 'a','c','g', 'n', 't' };
    const char* charSet = nullptr;

    if (!geneDataDir.empty()) {
        charSet = dnaCharSet;
    }

    runAllAlgorithms(TStr, PStr, tLen, pLen, charSet);

    return 0;
}
