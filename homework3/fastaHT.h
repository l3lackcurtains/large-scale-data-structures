#ifndef FASTAHT_H
#define FASTAHT_H

#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "fastaDAT.h"

// Represents the genome sequence string length
#define SEQUENCE_LENGTH 16

struct HashNode {
  long unsigned int radix;
  HashNode* next;
};

using namespace std;

class FASTAreadset_Chain {
 private:
  int hashTableSize;
  int collisionCount;
  int datasetCount;
  int elementsStored;
  HashNode** hashTable;
  long unsigned int calculateRadix(char* sequence);
  void insertInHashTable(long unsigned int key);
  Node* genomeHead;

 public:
  FASTAreadset_Chain(int hashSize);
  ~FASTAreadset_Chain();
  void readFile(char* path);
  void insertData(char* sequence);
  int getElementsStored();
  int getCollisions();
  int getTotalDataset();
  int getHashTableSize();
  bool searchSequence(char* sequence);
  void readGenomeDataset(char* filePath);
  void searchAllGenomeSequences();
};

#endif