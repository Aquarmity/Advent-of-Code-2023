#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>

struct LineInfo {
    unsigned long long destinationRangeStart;
    unsigned long long sourceRangeStart;
    unsigned long long rangeLength;
};

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string filler;
    std::vector<unsigned long long> seedList;
    std::vector<unsigned long long> seedRangeList;
    unsigned long long seed;
    unsigned long long seedRange;
    unsigned long long curMapVal;
    unsigned long long lowestLocation = 99999999999999;
    std::vector<std::vector<LineInfo*>*> maps;

    infile >> filler;
    infile >> seed;
    while (!infile.fail()) {
        infile >> seedRange;
        if (!infile.fail()) {
            seedList.push_back(seed);
            seedRangeList.push_back(seedRange);
        }
        infile >> seed;
    }

    infile.clear();
    infile >> filler;
    while (infile) {
        infile >> filler;

        std::vector<LineInfo*>* curMap = new std::vector<LineInfo*>();
        while (!infile.fail()) {
            LineInfo* curLine = new LineInfo();
            infile >> curLine->destinationRangeStart;
            infile >> curLine->sourceRangeStart;
            infile >> curLine->rangeLength;

            curMap->push_back(curLine);
        }

        maps.push_back(curMap);
        infile.clear();
        infile >> filler;
    }

    int r = 0;
    for (unsigned long long s : seedList) {
        std::cout << "Checking from " << s << " to " << s + seedRangeList.at(r) - 1 << std::endl;
        for (int i = 0; i < seedRangeList.at(r); i++) {
            curMapVal = s + i;
            
            for (std::vector<LineInfo*>* m : maps) {
                for (LineInfo* l : *m) {
                    if (curMapVal >= l->sourceRangeStart && curMapVal < l->sourceRangeStart + l->rangeLength) {
                        curMapVal = l->destinationRangeStart + (curMapVal - l->sourceRangeStart);
                        break;
                    }
                }
            }

            if (curMapVal < lowestLocation) {
                lowestLocation = curMapVal;
            }
        }

        r++;
    }
    
    std::cout << lowestLocation;

    return 0;
}