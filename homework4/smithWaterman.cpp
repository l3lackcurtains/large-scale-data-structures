#include "./smithWaterman.h"

using namespace std;

int matchScore(char a, char b, int gapPenalty, int match, int mismatch) {
  if (a == b) return match;
  if (a == '_' || b == '_') return gapPenalty;
  return mismatch;
}

int getFinalScore(char *alignA, char *alignB, int alignLength, int gapPenalty,
                  int match, int mismatch, bool doPrint) {
  reverse(alignA, alignA + alignLength);
  reverse(alignB, alignB + alignLength);

  int x = 0, y = 0;

  char *symbol;
  symbol = (char *)malloc(sizeof(char) * alignLength);
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

  return score;
}

int smithWaterman(const char *sequenceA, const char *sequenceB, int gapPenalty,
                  int match, int mismatch, bool doPrint) {
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

  char *finalAlignA, *finalAlignB;
  finalAlignA = (char *)malloc(sizeof(char) * alignCount);
  finalAlignB = (char *)malloc(sizeof(char) * alignCount);

  strncpy(finalAlignA, alignA, alignCount);
  strncpy(finalAlignB, alignB, alignCount);

  int finalScore = getFinalScore(finalAlignA, finalAlignB, alignCount,
                                 gapPenalty, match, mismatch, doPrint);

  return finalScore;
}

char *readSequenceFromFile(char *filePath) {
  ifstream input;
  input.open(filePath);
  char *tempRead;
  tempRead = (char *)malloc(sizeof(char) * SARS_FULL_SEQUENCE_LENGTH);

  char c = '\0';
  int characterCount = 0;

  while (c != '\n') {
    input.get(c);
  }

  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      tempRead[characterCount] = c;
      characterCount++;
    }
  }
  tempRead[characterCount] = '\0';

  cout << "Initialized " << characterCount << " character sequences." << endl;

  input.close();

  return tempRead;
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

char **generateRandomSequences(int sequencesCount) {
  int randomNumber;
  char **sequences = (char **)malloc(sizeof(char *) * sequencesCount);
  for (int x = 0; x < sequencesCount; x++) {
    sequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
  }

  for (int x = 0; x < sequencesCount; x++) {
    for (int y = 0; y < SEQUENCE_LENGTH; y++) {
      randomNumber = rand() % 4;
      switch (randomNumber) {
        case 0:
          sequences[x][y] = 'A';
          break;
        case 1:
          sequences[x][y] = 'C';
          break;
        case 2:
          sequences[x][y] = 'G';
          break;
        case 3:
          sequences[x][y] = 'T';
          break;

        default:
          break;
      }
    }
  }

  return sequences;
}

void testSubjectWithRandomSequences(char *sequence, int sequencesCount) {
  char **sequences;
  sequences = (char **)malloc(sizeof(char *) * sequencesCount);
  for (int x = 0; x < sequencesCount; x++) {
    sequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
  }
  sequences = generateRandomSequences(sequencesCount);
  for (int x = 0; x < sequencesCount; x++) {
    smithWaterman(sequence, sequences[x], -3, 2, -1, false);
  }
  for (int x = 0; x < sequencesCount; x++) free(sequences[x]);
  free(sequences);
}