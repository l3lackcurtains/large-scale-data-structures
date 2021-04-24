#include "./suffixTrie.h"

/**
 * * suffix_trie::createNewNode
 * Helper function to create a new node for the tree
 */
struct SuffixTrieNode *suffix_trie::createNewNode() {
  struct SuffixTrieNode *newNode = NULL;
  newNode = (struct SuffixTrieNode *)malloc(sizeof(struct SuffixTrieNode));
  newNode->A = NULL;
  newNode->C = NULL;
  newNode->G = NULL;
  newNode->T = NULL;
  newNode->DS = NULL;
  return newNode;
}

/**
 * * suffix_trie::getSubjectLength
 * Helper function to quickly get the length of subject
 * @param filePath File path to read the length
 * @return length of subject
 */
int suffix_trie::getSubjectLength(char *filePath) {
  ifstream input;
  input.open(filePath);
  char c = '\0';
  int characterCount = 0;
  while (c != '\n') {
    input.get(c);
  }
  while (input.get(c)) {
    if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
      characterCount++;
    }
  }
  return characterCount;
}

/**
 * * suffix_trie::insert
 * Inserts the sequence in the suffix trie tree
 * @param sequence the genome sequence to be inserted in the tree
 */
void suffix_trie::insert(int start) {
  struct SuffixTrieNode *current = root;

  for (int i = start; i < subjectLength + 1; i++) {
    if (subjectSequence[i] == 'A') {
      if (!current->A) current->A = createNewNode();
      current = current->A;
    } else if (subjectSequence[i] == 'C') {
      if (!current->C) current->C = createNewNode();
      current = current->C;
    } else if (subjectSequence[i] == 'G') {
      if (!current->G) current->G = createNewNode();
      current = current->G;
    } else if (subjectSequence[i] == 'T') {
      if (!current->T) current->T = createNewNode();
      current = current->T;
    } else if (subjectSequence[i] == '$') {
      if (!current->DS) current->DS = createNewNode();
    }
  }
}

/**
 * * suffix_trie::readSequenceFromFile
 * Reads the subject sequence from the file
 * @param filePath File path to read the sequence
 * @return sequence that is read
 */
char *suffix_trie::readSequenceFromFile(char *filePath) {
  ifstream input;
  input.open(filePath);
  subjectLength = getSubjectLength(filePath);
  char *sequence = (char *)malloc(sizeof(char) * (subjectLength + 1));
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
  sequence[characterCount] = '$';
  cout << "Initialized " << characterCount << " character sequences." << endl;
  input.close();
  return sequence;
}

/**
 * * suffix_trie::fuzzySearch
 * Function that does the fuzzt search on the subject query
 */
bool suffix_trie::searchSequence(char *sequence, int sequenceLength) {
  struct SuffixTrieNode *current = root;
  bool found = false;
  for (int x = 0; x < sequenceLength + 1; x++) {
    if (sequence[x] == 'A' && current->A) {
      current = current->A;
    } else if (sequence[x] == 'C' && current->C) {
      current = current->C;
    } else if (sequence[x] == 'G' && current->G) {
      current = current->G;
    } else if (sequence[x] == 'T' && current->T) {
      current = current->T;
    } else if (sequence[x] == '$') {
      found = true;
    } else {
      break;
    }
  }
  return found;
}

void suffix_trie::searchSequencesFromFile(char *filePath) {
  //

  char **testSequences = (char **)malloc(sizeof(char *) * TEST_LENGTH);
  for (int x = 0; x < TEST_LENGTH; x++) {
    testSequences[x] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH + 1);
  }

  ifstream input;
  input.open(filePath);

  char *tempHeader = new char[100];
  int readCount = 0;

  while (!input.eof()) {
    input >> tempHeader;
    input >> testSequences[readCount];
    testSequences[readCount][SEQUENCE_LENGTH] = '$';
    readCount++;
  }

  delete[] tempHeader;
  input.close();
  cout << "Searching from file." << endl;
  for (int x = 0; x < TEST_LENGTH; x++) {
    bool found = searchSequence(testSequences[x], SEQUENCE_LENGTH);
    cout << testSequences[x];
    if (found) {
      cout << " : FOUND" << endl;
    } else {
      cout << " : NOT FOUND" << endl;
    }
  }
}

char *suffix_trie::generateRandomSequenceFromSubject() {
  char *sequence = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH + 1);
  int randomNumber = rand() % (subjectLength - SEQUENCE_LENGTH);
  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    sequence[x] = subjectSequence[randomNumber + x];
  }
  sequence[SEQUENCE_LENGTH] = '$';
  return sequence;
}

void suffix_trie::generateAndSearchRandomSequences(int simNumber) {
  clock_t startTime, endTime;
  float totalTime = 0.0;
  startTime = clock();
  /////////////////////////////////////////////////////
  int foundCount = 0;
  for (int x = 0; x < simNumber; x++) {
    char *sequence = generateRandomSequenceFromSubject();
    bool found = searchSequence(sequence, SEQUENCE_LENGTH);
    if (found) foundCount++;
  }
  cout << simNumber << " random sequences: " << foundCount << " sequences found"
       << endl;

  /////////////////////////////////////////////////////
  endTime = clock();
  totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
  cout << "Time taken: " << totalTime << " seconds." << endl;
  cout << "#####################################################" << endl;
}

/**
 * * suffix_trie::suffixTrieSize
 * Helper function to get the size of the suffix trie tree
 * @param root root node of the tree
 * @return total number of non empty nodes
 */
int suffix_trie::suffixTrieSize(SuffixTrieNode *root) {
  if (root == NULL)
    return 0;
  else
    return suffixTrieSize(root->A) + suffixTrieSize(root->C) +
           suffixTrieSize(root->G) + suffixTrieSize(root->T) + 1;
}

int suffix_trie::getSuffixTrieSize() { return suffixTrieSize(root); }

/**
 * * suffix_trie::suffix_trie
 * Constructor that read the file containing subject sequence
 */
suffix_trie::suffix_trie(char *filepath) {
  root = createNewNode();
  subjectSequence = readSequenceFromFile(filepath);
  for (int x = 0; x < subjectLength + 1; x++) {
    insert(x);
  }
}

/**
 * * suffix_trie::suffix_trie
 * Constructor that read the file containing subject sequence
 */
suffix_trie::suffix_trie(char *newSequence, int sequenceLength) {
  subjectSequence = subjectSequence;
  subjectLength = sequenceLength;
  for (int x = 0; x < subjectLength + 1; x++) {
    insert(x);
  }
}

void suffix_trie::deallocateNode(SuffixTrieNode *root) {
  if (root == NULL) return;
  deallocateNode(root->A);
  deallocateNode(root->C);
  deallocateNode(root->G);
  deallocateNode(root->T);
  deallocateNode(root->DS);
  free(root);
}

/**
 * * suffix_trie::~suffix_trie
 * Destructor function that cleans up tree data structure and subject sequence
 */
suffix_trie::~suffix_trie() { deallocateNode(root); }