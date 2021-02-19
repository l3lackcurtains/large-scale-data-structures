#include "fasta.h"
#include <unistd.h>
#include <string.h>
#include <iostream>

// default constructor
FASTA_readset::FASTA_readset() { }

// Constructor that takes the file path
FASTA_readset::FASTA_readset(string path) {
  filePath = path;
}

// Method to read readLength count of data from the file from its path
void FASTA_readset::readFile(string path, int readLength) {
  // Open the file
  ifstream input;
  input.open(path);

  // helper variables
  int a, b, i, j;

  // Declare and allocate memory for temporary head
  char* tempHeader = new char[100];

  // Allocate memory for headerNumber and read
  headerNumber = new char*[readLength];
  read = new char*[readLength];
  for (int i = 0; i < readLength; i++) {
    read[i] = new char[SEQUENCE_LENGTH];
    headerNumber[i] = new char[8];
  }

  int headerLength;
  for (int i = 0; i < readLength; i++) {
    input >> tempHeader;
    input >> read[i];
    headerLength = 0;

    // Get the header length
    while (tempHeader[headerLength] != '\0') {
      headerLength++;
    }
    a = 2;
    b = a;

    // Get the position before first _
    while (tempHeader[b] != '_' && b < headerLength) {
      b++;
    }
    if (b == headerLength) {
      cout
          << "Error: exhausted header string looking for read number... exiting"
          << endl;
      exit(-1);
    } else {

      // Get the header number from header string.
      for (j = a; j < b; j++) {
        headerNumber[i][j - a] = tempHeader[j];
      }
      headerNumber[i][j] = '\0';
    }
  }
  
  // Close file and delete tenporary head
  input.close();
  delete[] tempHeader;

}

// Method to read file upto the specified length
void FASTA_readset::readFile(int readLength) {
  readFile(filePath, readLength);
}

// Method to initialize the million data
void FASTA_readset::initMillionData() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  /////////////////////////////////////////////////////
  datasetCount = 1000000;
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
void FASTA_readset::initFullData() {
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
void FASTA_readset::printData() {
  for (int i = 0; i < datasetCount; i++) {
    cout << headerNumber[i] << ":";
    cout << read[i] << endl;
  }
}

// Function to get the total unique sequence fragments
void FASTA_readset::totalUniqueSequenceFragments() {

  int totalSequence = 0;
  int lineCounter = 1;

  string line;
  ifstream uniqueInput;
  uniqueInput.open(filePath);

  // Loop through each line of the file
  while (getline(uniqueInput, line)) {
    // counting the sequences located in even position
    if ((lineCounter % 2) == 0) {
      totalSequence++;
    }
    lineCounter++;
  }

  uniqueInput.close();

  cout << "Total unique sequence fragments: " << totalSequence << endl;
  // datasetCount was set to totalSequence for question 3 to get statistics for full data set count (36220411)
  // datasetCount = totalSequence;
}

// Function to count the unique sequences in each datasets
void FASTA_readset::allDatasetTotalUniqueSequenceFragments() {
  ifstream uniqueInput;
  uniqueInput.open(filePath);

  // Declare the count variable for all datasets
  int totalDatasets[ALL_DATASETS_COUNT];
  for (int x = 0; x < ALL_DATASETS_COUNT; x++) {
    totalDatasets[x] = 0;
  }

  // helper variables
  int count, rowPosition, index;

  // temporary head and read variable used in loop
  char *tempRead, *tempHeader;
  tempRead = new char[SEQUENCE_LENGTH];
  tempHeader = new char[100];

  for (int i = 0; i < datasetCount; i++) {
    
    uniqueInput >> tempHeader;
    uniqueInput >> tempRead;

    count = 0;
    rowPosition = 0;
    while (tempHeader[rowPosition] != '_') {
      rowPosition++;
    }
    rowPosition++;
    // Get the dataset position and the value
    // The value is added towards the total dataset count
    while (count <= ALL_DATASETS_COUNT) {
      count++;
      if (tempHeader[rowPosition] >= '0' && tempHeader[rowPosition] <= '9') {
        int value = tempHeader[rowPosition] - '0';
        totalDatasets[count - 1] += value;
      }
      // advance to the new dataset
      rowPosition = rowPosition + 2;
    }
  }

  // delete the temporary variables and close file
  delete[] tempRead;
  delete[] tempHeader;
  uniqueInput.close();

  cout << "Total number of reads for each datasets are as follows:" << endl;
  for (int i = 0; i < ALL_DATASETS_COUNT; i++) {
    cout << "Dataset #" << i + 1 << ": " << totalDatasets[i] << endl;
  }
}

// Function to count the characters count
void FASTA_readset::totalCharacterCounts() {
  int a = 0;
  int c = 0;
  int g = 0;
  int t = 0;

  for (int i = 0; i < datasetCount; i++) {
    for (int j = 0; j < SEQUENCE_LENGTH; j++) {
      if (read[i][j] == 'A') {
        a++;
      } else if (read[i][j] == 'C') {
        c++;
      } else if (read[i][j] == 'G') {
        g++;
      } else if (read[i][j] == 'T') {
        t++;
      }
    }
  }

  cout << "Total number of characters in the data set are as follows:" << endl;
  cout << "A: " << a << endl;
  cout << "C: " << c << endl;
  cout << "G: " << g << endl;
  cout << "T: " << t << endl;
}

// Function to get all the statistics of the genome sequence
void FASTA_readset::getAllStatistics() {
  totalUniqueSequenceFragments();
  cout << "=====================================================" << endl;
  allDatasetTotalUniqueSequenceFragments();
  cout << "=====================================================" << endl;
  readFile(datasetCount);
  totalCharacterCounts();
}

// Helper function for quick sort algorith for swaping
void FASTA_readset::swap(char* stringData[], int i, int j) {
  char* temp = new char[SEQUENCE_LENGTH];
  temp = stringData[i];
  stringData[i] = stringData[j];
  stringData[j] = temp;
}

// Quick sort algorithm function
void FASTA_readset::quickSort(char* stringData[], int left, int right) {
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

// Function to sort the genome sequences read
void FASTA_readset::sortSequenceRead() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  ////////////////////////////////////////////////
  char** temp = new char*[datasetCount];
  for (int i = 0; i < datasetCount; i++) {
    temp[i] = new char[SEQUENCE_LENGTH];
    temp[i] = read[i];
  }

  // Start the quick sort
  quickSort(temp, 0, datasetCount - 1);

  char** sortedRead = new char*[datasetCount];
  for (int i = 0; i < datasetCount; i++) {
    sortedRead[i] = new char[SEQUENCE_LENGTH];
    strcpy(sortedRead[i], temp[i]);
  }

  cout << "First 20 lines after sorting are as follows:" << endl;
  for (int i = 0; i < 20; i++) {
    cout << sortedRead[i] << endl;
  }

  // Deallocate temporary arrays
  delete[] sortedRead;
  delete[] temp;

  //////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  printf("Time to sort genomic sequence: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}

// Destroy function to deallocate headerNumber and read arrays
FASTA_readset::~FASTA_readset() {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();

  for (int i = 0; i < datasetCount; i++) {
    delete[] read[i];
    delete[] headerNumber[i];
  }

  delete[] read;
  delete[] headerNumber;

  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "#####################################################" << endl;
  cout << "Deallocating all array memory.." << endl;
  printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
  ;
  cout << "#####################################################" << endl;
}
