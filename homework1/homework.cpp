// !!! Use the head command to make a smaller version of the dataset file to transfer to your laptop... for example
// head -2000 /common/contrib/classroom/inf503/hw_dataset.fa > /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)

#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "./fasta.cpp"

using namespace std;

int main(int argc, char** argv) {
    ////////////////////////////////////////////////////////////////////////////////////
    //Lets do sanity checks to make sure the proper number of parameters were passed in
    ////////////////////////////////////////////////////////////////////////////////////

    if (argc != 3) {  // unexpected program call
        cout << endl
             << endl
             << "==========================" << endl;
        cout << "Error: 2 input parameters expected" << endl;
        cout << "Proper usage is:" << endl;
        cout << "./homework <problem-flag> <filepath>" << endl;
        cout << "Example:" << endl;
        cout << "./homework problem1A /scratch/vyf2/HW1/sample_hw_dataset.fa" << endl;
        cout << "==========================" << endl
             << endl;
        cout << "exiting..." << endl;
        exit(-1);
    } else {
        cout << "The number of arguments passed: " << argc << endl;
        cout << "The first argument is: " << argv[0] << endl;
        cout << "The second argument is: " << argv[1] << endl;
        cout << "The third argument is: " << argv[2] << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //Lets open our sample file and read in the first set of sequences
    ////////////////////////////////////////////////////////////////////////////////////

    cout << "/////////////////////////////////////////////////////" << endl;

    string problem = argv[1];
    string filePath = argv[2];

    FASTA_readset fasta(filePath);

    if (problem == "1") {
        fasta.initMillionData();
        cout << "/////////////////////////////////////////////////////" << endl;
        fasta.printData();

    } else if (problem == "2") {
        fasta.totalUniqueSequenceFragments();
    } else if (problem == "3") {
        fasta.initFullData();
        cout << "/////////////////////////////////////////////////////" << endl;
        fasta.getAllStatistics();
    } else if (problem == "4") {
        fasta.initFullData();
    } else if (problem == "5") {
        fasta.initFullData();
        cout << "/////////////////////////////////////////////////////" << endl;
        fasta.sortSequenceRead();
    } else {
        cout << "[Error] Invalid Option number." << endl;
    }

    cout << "/////////////////////////////////////////////////////" << endl;

    return (0);
}