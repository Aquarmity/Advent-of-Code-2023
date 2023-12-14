// recursivePlaceDamagedSprings is cleaned up further in partTwoNew.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int placeDamagedSprings(const std::string& springRow, const std::vector<int>& groupSize);
void recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, int& total,
                                  std::vector<int>& placementIndices);

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

        groupSizes.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

int placeDamagedSprings(const std::string& springRow, const std::vector<int>& groupSizes) {
    int total = 0;
    std::vector<int> placementIndices;
    recursivePlaceDamagedSprings(springRow, 0, 0, groupSizes, total, placementIndices);
    return total;
}

void recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, int& total,
                                  std::vector<int>& placementIndices) {
    for (int i = loopStart; i + groupSizes.at(groupSizeIndex) - 1 < springRow.length(); i++) {
        bool endLoop = false;

        if (i != 0) {
            if (springRow.at(i - 1) == '#') {
                break;
            }
        }

        for (char ch : springRow.substr(i, groupSizes.at(groupSizeIndex))) {
            if (ch == '.') {
                endLoop = true;
                break;
            }
        }

        if (endLoop) {
            continue;
        }
        if (i + groupSizes.at(groupSizeIndex) < springRow.length()) {
            if (springRow.at(i + groupSizes.at(groupSizeIndex)) == '#') {
                continue;
            }
        }

        placementIndices.push_back(i);
        if (groupSizeIndex < groupSizes.size() - 1) {
            recursivePlaceDamagedSprings(springRow, groupSizeIndex + 1, i + groupSizes.at(groupSizeIndex) + 1, groupSizes, total, placementIndices);
        } else {
            bool validPlacement;
            for (int j = 0; j < springRow.length(); j++) {
                validPlacement = false;
                for (int k = 0; k < placementIndices.size(); k++) {
                    if (springRow.at(j) == '#') {
                        if (j >= placementIndices.at(k) && j < placementIndices.at(k) + groupSizes.at(k)) {
                            validPlacement = true;
                            break;
                        }
                    }
                }
                if (!validPlacement && springRow.at(j) == '#') {
                    break;
                } else {
                    validPlacement = true;
                }
            }
            if (validPlacement) {
                total += 1;
            }
        }

        placementIndices.pop_back();
    }
}