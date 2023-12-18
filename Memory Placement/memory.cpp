#include <iostream>
#include <algorithm>

using namespace std;

int blocksCount, procCount;
int *blockSizes;
int *procSizes;

void input() {
    cout << "Enter the Number of Blocks: ";
    cin >> blocksCount;
    blockSizes = new int[blocksCount];

    for (int i = 0; i < blocksCount; i++) {
        cout << "Enter the size of Block" << (i + 1) << ": ";
        cin >> blockSizes[i];
    }

    cout << "Enter the Number of Processes: ";
    cin >> procCount;
    procSizes = new int[procCount];

    for (int i = 0; i < procCount; i++) {
        cout << "Enter the size of Process" << (i + 1) << ": ";
        cin >> procSizes[i];
    }
}

void firstFit() {
    int internalFragCount = 0;
    int externalFragCount = 0;
    bool *isOccupied = new bool[blocksCount] {false};

    cout << "Process No. \t Process size \t Block Allocated \t Internal Fragmentation" << endl;
    for (int i = 0; i < procCount; i++) {
        bool isExternalFrag = false;
        for (int j = 0; j < blocksCount; j++) {
            if (!isOccupied[j] && procSizes[i] <= blockSizes[j]) {
                isOccupied[j] = true;
                isExternalFrag = true;
                internalFragCount += blockSizes[j] - procSizes[i];
                cout << "\t P" << (i + 1) << " \t\t   " << procSizes[i] << " \t\t\t\t " << blockSizes[j] << " \t\t\t\t  " << (blockSizes[j] - procSizes[i]) << endl;
                break;
            }
        }
        if (!isExternalFrag) {
            externalFragCount += procSizes[i];
        }
    }
    cout << "Internal Fragmentation is: " << internalFragCount << endl;
    cout << "External Fragmentation is: " << externalFragCount << endl;

    delete[] isOccupied;
}

void bestFit() {
    int internalFragCount = 0;
    int externalFragCount = 0;
    bool *isOccupied = new bool[blocksCount] {false};

    int *localBlockSizes = new int[blocksCount];
    copy(blockSizes, blockSizes + blocksCount, localBlockSizes);
    sort(localBlockSizes, localBlockSizes + blocksCount);

    cout << "Process No. \t Process size \t Block Allocated \t Internal Fragmentation" << endl;
    for (int i = 0; i < procCount; i++) {
        bool isExternalFrag = false;
        for (int j = 0; j < blocksCount; j++) {
            if (!isOccupied[j] && procSizes[i] <= localBlockSizes[j]) {
                isOccupied[j] = true;
                isExternalFrag = true;
                internalFragCount += localBlockSizes[j] - procSizes[i];
                cout << "\t P" << (i + 1) << " \t\t   " << procSizes[i] << " \t\t\t\t " << localBlockSizes[j] << " \t\t\t\t  " << (localBlockSizes[j] - procSizes[i]) << endl;
                break;
            }
        }
        if (!isExternalFrag) {
            externalFragCount += procSizes[i];
        }
    }
    cout << "Internal Fragmentation is: " << internalFragCount << endl;
    cout << "External Fragmentation is: " << externalFragCount << endl;

    delete[] isOccupied;
    delete[] localBlockSizes;
}

void worstFit() {
    int internalFragCount = 0;
    int externalFragCount = 0;
    bool *isOccupied = new bool[blocksCount] {false};

    int *localBlockSizes = new int[blocksCount];
    copy(blockSizes, blockSizes + blocksCount, localBlockSizes);
    sort(localBlockSizes, localBlockSizes + blocksCount, greater<int>());

    cout << "Process No. \t Process size \t Block Allocated \t Internal Fragmentation" << endl;
    for (int i = 0; i < procCount; i++) {
        bool isExternalFrag = false;
        for (int j = 0; j < blocksCount; j++) {
            if (!isOccupied[j] && procSizes[i] <= localBlockSizes[j]) {
                isOccupied[j] = true;
                isExternalFrag = true;
                internalFragCount += localBlockSizes[j] - procSizes[i];
                cout << "\t P" << (i + 1) << " \t\t   " << procSizes[i] << " \t\t\t\t " << localBlockSizes[j] << " \t\t\t\t  " << (localBlockSizes[j] - procSizes[i]) << endl;
                break;
            }
        }
        if (!isExternalFrag) {
            externalFragCount += procSizes[i];
        }
    }
    cout << "Internal Fragmentation is: " << internalFragCount << endl;
    cout << "External Fragmentation is: " << externalFragCount << endl;

    delete[] isOccupied;
    delete[] localBlockSizes;
}

void nextFit() {
    int internalFragCount = 0;
    int externalFragCount = 0;
    bool *isOccupied = new bool[blocksCount] {false};
    int resume = 0;

    cout << "Process No. \t Process size \t Block Allocated \t Internal Fragmentation" << endl;
    for (int i = 0; i < procCount; i++) {
        bool isExternalFrag = false;
        for (int j = resume; true; j = (j + 1) % blocksCount) {
            if (!isOccupied[j] && procSizes[i] <= blockSizes[j]) {
                isOccupied[j] = true;
                isExternalFrag = true;
                internalFragCount += blockSizes[j] - procSizes[i];
                cout << "\t P" << (i + 1) << " \t\t   " << procSizes[i] << " \t\t\t\t " << blockSizes[j] << " \t\t\t\t  " << (blockSizes[j] - procSizes[i]) << endl;
                resume = j;
                break;
            }
            // terminating condition for circular rotation
            if (resume == (j + 1) % blocksCount)
                break;
        }
        if (!isExternalFrag) {
            externalFragCount += procSizes[i];
        }
    }
    cout << "Internal Fragmentation is: " << internalFragCount << endl;
    cout << "External Fragmentation is: " << externalFragCount << endl;

    delete[] isOccupied;
}

int main() {
    input();

    while (true) {
        cout << "------Menu------" << endl;
        cout << "1. First Fit" << endl;
        cout << "2. Best Fit" << endl;
        cout << "3. Worst Fit" << endl;
        cout << "4. Next Fit" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                firstFit();
                break;
            case 2:
                bestFit();
                break;
            case 3:
                worstFit();
                break;
            case 4:
                nextFit();
                break;
            case 5:
                cout << "Thank You! Exiting..." << endl;
                return 0;
            default:
                cout << "Please enter a valid choice from the menu." << endl;
                break;
        }
    }
}
