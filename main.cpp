/*----------------------------------------------------------
 * Program 4: Two Codes
 *
 * Class: CS 141, Spring 2020. Tue 4pm lab
 * System: CLion on Windows 10
 * Author: Shawn Klein
 * ---------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int ARRAYSIZE=300;

// loads a book of the given name into the given array.
void loadBook(string dictArray[ARRAYSIZE], string bookName) {
    ifstream inStream;
    inStream.open( bookName);
    if( !inStream.is_open()) {cout << "Could not find file.  Exiting..." << endl; exit( -1);}

    int i = 0;
    string line;
    while(getline(inStream,  line)) {
        if (!line.empty()) {
            (dictArray[i]).assign(line);
            i++;
        }
    }
    dictArray[i] = '\0';
    inStream.close();
}

// prompts user for inputs
void prompt(bool isFullPrompt){
    cout << "Select from the following choices:\n"
         << "   W  Enter word or phrase to find, and display enclosing text" << endl;
    if (isFullPrompt) {
        cout << "   P  Display previous text\n"
             << "   F  Display following text\n"
             << "   A  Display all occurrences of found word or phrase" << endl;
    }
    cout <<  "   X  Exit program\n"
         << "Your choice:" << endl;
}

// returns the size of the given array
int getBookSize(const string book[ARRAYSIZE]) {
    int i = 0;
    while (book[i] != "\0") {
        i++;
    }
    return --i;
}

// returns a vector of indices from the given array, using the given string
vector<int> getIndicesFrom(const string bookArray[ARRAYSIZE], string textToFind) {
    vector<int> foundIndices;
    int maxSize = getBookSize( bookArray);

    for (int i = 0; i < maxSize; i++) {
        string bookStr = bookArray[i];

        transform(bookStr.begin(), bookStr.end(), bookStr.begin(), ::tolower);

        if (bookStr.find(textToFind) != string::npos) {
            foundIndices.push_back(i);
        }
    }

    return foundIndices;
}

// prints indices of array from the given vector
void printFromIndices(const string book[ARRAYSIZE], vector<int> indices) {
    for (size_t i =0; i < indices.size(); i++) {
        int indexNum = indices.at(i);
        cout << "Line " << indexNum << ':' << endl;
        cout << book[indexNum] << '\n' << endl;
    }
}

// prompts user for phrase, searches for phrase, and returns a vector of found indices
vector<int> userSearchPrompt(const string bookArray[ARRAYSIZE], string* userSearchTerm) {
    vector<int> foundIndices;
    cout << "Enter word or phrase: " << endl;
    getline(cin, *userSearchTerm);

    transform(userSearchTerm->begin(), userSearchTerm->end(), userSearchTerm->begin(), ::tolower);

    foundIndices = getIndicesFrom(bookArray, *userSearchTerm);

    return foundIndices;
}


int main() {
    char userInput;
    bool isRunning = true;
    bool isFullPrompt = 0;
    string userSearchTerm;
    string bookName = "ConstitutionAndBillOfRights.txt";
    vector<int> foundIndices;
    string  bookArray[ARRAYSIZE];

    loadBook(bookArray, bookName);

    while (isRunning) {
        prompt(isFullPrompt++);
        cin >> userInput;
        cin.get();

        switch(toupper(userInput)) {
            case 'W':
                foundIndices = userSearchPrompt(bookArray, &userSearchTerm);
                if (!foundIndices.empty()) {foundIndices = {foundIndices.at(0)};}
                printFromIndices(bookArray, foundIndices);
                break;
            case 'P':
                if (!foundIndices.empty() && (foundIndices.front() - 1 >= 0)) {
                    foundIndices = {foundIndices.front() - 1};
                    printFromIndices(bookArray, foundIndices);
                } else {
                    cout << "There is no previous file contents." << endl;
                }
                break;
            case 'F':
                if (!foundIndices.empty() && (foundIndices.front()+1 < getBookSize(bookArray))) {
                    foundIndices = {foundIndices.front() + 1};
                    printFromIndices(bookArray, foundIndices);
                } else {
                    cout << "There is no following file contents." << endl;
                }
                break;
            case 'A':
                foundIndices = getIndicesFrom(bookArray, userSearchTerm);
                printFromIndices(bookArray, foundIndices);
                break;
            case 'X':
                cout << "Exiting program." << endl;
                foundIndices = {};
                isRunning = false;
                break;
        }
    }

    return 0;
}


