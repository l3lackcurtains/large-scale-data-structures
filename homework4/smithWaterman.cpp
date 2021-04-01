#include "./smithWaterman.h"

using namespace std;

int matchScore(char a, char b, int gapPenalty, int match, int mismatch) {
  if (a == b) return match;
  if (a == '_' || b == '_') return gapPenalty;
  return mismatch;
}

int getFinalScore(char *alignA, char *alignB, int alignLength, int gapPenalty,
                  int match, int mismatch, bool doPrint) {

  char *finalAlignA = (char *)malloc(sizeof(char) * alignLength);
  char * finalAlignB = (char *)malloc(sizeof(char) * alignLength);

  for(int x = 0; x < alignLength; x++) {
    finalAlignA[x] = alignA[alignLength - x - 1];
    finalAlignB[x] = alignB[alignLength - x - 1];
  }

  int x = 0, y = 0;

  char *symbol = (char *)malloc(sizeof(char) * alignLength);
  int symbolCount = 0;

  int score = 0;

  for (int x = 0; x < alignLength; x++) {
    if (finalAlignA[x] == finalAlignB[x]) {
      symbol[symbolCount++] = '|';
      score += matchScore(finalAlignA[x], finalAlignB[x], gapPenalty, match, mismatch);
    } else if (finalAlignA[x] != finalAlignB[x] && finalAlignA[x] != '_' && finalAlignB[x] != '_') {
      symbol[symbolCount++] = 'x';
      score += matchScore(finalAlignA[x], finalAlignB[x], gapPenalty, match, mismatch);
    } else if (finalAlignA[x] == '_' || finalAlignB[x] == '_') {
      symbol[symbolCount++] = ' ';
      score += gapPenalty;
    }
  }

  if (doPrint) {
    for (int x = 0; x < alignLength; x++) cout << finalAlignA[x];
    cout << endl;

    for (int x = 0; x < alignLength; x++) cout << symbol[x];
    cout << endl;

    for (int x = 0; x < alignLength; x++) cout << finalAlignB[x];
    cout << endl;
  }

  free(symbol);
  free(finalAlignA);
  free(finalAlignB);

  return score;
}

int smithWaterman(char *sequenceA, char *sequenceB, int gapPenalty, int match, int mismatch, bool doPrint) {
  
  int sequenceALength = strlen(sequenceA) + 1;
  int sequenceBLength = strlen(sequenceB) + 1;

  int **scoreMatrix, **traceMatrix;
  scoreMatrix = (int **)malloc(sizeof(int *) * sequenceALength);
  traceMatrix = (int **)malloc(sizeof(int *) * sequenceALength);

  for (int x = 0; x < sequenceALength; x++) {
    scoreMatrix[x] = (int *)malloc(sizeof(int) * sequenceBLength);
    traceMatrix[x] = (int *)malloc(sizeof(int) * sequenceBLength);
  }

  for (int x = 0; x < sequenceALength; x++) {
    for (int y = 0; y < sequenceBLength; y++) {
      scoreMatrix[x][y] = 0;
      traceMatrix[x][y] = 0;
    }
  }

  int maxScore = 0;
  int maxX, maxY;

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
  alignA = (char *)malloc(sizeof(char) * sequenceALength);
  alignB = (char *)malloc(sizeof(char) * sequenceBLength);

  int alignCount = 0;

  int x = maxX;
  int y = maxY;

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

  int finalScore = getFinalScore(alignA, alignB, alignCount,
                                 gapPenalty, match, mismatch, doPrint);

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

char *readSequenceFromFile(char *filePath) {
  ifstream input;
  input.open(filePath);
  char *sequence = (char *)malloc(sizeof(char) * SARS_FULL_SEQUENCE_LENGTH);

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

  cout << "Initialized " << characterCount << " character sequences." << endl;

  input.close();

  return sequence;
}

char **readTestSequencesFromFile(char *filePath) {
  char **testSequences = (char **)malloc(sizeof(char *) * TEST_LENGTH);
  for (int x = 0; x < TEST_LENGTH; x++) {
    testSequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
  }

  ifstream input;
  input.open(filePath);

  char *tempHeader = new char[100];
  int readCount = 0;

  while (!input.eof()) {
    input >> tempHeader;
    input >> testSequences[readCount];
    readCount++;
  }

  delete[] tempHeader;
  input.close();

  return testSequences;
}

char* generateRandomSequence() {
  int randomNumber;
  char *sequence = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
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
  return sequence;
}

void testSubjectWithRandomSequences(char *sequence, int sequencesCount) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();
  //////////////////////////////////////////////////////////////////////
  for (int x = 0; x < sequencesCount; x++) {
    char* testSequence = generateRandomSequence();
    smithWaterman(sequence, testSequence, -3, 2, -1, false);
    free(testSequence);
  }
  

  //////////////////////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("Time to test Smith Waterman with %d sequence: %3.3f seconds. \n", sequencesCount, totalTime);

  
}