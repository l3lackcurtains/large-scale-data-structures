#include "./suffixTree.h"

/**
 * * suffix_tree::createNewNode
 * Helper function to create a new node for the tree
 */
struct SuffixTreeNode *suffix_tree::createNewNode(SuffixTreeNode *parent,
                                                  int offset, int length) {
  struct SuffixTreeNode *newNode = NULL;
  newNode = (struct SuffixTreeNode *)malloc(sizeof(struct SuffixTreeNode));
  newNode->offset = offset;
  newNode->length = length;

  newNode->A = NULL;
  newNode->C = NULL;
  newNode->G = NULL;
  newNode->T = NULL;
  newNode->DS = NULL;

  if (parent && parent->A) {
    newNode->A = parent->A;
  }

  if (parent && parent->C) {
    newNode->C = parent->C;
  }

  if (parent && parent->G) {
    newNode->G = parent->G;
  }

  if (parent && parent->T) {
    newNode->T = parent->T;
  }

  if (parent && parent->DS) {
    newNode->DS = parent->DS;
  }

  return newNode;
}

/**
 * * suffix_tree::getSubjectLength
 * Helper function to quickly get the length of subject
 * @param filePath File path to read the length
 * @return length of subject
 */
int suffix_tree::getSubjectLength(char *filePath) {
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
 * * suffix_tree::insert
 * Inserts the sequence in the suffix trie tree
 * @param sequence the genome sequence to be inserted in the tree
 */
void suffix_tree::insert(int start) {
  struct SuffixTreeNode *current = root;
  int tempStart = start;
  bool exit = false;

  while (tempStart < subjectLength + 1) {
    if (exit) break;

    if (subjectSequence[tempStart] == 'A') {
      if (!current->A) {
        current->A =
            createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
        break;
      }

      int offset = current->A->offset;
      int length = current->A->length;

      for (int x = offset; x < offset + length; x++) {
        if (subjectSequence[x] != subjectSequence[tempStart]) {
          current->A->length = x - offset;

          // Check old
          if (subjectSequence[x] == 'A') {
            current->A->A = createNewNode(current->A, x, length - x + offset);
          } else if (subjectSequence[x] == 'C') {
            current->A->C = createNewNode(current->A, x, length - x + offset);
          } else if (subjectSequence[x] == 'G') {
            current->A->G = createNewNode(current->A, x, length - x + offset);
          } else if (subjectSequence[x] == 'T') {
            current->A->T = createNewNode(current->A, x, length - x + offset);
          } else if (subjectSequence[x] == '$') {
            current->A->DS = createNewNode(NULL, -1, -1);
          }

          // Insert New
          if (subjectSequence[tempStart] == 'A') {
            current->A->A =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'C') {
            current->A->C =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'G') {
            current->A->G =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'T') {
            current->A->T =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == '$') {
            current->A->DS = createNewNode(NULL, -1, -1);
          }
          exit = true;
          break;
        }
        tempStart++;
      }
      current = current->A;
    } else if (subjectSequence[tempStart] == 'C') {
      if (!current->C) {
        current->C =
            createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
        break;
      }

      int offset = current->C->offset;
      int length = current->C->length;

      for (int x = offset; x < offset + length; x++) {
        if (subjectSequence[x] != subjectSequence[tempStart]) {
          current->C->length = x - offset;

          // Check old
          if (subjectSequence[x] == 'A') {
            current->C->A = createNewNode(current->C, x, length - x + offset);
          } else if (subjectSequence[x] == 'C') {
            current->C->C = createNewNode(current->C, x, length - x + offset);
          } else if (subjectSequence[x] == 'G') {
            current->C->G = createNewNode(current->C, x, length - x + offset);
          } else if (subjectSequence[x] == 'T') {
            current->C->T = createNewNode(current->C, x, length - x + offset);
          } else if (subjectSequence[x] == '$') {
            current->C->DS = createNewNode(NULL, -1, -1);
          }

          // Insert New
          if (subjectSequence[tempStart] == 'A') {
            current->C->A =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'C') {
            current->C->C =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'G') {
            current->C->G =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'T') {
            current->C->T =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == '$') {
            current->C->DS = createNewNode(NULL, -1, -1);
          }
          exit = true;
          break;
        }
        tempStart++;
      }
      current = current->C;
    } else if (subjectSequence[tempStart] == 'G') {
      if (!current->G) {
        current->G =
            createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
        break;
      }

      int offset = current->G->offset;
      int length = current->G->length;

      for (int x = offset; x < offset + length; x++) {
        if (subjectSequence[x] != subjectSequence[tempStart]) {
          current->G->length = x - offset;

          // Check old
          if (subjectSequence[x] == 'A') {
            current->G->A = createNewNode(current->G, x, length - x + offset);
          } else if (subjectSequence[x] == 'C') {
            current->G->C = createNewNode(current->G, x, length - x + offset);
          } else if (subjectSequence[x] == 'G') {
            current->G->G = createNewNode(current->G, x, length - x + offset);
          } else if (subjectSequence[x] == 'T') {
            current->G->T = createNewNode(current->G, x, length - x + offset);
          } else if (subjectSequence[x] == '$') {
            current->G->DS = createNewNode(NULL, -1, -1);
          }

          // Insert New
          if (subjectSequence[tempStart] == 'A') {
            current->G->A =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'C') {
            current->G->C =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'G') {
            current->G->G =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'T') {
            current->G->T =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == '$') {
            current->G->DS = createNewNode(NULL, -1, -1);
          }
          exit = true;
          break;
        }
        tempStart++;
      }
      current = current->G;
    } else if (subjectSequence[tempStart] == 'T') {
      if (!current->T) {
        current->T =
            createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
        break;
      }

      int offset = current->T->offset;
      int length = current->T->length;

      for (int x = offset; x < offset + length; x++) {
        if (subjectSequence[x] != subjectSequence[tempStart]) {
          current->T->length = x - offset;

          // Check old
          if (subjectSequence[x] == 'A') {
            current->T->A = createNewNode(current->T, x, length - x + offset);
          } else if (subjectSequence[x] == 'C') {
            current->T->C = createNewNode(current->T, x, length - x + offset);
          } else if (subjectSequence[x] == 'G') {
            current->T->G = createNewNode(current->T, x, length - x + offset);
          } else if (subjectSequence[x] == 'T') {
            current->T->T = createNewNode(current->T, x, length - x + offset);
          } else if (subjectSequence[x] == '$') {
            current->T->DS = createNewNode(NULL, -1, -1);
          }

          // Insert New
          if (subjectSequence[tempStart] == 'A') {
            current->T->A =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'C') {
            current->T->C =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'G') {
            current->T->G =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == 'T') {
            current->T->T =
                createNewNode(NULL, tempStart, subjectLength + 1 - tempStart);
          } else if (subjectSequence[tempStart] == '$') {
            current->T->DS = createNewNode(NULL, -1, -1);
          }
          exit = true;
          break;
        }
        tempStart++;
      }
      current = current->T;

    } else if (subjectSequence[tempStart] == '$') {
      current->DS = createNewNode(NULL, -1, -1);
      break;
    }
  }
}

/**
 * * suffix_tree::readSequenceFromFile
 * Reads the subject sequence from the file
 * @param filePath File path to read the sequence
 * @return sequence that is read
 */
char *suffix_tree::readSequenceFromFile(char *filePath) {
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
 * * suffix_tree::fuzzySearch
 * Function that does the fuzzt search on the subject query
 */
bool suffix_tree::searchSequence(char *sequence, int sequenceLength) {
  //
  struct SuffixTreeNode *current = root;
  bool found = false;
  bool exit = false;
  int x = 0;

  while (x < sequenceLength + 1) {
    if (exit) break;

    if (sequence[x] == 'A' && current->A) {
      int offset = current->A->offset;
      int length = current->A->length;

      for (int i = offset; i < offset + length; i++) {
        if (sequence[x] != subjectSequence[i]) {
          exit = true;
          break;
        }
        x++;
        if (sequence[x] == '$') {
          exit = true;
          found = true;
        }
      }

      current = current->A;
    } else if (sequence[x] == 'C' && current->C) {
      int offset = current->C->offset;
      int length = current->C->length;

      for (int i = offset; i < offset + length; i++) {
        if (sequence[x] != subjectSequence[i]) {
          exit = true;
          break;
        }
        x++;
        if (sequence[x] == '$') {
          exit = true;
          found = true;
        }
      }
      current = current->C;
    } else if (sequence[x] == 'G' && current->G) {
      int offset = current->G->offset;
      int length = current->G->length;
      for (int i = offset; i < offset + length; i++) {
        if (sequence[x] != subjectSequence[i]) {
          exit = true;
          break;
        }
        x++;
        if (sequence[x] == '$') {
          exit = true;
          found = true;
        }
      }
      current = current->G;
    } else if (sequence[x] == 'T' && current->T) {
      int offset = current->T->offset;
      int length = current->T->length;
      for (int i = offset; i < offset + length; i++) {
        if (sequence[x] != subjectSequence[i]) {
          exit = true;
          break;
        }
        x++;
        if (sequence[x] == '$') {
          exit = true;
          found = true;
        }
      }
      current = current->T;

    } else if (sequence[x] == '$') {
      found = true;
    } else {
      break;
    }
  }

  return found;
}

void suffix_tree::searchSequencesFromFile(char *filePath) {
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

char *suffix_tree::generateRandomSequenceFromSubject() {
  char *sequence = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH + 1);
  int randomNumber = rand() % (subjectLength - SEQUENCE_LENGTH);
  for (int x = 0; x < SEQUENCE_LENGTH; x++) {
    sequence[x] = subjectSequence[randomNumber + x];
  }
  sequence[SEQUENCE_LENGTH] = '$';
  return sequence;
}

void suffix_tree::generateAndSearchRandomSequences(int simNumber) {
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
 * * suffix_tree::suffixTreeSize
 * Helper function to get the size of the suffix trie tree
 * @param root root node of the tree
 * @return total number of non empty nodes
 */
int suffix_tree::suffixTreeSize(SuffixTreeNode *root) {
  if (root == NULL)
    return 0;
  else
    return suffixTreeSize(root->A) + suffixTreeSize(root->C) +
           suffixTreeSize(root->G) + suffixTreeSize(root->T) + 1;
}

int suffix_tree::getSuffixTreeSize() { return suffixTreeSize(root); }
/**
 * * suffix_tree::suffix_tree
 * Constructor that read the file containing subject sequence
 */
suffix_tree::suffix_tree(char *filepath) {
  root = createNewNode(NULL, -1, -1);
  subjectSequence = readSequenceFromFile(filepath);
  for (int x = 0; x < subjectLength + 1; x++) {
    insert(x);
  }
}

void suffix_tree::deallocateNode(SuffixTreeNode *root) {
  if (root == NULL) return;
  deallocateNode(root->A);
  deallocateNode(root->C);
  deallocateNode(root->G);
  deallocateNode(root->T);
  deallocateNode(root->DS);
  root = NULL;
  free(root);
}

/**
 * * suffix_tree::~suffix_tree
 * Destructor function that cleans up tree data structure and subject
 * sequence
 */
suffix_tree::~suffix_tree() { deallocateNode(root); }