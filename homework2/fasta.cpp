#include "fasta.h"
#include <iostream>

// default constructor
FASTAreadset_LL::FASTAreadset_LL() {
  head = NULL;
  genomeHead = NULL;
}

// Constructor that takes the file path
FASTAreadset_LL::FASTAreadset_LL(char* path) {
  filePath = path;
  head = NULL;
  genomeHead = NULL;
}

FASTAreadset_LL::FASTAreadset_LL(FASTAreadset_LL* oldFastaReadset) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  head = NULL;
  Node* current;
  int count = 0;
  Node* temp = oldFastaReadset->head;
  while (temp != NULL) {
    Node* newNode = new Node;
    for (int k = 0; k < SEQUENCE_LENGTH; k++) {
      (newNode->sequenceRead)[k] = (temp->sequenceRead)[k];
    }
    (newNode->sequenceRead)[SEQUENCE_LENGTH] = '\0';
    newNode->next = NULL;

    if (count == 0) {
      head = newNode;
    } else {
      current->next = newNode;
    }
    current = newNode;
    temp = temp->next;
    count++;
  }
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to perform a deep copy of entire dataset: %3.3f seconds. \n",
         totalTime);
  ;
  cout << "#####################################################" << endl;
}
// Method to read readLength count of data from the file from its path
void FASTAreadset_LL::readFile(char* path, int readLength) {
  // Open the file
  ifstream input;
  input.open(path);

  // helper variables
  int a, b, i, j;

  // Declare and allocate memory for temporary head
  char* tempHeader = new char[100];

  Node* currentRead = NULL;
  int tempCount = -1;

  while (!input.eof()) {
    tempCount++;
    Node* newRead = new Node;

    input >> tempHeader;
    input >> newRead->sequenceRead;

    newRead->next = NULL;

    if (currentRead != NULL) {
      currentRead->next = newRead;
    }
    currentRead = newRead;
    if (tempCount == 0) {
      head = newRead;
    }
    if (readLength == tempCount) break;
  }

  datasetCount = tempCount;

  cout << "Initialized " << tempCount << " genome sequences." << endl;

  // Close file and delete tenporary head
  input.close();
  delete[] tempHeader;
}

// Method to read file upto the specified length
void FASTAreadset_LL::readFile(int readLength) {
  readFile(filePath, readLength);
}

// Method to initialize all data from dataset
void FASTAreadset_LL::initNthData(int limit) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  readFile(limit);
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to read full dataset: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;

  // Sleep was used to capture memory used in question 2
  sleep(60);
}

// Function to print the data stored in arrays
void FASTAreadset_LL::printData() {
  Node* temp;
  temp = head;

  while (temp != NULL) {
    cout << temp->sequenceRead << endl;
    temp = temp->next;
  }
}

void FASTAreadset_LL::printGenomeData() {
  Node* temp;
  temp = genomeHead;

  while (temp != NULL) {
    cout << temp->sequenceRead << endl;
    temp = temp->next;
  }
}

Node* FASTAreadset_LL::performSearch(char toSearch[SEQUENCE_LENGTH]) {
  Node* foundIndex = NULL;
  Node* current = head;
  int count = 0;
  while (current != NULL) {
    count++;
    if (strcmp(toSearch, current->sequenceRead) == 0) {
      foundIndex = current;
      break;
    }
    current = current->next;
  }
  return foundIndex;
}

// Function to sort the genome sequences read
void FASTAreadset_LL::searchSequences() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  ////////////////////////////////////////////////
  char toSearch1[] = "CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT";
  char toSearch2[] = "GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC";
  char toSearch3[] = "CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC";
  char toSearch4[] = "CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA";
  char toSearch5[] = "ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN";

  Node* search1 = performSearch(toSearch1);
  if (search1 != NULL) {
    cout << toSearch1 << ": FOUND" << endl;
  } else {
    cout << toSearch1 << ": NOT FOUND" << endl;
  }

  Node* search2 = performSearch(toSearch2);
  if (search2 != NULL) {
    cout << toSearch2 << ": FOUND" << endl;
  } else {
    cout << toSearch2 << ": NOT FOUND" << endl;
  }

  Node* search3 = performSearch(toSearch3);
  if (search3 != NULL) {
    cout << toSearch3 << ": FOUND" << endl;
  } else {
    cout << toSearch3 << ": NOT FOUND" << endl;
  }

  Node* search4 = performSearch(toSearch4);
  if (search4 != NULL) {
    cout << toSearch4 << ": FOUND" << endl;
  } else {
    cout << toSearch4 << ": NOT FOUND" << endl;
  }

  Node* search5 = performSearch(toSearch5);
  if (search5 != NULL) {
    cout << toSearch5 << ": FOUND" << endl;
  } else {
    cout << toSearch5 << ": NOT FOUND" << endl;
  }

  //////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to sort search sequences: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Destroy function to deallocate headerNumber and read arrays
FASTAreadset_LL::~FASTAreadset_LL() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////
  if (head != NULL) {
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
    head = NULL;
  }

  if (genomeHead != NULL) {
    Node* current = genomeHead;
    Node* next = NULL;

    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
    head = NULL;
  }

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all linkedlists.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

void FASTAreadset_LL::readGenomeDataset(char* filePath) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////
  ifstream input;
  input.open(filePath);
  char tempRead[SEQUENCE_LENGTH];
  char c = '\0';
  int characterCount = 0;
  int nodesStored = 0;
  Node* current;
  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'N') {
      tempRead[characterCount] = c;
      characterCount++;
      if (characterCount == SEQUENCE_LENGTH) {
        Node* newNode = new Node;
        for (int k = 0; k < SEQUENCE_LENGTH; k++) {
          newNode->sequenceRead[k] = tempRead[k];
        }
        (newNode->sequenceRead)[SEQUENCE_LENGTH] = '\0';
        newNode->next = NULL;
        if (nodesStored == 0) {
          genomeHead = newNode;
        } else {
          current->next = newNode;
        }
        current = newNode;
        nodesStored++;
        characterCount = SEQUENCE_LENGTH - 1;
      }
      for (int i = 1; i < SEQUENCE_LENGTH; i++) {
        tempRead[i - 1] = tempRead[i];
      }
    }
  }

  input.close();

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Initialized " << nodesStored << " 50-mers data." << endl;
  printf("Time to Allocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

void FASTAreadset_LL::searchGenomeDataset() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  Node* current = genomeHead;
  int count = 0;
  int total = 0;
  while (current != NULL) {
    count++;
    Node* result = performSearch(current->sequenceRead);
    if (result != NULL) total++;
    current = current->next;
  }
  cout << total << " 50 mers genome sequences match were found." << endl;
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time search all 50-mers genome sequences: %3.3f seconds. \n",
         totalTime);
  ;
  cout << "#####################################################" << endl;
}