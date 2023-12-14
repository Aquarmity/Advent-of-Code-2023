#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

unsigned long long placeDamagedSprings(std::string springRow, const std::vector<int>& groupSize);
void recursivePlaceDamagedSprings(std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long& total,
                                  std::vector<int>& placementIndices, std::unordered_map<std::pair<int, int>, bool>& memos);

int main() {
    std::ifstream infile("test.txt");
    std::string springRow;
    unsigned long long totalCombinations = 0;
    unsigned long long combinations;

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

        std::vector<int> originalGroupSizes = groupSizes;
        std::string originalSpringRow = springRow;
        for (int i = 0; i < 4; i++) {
            springRow += '?' + originalSpringRow;
            for (int gs : originalGroupSizes) {
                groupSizes.push_back(gs);
            }
        }

        combinations = placeDamagedSprings(springRow, groupSizes);
        totalCombinations += placeDamagedSprings(springRow, groupSizes);
        std::cout << combinations << std::endl;

        groupSizes.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

unsigned long long placeDamagedSprings(std::string springRow, const std::vector<int>& groupSizes) {
    unsigned long long total = 0;
    std::vector<int> placementIndices;
    std::unordered_map<std::pair<int, int>, bool> memos;
    recursivePlaceDamagedSprings(springRow, 0, 0, groupSizes, total, placementIndices, memos);
    return total;
}

void recursivePlaceDamagedSprings(std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long& total,
                                  std::vector<int>& placementIndices, std::unordered_map<std::pair<int, int>, bool>& memos) {
    for (int i = loopStart; i + groupSizes.at(groupSizeIndex) - 1 < springRow.length(); i++) {
        bool endLoop = false;

        if (i != 0) {
            if (springRow.at(i - 1) == '#') {
                break;
            }
        }

        if (memos.count(std::make_pair(loopStart, groupSizeIndex)) == 0) {
            for (char ch : springRow.substr(i, groupSizes.at(groupSizeIndex))) {
                if (ch == '.') {
                    endLoop = true;
                    break;
                }
            }

            if (endLoop) {
                memos.insert(std::make_pair(std::make_pair(loopStart, groupSizeIndex), false));
                continue;
            }
            if (i + groupSizes.at(groupSizeIndex) < springRow.length()) {
                if (springRow.at(i + groupSizes.at(groupSizeIndex)) == '#') {
                    memos.insert(std::make_pair(std::make_pair(loopStart, groupSizeIndex), false));
                    continue;
                }
            }
        }

        if (memos.at(std::make_pair(loopStart, groupSizeIndex)) = false) {
            continue;
        }

        placementIndices.push_back(i);
        if (groupSizeIndex < groupSizes.size() - 1) {
            recursivePlaceDamagedSprings(springRow, groupSizeIndex + 1, i + groupSizes.at(groupSizeIndex) + 1, groupSizes, total, placementIndices, memos);
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