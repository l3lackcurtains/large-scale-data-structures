#ifndef FASTA_H
#define FASTA_H

#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>

// Represents the dataset number
#define ALL_DATASETS_COUNT 14

// Represents the genome sequence string length
#define SEQUENCE_LENGTH 50

struct Node {
    char sequenceRead[SEQUENCE_LENGTH+1];
    struct Node* next;
};

using namespace std;

class FASTAreadset_LL {
   private:
    int datasetCount = 100;
    char* filePath;
    Node* head;
    Node* genomeHead;
    char** sortedRead;
    void swap(char* stringData[], int i, int j);
    void quickSort(char* stringData[], int left, int right);
    Node* performSearch(char toSearch[SEQUENCE_LENGTH]);

   public:
    FASTAreadset_LL();
    FASTAreadset_LL(char* path);
    FASTAreadset_LL(FASTAreadset_LL* oldFastaReadset);
    void readFile(char* path, int readLength);
    void readFile(int readLength);
    void initMillionData();
    void initFullData();
    void printData();
    void printGenomeData();
    void searchSequences();
    void searchGenomeDataset();
    void readGenomeDataset(char* filePath);
    ~FASTAreadset_LL();
};

#endif