#ifndef BLAST_H
#define BLAST_H

#define SPLIT_SEQUENCE_LENGTH 11
#define HASH_TABLE_SIZE 10000

/**
 * * HashNode
 * Struct that stores the radix of sequence and position in the sequence
 */
struct HashNode {
  long unsigned int radix;
  long unsigned int position;
  HashNode* next;
};

/**
 * * BLAST
 * Class that implements the seed based smith waterman algorithm
 */
class BLAST {
private:
  HashNode** hashTable;
  char* subjectSequence;
  int subjectSequenceSize;
  long unsigned int calculateRadix(char* sequence);
  void insertInHashTable(long unsigned int key, int position);
  int* getExtendSubjectPositions(char* querySequence, int queryPosition,
    int sequencePosition);

public:
  BLAST();
  ~BLAST();
  void insertData(char* sequence, int position);
  int findMatch(char* sequence);
  int startBlast(char* sequence, bool doPrint);
  void readSubjectSequencesFromFile(char* filePath);
  void testSubjectWithRandomSequences(int sequencesLimit, bool doPrint);
  char* generateRandomSequenceFromSubject();
  char* generateRandomSequenceFromSubjectWithError(float errorRate);
};

#endif