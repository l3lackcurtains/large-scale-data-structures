#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H
#include <string.h>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#define SEQUENCE_LENGTH 36
#define TEST_LENGTH 5

using namespace std;

/**
 * * SuffixTreeNode
 * Suffix Trie SuffixTreeNode
 */
struct SuffixTreeNode {
  int offset;
  int length;
  struct SuffixTreeNode *A;
  struct SuffixTreeNode *C;
  struct SuffixTreeNode *G;
  struct SuffixTreeNode *T;
  struct SuffixTreeNode *DS;
};

/**
 * * suffix_tree
 * Suffix tree class
 */
class suffix_tree {
 private:
  char *subjectSequence;
  int subjectLength;
  struct SuffixTreeNode *root;
  struct SuffixTreeNode *createNewNode(SuffixTreeNode *parent, int offset,
                                       int length);
  int getSubjectLength(char *filePath);
  int suffixTreeSize(SuffixTreeNode *root);

 public:
  suffix_tree(char *filepath);
  ~suffix_tree();
  char *readSequenceFromFile(char *filePath);
  void insert(int start);
  bool searchSequence(char *sequence);
  void searchSequencesFromFile(char *filePath);
  char *generateRandomSequenceFromSubject();
  void generateAndSearchRandomSequences(int simNumber);
  int getSuffixTreeSize();
};

#endif