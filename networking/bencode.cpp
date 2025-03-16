#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string parseToString(string rawdict) {
    ifstream readfile(rawdict);
    string line;
    string fullfile;
    if (!readfile) {
        return "";
    }
    while (getline(readfile, line)) {
        fullfile += line;
    }
    readfile.close();
    return fullfile;
}