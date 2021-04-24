#include <string.h>

#include <algorithm>
#include <iostream>

#include "./prefixTrie.h"

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
  }

  cout << "===========================================================" << endl;

  srand(time(NULL));

  char *problem = new char[10];
  char *filePath = new char[100];

  problem = argv[1];
  filePath = argv[2];

  /////////////////////////////////////////////////////////////////////////////////////////////////
  if (strcmp(problem, "problem1A") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    int simulations[3] = {5000, 50000, 100000};

    for (int x = 0; x < 3; x++) {
      prefix_trie trie(filePath);
      cout << "###########################################################"
           << endl;
      cout << "Generating " << simulations[x]
           << " Random 36-Mers to the Prefix-Trie" << endl;
      trie.generateAndInsertRandomSequences(simulations[x], 0);
      trie.fuzzySearch();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else if (strcmp(problem, "problem1B") == 0) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    int simulations[3] = {1000, 50000, 100000};

    for (int x = 0; x < 3; x++) {
      prefix_trie trie(filePath);
      cout << "###########################################################"
           << endl;
      cout << "Generating " << simulations[x]
           << " Random 36-Mers to the Prefix-Trie" << endl;
      trie.generateAndInsertRandomSequences(simulations[x], 0.05);
      trie.fuzzySearch();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  } else {
    cout << "Invalid problem" << endl;
  }

  return 0;
}