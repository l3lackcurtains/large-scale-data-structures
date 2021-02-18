#include "fasta.h"
#include <unistd.h>

#include <iostream>

FASTA_readset::FASTA_readset() { }

FASTA_readset::FASTA_readset(string path) {
  filePath = path;
}

void FASTA_readset::readFile(string path, int readLength) {
  ifstream input;
  input.open(path);
  int a, b, i, j;

  char* tempHeader = new char[100];
  char* tempRead = new char[SEQUENCE_LENGTH];
  int tempSequenceLength = 0;

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
    while (tempHeader[headerLength] != '\0') {
      headerLength++;
    }

    a = 2;
    b = a;

    while (tempHeader[b] != '_' && b < headerLength) {
      b++;
    }

    if (b == headerLength) {
      cout
          << "Error: exhausted header string looking for read number... exiting"
          << endl;
      exit(-1);
    } else {
      for (j = a; j < b; j++) {
        headerNumber[i][j - a] = tempHeader[j];
      }
      headerNumber[i][j] = '\0';
    }
  }
  
  input.close();
  delete[] tempHeader;

}

void FASTA_readset::readFile(int readLength) { readFile(filePath, readLength); }

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

  // sleep(60);
}

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
  
  // sleep(60);
}

void FASTA_readset::printData() {
  for (int i = 0; i < datasetCount; i++) {
    cout << headerNumber[i] << ":";
    cout << read[i] << endl;
  }
}

void FASTA_readset::totalUniqueSequenceFragments() {
  int totalSequence = 0;
  int lineCounter = 1;
  string line;
  ifstream uniqueInput;
  uniqueInput.open(filePath);

  while (getline(uniqueInput, line)) {
    if ((lineCounter % 2) == 0) {
      totalSequence++;
    }
    lineCounter++;
  }

  uniqueInput.close();

  cout << "Total unique sequence fragments: " << totalSequence << endl;

  // datasetCount = totalSequence;
}

void FASTA_readset::allDatasetTotalUniqueSequenceFragments() {
  ifstream uniqueInput;
  uniqueInput.open(filePath);

  int totalDatasets[ALL_DATASETS_COUNT];
  for (int x = 0; x < ALL_DATASETS_COUNT; x++) {
    totalDatasets[x] = 0;
  }

  int count, rowPosition, index;
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
    while (count <= ALL_DATASETS_COUNT) {
      count++;
      if (tempHeader[rowPosition] >= '0' && tempHeader[rowPosition] <= '9') {
        int value = tempHeader[rowPosition] - '0';
        totalDatasets[count - 1] += value;
      }
      rowPosition = rowPosition + 2;
    }
  }

  delete[] tempRead;
  delete[] tempHeader;

  uniqueInput.close();

  cout << "Total number of reads for each datasets are as follows:" << endl;

  for (int i = 0; i < ALL_DATASETS_COUNT; i++) {
    cout << "Dataset #" << i + 1 << ": " << totalDatasets[i] << endl;
  }
}

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

void FASTA_readset::getAllStatistics() {
  totalUniqueSequenceFragments();
  cout << "=====================================================" << endl;
  allDatasetTotalUniqueSequenceFragments();
  cout << "=====================================================" << endl;
  readFile(datasetCount);
  totalCharacterCounts();
}

void FASTA_readset::swap(char* stringData[], int i, int j) {
  char* temp = new char[SEQUENCE_LENGTH];
  temp = stringData[i];
  stringData[i] = stringData[j];
  stringData[j] = temp;
}

int FASTA_readset::customStrCmp(const char *a, const char *b)
{
    while (*a && *a == *b) { ++a; ++b; }
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

void FASTA_readset::quickSort(char* stringData[], int left, int right) {
  if (left >= right) {
    return;
  }
  swap(stringData, left, (left + right) / 2);
  int last = left;

  for (int i = left + 1; i <= right; i++) {
    if (customStrCmp(stringData[i], stringData[left]) < 0) {
      swap(stringData, ++last, i);
    }
  }
  swap(stringData, left, last);
  quickSort(stringData, left, last - 1);
  quickSort(stringData, last + 1, right);
}

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

  quickSort(temp, 0, datasetCount - 1);

  char** sortedRead = new char*[datasetCount];
  for (int i = 0; i < datasetCount; i++) {
    sortedRead[i] = new char[SEQUENCE_LENGTH];
    strcpy(sortedRead[i], temp[i]);
  }

  cout << "First 10 lines after sorting are as follows:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << sortedRead[i] << endl;
  }

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
