#include "./prefixTrie.h"

struct Node *prefix_trie::createNewNode() {
  struct Node *newNode = NULL;
  newNode = (struct Node *)malloc(sizeof(struct Node));
  for (int i = 0; i < BASE; i++) {
    newNode->childrens[i] = NULL;
  }

  return newNode;
}

int prefix_trie::charToIndex(char character) {
  int index;
  switch (character) {
    case 'A':
      index = 0;
      break;
    case 'C':
      index = 1;
      break;
    case 'G':
      index = 2;
      break;
    case 'T':
      index = 3;
      break;
    default:
      index = -1;
      break;
  }
  return index;
}

void prefix_trie::insert(char *sequence) {
  root->index = -1;
  struct Node *current = root;
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {
    int index = charToIndex(sequence[i]);
    if (current->childrens[index] == NULL) {
      current->childrens[index] = createNewNode();
      current->childrens[index]->index = i;
      current->childrens[index]->parent = current;
    }
    current = current->childrens[index];
  }
}

int prefix_trie::traverse(char *sequence, int mismatchTolorence) {
  int mismatchCount = 0;
  Stack stack;

  StackVal newStackVal;
  newStackVal.mismatch = mismatchCount;
  newStackVal.stackNode = root;
  stack.push(newStackVal);

  while (stack.top >= 0) {
    StackVal tempNodeFromStack = stack.pop();
    Node *tempNode = tempNodeFromStack.stackNode;
    mismatchCount = tempNodeFromStack.mismatch;

    int i = tempNode->index + 1;

    while (i < SEQUENCE_LENGTH) {
      int index = charToIndex(sequence[i]);
      if (tempNode->childrens[index] == NULL) {
        mismatchCount++;
        if (mismatchCount > mismatchTolorence) break;

        for (int j = 0; j < BASE; j++) {
          if (tempNode->childrens[j] != NULL) {
            StackVal altNode;
            altNode.mismatch = mismatchCount;
            altNode.stackNode = tempNode->childrens[j];
            stack.push(altNode);
          }
        }
        tempNodeFromStack = stack.pop();
        tempNode = tempNodeFromStack.stackNode;
        mismatchCount = tempNodeFromStack.mismatch;
      } else {
        tempNode = tempNode->childrens[index];
      }
      i++;
    }
  }

  if (mismatchCount == 0)
    return 0;
  else if (mismatchCount == 1)
    return 1;
  else
    return 2;
}

int prefix_trie::getSubjectLength(char *filePath) {
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

char *prefix_trie::readSequenceFromFile(char *filePath) {
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
  sequence[characterCount] = '\0';
  cout << "Initialized " << characterCount << " character sequences." << endl;
  input.close();
  return sequence;
}

char **prefix_trie::generateRandomSequencesFromSubject(int limit,
                                                       float errorRate) {
  char **randSequences = (char **)malloc(sizeof(char *) * limit);
  for (int i = 0; i < limit; i++) {
    randSequences[i] = (char *)malloc(sizeof(char) * SEQUENCE_LENGTH + 1);
  }

  char randomBaseA[3] = {'C', 'G', 'T'};
  char randomBaseC[3] = {'A', 'G', 'T'};
  char randomBaseG[3] = {'A', 'C', 'T'};
  char randomBaseT[3] = {'A', 'C', 'G'};

  for (int i = 0; i < limit; i++) {
    int randomNumber = rand() % (subjectLength - SEQUENCE_LENGTH);

    for (int j = 0; j < SEQUENCE_LENGTH; j++) {
      randSequences[i][j] = subjectSequence[j + randomNumber];
      float percentage = ((float)rand() / (RAND_MAX));

      if (errorRate > 0 && percentage < errorRate) {
        int randChar;
        switch (randSequences[i][j]) {
          case 'A':
            randChar = rand() % (BASE - 1);
            randSequences[i][j] = randomBaseA[randChar];
            break;
          case 'C':
            randChar = rand() % (BASE - 1);
            randSequences[i][j] = randomBaseC[randChar];
            break;
          case 'G':
            randChar = rand() % (BASE - 1);
            randSequences[i][j] = randomBaseG[randChar];
            break;
          case 'T':
            randChar = rand() % (BASE - 1);
            randSequences[i][j] = randomBaseT[randChar];
            break;
          default:
            break;
        }
      }
    }
    randSequences[i][SEQUENCE_LENGTH] = '\0';
  }
  return randSequences;
}

void prefix_trie::generateAndInsertRandomSequences(int limit, float errorRate) {
  char **randomSequences = generateRandomSequencesFromSubject(limit, errorRate);
  for (int i = 0; i < limit; i++) {
    insert(randomSequences[i]);
  }
  int treeSize = prefixTrieSize(root);

  cout << "PrefixTrie size"  << " (including root node)"
       << " for " << limit << " random 36-mers: " << treeSize << endl;
}

void prefix_trie::fuzzySearch() {
  int mismatchNumber;
  int mismatchCheck[3] = {0, 0, 0};

  for (int k = 0; k < subjectLength - SEQUENCE_LENGTH + 1; k++) {
    char query[SEQUENCE_LENGTH + 1];
    for (int x = 0; x < SEQUENCE_LENGTH; x++) {
      query[x] = subjectSequence[x + k];
    }
    query[SEQUENCE_LENGTH] = '\0';

    mismatchNumber = traverse(query, 1);
    if (mismatchNumber == 0)
      mismatchCheck[0]++;
    else if (mismatchNumber == 1)
      mismatchCheck[1]++;
    else
      mismatchCheck[2]++;
  }

  cout << "===========================================================" << endl;
  cout << "0 Mismatch: " << mismatchCheck[0] << endl
       << "1 Mismatch: " << mismatchCheck[1] << endl
       << "1+ Mismatch: " << mismatchCheck[2] << endl;
  cout << "*****************************" << endl;
  cout << "Total Matches: " << mismatchCheck[0] + mismatchCheck[1] << endl;
  cout << "===========================================================" << endl;
}

int prefix_trie::prefixTrieSize(Node *root) {
  if (root == NULL)
    return 0;
  else
    return prefixTrieSize(root->childrens[0]) +
           prefixTrieSize(root->childrens[1]) +
           prefixTrieSize(root->childrens[2]) +
           prefixTrieSize(root->childrens[3]) + 1;
}

prefix_trie::prefix_trie(char *filepath) {
  root = createNewNode();
  subjectSequence = readSequenceFromFile(filepath);
}

prefix_trie::prefix_trie(prefix_trie &copy) {
  root = copy.root;
  subjectSequence = copy.subjectSequence;
  subjectLength = copy.subjectLength;
}

prefix_trie::~prefix_trie() {

  
}

// Stack
Stack::Stack() { top = -1; }

bool Stack::push(StackVal val) {
  if (top >= STACKSIZE - 1) {
    return false;
  } else {
    stackValue[++top] = val;
    return true;
  }
}

StackVal Stack::pop() {
  if (top < 0) {
    cout << "Stack Underflow";
    StackVal nullStruct;
    nullStruct.mismatch = 0;
    nullStruct.stackNode = nullptr;
    return nullStruct;
  } else {
    StackVal val = stackValue[top--];
    return val;
  }
}

bool Stack::isEmpty() { return (top < 0); }