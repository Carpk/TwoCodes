#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

const int ARRAYSIZE=251;

void loadBook(string dictArray[ARRAYSIZE]) {
    ifstream inStream;
    inStream.open( "ConstitutionAndBillOfRights.txt");
    if( !inStream.is_open()) {cout << "Could not find file.  Exiting..." << endl; exit( -1);}

    int i = 0;
    string line;
    while( getline(inStream,  line)) {
        if (line != "") {
            dictArray[i] = line;
            i++;
        }
    }
    inStream.close();
}

void prompt(){
    cout << "\n"
    << "Select from the following choices:\n"
    << "W  Enter word or phrase to find, and display enclosing text\n"
    << "P  Display previous text\n"
    << "F  Display following text\n"
    << "A  Display all occurrences of found word or phrase\n"
    << "X  Exit program\n"
    << "Your choice:" << endl;
}


vector<int> findText(string bookArray[ARRAYSIZE], string textToFind) {
    vector<int> foundIndices;

    for (int i = 0; i < ARRAYSIZE; i++) {
        foundIndices = {1,2,3,4,5};
    }

    return foundIndices;
}


int main() {
    char userInput;
    string userSearchTerm;
    bool isRunning = true;
    vector<int> foundIndices;
    string  bookArray[ARRAYSIZE];

    loadBook(bookArray);

    while (isRunning) {
        //prompt();
        //cin >> userInput;
        userInput = 'W';

        switch(userInput) {
            case 'W':
                cout << "W is selected" << endl;
                userSearchTerm = "five years";
                foundIndices = findText(bookArray, userSearchTerm);

                break;
            case 'P':
                cout << "P is selected" << endl;
                break;
            case 'F':
                cout << "F is selected" << endl;
                break;
            case 'A':
                cout << "A is selected" << endl;
                break;
            case 'X':
                cout << "exiting the system" << endl;
                break;
        }
        for (int i =0; i < foundIndices.size(); i++) {
            cout << "in the repetion loop" << endl;
            cout << bookArray[foundIndices.at(i)] << endl;
        }
        isRunning = false;
    }


}


