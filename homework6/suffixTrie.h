
#ifndef SUFFIX_TRIE_H
#define SUFFIX_TRIE_H
#include <string.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#define SEQUENCE_LENGTH 36
#define TEST_LENGTH 5

using namespace std;

/**
 * * Node
 * Suffix Trie Node
 */
struct SuffixTrieNode {
  struct SuffixTrieNode *A;
  struct SuffixTrieNode *C;
  struct SuffixTrieNode *G;
  struct SuffixTrieNode *T;
  struct SuffixTrieNode *DS;
};

/**
 * * suffix_trie
 * Suffix tree class
 */
class suffix_trie {
 private:
  char *subjectSequence;
  int subjectLength;
  struct SuffixTrieNode *root;
  struct SuffixTrieNode *createNewNode();
  int getSubjectLength(char *filePath);
  int suffixTrieSize(SuffixTrieNode *root);

 public:
  suffix_trie(char *filepath);
  ~suffix_trie();
  char *readSequenceFromFile(char *filePath);
  void insert(int start);
  bool searchSequence(char *sequence);
  void searchSequencesFromFile(char *filePath);
  char *generateRandomSequenceFromSubject();
  void generateAndSearchRandomSequences(int simNumber);
  int getSuffixTrieSize();
};

#endif