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


            if (curLine.at(i) == '*') {
                symbolPositions.push_back(new SymbolPosition(i, curRow));
            }
        }
        
        infile >> curLine;
        curRow++;
    }


    int adjCount;
    std::vector<int> adjacentNumbers;
    for (SymbolPosition* curSymbol : symbolPositions) {
        adjCount = 0;
        for (PartNumber* curPart : partNumbers) {
            if (curSymbol->row < curPart->rowNumber - 1) {
                break;
            }
            if (curSymbol->row > curPart->rowNumber + 1) {
                continue;
            }

            if (adjacent(curPart, curSymbol)) {
                adjCount++;
                adjacentNumbers.push_back(curPart->value);
            }
        }

        if (adjCount == 2) {
            total += adjacentNumbers.at(0) * adjacentNumbers.at(1);
        }

        adjacentNumbers.clear();
    }

    std::cout << total;


    return 0;
}

bool adjacent(const PartNumber* part, const SymbolPosition* symbol) {
    return symbol->col >= part->startIndex - 1 && symbol->col <= part->endIndex + 1;
}