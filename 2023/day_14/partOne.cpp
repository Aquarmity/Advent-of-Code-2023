#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

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

    for (int i = 1; i < platform.size(); i++) {
        for (int j = 0; j < platform.size(); j++) {
            if (platform.at(i).at(j) == 'O') {
                int curRow = i;
                while (curRow > 0 && platform.at(curRow - 1).at(j) == '.') {
                    std::swap(platform.at(curRow).at(j), platform.at(curRow - 1).at(j));
                    curRow--;
                }
            }
        }
    }

    for (int i = 0; i < platform.size(); i++) {
        total += (platform.size() - i) * std::count(platform.at(i).begin(), platform.at(i).end(), 'O');
    }

    std::cout << total;

    return 0;
}