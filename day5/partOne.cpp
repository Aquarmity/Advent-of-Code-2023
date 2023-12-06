#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string filler;
    std::vector<unsigned long long> seedList;
    unsigned long long seed;
    unsigned long long destinationRangeStart;
    unsigned long long sourceRangeStart;
    unsigned long long rangeLength;
    
    infile >> filler;
    while (!infile.fail()) {
        infile >> seed;
        if (!infile.fail()) {
            seedList.push_back(seed);
        }
    }

    

    return 0;
}