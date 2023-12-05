#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

bool contains(const std::vector<int>& v, int refVal);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string filler;
    char letter;
    std::vector<int> winningNumbers;
    int curNum;
    int matches = 0;
    int total = 0;
    
    infile >> filler;
    while (infile) {
        infile >> filler;
        
        for (int i = 0; i < 10; i++) {
            infile >> curNum;
            winningNumbers.push_back(curNum);
        }

        infile >> filler;
        
        for (int i = 0; i < 25; i++) {
            infile >> curNum;
            if (contains(winningNumbers, curNum)) {
                matches++;
            }
        }

        total += pow(2, matches - 1);
        matches = 0;
        winningNumbers.clear();
        infile >> filler;
    }

    std::cout << total;

    return 0;
}

bool contains(const std::vector<int>& v, int refVal) {
    for (int i : v) {
        if (refVal == i) {
            return true;
        }
    }

    return false;
}