#include "blast.h"

#include "math.h"
#include "smithWaterman.h"


/**
 * * BLAST::~BLAST
 * Blast constructor that initialize the hash table
 */
BLAST::BLAST() {
  hashTable = new HashNode * [HASH_TABLE_SIZE];
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    hashTable[i] = NULL;
  }
}


/**
 * * BLAST::insertData
 * Helper function to insert data in hash table
 * @param sequence sequence to insert in hash table
 * @param position position of the sequence in subject
 */
void BLAST::insertData(char* sequence, int position) {
  unsigned int radixValue = calculateRadix(sequence);
  insertInHashTable(radixValue, position);
}

/**
 * * BLAST::insertInHashTable
 * Inner function to insert data in hash table
 * @param key key of the hash table
 * @param position position of the sequence in subject
 */
void BLAST::insertInHashTable(long unsigned int key, int position) {
  int index = key % HASH_TABLE_SIZE;
  HashNode* temp = hashTable[index];
  HashNode* entry = new HashNode;
  entry->radix = key;
  entry->position = position;
  entry->next = NULL;
  if (temp == NULL) {
    hashTable[index] = entry;
  }
  else {
    hashTable[index] = entry;
    entry->next = temp;
  }
}

/**
 * * BLAST::calculateRadix
 * Helper function to calculate the radix from sequence
 * @param sequence sequence to calculate the radix
 * @return radix value
 */
long unsigned int BLAST::calculateRadix(char* sequence) {
  unsigned int radixVal = 0;
  int i = SPLIT_SEQUENCE_LENGTH - 1;
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

/**
 * * BLAST::findMatch
 * Function to find the match of the sequence
 * @param sequence sequence to find the match
 * @return The position of the match
 */
int BLAST::findMatch(char* sequence) {
  long unsigned int radixValue = calculateRadix(sequence);
  int index = radixValue % HASH_TABLE_SIZE;
  HashNode* current = hashTable[index];
  if (current == NULL) {
    return -1;
  }

  int found = -1;
  while (current != NULL) {
    if (current->radix == radixValue) {
      found = current->position;
      break;
    }
    current = current->next;
  }
  return found;
}

/**
 * * BLAST::readSubjectSequencesFromFile
 * Function to read the subject file and store sequences in hash table
 * @param filePath Subject file path
 */
void BLAST::readSubjectSequencesFromFile(char* filePath) {
  ifstream input;
  input.open(filePath);

  subjectSequenceSize = getSubjectLength(filePath);
  subjectSequence = (char*)malloc(sizeof(char) * subjectSequenceSize);

  char c = '\0';
  int characterCount = 0;

  while (c != '\n') {
    input.get(c);
  }

  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      subjectSequence[characterCount] = c;
      characterCount++;
    }
  }
  cout << "Initialized " << characterCount << " character sequences." << endl;

  input.close();

  char* tempRead;
  tempRead = new char[SPLIT_SEQUENCE_LENGTH];
  characterCount = 0;
  int nodesStored = 0;

  for (int x = 0; x < subjectSequenceSize; x++) {
    c = subjectSequence[x];
    tempRead[characterCount] = c;
    characterCount++;
    if (characterCount == SPLIT_SEQUENCE_LENGTH) {
      insertData(tempRead, nodesStored);
      nodesStored++;
      characterCount = SPLIT_SEQUENCE_LENGTH - 1;
      for (int i = 1; i < SPLIT_SEQUENCE_LENGTH; i++) {
        tempRead[i - 1] = tempRead[i];
      }
    }
  }
  delete[] tempRead;
  cout << "Broken down into " << nodesStored << " 11-mers sequences." << endl;
  cout << "===========================================================" << endl;
}

/**
 * * BLAST::getExtendSubjectPositions
 * Function to return the extended position of the subject sequence
 * @param querySequence query sequence
 * @param queryPosition Query position in parent sequence
 * @param subjectSequencePosition Subject sequence in parent sequence
 * @return array of left and right extended position of the subject sequence
 */
int* BLAST::getExtendSubjectPositions(char* querySequence, int queryPosition,
  int subjectSequencePosition) {
  int sequenceleft = 0, sequenceRight = 0;
  int leftCounter = 1;
  int rightCounter = 1;

  bool mismatch = false;

  while (!mismatch) {
    bool checkLimit =
      (queryPosition - leftCounter) >= 0 && (subjectSequencePosition - leftCounter);

    if (checkLimit && querySequence[queryPosition - leftCounter] ==
      subjectSequence[subjectSequencePosition - leftCounter]) {
      leftCounter++;
      sequenceleft++;
    }
    else {
      mismatch = true;
    }
  }

  mismatch = false;

  while (!mismatch) {
    bool checkLimit =
      (queryPosition + SPLIT_SEQUENCE_LENGTH + rightCounter - 1) <
      SEQUENCE_LENGTH &&
      (subjectSequencePosition + SPLIT_SEQUENCE_LENGTH + rightCounter - 1) <
      subjectSequenceSize;

    if (checkLimit &&
      querySequence[queryPosition + SPLIT_SEQUENCE_LENGTH + rightCounter -
      1] ==
      subjectSequence[subjectSequencePosition + SPLIT_SEQUENCE_LENGTH +
      rightCounter - 1]) {
      rightCounter++;
      sequenceRight++;
    }
    else {
      mismatch = true;
    }
  }
  int* leftRightPosition = (int*)malloc(sizeof(int) * 2);

  leftRightPosition[0] = subjectSequencePosition - sequenceleft;
  leftRightPosition[1] =
    subjectSequencePosition + SPLIT_SEQUENCE_LENGTH + sequenceRight;
  return leftRightPosition;
}

/**
 * * BLAST::startBlast
 * Function to start the blast on the sequence
 * @param sequence query sequence
 * @param doPrint When true prints the genome sequences alignment
 * @return Best alignment
 */
int BLAST::startBlast(char* sequence, bool doPrint) {
  char* tempRead;
  tempRead = new char[SPLIT_SEQUENCE_LENGTH];
  int characterCount = 0;
  int nodesStored = 0;
  int foundSubject = -1;
  int foundQuery = -1;
  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    char c = sequence[x];
    tempRead[characterCount] = c;
    characterCount++;
    if (characterCount == SPLIT_SEQUENCE_LENGTH) {
      foundSubject = findMatch(tempRead);

      if (foundSubject > -1) {
        foundQuery = nodesStored;
        break;
      }

      nodesStored++;
      characterCount = SPLIT_SEQUENCE_LENGTH - 1;
      for (int i = 1; i < SPLIT_SEQUENCE_LENGTH; i++) {
        tempRead[i - 1] = tempRead[i];
      }
    }
  }

  if (foundQuery == -1) {
    if (doPrint) cout << "No Match found" << endl;
    return 0;
  }

  int* leftRightPosition = getExtendSubjectPositions(sequence, foundQuery, foundSubject);

  char* subjectSequenceFragment = (char*)malloc(
    sizeof(char) * (leftRightPosition[1] - leftRightPosition[0]));

  int fragmentPosition = 0;
  for (int x = leftRightPosition[0]; x < leftRightPosition[1]; x++) {
    subjectSequenceFragment[fragmentPosition++] = subjectSequence[x];
  }

  int bestAlignment =
    smithWaterman(sequence, subjectSequenceFragment, -3, 2, -1, doPrint);

  if (doPrint) cout << "Best alignment score: " << bestAlignment << endl;

  free(leftRightPosition);
  free(subjectSequenceFragment);

  return 1;
}

/**
 * * BLAST::testSubjectWithRandomSequences
 * Function to test the subject with random sequences
 * @param sequencesLimit number of random sequences to generate
 * @param doPrint When true prints the genome sequences alignment
 */
void BLAST::testSubjectWithRandomSequences(int sequencesLimit, bool doPrint) {

  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();
  //////////////////////////////////////////////////////////////////////
  for (int x = 0; x < sequencesLimit; x++) {
    char* sequence = generateRandomSequence();
    startBlast(sequence, doPrint);
    free(sequence);
  }

  //////////////////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("Time to test BLAST with %d sequence: %3.3f seconds. \n", sequencesLimit, totalTime);
}

/**
 * * BLAST::generateRandomSequenceFromSubject
 * Function to generate random sequence
 * @return generated sequence
 */
char* BLAST::generateRandomSequenceFromSubject() {
  char* sequence = (char*)malloc(sizeof(char) * SEQUENCE_LENGTH);

  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    int randomNumber = rand() % subjectSequenceSize;
    sequence[x] = subjectSequence[randomNumber];
  }
  sequence[SEQUENCE_LENGTH] = '\0';

  return sequence;
}

/**
 * * BLAST::generateRandomSequenceFromSubjectWithError
 * Function to generate random sequence
 * @param errorRate Error rate
 * @return generated sequence
 */
char* BLAST::generateRandomSequenceFromSubjectWithError(float errorRate) {
  int randomNumber;
  char* sequence = (char*)malloc(sizeof(char) * SEQUENCE_LENGTH);

  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    randomNumber = rand() % subjectSequenceSize;
    float percentage = (randomNumber / subjectSequenceSize) * 100;
    if (percentage < errorRate) {
      int randomCharacter = rand() % 4;
      switch (randomCharacter) {
      case 0:
        if (subjectSequence[randomNumber] == 'A') {
          sequence[x] = 'C';
        }
        else {
          sequence[x] = 'A';
        }
        break;
      case 1:
        if (subjectSequence[randomNumber] == 'C') {
          sequence[x] = 'G';
        }
        else {
          sequence[x] = 'C';
        }
        break;
      case 2:
        if (subjectSequence[randomNumber] == 'G') {
          sequence[x] = 'T';
        }
        else {
          sequence[x] = 'G';
        }
        break;
      case 3:
        if (subjectSequence[randomNumber] == 'T') {
          sequence[x] = 'A';
        }
        else {
          sequence[x] = 'T';
        }
        break;
      default:
        break;
      }
    }
    else {
      sequence[x] = subjectSequence[randomNumber];
    }
  }
  sequence[SEQUENCE_LENGTH] = '\0';

  return sequence;
}

/**
 * * BLAST::~BLAST
 * Destroy function to deallocate all data structures
 */
BLAST::~BLAST() {
  /////////////////////////////////////////////////////////////////
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode* head = hashTable[i];
    if (head != NULL) {
      HashNode* current = head;
      HashNode* next = NULL;

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
  free(subjectSequence);
  //////////////////////////////////////////////////////////////////
}
