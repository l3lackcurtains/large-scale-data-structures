#include <stdlib.h>

#include <fstream>
#include <iostream>

#define ALL_DATASETS_COUNT 14

#define SEQUENCE_LENGTH 50

using namespace std;

class FASTA_readset {
   private:
    int datasetCount;
    int headerLength;
    string filePath;
    ifstream input;
    char** headerNumber;
    char** header;
    char** read;

   public:
    FASTA_readset(string path) {
        filePath = path;
        datasetCount = 15;
    }

    void readFile(int readLength) {
        input.open(filePath);
        int a, b, i, j;

        char* tempHeader = new char[1000];
        int tempSequenceLength = 0;

        header = (char**)malloc(sizeof(char*) * readLength);
        headerNumber = (char**)malloc(sizeof(char*) * readLength);
        read = (char**)malloc(sizeof(char*) * readLength);

        for (int i = 0; i < readLength; i++) {
            read[i] = (char*)malloc(sizeof(char) * 1000);
            header[i] = (char*)malloc(sizeof(char) * 1000);
            headerNumber[i] = (char*)malloc(sizeof(char) * 1000);

            input >> tempHeader;  //read in the header line
            input >> read[i];     //read in the read line

            // Lets figure out how long the header is
            headerLength = 0;
            while (tempHeader[headerLength] != '\0') {  // '\0' is a special end-of-string character
                headerLength++;
            }

            // pull out the read number... may want to make this into a function... you'll be doing this
            // a lot for the parsing out the read count numbers from the header string

            a = 2;  //third letter in header... we are assuming the first two are ">R"... may be good to double check
            b = a;

            while (tempHeader[b] != '_' && b < headerLength) {
                b++;
            }
            // by this point we either found the delimiter "_" or we ran off the end of the header
            if (b == headerLength) {  // something went wrong
                cout << "Error: exhausted header string looking for read number... exiting" << endl;
                exit(-1);
            } else {
                for (j = a; j < b; j++) {  //copy of the read number to a new string
                    headerNumber[i][j - a] = tempHeader[j];
                }
                headerNumber[i][j] = '\0';  // top of the read number with the end-of-string special character
            }

            header[i] = tempHeader;
        }
    }

    void initMillionData() {
        // datasetCount = 10000000;
        readFile(datasetCount);
    }

    void initFullData() {
        datasetCount = 36000000;
        readFile(datasetCount);
    }

    void printData() {
        for (int i = 0; i < datasetCount; i++) {
            cout << headerNumber[i] << ":";
            cout << read[i] << endl;
        }
    }

    void totalUniqueSequenceFragments() {
        int totalSequence = 0;
        int lineCounter = 1;
        string line;

        input.open(filePath);

        while (getline(input, line)) {
            if ((lineCounter % 2) == 0) {
                totalSequence++;
            }
            lineCounter++;
        }

        input.close();

        cout << "Total unique sequence fragments: " << totalSequence << endl;
    }

    void allDatasetTotalUniqueSequenceFragments() {
        int totalDatasets[ALL_DATASETS_COUNT];
        for (int x = 0; x < ALL_DATASETS_COUNT; x++) {
            totalDatasets[x] = 0;
        }

        int count, rowPosition, index;

        for (index = 0; index < datasetCount; index++) {
            count = 0;
            rowPosition = 0;
            while (header[index][rowPosition] != '_') {
                rowPosition++;
            }
            rowPosition++;
            while (count <= ALL_DATASETS_COUNT) {
                count++;
                if (header[index][rowPosition] >= '0' && header[index][rowPosition] <= '9') {
                    int value = header[index][rowPosition] - '0';
                    totalDatasets[count - 1] += value;
                }
                rowPosition = rowPosition + 2;
            }
        }
        cout << "Total number of reads for each datasets are as follows:" << endl;

        for (int i = 0; i < ALL_DATASETS_COUNT; i++) {
            cout << "Dataset #" << i + 1 << ": " << totalDatasets[i] << endl;
        }
    }

    void totalCharacterCounts() {
        int a = 0;
        int c = 0;
        int g = 0;
        int t = 0;

        for (int i = 0; i < datasetCount; i++) {
            for (int j = 0; j < SEQUENCE_LENGTH; j++) {
                if (read[i][j] == 'A') {
                    a++;
                } else if (read[i][j] == 'C') {
                    c++;
                } else if (read[i][j] == 'G') {
                    g++;
                } else if (read[i][j] == 'T') {
                    t++;
                }
            }
        }

        cout << "Total number of characters in the data set are as follows:" << endl;
        cout << "A: " << a << endl;
        cout << "C: " << c << endl;
        cout << "G: " << g << endl;
        cout << "T: " << t << endl;
    }

    void getAllStatistics() {
        totalUniqueSequenceFragments();
        cout << "=====================================================" << endl;
        allDatasetTotalUniqueSequenceFragments();
        cout << "=====================================================" << endl;
        totalCharacterCounts();
    }

    void removeDatasetArrayAllocations() {
        for (int i = 0; i < datasetCount; i++) {
            delete[] read[i];
            delete[] header[i];
        }
        delete[] read;
        delete[] header;
        cout << "Deallocated the memory storing data.";
    }

    ~FASTA_readset() {
        removeDatasetArrayAllocations();
    }

};
