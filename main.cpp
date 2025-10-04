#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

int main() {
    system("chcp 65001 > nul");
    ofstream MyFile("mynote.txt");

    string myText;
    getline(cin, myText);

    MyFile << myText;
    MyFile.close();
    

    ifstream ReadFile("mynote.txt");
    while (getline(ReadFile, myText))
    {
        cout<<myText;
    }

    ReadFile.close();
    
    return 0;
}