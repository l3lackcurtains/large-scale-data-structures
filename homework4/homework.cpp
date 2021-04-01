#include <string.h>

#include <algorithm>
#include <iostream>

#include "./blast.h"
#include "./smithWaterman.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << endl << endl << "==========================" << endl;
    cout << "Error: 2 input parameters expected" << endl;
    cout << "Proper usage is:" << endl;
    cout << "./homework <problem-flag> <filepath>" << endl;
    cout << "Example:" << endl;
    cout << "./homework problem1A /scratch/vyf2/HW1/sample_hw_dataset.fa"
         << endl;
    cout << "==========================" << endl << endl;
    cout << "exiting..." << endl;
    exit(-1);
  } else {
    cout << "The number of arguments passed: " << argc << endl;
    cout << "The first argument is: " << argv[0] << endl;
    cout << "The second argument is: " << argv[1] << endl;
    cout << "The third argument is: " << argv[2] << endl;
    if (argv[3]) {
      cout << "The fourth argument is: " << argv[3] << endl;
    }
  }

  cout << "===========================================================" << endl;

  srand(time(NULL));

  char *problem = new char[10];
  char *filePath = new char[100];
  char *filePath2 = new char[100];

  problem = argv[1];
  filePath = argv[2];
  if (argv[3]) filePath2 = argv[3];

  /////////////////////////////////////////////////////////////////////////////////////////////////
  if (strcmp(problem, "problem1A") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////

    char *sequence = readSequenceFromFile(filePath);

    char **testSequences = readTestSequencesFromFile(filePath2);

    for (int x = 0; x < TEST_LENGTH; x++) {
      int bestAlignment =
          smithWaterman(sequence, testSequences[x], -3, 2, -1, true);
      cout << x << ": Best alignment score: " << bestAlignment << endl;
    }

    free(sequence);
    for (int x = 0; x < TEST_LENGTH; x++) delete testSequences[x];
    free(testSequences);

    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem1B") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    char *sequence = readSequenceFromFile(filePath);
    // # 1k sequences
    int sequencesCount = 1000;
    testSubjectWithRandomSequences(sequence, sequencesCount);

    // # 10k sequences
    sequencesCount = 10000;
    testSubjectWithRandomSequences(sequence, sequencesCount);

    // # 100k sequences
    sequencesCount = 100000;
    testSubjectWithRandomSequences(sequence, sequencesCount);

    // # 1m sequences
    sequencesCount = 1000000;
    testSubjectWithRandomSequences(sequence, sequencesCount);

    free(sequence);
    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem2A") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////

    BLAST blast = BLAST();
    blast.readSubjectSequencesFromFile(filePath);
    char **testSequences = readTestSequencesFromFile(filePath2);

    cout << "################################################################"
         << endl;
    for (int x = 0; x < TEST_LENGTH; x++) {
      cout << "TEST SEQUENCE " << x << endl;
      blast.startBlast(testSequences[x], true);
      cout << "################################################################"
           << endl;
    }
    for (int x = 0; x < TEST_LENGTH; x++) free(testSequences[x]);
    free(testSequences);
    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem2B") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    BLAST blast = BLAST();
    blast.readSubjectSequencesFromFile(filePath);

    // # 1k sequences
    int sequencesCount = 1000;
    blast.testSubjectWithRandomSequences(sequencesCount, false);

    // # 10k sequences
    sequencesCount = 10000;
    blast.testSubjectWithRandomSequences(sequencesCount, false);

    // # 100k sequences
    sequencesCount = 100000;
    blast.testSubjectWithRandomSequences(sequencesCount, false);

    // # 1m sequences
    sequencesCount = 1000000;
    blast.testSubjectWithRandomSequences(sequencesCount, false);
    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem2C") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    int totalSequences = 100000;

    BLAST blast = BLAST();
    blast.readSubjectSequencesFromFile(filePath);

    int totalFound = 0;
    for (int x = 0; x < totalSequences; x++) {
      char *sequence = blast.generateRandomSequenceFromSubject();
      totalFound += blast.startBlast(sequence, false);
      free(sequence);
    }
    cout << "Total Random Sequences Found: " << totalFound << endl;

    totalFound = 0;
    for (int x = 0; x < totalSequences; x++) {
      char *sequence = blast.generateRandomSequenceFromSubjectWithError(5.0);
      totalFound += blast.startBlast(sequence, false);
      free(sequence);
    }
    cout << "Total Random Sequences Found (5% Error): " << totalFound << endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }

  return 0;
}