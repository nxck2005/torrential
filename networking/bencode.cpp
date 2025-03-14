#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string parseToString(string rawdict) {
    ifstream readfile(rawdict);
    string line;
    string fullfile;
    if (!readfile) {
        return NULL;
    }
    while (getline(readfile, line)) {
        fullfile += line;
    }
    readfile.close();
    return fullfile;
}

int main() {
    string file = parseToString("sample.torrent");
    cout << file << endl;
}