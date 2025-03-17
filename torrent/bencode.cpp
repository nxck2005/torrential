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

string getAnnounce(string& rawstr) {
    int indexAnnounce = rawstr.find(":announce");
    if (indexAnnounce == string::npos) {
        return "";
    }
    
    // Skip past ":announce"
    int startPos = indexAnnounce + 9;
    
    // Extract the length digits
    string annLengthExtracted;
    int i = startPos;
    while (i < rawstr.length() && isdigit(rawstr[i])) {
        annLengthExtracted += rawstr[i];
        i++;
    }
    
    // If we didn't find any digits or didn't reach a colon
    if (annLengthExtracted.empty() || i >= rawstr.length() || rawstr[i] != ':') {
        return "";
    }
    
    try {
        int announceLength = stoi(annLengthExtracted);
        // Move past the colon
        i++;
        // Extract the announce URL
        string announceURL = rawstr.substr(i, announceLength);
        return announceURL;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid integer conversion: " << annLengthExtracted << std::endl;
        return "";
    } catch (const std::out_of_range& e) {
        std::cerr << "Number out of range: " << annLengthExtracted << std::endl;
        return "";
    }
}

/* int main(void) {
    // Test for string parsing
    string filename;
    cout << "Filename?" << endl;
    cin >> filename;
    string parsedContent = parseToString(filename);
    cout << parsedContent << endl;
    cout << getAnnounce(parsedContent) << endl;
} */