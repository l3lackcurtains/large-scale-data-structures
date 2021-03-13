#include "fastaDAT.h"

// Helper function for the string comparision
int strcmp(const char *a, const char *b) {
  while (*a && *a == *b) {
    ++a;
    ++b;
  }
  return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

// Constructor that takes the file path
FASTAreadset_DA::FASTAreadset_DA(char *path) {
  collisionCount = 0;
  elementsStored = 0;
  datasetCount = 0;

  boolArraySize = pow(4, 16);
  boolArray = new bool[boolArraySize];
  for (unsigned int x = 0; x < boolArraySize; x++) {
    boolArray[x] = false;
  }

  ifstream file;
  if (file.is_open()) {
    file.close();
  }

  file.open(path);

  string line;
  int count = 0;
  char* currentLine;
  currentLine = (char*)malloc(sizeof(char) * SEQUENCE_LENGTH);
  bool isHeader = true;
  unsigned int radixValue;

  while (getline(file, line)) {
    if (!isHeader) {
      for (int k = 0; k < SEQUENCE_LENGTH - 1; k++) {
        currentLine[k] = (line.c_str())[k];
      }

      radixValue = calculateRadix(currentLine);
      if(boolArray[radixValue]) {
        collisionCount++;
      } else {
        boolArray[radixValue] = true;
      }

      datasetCount++;
    }
    isHeader = !isHeader;
  }
  file.close();

  elementsStored = datasetCount - collisionCount;
}

  unsigned int FASTAreadset_DA::calculateRadix(char* sequence){
    unsigned int value = 0; 
    int i = SEQUENCE_LENGTH - 1; 
    int pos = 0; 
    char current; 
    int base = 4; 
    int posValue;
    while(i > 0){
      current = sequence[i - 1];
      switch (current){
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
      value += pow(base, pos) * posValue;
      pos++;
      i--;
    }
    return value;
  }


int FASTAreadset_DA::getElementsStored() {
  return elementsStored;
}

int FASTAreadset_DA::getCollisions() {
  return collisionCount;
}

// Destroy function to deallocate headerNumber and read arrays
FASTAreadset_DA::~FASTAreadset_DA() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////

  delete[] boolArray;
  

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all linkedlists.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}