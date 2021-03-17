#include "fastaDAT.h"

// Default constructor
FASTAreadset_DA::FASTAreadset_DA() {
  collisionCount = 0;
  elementsStored = 0;
  datasetCount = 0;

  boolArraySize = pow(4, 16);
  boolArray = new bool[boolArraySize];

  for (long unsigned int x = 0; x < boolArraySize; x++) {
    boolArray[x] = false;
  }
}

// Helper function to insert data in hash table
void FASTAreadset_DA::insertData(char* sequence) {
  unsigned int radixValue = calculateRadix(sequence);
  if (boolArray[radixValue]) {
    collisionCount++;
  } else {
    boolArray[radixValue] = true;
  }
  datasetCount++;
}

// Function to read the file
void FASTAreadset_DA::readFile(char *path) {
  ifstream input;
  input.open(path);
  char *tempHeader = new char[100];
  char *tempRead = new char[SEQUENCE_LENGTH];
 
  while (!input.eof()) {
    input >> tempHeader;
    input >> tempRead;
    insertData(tempRead);
  }

  elementsStored = datasetCount - collisionCount;

  delete[] tempRead;
  delete[] tempHeader;
  input.close();
}

// Helper function to calculate the radix from sequence
long unsigned int FASTAreadset_DA::calculateRadix(char *sequence) {
  long unsigned int radixVal = 0;
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

// Helper function to get total elements stored
int FASTAreadset_DA::getElementsStored() { return elementsStored; }

// Helper function to get total collisions
int FASTAreadset_DA::getCollisions() { return collisionCount; }

// Helper function to get total dataset count
int FASTAreadset_DA::getTotalDataset() { return datasetCount; }

// Helper function to get hash table size
int FASTAreadset_DA::getHashTableSize() {
  return (boolArraySize / (1024 * 1024 * 1024.0));
}

// Function to search single genome sequence
bool FASTAreadset_DA::searchSequence(char *sequence) {
  long unsigned int radixValue = calculateRadix(sequence);
  return boolArray[radixValue];
}

// Function to search all genome sequences
void FASTAreadset_DA::searchAllGenomeSequences() {
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

// Function to read the genome database from file path
void FASTAreadset_DA::readGenomeDataset(char *filePath) {
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

// Destroy function to deallocate all data structures
FASTAreadset_DA::~FASTAreadset_DA() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////

  delete[] boolArray;

  if (genomeHead != NULL) {
    Node *current = genomeHead;
    Node *next = NULL;

    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
    genomeHead = NULL;
  }

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all data structures.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}