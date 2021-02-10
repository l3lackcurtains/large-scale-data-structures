#include <stdlib.h>
#include <string.h>

#include <ctime>
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
    bool arrayInitalized = true;

   public:
    FASTA_readset() {
        datasetCount = 15;
    }

    FASTA_readset(string path) {
        filePath = path;
        datasetCount = 15;
    }

    void readFile(string path, int readLength) {
        input.open(path);
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

    void readFile(int readLength) {
        readFile(filePath, readLength);
    }

    void initMillionData() {
        clock_t startTime, endTime;
        float totalTime = 0.0;
        startTime = clock();

        /////////////////////////////////////////////////////
        datasetCount = 10000000;
        readFile(datasetCount);
        /////////////////////////////////////////////////////

        endTime = clock();
        totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "#####################################################" << endl;
        printf("Time to read 1 million data: %3.3f seconds. \n", totalTime);
        ;
        cout << "#####################################################" << endl;
    }

    void initFullData() {
        clock_t startTime, endTime;
        float totalTime = 0.0;
        startTime = clock();

        /////////////////////////////////////////////////////
        // datasetCount = 36000000;
        readFile(datasetCount);
        /////////////////////////////////////////////////////

        endTime = clock();
        totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "#####################################################" << endl;
        printf("Time to read 36 million data: %3.3f seconds. \n", totalTime);
        ;
        cout << "#####################################################" << endl;
    }

    void printData() {
        for (int i = 0; i < datasetCount; i++) {
            cout << headerNumber[i] << ":";
            cout << read[i] << endl;
        }
    }

    void totalUniqueSequenceFragments() {
        arrayInitalized = false;

        int totalSequence = 0;
        int lineCounter = 1;
        string line;
        ifstream uniqueInput;
        uniqueInput.open(filePath);

        while (getline(uniqueInput, line)) {
            if ((lineCounter % 2) == 0) {
                totalSequence++;
            }
            lineCounter++;
        }

        uniqueInput.close();

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

    void swap(char* stringData[], int i, int j) {
        char* temp;
        temp = stringData[i];
        stringData[i] = stringData[j];
        stringData[j] = temp;
    }

    void quickSort(char* stringData[], int left, int right) {
        if (left >= right) {
            return;
        }
        swap(stringData, left, (left + right) / 2);
        int last = left;

        for (int i = left + 1; i <= right; i++) {
            if (strcmp(stringData[i], stringData[left]) < 0) {
                swap(stringData, ++last, i);
            }
        }
        swap(stringData, left, last);
        quickSort(stringData, left, last - 1);
        quickSort(stringData, last + 1, right);
    }

    void sortSequenceRead() {
        clock_t startTime, endTime;
        float totalTime = 0.0;
        startTime = clock();

        ////////////////////////////////////////////////
        char** temp = new char*[datasetCount];
        for (int i = 0; i < datasetCount; i++) {
            temp[i] = read[i];
        }

        quickSort(temp, 0, datasetCount - 1);

        char** sortedRead = new char*[datasetCount];
        for (int i = 0; i < datasetCount; i++) {
            sortedRead[i] = new char[SEQUENCE_LENGTH];
            strcpy(sortedRead[i], temp[i]);
        }

        cout << "First 10 lines after sorting are as follows:"
             << endl;
        for (int i = 0; i < 10; i++) {
            cout << sortedRead[i] << endl;
        }

        for (int i = 0; i < datasetCount; i++) {
            delete[] sortedRead[i];
            delete[] temp[i];
        }
        delete[] sortedRead;
        delete[] temp;

        //////////////////////////////////////////////////////////
        endTime = clock();
        totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "#####################################################" << endl;
        printf("Time to sort genomic sequence: %3.3f seconds. \n", totalTime);
        ;
        cout << "#####################################################" << endl;
    }

    ~FASTA_readset() {
        clock_t startTime, endTime;
        float totalTime = 0.0;
        startTime = clock();
        if (arrayInitalized) {
            for (int i = 0; i < datasetCount; i++) {
                delete[] read[i];
                delete[] header[i];
                delete[] headerNumber[i];
            }
            delete[] read;
            delete[] header;
            delete[] headerNumber;
        }

        if (input.is_open()) {
            input.close();
        }
        cout << "Deallocated all array memory." << endl;
        endTime = clock();
        totalTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "#####################################################" << endl;
        printf("Time to Deallocate memory: %3.3f seconds. \n", totalTime);
        ;
        cout << "#####################################################" << endl;
    }
};
