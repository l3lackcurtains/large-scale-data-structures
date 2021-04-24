#include "./smithWaterman.h"

using namespace std;

/**
 * * matchScore
 * Function to check the score of the match
 * @param a sequence 1
 * @param b sequence 2
 * @param gapPenalty gap penalty value
 * @param match match value
 * @param mismatch mismatch value
 * @return match score
 */
int matchScore(char a, char b, int gapPenalty, int match, int mismatch) {
  if (a == b) return match;
  if (a == '_' || b == '_') return gapPenalty;
  return mismatch;
}

/**
 * * getFinalScore
 * Function to check the score of the match
 * @param alignA sequence 1 alignment
 * @param alignB sequence 2 alignment
 * @param alignLength length of the alignment
 * @param gapPenalty gap penalty value
 * @param match match value
 * @param mismatch mismatch value
 * @param doPrint if true prints the alignment of sequences
 * @return final score of the sequences alignment
 */
int getFinalScore(char* alignA, char* alignB, int alignLength, int gapPenalty,
                  int match, int mismatch, bool doPrint) {
  reverse(alignA, alignA + alignLength);
  reverse(alignB, alignB + alignLength);

  int x = 0, y = 0;

  char* symbol = (char*)malloc(sizeof(char) * alignLength);
  int symbolCount = 0;

  int score = 0;

  for (int x = 0; x < alignLength; x++) {
    if (alignA[x] == alignB[x]) {
      symbol[symbolCount++] = '|';
      score += matchScore(alignA[x], alignB[x], gapPenalty, match, mismatch);
    } else if (alignA[x] != alignB[x] && alignA[x] != '_' && alignB[x] != '_') {
      symbol[symbolCount++] = 'x';
      score += matchScore(alignA[x], alignB[x], gapPenalty, match, mismatch);
    } else if (alignA[x] == '_' || alignB[x] == '_') {
      symbol[symbolCount++] = ' ';
      score += gapPenalty;
    }
  }

  if (doPrint) {
    for (int x = 0; x < alignLength; x++) cout << alignA[x];
    cout << endl;

    for (int x = 0; x < alignLength; x++) cout << symbol[x];
    cout << endl;

    for (int x = 0; x < alignLength; x++) cout << alignB[x];
    cout << endl;
  }

  free(symbol);

  return score;
}

/**
 * * smithWaterman
 * Function that performs the smith water man algorithm on two sequences
 * @param sequenceA sequence 1
 * @param sequenceB sequence 2
 * @param gapPenalty gap penalty value
 * @param match match value
 * @param mismatch mismatch value
 * @param doPrint if true prints the alignment of sequences
 * @return the best alignment score
 */
int smithWaterman(char* sequenceA, char* sequenceB, int gapPenalty, int match,
                  int mismatch, bool doPrint) {
  int sequenceALength = strlen(sequenceA) + 1;
  int sequenceBLength = strlen(sequenceB) + 1;

  // Build the score and trace matrix
  int **scoreMatrix, **traceMatrix;
  scoreMatrix = (int**)malloc(sizeof(int*) * sequenceALength);
  traceMatrix = (int**)malloc(sizeof(int*) * sequenceALength);

  for (int x = 0; x < sequenceALength; x++) {
    scoreMatrix[x] = (int*)malloc(sizeof(int) * sequenceBLength);
    traceMatrix[x] = (int*)malloc(sizeof(int) * sequenceBLength);
  }

  // Initialize the matices
  for (int x = 0; x < sequenceALength; x++) {
    for (int y = 0; y < sequenceBLength; y++) {
      scoreMatrix[x][y] = 0;
      traceMatrix[x][y] = 0;
    }
  }

  int maxScore = 0;
  int maxX, maxY;

  // Scan through the sequence and fill the matrices
  for (int x = 1; x < sequenceALength; x++) {
    for (int y = 1; y < sequenceBLength; y++) {
      int diagonalScore = scoreMatrix[x - 1][y - 1] +
                          matchScore(sequenceA[x - 1], sequenceB[y - 1],
                                     gapPenalty, match, mismatch);
      int upScore = scoreMatrix[x][y - 1] + gapPenalty;
      int leftScore = scoreMatrix[x - 1][y] + gapPenalty;
      scoreMatrix[x][y] = max({0, diagonalScore, leftScore, upScore});

      if (scoreMatrix[x][y] == 0) {
        traceMatrix[x][y] = END;
      }

      if (scoreMatrix[x][y] == leftScore) {
        traceMatrix[x][y] = UP;
      }

      if (scoreMatrix[x][y] == upScore) {
        traceMatrix[x][y] = LEFT;
      }

      if (scoreMatrix[x][y] == diagonalScore) {
        traceMatrix[x][y] = DIAG;
      }

      if (scoreMatrix[x][y] >= maxScore) {
        maxX = x;
        maxY = y;
        maxScore = scoreMatrix[x][y];
      }
    }
  }

  char *alignA, *alignB;
  alignA = (char*)malloc(sizeof(char) * sequenceALength * sequenceBLength);
  alignB = (char*)malloc(sizeof(char) * sequenceALength * sequenceBLength);

  int alignCount = 0;

  int x = maxX;
  int y = maxY;

  // Get the aligned sequences
  while (traceMatrix[x][y] != END) {
    if (traceMatrix[x][y] == DIAG) {
      alignA[alignCount] = sequenceA[x - 1];
      alignB[alignCount] = sequenceB[y - 1];
      alignCount++;
      x--;
      y--;
    } else if (traceMatrix[x][y] == LEFT) {
      alignA[alignCount] = '_';
      alignB[alignCount] = sequenceB[y - 1];
      alignCount++;
      y--;
    } else if (traceMatrix[x][y] == UP) {
      alignA[alignCount] = sequenceA[x - 1];
      alignB[alignCount] = '_';
      alignCount++;
      x--;
    }
  }
  alignA[alignCount] = '\0';
  alignB[alignCount] = '\0';

  // Get the alignment socre
  int finalScore = getFinalScore(alignA, alignB, alignCount, gapPenalty, match,
                                 mismatch, doPrint);

  free(alignA);
  free(alignB);
  for (int x = 0; x < sequenceALength; x++) {
    free(scoreMatrix[x]);
    free(traceMatrix[x]);
  }
  free(scoreMatrix);
  free(traceMatrix);

  return finalScore;
}

int getSubjectLength(char* filePath) {
  ifstream input;
  input.open(filePath);

  char c = '\0';
  int characterCount = 0;

  while (c != '\n') {
    input.get(c);
  }

  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      characterCount++;
    }
  }
  return characterCount;
}

/**
 * * readSequenceFromFile
 * Function that read file for the subject sequence
 * @param filePath file path of the subject
 * @return sequence read
 */
char* readSequenceFromFile(char* filePath) {
  ifstream input;
  input.open(filePath);
  int subjectLength = getSubjectLength(filePath);
  char* sequence = (char*)malloc(sizeof(char) * subjectLength);

  char c = '\0';
  int characterCount = 0;

  while (c != '\n') {
    input.get(c);
  }

  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      sequence[characterCount] = c;
      characterCount++;
    }
  }
  sequence[characterCount] = '\0';
  cout << "Initialized " << characterCount << " character sequences." << endl;
  input.close();
  return sequence;
}

/**
 * * readTestSequencesFromFile
 * Function that read file for the test sequences
 * @param filePath file path of the test sequences
 * @return sequences read
 */
char** readTestSequencesFromFile(char* filePath) {
  char** testSequences = (char**)malloc(sizeof(char*) * TEST_LENGTH);
  for (int x = 0; x < TEST_LENGTH; x++) {
    testSequences[x] = (char*)malloc(sizeof(char) * SEQUENCE_LENGTH);
  }

  ifstream input;
  input.open(filePath);

  char* tempHeader = new char[100];
  int readCount = 0;

  while (!input.eof()) {
    input >> tempHeader;
    input >> testSequences[readCount];
    testSequences[readCount][SEQUENCE_LENGTH] = '\0';
    readCount++;
  }

  delete[] tempHeader;
  input.close();

  return testSequences;
}

/**
 * * generateRandomSequence
 * Function to generate the random sequence of size SEQUENCE_LENGTH
 * @return random sequence
 */
char* generateRandomSequence() {
  int randomNumber;
  char* sequence = (char*)malloc(sizeof(char) * SEQUENCE_LENGTH);
  for (int y = 0; y < SEQUENCE_LENGTH; y++) {
    randomNumber = rand() % 4;
    switch (randomNumber) {
      case 0:
        sequence[y] = 'A';
        break;
      case 1:
        sequence[y] = 'C';
        break;
      case 2:
        sequence[y] = 'G';
        break;
      case 3:
        sequence[y] = 'T';
        break;
      default:
        break;
    }
  }
  sequence[SEQUENCE_LENGTH] = '\0';
  return sequence;
}

/**
 * * testSubjectWithRandomSequences
 * Function that read the subject sequence and test on random sequences of
 * length sequencesLimit
 * @param sequence subject sequence
 * @param sequencesLimit random sequences limit
 */
void testSubjectWithRandomSequences(char* sequence, int sequencesLimit) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();
  //////////////////////////////////////////////////////////////////////
  for (int x = 0; x < sequencesLimit; x++) {
    char* testSequence = generateRandomSequence();
    smithWaterman(sequence, testSequence, -3, 2, -1, false);
    free(testSequence);
  }
  //////////////////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("Time to test Smith Waterman with %d sequence: %3.3f seconds. \n",
         sequencesLimit, totalTime);
}