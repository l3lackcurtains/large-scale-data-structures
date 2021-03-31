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

  char *problem = new char[10];
  char *filePath = new char[100];
  char *filePath2 = new char[100];

  problem = argv[1];
  filePath = argv[2];
  if (argv[3]) filePath2 = argv[3];

  if (strcmp(problem, "problem1A") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    char *sequence;
    sequence = (char *)malloc(sizeof(char) * SARS_FULL_SEQUENCE_LENGTH);
    sequence = readSequenceFromFile(filePath);

    char **testSequences = (char **)malloc(sizeof(char *) * TEST_LENGTH);
    for (int x = 0; x < TEST_LENGTH; x++) {
      testSequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
    }

    testSequences = readTestSequencesFromFile(filePath2);
    for (int x = 0; x < TEST_LENGTH; x++) {
      cout << testSequences[x] << endl;
    }

    for (int x = 0; x < TEST_LENGTH; x++) {
      int bestAlignment =
          smithWaterman(sequence, testSequences[x], -3, 2, -1, true);
      cout << x << ": Best alignment score: " << bestAlignment << endl;
    }

    free(sequence);
    for (int x = 0; x < TEST_LENGTH; x++) free(testSequences[x]);
    free(testSequences);

    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem1B") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    char *sequence;
    sequence = (char *)malloc(sizeof(char) * SARS_FULL_SEQUENCE_LENGTH);
    sequence = readSequenceFromFile(filePath);
    // # 1k sequences
    int sequencesCount = 1000;
    testWithRandomSequences(sequence, sequencesCount);

    // # 10k sequences
    sequencesCount = 10000;
    testWithRandomSequences(sequence, sequencesCount);

    // # 100k sequences
    sequencesCount = 100000;
    testWithRandomSequences(sequence, sequencesCount);

    // # 1m sequences
    sequencesCount = 1000000;
    testWithRandomSequences(sequence, sequencesCount);

    free(sequence);
    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem2A") == 0) {
    char **testSequences = (char **)malloc(sizeof(char *) * TEST_LENGTH);
    for (int x = 0; x < TEST_LENGTH; x++) {
      testSequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH);
    }

    BLAST blast = BLAST(10000);
    blast.readGenomeDataset(filePath);
    testSequences = readTestSequencesFromFile(filePath2);
    cout << "################################################################"
            "###"
         << endl;
    for (int x = 0; x < TEST_LENGTH; x++) {
      cout << "TEST SEQUENCE " << x << endl;
      blast.searchSequence(testSequences[x], true);
      cout << "################################################################"
              "###"
           << endl;
    }
  } else if (strcmp(problem, "problem2B") == 0) {
    BLAST blast = BLAST(10000);
    blast.readGenomeDataset(filePath);

    // # 1k sequences
    int sequencesCount = 1000;
    blast.testWithRandomSequences(sequencesCount, false);

    // # 10k sequences
    sequencesCount = 10000;
    blast.testWithRandomSequences(sequencesCount, false);

    // # 100k sequences
    sequencesCount = 100000;
    blast.testWithRandomSequences(sequencesCount, false);

    // # 1m sequences
    sequencesCount = 1000000;
    blast.testWithRandomSequences(sequencesCount, false);
  }

  return 0;
}