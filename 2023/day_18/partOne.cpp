#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>

int nonrecursiveFillArea(char** grid, std::pair<int, int> startingCoord);

int main() {
    std::ifstream infile("puzzleInput.txt");
    int total = 0;
    char direction;
    int magnitude;
    std::string rgbCode;
    std::pair<int, int> currentCoordinates(0, 0);
    std::vector<std::pair<int, int>> lagoonPerimeter;
    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;

    infile >> direction >> magnitude >> rgbCode;
    while (infile) {
        switch (direction) {
            case 'U':
                currentCoordinates.first -= magnitude;
                if (currentCoordinates.first < minY) {
                    minY = currentCoordinates.first;
                }
                break;
            case 'D':
                currentCoordinates.first += magnitude;
                if (currentCoordinates.first > maxY) {
                    maxY = currentCoordinates.first;
                }
                break;
            case 'L':
                currentCoordinates.second -= magnitude;
                if (currentCoordinates.second < minX) {
                    minX = currentCoordinates.second;
                }
                break;
            default:
            case 'R':
                currentCoordinates.second += magnitude;
                if (currentCoordinates.second > maxX) {
                    maxX = currentCoordinates.second;
                }
                break;
        }

        lagoonPerimeter.push_back(currentCoordinates);
        infile >> direction >> magnitude >> rgbCode;
    }

    int distanceX = maxX - minX + 1;
    int distanceY = maxY - minY + 1;
    char** grid = new char*[distanceY];
    for (int i = 0; i < distanceY; i++) {
        grid[i] = new char[distanceX];
        for (int j = 0; j < distanceX; j++) {
            grid[i][j] = '.';
        }
    }

    for (auto& coord : lagoonPerimeter) {
        coord.first -= minY;
        coord.second -= minX;
    }

    std::pair<int, int> prevCoord = lagoonPerimeter.back();
    for (auto coord : lagoonPerimeter) {
        if (coord.first == prevCoord.first && coord.second != prevCoord.second) {
            int lesserCoord = std::min(coord.second, prevCoord.second);
            int greaterCoord = std::max(coord.second, prevCoord.second);
            for (int i = lesserCoord; i <= greaterCoord; i++) {
                if (grid[coord.first][i] != '#') {
                    grid[coord.first][i] = '#';
                    total++;
                }
            }
        } else {
            int lesserCoord = std::min(coord.first, prevCoord.first);
            int greaterCoord = std::max(coord.first, prevCoord.first);
            for (int i = lesserCoord; i <= greaterCoord; i++) {
                if (grid[i][coord.second] != '#') {
                    grid[i][coord.second] = '#';
                    total++;
                }
            }
        }
        prevCoord = coord;
    }

    total += nonrecursiveFillArea(grid, lagoonPerimeter.back());

    std::cout << total;

    return 0;
}

int nonrecursiveFillArea(char** grid, std::pair<int, int> startingCoord) {
    std::deque<std::pair<int, int>> squaresToFill;
    startingCoord.first++;
    startingCoord.second++;
    squaresToFill.push_back(startingCoord);

    int totalArea = 0;
    while (!squaresToFill.empty()) {
        std::pair<int, int> coord = squaresToFill.front();
        squaresToFill.pop_front();

        grid[coord.first][coord.second] = '#';
        totalArea++;

        if (grid[coord.first + 1][coord.second] == '.'
            && std::find(squaresToFill.begin(), squaresToFill.end(), std::make_pair(coord.first + 1, coord.second)) == squaresToFill.end()) {
            squaresToFill.push_back(std::make_pair(coord.first + 1, coord.second));
        }
        if (grid[coord.first - 1][coord.second] == '.'
            && std::find(squaresToFill.begin(), squaresToFill.end(), std::make_pair(coord.first - 1, coord.second)) == squaresToFill.end()) {
            squaresToFill.push_back(std::make_pair(coord.first - 1, coord.second));
        }
        if (grid[coord.first][coord.second + 1] == '.'
            && std::find(squaresToFill.begin(), squaresToFill.end(), std::make_pair(coord.first, coord.second + 1)) == squaresToFill.end()) {
            squaresToFill.push_back(std::make_pair(coord.first, coord.second + 1));
        }
        if (grid[coord.first][coord.second - 1] == '.'
            && std::find(squaresToFill.begin(), squaresToFill.end(), std::make_pair(coord.first, coord.second - 1)) == squaresToFill.end()) {
            squaresToFill.push_back(std::make_pair(coord.first, coord.second - 1));
        }
    }

    return totalArea;
}