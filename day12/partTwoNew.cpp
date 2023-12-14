#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

unsigned long long placeDamagedSprings(const std::string springRow, const std::vector<int>& groupSize);
void recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long& total,
                                  std::vector<int>& placementIndices, int memos[200][50]);

int main() {
    std::ifstream infile("puzzleInput.txt");
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
        totalCombinations += combinations;
        std::cout << combinations << std::endl;

        groupSizes.clear();
        infile >> springRow;
    }

    std::cout << totalCombinations;
}

unsigned long long placeDamagedSprings(std::string springRow, const std::vector<int>& groupSizes) {
    unsigned long long total = 0;
    std::vector<int> placementIndices;

    int memos[200][50];
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 50; j++) {
            memos[i][j] = -1;
        }
    }

    recursivePlaceDamagedSprings(springRow, 0, 0, groupSizes, total, placementIndices, memos);

    return total;
}

void recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long& total,
                                  std::vector<int>& placementIndices, int memos[200][50]) {
    #pragma omp parallel for
    for (int i = loopStart; i + groupSizes.at(groupSizeIndex) - 1 < springRow.length(); i++) {
        if (i != 0) {
            if (springRow.at(i - 1) == '#') {
                break;
            }
        }

        if (memos[i][groupSizeIndex] == -1) {
            bool endLoop = false;
            for (char ch : springRow.substr(i, groupSizes.at(groupSizeIndex))) {
                if (ch == '.') {
                    endLoop = true;
                    break;
                }
            }

            if (endLoop) {
                memos[i][groupSizeIndex] = 0;
                continue;
            }
            if (i + groupSizes.at(groupSizeIndex) < springRow.length()) {
                if (springRow.at(i + groupSizes.at(groupSizeIndex)) == '#') {
                    memos[i][groupSizeIndex] = 0;
                    continue;
                }
            }
        } else if (memos[i][groupSizeIndex] == 0) {
            continue;
        }

        placementIndices.push_back(i);
        if (groupSizeIndex < groupSizes.size() - 1) {
            recursivePlaceDamagedSprings(springRow, groupSizeIndex + 1, i + groupSizes.at(groupSizeIndex) + 1, groupSizes, total, placementIndices, memos);
        } else {
            /*bool validPlacement = true;
            /*for (int j = i + groupSizes.at(groupSizeIndex) - 1; j < springRow.length(); j++) {
                validPlacement = false;
                if (springRow.at(j) == '#') {
                    validPlacement = true;
                    break;
                }
                validPlacement = true;
            }*/
            //if (validPlacement) {
                #pragma omp critical
                total += 1;
            //}
        }

        placementIndices.pop_back();
    }
}