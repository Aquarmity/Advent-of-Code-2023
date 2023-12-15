#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
                if (horizontalLines.at(i) == horizontalLines.at(i + 1)) {
                    numToAdd = 100 * (i + 1);
                    for (int j = 1; j <= i && j + i + 1 < horizontalLines.size(); j++) {
                        if (horizontalLines.at(i + j + 1) != horizontalLines.at(i - j)) {
                            numToAdd = 0;
                        }
                    }

                    if (numToAdd != 0) {
                        break;
                    }
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
                    if (verticalLines.at(i) == verticalLines.at(i + 1)) {
                        numToAdd = i + 1;
                        for (int j = 1; j <= i && j + i + 1 < verticalLines.size(); j++) {
                            if (verticalLines.at(i + j + 1) != verticalLines.at(i - j)) {
                                numToAdd = 0;
                            }
                        }

                        if (numToAdd != 0) {
                            break;
                        }
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