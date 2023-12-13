#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>

int placeDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow, const int damagedSprings, const std::vector<int>& substrLength);
void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart, const std::vector<int>& substrLength, int& total);

int main() {
    int a = 1;
    std::ifstream infile("puzzleInput.txt");
    std::string springRow;
    int totalCombinations = 0;

    infile >> springRow;
    while (infile) {
        std::vector<int> groupSizes;
        std::vector<int> unknownLocations;
        int totalDamagedSprings = 0;    
        int num;
        char filler;

        infile >> num;

        totalDamagedSprings += num;
        groupSizes.push_back(num);
        while (infile.peek() == ',') {
            infile >> filler;
            infile >> num;

            totalDamagedSprings += num;
            groupSizes.push_back(num);
        }

        for (int i = 0; i < springRow.length(); i++) {
            if (springRow.at(i) == '#') {
                totalDamagedSprings--;
            } else if (springRow.at(i) == '?') {
                unknownLocations.push_back(i);
            }
        }

        totalCombinations += placeDamagedSprings(unknownLocations, springRow, totalDamagedSprings, groupSizes);

        groupSizes.clear();
        unknownLocations.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

int placeDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow, const int damagedSprings, const std::vector<int>& substrLength) {
    int total = 0;

    for (int u : unknownLocations) {
        springRow.at(u) = '.';
    }

    if (damagedSprings != 1) {
        for (int i = 0; i < unknownLocations.size(); i++) {
            springRow.at(unknownLocations.at(i)) = '#';
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, substrLength, total);
            springRow.at(unknownLocations.at(i)) = '.';
        }
    } else {
        recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings, -1, substrLength, total);
    }
    
    return total;
}

void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart, const std::vector<int>& substrLength, int& total) {
    for (int i = prevLoopStart + 1; i < unknownLocations.size(); i++) {
        springRow.at(unknownLocations.at(i)) = '#';

        if (damagedSprings != 1) {
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, substrLength, total);
        } else {
            bool validArrangement = true;

            for (int l : substrLength) {
                std::string r = "#{" + std::to_string(substrLength.at(0)) + '}';
                for (int j = 1; j < substrLength.size(); j++) {
                    r += "\\.+#{" + std::to_string(substrLength.at(j)) + '}';
                }
                std::regex e(r);

                if (!std::regex_search(springRow, e)) {
                    validArrangement = false;
                    break;
                }
            }

            if (validArrangement) {
                total += 1;
            }
        }

        springRow.at(unknownLocations.at(i)) = '.';
    }
}