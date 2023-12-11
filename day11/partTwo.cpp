#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

const int GRID_SIZE = 140;

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::vector<std::pair<int, int>> galaxyPositions;
    std::string line;
    int currentLine = 0;
    bool foundGalaxyOnLine = false;
    unsigned long long sum = 0;
    bool emptyColumns[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        emptyColumns[i] = true;
    }

    getline(infile, line);
    while (infile) {
        for (int i = 0; i < line.length(); i++) {
            if (line.at(i) == '#') {
                emptyColumns[i] = false;
                galaxyPositions.push_back(std::make_pair(currentLine, i));
                foundGalaxyOnLine = true;
            }
        }

        if (!foundGalaxyOnLine) { currentLine += 999999; }
        currentLine++;
        foundGalaxyOnLine = false;
        getline(infile, line);
    }

    for (int i = GRID_SIZE; i >= 0; i--) {
        for (auto& g : galaxyPositions) {
            if (emptyColumns[i] && g.second > i) {
                g.second += 999999;
            }
        }
    }
    for (auto i = galaxyPositions.begin(); i != galaxyPositions.end(); i++) {
        for (auto j = i + 1; j != galaxyPositions.end(); j++) {
            sum += abs(i->second - j->second) + abs(i->first - j->first);
        }
    }

    std::cout << sum;
}
