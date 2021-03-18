#ifndef FASTADAT_H
#define FASTADAT_H

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
  long unsigned int calculateRadix(char* sequence);
  bool* boolArray;
  long unsigned int boolArraySize;
  int datasetCount;
  Node* genomeHead;

 public:
  FASTAreadset_DA();
  ~FASTAreadset_DA();
  void readFile(char* path);
  void insertData(char* sequence);
  bool searchSequence(char* sequence);
  void readGenomeDataset(char* filePath);
  void searchAllGenomeSequences();
  int getElementsStored();
  int getCollisions();
  int getTotalDataset();
  int getHashTableSize();
};

#endif