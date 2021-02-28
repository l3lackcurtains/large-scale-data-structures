#include "fasta.h"

#include <string.h>
#include <unistd.h>

#include <iostream>

// default constructor
FASTAreadset_LL::FASTAreadset_LL() { head = NULL; }

// Constructor that takes the file path
FASTAreadset_LL::FASTAreadset_LL(char* path) {
  filePath = path;
  head = NULL;
}

FASTAreadset_LL::FASTAreadset_LL(FASTAreadset_LL* oldFastaReadset) {
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
  for (int i = 0; i < readLength; i++) {
    Node* newRead = new Node;

    input >> tempHeader;
    input >> newRead->sequenceRead;

    newRead->next = NULL;

    if (currentRead != NULL) {
      currentRead->next = newRead;
    }
    currentRead = newRead;
    if (i == 0) {
      head = newRead;
    }
  }

  // Close file and delete tenporary head
  input.close();
}

// Method to read file upto the specified length
void FASTAreadset_LL::readFile(int readLength) {
  readFile(filePath, readLength);
}

// Method to initialize the million data
void FASTAreadset_LL::initMillionData() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  readFile(datasetCount);
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to read 1 million data: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;

  // Sleep was used to capture memory used in question 1
  // sleep(60);
}

// Method to initialize the 36 million data
void FASTAreadset_LL::initFullData() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  readFile(datasetCount);
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to read 36 million data: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;

  // Sleep was used to capture memory used in question 2
  // sleep(60);
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

// Helper function for quick sort algorith for swaping
void FASTAreadset_LL::swap(char* stringData[], int i, int j) {
  char* temp = new char[SEQUENCE_LENGTH];
  temp = stringData[i];
  stringData[i] = stringData[j];
  stringData[j] = temp;
}

// Quick sort algorithm function
void FASTAreadset_LL::quickSort(char* stringData[], int left, int right) {
  if (left >= right) {
    return;
  }
  swap(stringData, left, (left + right) / 2);
  int last = left;

  for (int i = left + 1; i <= right; i++) {
    if (strcmp(stringData[i], stringData[left]) < 0) {
      swap(stringData, ++last, i);
    }
  }
  swap(stringData, left, last);
  quickSort(stringData, left, last - 1);
  quickSort(stringData, last + 1, right);
}

Node* FASTAreadset_LL::performSearch(char toSearch[SEQUENCE_LENGTH]) {
    Node* foundIndex = NULL;
    Node* current = head;
    while (current != NULL) {
      if(strcmp(toSearch, current->sequenceRead) == 0) {
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
  if(search1 != NULL) {
    cout << toSearch1 << ": FOUND"<< endl;
  } else {
    cout << toSearch1 << ": NOT FOUND"<< endl;
  }

  Node* search2 = performSearch(toSearch2);
  if(search2 != NULL) {
    cout << toSearch2 << ": FOUND"<< endl;
  } else {
    cout << toSearch2 << ": NOT FOUND"<< endl;
  }

  Node* search3 = performSearch(toSearch3);
  if(search3 != NULL) {
    cout << toSearch3 << ": FOUND"<< endl;
  } else {
    cout << toSearch3 << ": NOT FOUND"<< endl;
  }

  Node* search4 = performSearch(toSearch4);
  if(search4 != NULL) {
    cout << toSearch4 << ": FOUND"<< endl;
  } else {
    cout << toSearch4 << ": NOT FOUND"<< endl;
  }

  Node* search5 = performSearch(toSearch5);
  if(search5 != NULL) {
    cout << toSearch5 << ": FOUND"<< endl;
  } else {
    cout << toSearch5 << ": NOT FOUND"<< endl;
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
  Node* current = head;
  Node* next = NULL;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  head = NULL;

  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all array memory.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}
