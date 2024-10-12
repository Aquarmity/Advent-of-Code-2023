#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>

struct PartNumber {
    int startIndex;
    int endIndex;
    int value;
    int rowNumber;

    PartNumber(int start, int row) {
        startIndex = start;
        endIndex = start;
        rowNumber = row;
        value = 0;
    }
};

struct SymbolPosition {
    int col;
    int row;

    SymbolPosition(int c, int r) {
        col = c;
        row = r;
    }
};

bool adjacent(const PartNumber* part, const SymbolPosition* symbol);

int main() {
    std::ifstream infile("puzzleinput.txt");
    int curRow = 0;
    int total = 0;
    std::string curLine;
    std::vector<PartNumber*> partNumbers;
    std::vector<SymbolPosition*> symbolPositions;

    infile >> curLine;
    while (infile) {
        for (int i = 0; i < curLine.length(); i++) {
            if (isdigit(curLine.at(i))) {
                partNumbers.push_back(new PartNumber(i, curRow));
                while (isdigit(curLine.at(i))) {
                    partNumbers.back()->endIndex = i;
                    partNumbers.back()->value = (10 * partNumbers.back()->value) + curLine.at(i) - '0';

                    i++;
                    if (i >= curLine.length()) { break; }
                }

                if (i >= curLine.length()) { break; }
            }


            if (curLine.at(i) != '.') {
                symbolPositions.push_back(new SymbolPosition(i, curRow));
            }
        }
        
        infile >> curLine;
        curRow++;
    }

    for (PartNumber* curPart : partNumbers) {
        for (SymbolPosition* curSymbol : symbolPositions) {
            if (curSymbol->row < curPart->rowNumber - 1) {
                continue;
            }
            if (curSymbol->row > curPart->rowNumber + 1) {
                break;
            }

            if (adjacent(curPart, curSymbol)) {
                total += curPart->value;
                break;
            }
        }
    }

    std::cout << total;


    return 0;
}

bool adjacent(const PartNumber* part, const SymbolPosition* symbol) {
    return symbol->col >= part->startIndex - 1 && symbol->col <= part->endIndex + 1;
}