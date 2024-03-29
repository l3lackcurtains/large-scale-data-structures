
#ifndef PREFIX_TRIE_H
#define PREFIX_TRIE_H
#include <string.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#define SEQUENCE_LENGTH 36
#define STACKSIZE 100000
#define BASE 4

using namespace std;
/**
 * * Node
 * Prefix Trie Node
 */
struct Node {
  int index;
  struct Node *childrens[BASE];
};

/**
 * * StackVal
 * Stack Value that has Node and mismatch at that node
 */
struct StackVal {
  int mismatch = 0;
  Node *stackNode = NULL;
};

/**
 * * Stack
 * Custom stack data structure
 */
class Stack {
 public:
  Stack();
  bool push(StackVal val);
  bool isEmpty();
  StackVal pop();
  int top;
  StackVal stackValue[STACKSIZE];
};

/**
 * * prefix_trie
 * Prefix tree class
 */
class prefix_trie {
 private:
  char *subjectSequence;
  int subjectLength;
  struct Node *root;
  struct Node *createNewNode();
  int getSubjectLength(char *filePath);
  int charToIndex(char character);

 public:
  prefix_trie(char *filepath);
  prefix_trie(prefix_trie &copy);
  ~prefix_trie();
  void insert(char *sequence);
  char *readSequenceFromFile(char *filePath);
  int prefixTrieSize(Node *root);
  int traverse(char *sequence, int mismatchTolorence);
  char **generateRandomSequencesFromSubject(int limit, float errorRate);
  void generateAndInsertRandomSequences(int limit, float errorRate);
  void fuzzySearch();
};

#endif