#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>

int placeDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow, const int damagedSprings, const std::vector<int>& substrLength);
void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart,
                                  const std::vector<int>& substrLength, int& total, const std::regex& e);

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

    if (damagedSprings == 0) { return 1; }

    for (int u : unknownLocations) {
        springRow.at(u) = '.';
    }

    std::string generatedExpression = "\\.*#{" + std::to_string(substrLength.at(0)) + '}';
    for (int j = 1; j < substrLength.size(); j++) {
        generatedExpression += "\\.+#{" + std::to_string(substrLength.at(j)) + '}';
    }
    std::regex e(generatedExpression);

    if (damagedSprings != 1) {
        for (int i = 0; i < unknownLocations.size(); i++) {
            springRow.at(unknownLocations.at(i)) = '#';
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, substrLength, total, e);
            springRow.at(unknownLocations.at(i)) = '.';
        }
    } else {
        recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings, -1, substrLength, total, e);
    }
    
    return total;
}

void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart,
                                  const std::vector<int>& substrLength, int& total, const std::regex& e) {
    for (int i = prevLoopStart + 1; i < unknownLocations.size(); i++) {
        springRow.at(unknownLocations.at(i)) = '#';

        if (damagedSprings != 1) {
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, substrLength, total, e);
        } else {
            if (std::regex_search(springRow, e)) {
                total += 1;
            }
        }

        springRow.at(unknownLocations.at(i)) = '.';
    }
}