#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

unsigned long long placeDamagedSprings(const std::vector<int>& unknownLocations, std::string springRow, const int damagedSprings, const std::vector<int>& groupSize);
void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart,
                                  const std::vector<int>& groupSize, unsigned long long& total, const std::regex& e);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string springRow;
    unsigned long long totalCombinations = 0;

    infile >> springRow;
    while (infile) {
        std::vector<int> groupSizes;
        std::vector<int> unknownLocations;
        int totalDamagedSprings = 0;    
        int num;
        unsigned long long combinations = 0;
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

        combinations = placeDamagedSprings(unknownLocations, springRow, totalDamagedSprings, groupSizes);
        if (springRow.at(springRow.length() - 1) == '.') {
            springRow = '?' + springRow;
            for (int& u : unknownLocations) { u++; }
            unknownLocations.push_back(0);
            combinations *= pow(placeDamagedSprings(unknownLocations, springRow, totalDamagedSprings, groupSizes), 4); 
        } else {
            unknownLocations.push_back(springRow.length());
            springRow = springRow + '?';
            combinations *= pow(placeDamagedSprings(unknownLocations, springRow, totalDamagedSprings, groupSizes), 4);
        }

        totalCombinations += combinations;

        groupSizes.clear();
        unknownLocations.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

unsigned long long placeDamagedSprings(const std::vector<int>& unknownLocations, std::string springRow, const int damagedSprings, const std::vector<int>& groupSize) {
    unsigned long long total = 0;

    if (damagedSprings == 0) {
        return 1;
    }

    for (int u : unknownLocations) {
        springRow.at(u) = '.';
    }

    std::string generatedExpression = "\\.*#{" + std::to_string(groupSize.at(0)) + '}';
    for (int j = 1; j < groupSize.size(); j++) {
        generatedExpression += "\\.+#{" + std::to_string(groupSize.at(j)) + '}';
    }
    std::regex e(generatedExpression);

    if (damagedSprings != 1) {
        for (int i = 0; i < unknownLocations.size(); i++) {
            springRow.at(unknownLocations.at(i)) = '#';
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, groupSize, total, e);
            springRow.at(unknownLocations.at(i)) = '.';
        }
    } else {
        recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings, -1, groupSize, total, e);
    }
    
    return total;
}

void recursivePlaceDamagedSprings(const std::vector<int>& unknownLocations, std::string& springRow,
                                  const int damagedSprings, const int prevLoopStart,
                                  const std::vector<int>& groupSize, unsigned long long& total, const std::regex& e) {
    for (int i = prevLoopStart + 1; i < unknownLocations.size(); i++) {
        springRow.at(unknownLocations.at(i)) = '#';

        if (damagedSprings != 1) {
            recursivePlaceDamagedSprings(unknownLocations, springRow, damagedSprings - 1, i, groupSize, total, e);
        } else {
            if (std::regex_search(springRow, e)) {
                total += 1;
            }
        }

        springRow.at(unknownLocations.at(i)) = '.';
    }
}


/********************
 Just straight up try placing a string of #s length n in a position in the string
 if no periods, do it, if not don't

*/