#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void tiltNorth (std::vector<std::string>& platform);
void tiltWest (std::vector<std::string>& platform);
void tiltSouth (std::vector<std::string>& platform);
void tiltEast (std::vector<std::string>& platform);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::vector<std::string> platform;
    std::string line;
    int total = 0;

    infile >> line;
    while (infile) {
        platform.push_back(line);
        infile >> line;
    }

    for (int i = 0; i < 1000; i++) {
        total = 0;
        tiltNorth(platform);
        tiltWest(platform);
        tiltSouth(platform);
        tiltEast(platform);

        for (int i = 0; i < platform.size(); i++) {
            total += (platform.size() - i) * std::count(platform.at(i).begin(), platform.at(i).end(), 'O');
        }

        std::cout << total << std::endl;
    }

    return 0;
}

void tiltNorth (std::vector<std::string>& platform) {
    for (int i = 1; i < platform.size(); i++) {
        for (int j = 0; j < platform.size(); j++) {
            if (platform.at(i).at(j) == 'O') {
                int curRow = i;
                while (curRow > 0 && platform.at(curRow - 1).at(j) == '.') {
                    curRow--;
                }
                std::swap(platform.at(i).at(j), platform.at(curRow).at(j));
            }
        }
    }
}

void tiltWest (std::vector<std::string>& platform) {
    for (int i = 0; i < platform.size(); i++) {
        for (int j = 1; j < platform.size(); j++) {
            if (platform.at(i).at(j) == 'O') {
                int curCol = j;
                while (curCol > 0 && platform.at(i).at(curCol - 1) == '.') {
                    curCol--;
                }
                std::swap(platform.at(i).at(j), platform.at(i).at(curCol));
            }
        }
    }
}

void tiltSouth (std::vector<std::string>& platform) {
    for (int i = platform.size() - 2; i >= 0; i--) {
        for (int j = 0; j < platform.size(); j++) {
            if (platform.at(i).at(j) == 'O') {
                int curRow = i;
                while (curRow < platform.size() - 1 && platform.at(curRow + 1).at(j) == '.') {
                    curRow++;
                }
                std::swap(platform.at(i).at(j), platform.at(curRow).at(j));
            }
        }
    }
}

void tiltEast (std::vector<std::string>& platform) {
    for (int i = 0; i < platform.size(); i++) {
        for (int j = platform.size() - 2; j >= 0; j--) {
            if (platform.at(i).at(j) == 'O') {
                int curCol = j;
                while (curCol < platform.size() - 1 && platform.at(i).at(curCol + 1) == '.') {
                    curCol++;
                }
                std::swap(platform.at(i).at(j), platform.at(i).at(curCol));
            }
        }
    }
}