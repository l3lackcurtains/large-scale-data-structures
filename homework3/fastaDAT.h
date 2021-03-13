#ifndef FASTA_H
#define FASTA_H

#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

// Represents the genome sequence string length
#define SEQUENCE_LENGTH 16

struct Node {
    char sequenceRead[SEQUENCE_LENGTH];
    struct Node* next;
};

using namespace std;

class FASTAreadset_DA {
 private:
  int collisionCount;
  int elementsStored;
  unsigned int calculateRadix(char* sequence);
  bool* boolArray;
  long long unsigned int boolArraySize;
  int datasetCount;

 public:
  FASTAreadset_DA(char* path);
  ~FASTAreadset_DA();
  void insertData(char* sequence);
  void searchSequence(char* sequence);
  int getElementsStored();
  int getCollisions();
};

#endif