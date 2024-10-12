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
    unsigned long long curMap;
    unsigned long long lowestLocation = 99999999999999;

    infile >> filler;
    while (!infile.fail()) {
        infile >> seed;
        if (!infile.fail()) {
            seedList.push_back(seed);
        }
    }

    infile.clear();
    int posAfterSeeds = infile.tellg();

    for (unsigned long long s : seedList) {
        curMap = s;

        infile >> filler;
        while (infile) {
            infile >> filler;

            infile >> destinationRangeStart;
            while (!infile.fail()) {
                infile >> sourceRangeStart;
                infile >> rangeLength;
                
                if (curMap >= sourceRangeStart && curMap < sourceRangeStart + rangeLength) {
                    curMap = destinationRangeStart + (curMap - sourceRangeStart);
                    while (!infile.fail()) {
                        infile >> sourceRangeStart;
                    }
                    break;
                }
                infile >> destinationRangeStart;
            }

            infile.clear();
            infile >> filler;
        }

        if (curMap < lowestLocation) {
            lowestLocation = curMap;
        }

        infile.clear();
        infile.seekg(posAfterSeeds);
    }
    
    std::cout << lowestLocation;

    return 0;
}