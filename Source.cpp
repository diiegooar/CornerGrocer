#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class CornerGrocer {
public:
    void DisplayMenu();
    void SetMyList(string& itemName);
    void PrintList();
    void PrintHistogram();
    void searchList(string& userValue);

private:
    map<string, int> myList;
};

void CornerGrocer::DisplayMenu() {
    cout << "==========================================\n";
    cout << "\tWELCOME TO CORNER GROCER\n";
    cout << "==========================================\n";
    cout << "What option do you want to choose?\n";
    cout << "------------------------------------------\n";
    cout << "1. Specific item frequency\n\n";
    cout << "2. Frequency of all items purchased\n\n";
    cout << "3. Histogram frequency of all items\n\n";
    cout << "4. Exit\n\n";

}

void CornerGrocer::SetMyList(string& itemName) {
    if (myList.find(itemName) == myList.end()) {
        myList[itemName] = 1;
    }
    else {
        myList[itemName] += 1;
    }
}

void CornerGrocer::PrintList() {
    ofstream outFS;
    outFS.open("frequency.dat");
    for (auto& list : myList) {
        cout << list.first << " " << list.second << "\n";
        outFS << list.first << " " << list.second << "\n";
    }
    outFS.close();
}

void CornerGrocer::PrintHistogram() {
    for (auto& list : myList) {
        cout << list.first << " ";
        for (int i = 0; i < list.second; i++) {
            cout << "*";
        }
        cout << "\n";
    }
}

void CornerGrocer::searchList(string& userValue) {
    for (auto list : myList) {
        if (list.first == userValue) {
            cout << list.first << ": " << list.second;
            break;
        }
    }
}

int main() {
    string file;
    CornerGrocer first;
    int option;
    string userItem;
    string currWord;
    ifstream inFS;
    ofstream outFS;
    int wordFreq = 0;

    // Open file
    cout << "Enter the name of your file: ";
    getline(cin, file);
    inFS.open(file);
    
    if (inFS.is_open()) {
        do {
            first.DisplayMenu();
            cin >> option;
            switch (option) {
            case 1:
                system("cls");
                cout << "Item you looking for: ";
                cin >> userItem;
                wordFreq = 0;
                inFS.clear();
                inFS.seekg(0, ios::beg);
                while (!inFS.eof()) {
                    inFS >> currWord;
                    if (!inFS.fail()) {
                        if (currWord == userItem) {
                            ++wordFreq;
                        }
                    }
                }
                cout << userItem << ": " << wordFreq << "\n";
                break;
            case 2:
                while (!inFS.eof()) {
                    inFS >> currWord;
                    first.SetMyList(currWord);
                }
                first.PrintList();
                break;
            case 3:
                while (!inFS.eof()) {
                    inFS >> currWord;
                    first.SetMyList(currWord);
                }
                first.PrintHistogram();
                break;
            }

        } while (option != 4);
    }
    else { 
        cout << "Could not open file " << file << "\n";
        return 1;
    }
    
    inFS.close();

    return 0;
}