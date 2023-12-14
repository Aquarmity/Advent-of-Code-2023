#include <iostream>
#include <string>
#include <fstream>
#include <vector>

unsigned long long placeDamagedSprings(const std::string springRow, const std::vector<int>& groupSize);
unsigned long long recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                  const std::vector<int>& groupSizes, unsigned long long memos[200][50]);

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
    unsigned long long memos[200][50];
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 50; j++) {
            memos[i][j] = -1;
        }
    }

    return recursivePlaceDamagedSprings(springRow, 0, 0, groupSizes, memos);
}

unsigned long long recursivePlaceDamagedSprings(const std::string& springRow, const int groupSizeIndex, const int loopStart,
                                                const std::vector<int>& groupSizes, unsigned long long memos[200][50]) {
    unsigned long long subTotal = 0;
    for (int i = loopStart; i + groupSizes.at(groupSizeIndex) - 1 < springRow.length(); i++) {
        if (memos[i][groupSizeIndex] != -1) {
            subTotal += memos[i][groupSizeIndex];
            continue;
        }

        if (i != 0) {
            if (springRow.at(i - 1) == '#') {
                break;
            }
        }

        memos[i][groupSizeIndex] = 0;

        bool endLoop = false;
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

        if (groupSizeIndex < groupSizes.size() - 1) {
            memos[i][groupSizeIndex] = recursivePlaceDamagedSprings(springRow, groupSizeIndex + 1, i + groupSizes.at(groupSizeIndex) + 1, groupSizes, memos);
            subTotal += memos[i][groupSizeIndex];
        } else {
            bool validPlacement = true;
            for (int j = i + groupSizes.at(groupSizeIndex); j < springRow.length(); j++) {
                if (springRow.at(j) == '#') {
                    validPlacement = false;
                }
            }
            if (validPlacement) {
                subTotal++;
                memos[i][groupSizeIndex]++;
            }
        }
    }

    return subTotal;
}