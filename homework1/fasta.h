#ifndef FASTA_H
#define FASTA_H

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

// Represents the dataset number
#define ALL_DATASETS_COUNT 14

// Represents the genome sequence string length
#define SEQUENCE_LENGTH 50

using namespace std;

class FASTA_readset {
   private:
    int datasetCount = 36000000;
    string filePath;
    char** headerNumber;
    char** read;
    void swap(char* stringData[], int i, int j);
    void quickSort(char* stringData[], int left, int right);
    void totalUniqueSequenceFragments();
    void allDatasetTotalUniqueSequenceFragments();
    void totalCharacterCounts();

   public:
    FASTA_readset();
    FASTA_readset(string path);
    void readFile(string path, int readLength);
    void readFile(int readLength);
    void initMillionData();
    void initFullData();
    void printData();
    void getAllStatistics();
    void sortSequenceRead();
    ~FASTA_readset();
};

#endif