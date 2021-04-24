#include <string.h>

#include <algorithm>
#include <iostream>

#include "./suffixTree.h"
#include "./suffixTrie.h"

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    cout << endl
         << endl
         << "==========================" << endl;
    cout << "Error: 2 input parameters expected" << endl;
    cout << "Proper usage is:" << endl;
    cout << "./homework <problem-flag> <filepath>" << endl;
    cout << "Example:" << endl;
    cout << "./homework problem1A /scratch/vyf2/HW1/sample_hw_dataset.fa"
         << endl;
    cout << "==========================" << endl
         << endl;
    cout << "exiting..." << endl;
    exit(-1);
  }
  else
  {
    cout << "The number of arguments passed: " << argc << endl;
    cout << "The first argument is: " << argv[0] << endl;
    cout << "The second argument is: " << argv[1] << endl;
    cout << "The third argument is: " << argv[2] << endl;
    if (argv[3])
      cout << "The fourth argument is: " << argv[3] << endl;
  }

  cout << "===========================================================" << endl;

  srand(time(NULL));

  char *problem = new char[10];
  char *filePath = new char[100];
  char *filePath2 = new char[100];

  problem = argv[1];
  filePath = argv[2];
  if (argv[3])
    filePath2 = argv[3];

  /////////////////////////////////////////////////////////////////////////////////////////////////
  if (strcmp(problem, "problem1A") == 0)
  {
    /////////////////////////////////////////////////////////////////////////////////////////////////

    suffix_trie trie(filePath);
    trie.searchSequencesFromFile(filePath2);

    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  else if (strcmp(problem, "problem1B") == 0)
  {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    suffix_trie trie(filePath);

    int suffixTrieSize = trie.getSuffixTrieSize();
    cout << "Suffix Trie Size: " << suffixTrieSize << endl;

    int simulations[3] = {5000, 50000, 100000};
    for (int x = 0; x < 3; x++)
    {
      trie.generateAndSearchRandomSequences(simulations[x]);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  else if (strcmp(problem, "problem2A") == 0)
  {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    suffix_tree trie(filePath);
    trie.searchSequencesFromFile(filePath2);
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  else if (strcmp(problem, "problem2B") == 0)
  {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    suffix_tree trie(filePath);

    int suffixTreeSize = trie.getSuffixTreeSize();
    cout << "Suffix Tree Size: " << suffixTreeSize << endl;

    int simulations[3] = {5000, 50000, 100000};
    for (int x = 0; x < 3; x++)
    {
      trie.generateAndSearchRandomSequences(simulations[x]);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  else
  {
    cout << "Invalid problem" << endl;
  }

  return 0;
}