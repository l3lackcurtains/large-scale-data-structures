#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

#include <string.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#define TEST_LENGTH 15
#define SEQUENCE_LENGTH 50

using namespace std;

/**
 * * direction
 * ENUM that reference the matrix movement direction
 */
enum direction { END, UP, LEFT, DIAG };

int matchScore(char a, char b, int gapPenalty, int match, int mismatch);
int getFinalScore(char* alignA, char* alignB, int alignLength, int gapPenalty,
    int match, int mismatch, bool doPrint);
int smithWaterman(char* sequenceA, char* sequenceB, int gapPenalty, int match,
    int mismatch, bool doPrint);
char* readSequenceFromFile(char* filePath);
char** readTestSequencesFromFile(char* filePath);
char* generateRandomSequence();
void testSubjectWithRandomSequences(char* sequence, int sequencesCount);
int getSubjectLength(char* filePath);

#endif