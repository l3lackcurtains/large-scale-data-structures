// !!! Use the head command to make a smaller version of the dataset file to
// transfer to your laptop... for example head -2000
// /common/contrib/classroom/inf503/hw_dataset.fa >
// /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)

#include <stdlib.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include "./fastaDAT.h"
#include "./fastaHT.h"

using namespace std;

int main(int argc, char** argv) {
  ////////////////////////////////////////////////////////////////////////////////////
  // Lets do sanity checks to make sure the proper number of parameters were
  // passed in
  ////////////////////////////////////////////////////////////////////////////////////

  if (argc < 3) {  // unexpected program call
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
    if (argv[3]) {
      cout << "The fourth argument is: " << argv[3] << endl;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////
  // Lets open our sample file and read in the first set of sequences
  ////////////////////////////////////////////////////////////////////////////////////

  cout << "/////////////////////////////////////////////////////" << endl;
  char* problem = new char[10];
  char* filePath = new char[100];
  char* filePath2 = new char[100];
  problem = argv[1];
  filePath = argv[2];
  if (argv[3]) filePath2 = argv[3];

  FASTAreadset_DA fasta = FASTAreadset_DA();

  if (strcmp(problem, "problem1A") == 0) {
    
    fasta.readFile(filePath);
    
    cout << "Size of Hash Table: " << fasta.getHashTableSize() << " GB" << endl;
    cout << "Total sequences: " << fasta.getTotalDataset() << endl;
    cout << "Unique sequences: " << fasta.getElementsStored() << endl;
    cout << "Total collsions: " << fasta.getCollisions() << endl;    
    

  } else if (strcmp(problem, "problem1B") == 0) {

    fasta.readFile(filePath);

    fasta.readGenomeDataset(filePath2);
    fasta.searchAllGenomeSequences();


  } else if (strcmp(problem, "problem2A") == 0) {

    FASTAreadset_Chain cfasta = FASTAreadset_Chain(10000);
    cfasta.readFile(filePath);

    int collisions = cfasta.getCollisions();
    cout << "Total collsions in 10,000 hash Table: " << collisions << endl;

    FASTAreadset_Chain cfasta2 = FASTAreadset_Chain(100000);
    cfasta2.readFile(filePath);

    collisions = cfasta2.getCollisions();
    cout << "Total collsions in 100,000 hash Table: " << collisions << endl;

    FASTAreadset_Chain cfasta3 = FASTAreadset_Chain(1000000);
    cfasta3.readFile(filePath);

    collisions = cfasta3.getCollisions();
    cout << "Total collsions in 1,000,000 hash Table: " << collisions << endl;

    FASTAreadset_Chain cfasta4 = FASTAreadset_Chain(10000000);
    cfasta4.readFile(filePath);

    collisions = cfasta4.getCollisions();
    cout << "Total collsions in 10,000,000 hash Table: " << collisions << endl;


  } else if (strcmp(problem, "problem2B") == 0) {

    FASTAreadset_Chain cfasta = FASTAreadset_Chain(10000000);
    cfasta.readFile(filePath);
    cfasta.readGenomeDataset(filePath2);
    cfasta.searchAllGenomeSequences();

  }  else {

    cout << "[Error] Invalid Option number." << endl;
    
  }

  cout << "/////////////////////////////////////////////////////" << endl;

  return (0);
}