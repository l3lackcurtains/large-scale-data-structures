#include "fastaHT.h"

FASTAreadset_Chain::FASTAreadset_Chain(int hashSize) {
  collisionCount = 0;
  elementsStored = 0;
  datasetCount = 0;
  hashTableSize = hashSize;

  hashTable = new HashNode *[hashTableSize];

  for (int i = 0; i < hashTableSize; i++) {
    hashTable[i] = NULL;
  }
}

void FASTAreadset_Chain::insertData(char* sequence) {
  unsigned int radixValue = calculateRadix(sequence);
    insertInHashTable(radixValue);
}

void FASTAreadset_Chain::readFile(char *path) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////
  ifstream input;
  input.open(path);
  char *tempHeader = new char[100];
  char *tempRead = new char[SEQUENCE_LENGTH];
  long unsigned int radixValue;
  int tempCount = -1;
  while (!input.eof()) {
    tempCount++;
    input >> tempHeader;
    input >> tempRead;
    insertData(tempRead);    
  }
  datasetCount = tempCount;

  elementsStored = datasetCount - collisionCount;

  delete[] tempRead;
  delete[] tempHeader;
  input.close();

  //////////////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to store sequences in %d size Hash Table: %3.3f seconds. \n",
         hashTableSize, totalTime);
  ;
  cout << "#####################################################" << endl;
}

void FASTAreadset_Chain::insertInHashTable(long unsigned int key) {
  int index = key % hashTableSize;
  HashNode *temp = hashTable[index];
  HashNode *entry = new HashNode;
  entry->radix = key;
  entry->next = NULL;
  if (temp == NULL) {
    hashTable[index] = entry;
  } else {
    collisionCount++;
    hashTable[index] = entry;
    entry->next = temp;
  }
}

long unsigned int FASTAreadset_Chain::calculateRadix(char *sequence) {
  unsigned int radixVal = 0;
  int i = SEQUENCE_LENGTH - 1;
  int pos = 0;
  char current;
  int posValue;

  while (i >= 0) {
    current = sequence[i];

    switch (current) {
      case 'A':
        posValue = 0;
        break;
      case 'C':
        posValue = 1;
        break;
      case 'G':
        posValue = 2;
        break;
      case 'T':
        posValue = 3;
        break;
    }
    radixVal += pow(4, pos) * posValue;

    pos++;
    i--;
  }
  return radixVal;
}

int FASTAreadset_Chain::getElementsStored() { return elementsStored; }

int FASTAreadset_Chain::getCollisions() { return collisionCount; }

int FASTAreadset_Chain::getTotalDataset() { return datasetCount; }

bool FASTAreadset_Chain::searchSequence(char *sequence) {
  long unsigned int radixValue = calculateRadix(sequence);
  int index = radixValue % hashTableSize;
  HashNode *current = hashTable[index];
  if (current == NULL) {
    return false;
  }

  bool found = false;
  while (current != NULL) {
    if (current->radix == radixValue) {
      found = true;
      break;
    }
    current = current->next;
  }
  return found;
}

void FASTAreadset_Chain::searchAllGenomeSequences() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////
  Node *current = genomeHead;
  int count = 0;
  int total = 0;
  while (current != NULL) {
    count++;
    bool found = searchSequence(current->sequenceRead);
    if (found) total++;
    current = current->next;
  }
  cout << total << " 16-characters long sequences match were found" << endl;

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to search all genome sequences: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

void FASTAreadset_Chain::readGenomeDataset(char *filePath) {
  ifstream input;
  input.open(filePath);
  char *tempRead;
  tempRead = new char[SEQUENCE_LENGTH];
  char c = '\0';
  int characterCount = 0;
  int nodesStored = 0;
  Node *current;

  // Skip first line
  while (c != '\n') {
    input.get(c);
  }

  // Get the genome sequences in 50 blocks, and shift to right by 1
  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      tempRead[characterCount] = c;
      characterCount++;
      if (characterCount == SEQUENCE_LENGTH) {
        Node *newNode = new Node;

        for (int k = 0; k < SEQUENCE_LENGTH; k++) {
          newNode->sequenceRead[k] = tempRead[k];
        }
        newNode->next = NULL;

        if (nodesStored == 0) {
          genomeHead = newNode;
        } else {
          current->next = newNode;
        }
        current = newNode;
        nodesStored++;
        characterCount = SEQUENCE_LENGTH - 1;

        for (int i = 1; i < SEQUENCE_LENGTH; i++) {
          tempRead[i - 1] = tempRead[i];
        }
      }
    }
  }

  delete[] tempRead;

  cout << "Initialized " << nodesStored << " 16-mers sequences." << endl;

  input.close();
}

// Destroy function to deallocate headerNumber and read arrays
FASTAreadset_Chain::~FASTAreadset_Chain() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////

  for (int i = 0; i < hashTableSize; i++) {
    HashNode *head = hashTable[i];
    if (head != NULL) {
      HashNode *current = head;
      HashNode *next = NULL;

      while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
      }
      head = NULL;
    }
    delete head;
  }

  delete[] hashTable;

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all data structures.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}