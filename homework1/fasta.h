#ifndef FASTA_H
#define FASTA_H

#include <stdlib.h>
#include <string.h>

#include <ctime>
#include <fstream>
#include <iostream>

#define ALL_DATASETS_COUNT 14

#define SEQUENCE_LENGTH 50

using namespace std;

class FASTA_readset {
   private:
    int datasetCount;
    string filePath;
    ifstream input;
    char** headerNumber;
    char** read;

   public:
    FASTA_readset();
    FASTA_readset(string path);
    void readFile(string path, int readLength);
    void readFile(int readLength);
    void initMillionData();
    void initFullData();
    void printData();
    void totalUniqueSequenceFragments();
    void allDatasetTotalUniqueSequenceFragments();
    void totalCharacterCounts();
    void getAllStatistics();
    void swap(char* stringData[], int i, int j);
    void quickSort(char* stringData[], int left, int right);
    void sortSequenceRead();
    ~FASTA_readset();
};

#endif