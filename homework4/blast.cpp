#include "blast.h"

#include "math.h"
#include "smithWaterman.h"

BLAST::BLAST(int hashSize) {
  srand(time(NULL));
  datasetCount = 0;
  hashTableSize = hashSize;

  hashTable = new HashNode *[hashTableSize];

  for (int i = 0; i < hashTableSize; i++) {
    hashTable[i] = NULL;
  }

  subjectSequence = (char *)malloc(sizeof(char) * SARS_FULL_SEQUENCE_LENGTH);
}

// Helper function to insert data in hash table
void BLAST::insertData(char *sequence, int position) {
  unsigned int radixValue = calculateRadix(sequence);
  insertInHashTable(radixValue, position);
  datasetCount++;
}

// Function to insert data in hash table
void BLAST::insertInHashTable(long unsigned int key, int position) {
  int index = key % hashTableSize;
  HashNode *temp = hashTable[index];
  HashNode *entry = new HashNode;
  entry->radix = key;
  entry->position = position;
  entry->next = NULL;
  if (temp == NULL) {
    hashTable[index] = entry;
  } else {
    hashTable[index] = entry;
    entry->next = temp;
  }
}

// Helper function to calculate the radix from sequence
long unsigned int BLAST::calculateRadix(char *sequence) {
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

// Function to search single genome sequence
int BLAST::findMatch(char *sequence) {
  long unsigned int radixValue = calculateRadix(sequence);
  int index = radixValue % hashTableSize;
  HashNode *current = hashTable[index];
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

void BLAST::readSubjectSequencesFromFile(char *filePath) {
  ifstream input;
  input.open(filePath);
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

  char *tempRead;
  tempRead = new char[SPLIT_SEQUENCE_LENGTH];
  characterCount = 0;
  int nodesStored = 0;

  for (int x = 0; x < SARS_FULL_SEQUENCE_LENGTH; x++) {
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
  cout << "Initialized " << nodesStored << " 11-mers sequences." << endl;
}

int *BLAST::getExtendSubjectPositions(char *querySequence, int queryPosition,
                                      int sequencePosition) {
  int sequenceleft = 0, sequenceRight = 0;
  int leftCounter = 1;
  int rightCounter = 1;

  bool mismatch = false;

  while (!mismatch) {
    bool checkLimit =
        (queryPosition - leftCounter) >= 0 && (sequencePosition - leftCounter);

    if (checkLimit && querySequence[queryPosition - leftCounter] ==
                          subjectSequence[sequencePosition - leftCounter]) {
      leftCounter++;
      sequenceleft++;
    } else {
      mismatch = true;
    }
  }

  mismatch = false;

  while (!mismatch) {
    bool checkLimit =
        (queryPosition + SPLIT_SEQUENCE_LENGTH + rightCounter - 1) <
            SEQUENCE_LENGTH &&
        (sequencePosition + SPLIT_SEQUENCE_LENGTH + rightCounter - 1) <
            SARS_FULL_SEQUENCE_LENGTH;

    if (checkLimit &&
        querySequence[queryPosition + SPLIT_SEQUENCE_LENGTH + rightCounter -
                      1] ==
            subjectSequence[sequencePosition + SPLIT_SEQUENCE_LENGTH +
                            rightCounter - 1]) {
      rightCounter++;
      sequenceRight++;
    } else {
      mismatch = true;
    }
  }
  int *leftRightPosition = (int *)malloc(sizeof(int) * 2);
  leftRightPosition[0] = sequencePosition - sequenceleft;
  leftRightPosition[1] =
      sequencePosition + SPLIT_SEQUENCE_LENGTH + sequenceRight;

  return leftRightPosition;
}

int BLAST::startBlast(char *sequence, bool doPrint) {
  char *tempRead;
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

  int *leftRightPosition = (int *)malloc(sizeof(int) * 2);

  leftRightPosition =
      getExtendSubjectPositions(sequence, foundQuery, foundSubject);

  char *subjectSequenceFragment = (char *)malloc(
      sizeof(char) * (leftRightPosition[1] - leftRightPosition[0]));

  int fragmentPosition = 0;
  for (int x = leftRightPosition[0]; x < leftRightPosition[1]; x++) {
    subjectSequenceFragment[fragmentPosition++] = subjectSequence[x];
  }

  int bestAlignment =
      smithWaterman(sequence, subjectSequenceFragment, -3, 2, -1, doPrint);

  if (doPrint) cout << "Best alignment score: " << bestAlignment << endl;

  return 1;
}

void BLAST::testSubjectWithRandomSequences(int sequencesLimit, bool doPrint) {
  char **sequences;
  sequences = (char **)malloc(sizeof(char *) * sequencesLimit);
  for (int x = 0; x < sequencesLimit; x++) {
    sequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
  }
  sequences = generateRandomSequences(sequencesLimit);
  for (int x = 0; x < sequencesLimit; x++) {
    startBlast(sequences[x], doPrint);
  }
  for (int x = 0; x < sequencesLimit; x++) free(sequences[x]);
  free(sequences);
}

char *BLAST::generateRandomSequenceFromSubject() {
  char *sequence = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);

  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    int randomNumber = rand() % SARS_FULL_SEQUENCE_LENGTH;
    sequence[x] = subjectSequence[randomNumber];
  }

  return sequence;
}

char *BLAST::generateRandomSequenceFromSubjectWithError(float errorRate) {
  int randomNumber;
  char *sequence = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);

  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    randomNumber = rand() % SARS_FULL_SEQUENCE_LENGTH;
    float percentage = (randomNumber / SARS_FULL_SEQUENCE_LENGTH) * 100;
    if (percentage < errorRate) {
      randomNumber = rand() % 4;
      switch (randomNumber) {
        case 0:
          sequence[x] = 'A';
          break;
        case 1:
          sequence[x] = 'C';
          break;
        case 2:
          sequence[x] = 'G';
          break;
        case 3:
          sequence[x] = 'T';
          break;

        default:
          break;
      }
    } else {
      sequence[x] = subjectSequence[randomNumber];
    }
  }

  return sequence;
}

// Destroy function to deallocate all data structures
BLAST::~BLAST() {
  /////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
}
