#include "fasta.h"
#include <fstream>
#include <iostream>

// Helper function for the string comparision
int strcmp(const char *a, const char *b) {
  while (*a && *a == *b) {
    ++a;
    ++b;
  }
  return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

// default constructor
FASTAreadset_LL::FASTAreadset_LL() {
  head = NULL;
  genomeHead = NULL;
}

// Constructor that takes the file path
FASTAreadset_LL::FASTAreadset_LL(char *path) {
  filePath = path;
  head = NULL;
  genomeHead = NULL;
}

// the copy constructor
FASTAreadset_LL::FASTAreadset_LL(const FASTAreadset_LL &oldFastaReadset) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  head = NULL;
  genomeHead = NULL;
  Node *current;
  int count = 0;
  Node *temp = oldFastaReadset.head;
  while (temp != NULL) {

    // Copy data to new node
    Node *newNode = new Node;
    for (int k = 0; k < SEQUENCE_LENGTH; k++) {
      (newNode->sequenceRead)[k] = (temp->sequenceRead)[k];
    }
    (newNode->sequenceRead)[SEQUENCE_LENGTH] = '\0';
    newNode->next = NULL;

    // Link new node in the linkedlist
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
void FASTAreadset_LL::readFile(char *path, int readLength) {
  // Open the file
  ifstream input;
  input.open(path);

  // helper variables
  int a, b, i, j;

  // Declare and allocate memory for temporary head
  char *tempHeader = new char[100];

  Node *currentRead = NULL;
  int tempCount = -1;

  // read the file until EOF
  while (!input.eof()) {
    tempCount++;
    Node *newRead = new Node;

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
    // If limit specified, break the loop
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
  // sleep(60);
}

// Function to print the data of 1st genome dataset
void FASTAreadset_LL::printData() {
  Node *temp;
  temp = head;
  int count = 0;
  while (temp != NULL) {
    cout << temp->sequenceRead << endl;
    temp = temp->next;
    if (count == 20) break;
  }
}

// Print the data in 2nd genome dataset
void FASTAreadset_LL::printGenomeData() {
  Node *temp;
  temp = genomeHead;
  int count = 0;
  while (temp != NULL) {
    count++;
    cout << temp->sequenceRead << endl;
    temp = temp->next;
    if (count == 20) break;
  }
}

// Perform the naive search on the sequence string
Node *FASTAreadset_LL::performSearch(char toSearch[SEQUENCE_LENGTH]) {
  Node *foundIndex = NULL;
  Node *current = head;
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

// Function to search the given 5 genome sequences read
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

  Node *search1 = performSearch(toSearch1);
  if (search1 != NULL) {
    cout << toSearch1 << ": FOUND" << endl;
  } else {
    cout << toSearch1 << ": NOT FOUND" << endl;
  }

  Node *search2 = performSearch(toSearch2);
  if (search2 != NULL) {
    cout << toSearch2 << ": FOUND" << endl;
  } else {
    cout << toSearch2 << ": NOT FOUND" << endl;
  }

  Node *search3 = performSearch(toSearch3);
  if (search3 != NULL) {
    cout << toSearch3 << ": FOUND" << endl;
  } else {
    cout << toSearch3 << ": NOT FOUND" << endl;
  }

  Node *search4 = performSearch(toSearch4);
  if (search4 != NULL) {
    cout << toSearch4 << ": FOUND" << endl;
  } else {
    cout << toSearch4 << ": NOT FOUND" << endl;
  }

  Node *search5 = performSearch(toSearch5);
  if (search5 != NULL) {
    cout << toSearch5 << ": FOUND" << endl;
  } else {
    cout << toSearch5 << ": NOT FOUND" << endl;
  }

  //////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to search the 5 sequences: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Function to read the genome data from 2nd dataset
void FASTAreadset_LL::readGenomeDataset(char *filePath, int genomeDataLimit) {
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
  Node *current;

  // Skip first line
  while (c != '\n') {
    input.get(c);
  }

  // Get the genome sequences in 50 blocks, and shift to right by 1
  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'N') {
      tempRead[characterCount] = c;
      characterCount++;
      if (characterCount == SEQUENCE_LENGTH) {
        Node *newNode = new Node;
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

        for (int i = 1; i < SEQUENCE_LENGTH; i++) {
          tempRead[i - 1] = tempRead[i];
        }
      }
      // If 2nd dataset limit exists, break the loop
      if (nodesStored == genomeDataLimit) break;
    }
  }

  input.close();
  //////////////////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Initialized " << nodesStored
       << " 50-characters long genome sequences." << endl;
  printf("Time to read genome dataset: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Helper swap function required in quicksort
void FASTAreadset_LL::swap(char **a, char **b) {
  char *temp = *a;
  *a = *b;
  *b = temp;
}

// Helper quicksort algorithm to sort the genome sequences
void FASTAreadset_LL::quicksort(char *arr[], unsigned int length) {
  unsigned int i, piv = 0;
  if (length <= 1) return;
  for (i = 0; i < length; i++) {
    if (strcmp(arr[i], arr[length - 1]) < 0) swap(arr + i, arr + piv++);
  }
  swap(arr + piv, arr + length - 1);
  quicksort(arr, piv++);
  quicksort(arr + piv, length - piv);
}

// Perform the binary search of the genome sequences
int FASTAreadset_LL::performBinarySearch(char toSearch[SEQUENCE_LENGTH],
                                         int left, int right) {
  if (left > right) return -1;
  int mid = left + (right - left) / 2;
  if (strcmp(sortedRead[mid], toSearch) == 0)
    return mid;
  else if (strcmp(sortedRead[mid], toSearch) < 0)
    return performBinarySearch(toSearch, mid + 1, right);
  return performBinarySearch(toSearch, left, mid - 1);
}

// Function to do the binart search on the 2nd genome dataset
void FASTAreadset_LL::binarySearchGenomeDataset() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////

  // First, sort the genome sequences and store in array
  sortedRead = new char *[datasetCount];
  int index = 0;
  Node *current = head;
  while (current != NULL) {
    sortedRead[index] = current->sequenceRead;
    index++;
    current = current->next;
  }
  quicksort(sortedRead, datasetCount);

  // For each sequences in the 2nd dataset, perform search on the sorted array
  current = genomeHead;
  int count = 0;
  int total = 0;
  while (current != NULL) {
    count++;
    int index = performBinarySearch(current->sequenceRead, 0, datasetCount - 1);
    if (index > -1) total++;
    current = current->next;
  }
  cout << total << " 50-characters long sequences match were found" << endl;
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf(
      "Time search all 50-characters long genome sequences: %3.3f seconds. \n",
      totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Function to do the search of 2nd genome dataset naiviely
void FASTAreadset_LL::searchGenomeDataset() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  Node *current = genomeHead;
  int count = 0;
  int total = 0;
  while (current != NULL) {
    count++;
    Node *result = performSearch(current->sequenceRead);
    if (result != NULL) total++;
    current = current->next;
  }
  cout << total << " 50-characters long genome sequences match were found."
       << endl;
  /////////////////////////////////////////////////////

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf(
      "Time search all 50-characters long genome sequences: %3.3f seconds. \n",
      totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Destroy function to deallocate headerNumber and read arrays
FASTAreadset_LL::~FASTAreadset_LL() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////////////////
  // If linkelist of first dataset is not empty, deallocate the memory
  if (head != NULL) {
    Node *current = head;
    Node *next = NULL;

    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
    head = NULL;
  }

  // If linkelist of second dataset is not empty, deallocate the memory
  if (genomeHead != NULL) {
    Node *current = genomeHead;
    Node *next = NULL;

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