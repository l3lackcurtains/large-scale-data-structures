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
    char sequenceRead[SEQUENCE_LENGTH];
    struct Node* next;
};

using namespace std;

class FASTAreadset_LL {
   private:
    int datasetCount;
    char* filePath;
    Node* head;
    Node* genomeHead;
    char** sortedRead;
    Node* performSearch(char toSearch[SEQUENCE_LENGTH]);
    int performBinarySearch(char toSearch[SEQUENCE_LENGTH], int left, int right);
    void swap(char **a, char **b);
    void quicksort(char* arr[], unsigned int length);

   public:
    FASTAreadset_LL();
    FASTAreadset_LL(char* path);
    FASTAreadset_LL(FASTAreadset_LL* oldFastaReadset);
    void readFile(char* path, int readLength);
    void readFile(int readLength);
    void initNthData(int limit);
    void printData();
    void printGenomeData();
    void searchSequences();
    void searchGenomeDataset();
    void binarySearchGenomeDataset();
    void readGenomeDataset(char* filePath, int genomeDataLimit);
    ~FASTAreadset_LL();
};

#endif