#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string BENC_decode(string rawdict) {
    return "";
}

int main() {
    ifstream readfile("bencoder.torrent");
    if (!readfile) {
        cout << "File not found" << endl;
        return 1;
    } else {
        cout << "File found!";
    }
    readfile.close();
}