#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

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
            i++;+
        }
    }
    inStream.close();
}

void prompt(bool isFullPrompt){
    cout << "\n"
         << "Select from the following choices:\n"
         << "W  Enter word or phrase to find, and display enclosing text" << endl;
    if (isFullPrompt) {
        cout << "P  Display previous text\n"
             << "F  Display following text\n"
             << "A  Display all occurrences of found word or phrase" << endl;
    }
    cout <<  "X  Exit program\n"
         << "Your choice:" << endl;
}


vector<int> findText(const string bookArray[ARRAYSIZE], string textToFind) {
    vector<int> foundIndices;

    for (int i = 0; i < ARRAYSIZE; i++) {
        string parentStr = bookArray[i];
        transform(parentStr.begin(), parentStr.end(), parentStr.begin(), ::tolower);

        if (parentStr.find(textToFind) != string::npos) {
            foundIndices.push_back(i);
        }
    }

    return foundIndices;
}

vector<int> getIndices(const string bookArray[ARRAYSIZE],char userInput, bool isRunning) {
    vector<int> foundIndices;
    string userSearchTerm;

    switch(toupper(userInput)) {
        case 'W':
            cout << "Enter word or phrase: " << endl;
            userSearchTerm = "five years";
            // convert userSearch to lowercase
            foundIndices = findText(bookArray, userSearchTerm);
            foundIndices = {foundIndices.at(0)};
            break;
        case 'P':
            cout << "P is selected" << endl;
            foundIndices = {foundIndices.at(0) - 1};
            break;
        case 'F':
            cout << "F is selected" << endl;
            foundIndices = {foundIndices.at(0) + 1};
            break;
        case 'A':
            cout << "A is selected" << endl;
            foundIndices = findText(bookArray, userSearchTerm);
            break;
        case 'X':
            cout << "exiting the system" << endl;
            isRunning = false;
            break;
    }

    return foundIndices;
}

void printFromIndices(const string bookArray[ARRAYSIZE], vector<int> indices) {
    for (int i =0; i < indices.size(); i++) {
        int indexNum = indices.at(i);
        cout << "Line " << indexNum << ':' << endl;
        cout << bookArray[indexNum] << endl;
    }
}

int main() {
    char userInput;
    string userSearchTerm;
    bool isRunning = true;
    vector<int> foundIndices;
    string  bookArray[ARRAYSIZE];

    loadBook(bookArray);

    //prompt(false);
    //cin >> userInput;

    foundIndices = getIndices(bookArray, userInput, isRunning);

    printFromIndices(bookArray, foundIndices);

    while (isRunning) {
        //prompt(true);
        //cin >> userInput;
        userInput = 'w';

        foundIndices = getIndices(bookArray, userInput, isRunning);

        printFromIndices(bookArray, foundIndices);
        isRunning = false;
    }

    return 0;
}


