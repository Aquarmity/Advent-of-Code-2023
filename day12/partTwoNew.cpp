#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

unsigned long long placeDamagedSprings(std::string springRow, const std::vector<int>& groupSize);
void recursivePlaceDamagedSprings(std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSize, unsigned long long& total);
/*
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

        
        combinations = placeDamagedSprings(unknownLocations, springRow, groupSizes);
        if (springRow.at(springRow.length() - 1) == '.') {
            springRow = '?' + springRow;
            for (int& u : unknownLocations) { u++; }
            unknownLocations.push_back(0);
            combinations *= pow(placeDamagedSprings(unknownLocations, springRow groupSizes), 4); 
        } else {
            unknownLocations.push_back(springRow.length());
            springRow = springRow + '?';
            combinations *= pow(placeDamagedSprings(unknownLocations, springRow groupSizes), 4);
        }

        totalCombinations += combinations;

        groupSizes.clear();
        unknownLocations.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}*/
int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string springRow;
    int totalCombinations = 0;

    infile >> springRow;
    while (infile) {
        std::vector<int> groupSizes;
        int num;
        char filler;

        infile >> num;

        groupSizes.push_back(num);
        while (infile.peek() == ',') {
            infile >> filler;
            infile >> num;
            groupSizes.push_back(num);
        }

        totalCombinations += placeDamagedSprings(springRow, groupSizes);
        std::cout << placeDamagedSprings(springRow, groupSizes) << std::endl;

        groupSizes.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

unsigned long long placeDamagedSprings(std::string springRow, const std::vector<int>& groupSizes) {
    unsigned long long total = 0;
    recursivePlaceDamagedSprings(springRow, 0, 0, groupSizes, total);
    return total;
}

void recursivePlaceDamagedSprings(std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long& total) {
    for (int i = loopStart; i + groupSizes.at(groupSizeIndex) - 1 < springRow.length(); i++) {
        bool endLoop = false;
        for (char ch : springRow.substr(i, groupSizes.at(groupSizeIndex))) {
            if (ch == '.') {
                endLoop = true;
                break;
            }
        }
        if (endLoop) { continue; }
        if (i + groupSizes.at(groupSizeIndex) < springRow.length()) {
            if (springRow.at(i + groupSizes.at(groupSizeIndex)) == '#') {
                continue;
            }
        }

        if (groupSizeIndex < groupSizes.size() - 1) {
            recursivePlaceDamagedSprings(springRow, groupSizeIndex + 1, i + groupSizeIndex + 1, groupSizes, total);
        } else {
            total += 1;
        }
    }
}


/********************
 Just straight up try placing a string of #s length n in a position in the string
 if no periods, do it, if not don't
*/