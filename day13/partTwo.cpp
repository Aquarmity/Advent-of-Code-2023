#include <iostream>
#include <string>
#include <fstream>
#include <vector>

bool mirrorCheck(const std::vector<std::string>& lines, int curIndex);
bool mirrorCheckOneOff(const std::vector<std::string>& lines, int curIndex);
bool oneOff(const std::string& first, const std::string& second);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string currentLine;
    std::vector<std::string> horizontalLines;
    std::vector<std::string> verticalLines;
    int total = 0;

    while (infile) {
        getline(infile, currentLine);
        
        if (currentLine != "\0") {
            horizontalLines.push_back(currentLine);
        } else {
            int numToAdd = 0;

            for (int i = 0; i < horizontalLines.size() - 1; i++) {
                if (oneOff(horizontalLines.at(i), horizontalLines.at(i + 1)) && mirrorCheck(horizontalLines, i)) {
                    numToAdd = 100 * (i + 1);
                    break;
                }
                
                if (horizontalLines.at(i) == horizontalLines.at(i + 1) && mirrorCheckOneOff(horizontalLines, i)) {
                    numToAdd = 100 * (i + 1);
                    break;
                }
            }

            if (numToAdd == 0) {
                for (int i = 0; i < horizontalLines.at(0).length(); i++) {
                    std::string tempString = std::string();
                    for (std::string str : horizontalLines) {
                        tempString += str.at(i);
                    }
                    verticalLines.push_back(tempString);
                }

                for (int i = 0; i < verticalLines.size() - 1; i++) {
                    if (oneOff(verticalLines.at(i), verticalLines.at(i + 1)) && mirrorCheck(verticalLines, i)) {
                        numToAdd = i + 1;
                        break;
                    }
                    
                    if (verticalLines.at(i) == verticalLines.at(i + 1) && mirrorCheckOneOff(verticalLines, i)) {
                        numToAdd = i + 1;
                        break;
                    }
                }
            }

            horizontalLines.clear();
            verticalLines.clear();
            total += numToAdd;
        }
    }

    std::cout << total;

    return 0;
}

bool mirrorCheck(const std::vector<std::string>& lines, int curIndex) {
    for (int j = 1; j <= curIndex && j + curIndex + 1 < lines.size(); j++) {
        if (lines.at(curIndex + j + 1) != lines.at(curIndex - j)) {
            return false;
        }
    }

    return true;
}

bool mirrorCheckOneOff(const std::vector<std::string>& lines, int curIndex) {
    int oneOffLines = 0;
    for (int j = 1; j <= curIndex && j + curIndex + 1 < lines.size(); j++) {
        if (lines.at(curIndex + j + 1) != lines.at(curIndex - j)) {
            if (oneOff(lines.at(curIndex + j + 1), lines.at(curIndex - j))) {
                oneOffLines++;
            }

            if (oneOffLines != 1) {
                return false;
            }
        }
    }

    if (oneOffLines == 1) {
        return true;
    }

    return false;
}

bool oneOff(const std::string& first, const std::string& second) {
    int charDiff = 0;
    for (int i = 0; i < first.length(); i++) {
        if (first.at(i) != second.at(i)) {
            charDiff++;
        }
    }

    if (charDiff == 1) {
        return true;
    }
    return false;
}