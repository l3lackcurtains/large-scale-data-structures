#ifndef BLAST_H
#define BLAST_H

#define SPLIT_SEQUENCE_LENGTH 11

struct HashNode {
  long unsigned int radix;
  long unsigned int position;
  HashNode* next;
};

class BLAST {
 private:
  int hashTableSize;
  int datasetCount;
  HashNode** hashTable;
  char* subjectSequence;
  int subjectSequenceSize;
  long unsigned int calculateRadix(char* sequence);
  void insertInHashTable(long unsigned int key, int position);

 public:
  BLAST(int hashSize);
  ~BLAST();
  void start();
  void insertData(char* sequence, int position);
  int findMatch(char* sequence);
  void searchSequence(char* sequence, bool doPrint);
  void readGenomeDataset(char* filePath);
  void searchAllGenomeSequences();
  int* getExtendSequencePositions(char* querySequence, int queryPosition,
                                  int sequencePosition);
  void testWithRandomSequences(int sequencesLimit, bool doPrint);
};

#endif