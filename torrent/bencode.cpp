#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct b_decoded {
    string announce;
    vector<string> info;
};

string parseToString(string filename) {
    ifstream readfile(filename);
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

string getAnnounce(string rawstr) {
    return "";
}

int main(void) {
    // Test for string parsing
    string filename;
    cout << "Filename?" << endl;
    cin >> filename;
    string parsedContent = parseToString(filename);
    cout << parsedContent << endl;
}