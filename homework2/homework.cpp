// !!! Use the head command to make a smaller version of the dataset file to
// transfer to your laptop... for example head -2000
// /common/contrib/classroom/inf503/hw_dataset.fa >
// /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)

#include <stdlib.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include "./fasta.h"

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
    if (argv[4]) {
      cout << "The fifth argument is: " << argv[4] << endl;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////
  // Lets open our sample file and read in the first set of sequences
  ////////////////////////////////////////////////////////////////////////////////////

  cout << "/////////////////////////////////////////////////////" << endl;
  char* problem = new char[10];
  char* filePath = new char[100];
  problem = argv[1];
  filePath = argv[2];
  int limit = -1;
  if (argv[3]) limit = atoi(argv[3]);

  int genomeDataLimit = -1;
  if (argv[4]) genomeDataLimit = atoi(argv[4]);

  if (strcmp(problem, "problem1A") == 0) {

    FASTAreadset_LL fasta(filePath);
    fasta.initNthData(limit);

  } else if (strcmp(problem, "problem1B") == 0) {

    FASTAreadset_LL fasta(filePath);
    fasta.initNthData(limit);

  } else if (strcmp(problem, "problem1C") == 0) {

    FASTAreadset_LL fasta(filePath);
    fasta.initNthData(limit);
    FASTAreadset_LL fastaCopy(fasta);

  } else if (strcmp(problem, "problem1D") == 0) {

    FASTAreadset_LL fasta(filePath);
    fasta.initNthData(limit);
    fasta.searchSequences();

  } else if (strcmp(problem, "problem2A") == 0) {

    FASTAreadset_LL fasta(filePath);
    fasta.readGenomeDataset(filePath, genomeDataLimit);

  } else if (strcmp(problem, "problem2B") == 0) {

    // load the 1st dataset
    // hard coded path, because 6th argument from command line is producing error.
    string question1Dataset = "/common/contrib/classroom/inf503/hw_dataset.fa";
    FASTAreadset_LL fasta(&question1Dataset[0]);
    fasta.initNthData(limit);

    // Read the 2nd dataset
    fasta.readGenomeDataset(filePath, genomeDataLimit);
    // Perform naive search
    fasta.searchGenomeDataset();

  } else if (strcmp(problem, "problem2B2") == 0) {

    // load the 1st dataset
    string question1Dataset = "/common/contrib/classroom/inf503/hw_dataset.fa";
    FASTAreadset_LL fasta(&question1Dataset[0]);
    fasta.initNthData(limit);

    // Read the 2nd dataset
    fasta.readGenomeDataset(filePath, genomeDataLimit);
    // Perform binary search
    fasta.binarySearchGenomeDataset();

  } else {

    cout << "[Error] Invalid Option number." << endl;
    
  }

  cout << "/////////////////////////////////////////////////////" << endl;

  return (0);
}