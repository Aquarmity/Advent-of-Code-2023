#include <iostream>
#include <string>
#include <fstream>
#include <utility>

const int GRID_SIZE = 140;
enum FacingDirection { UP, DOWN, LEFT, RIGHT };
const FacingDirection directions[] = { UP, DOWN, LEFT, RIGHT };

int findLoop(const char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction);
void stepForward(std::pair<int, int>& currentLocation, FacingDirection direction);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::pair<int, int> startPos;
    char pipeGrid[GRID_SIZE][GRID_SIZE];
    int loopLength;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            infile >> pipeGrid[i][j];
            if (pipeGrid[i][j] == 'S') {
                startPos = std::make_pair(i, j);
            }
        }
    }

    for (auto d : directions) {
        loopLength = findLoop(pipeGrid, startPos, d);
        if (loopLength != -1) {
            std::cout << loopLength / 2;
            break;
        }
    }

    return 0;
}

int findLoop(const char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction) {
    std::pair<int, int> currentLocation(startPos);
    stepForward(currentLocation, direction);
    int steps = 1;

    while (currentLocation != startPos) {
        if (currentLocation.first >= GRID_SIZE || currentLocation.first < 0 || currentLocation.second >= GRID_SIZE || currentLocation.second < 0) {
            return -1;
        }

        switch (grid[currentLocation.first][currentLocation.second]) {
            case '.':
            default:
                return -1;

            case 'L':
                if (direction == DOWN) { direction = RIGHT; }
                else if (direction == LEFT) { direction = UP; }
                else { return -1; }
                break;

            case 'J':
                if (direction == DOWN) { direction = LEFT; }
                else if (direction == RIGHT) { direction = UP; }
                else { return -1; }
                break;

            case '7':
                if (direction == UP) { direction = LEFT; }
                else if (direction == RIGHT) { direction = DOWN; }
                else { return -1; }
                break;

            case 'F':
                if (direction == UP) { direction = RIGHT; }
                else if (direction == LEFT) { direction = DOWN; }
                else { return -1; }
                break;

            case '-':
                if (direction == UP || direction == DOWN) { return -1; }
                break;

            case '|':
                if (direction == LEFT || direction == RIGHT) { return -1; }
                break;
        }

        stepForward(currentLocation, direction);
        steps++;
    }

    return steps;
}

void stepForward(std::pair<int, int>& currentLocation, FacingDirection direction) {
    switch (direction) {
            case UP:
                currentLocation.first -= 1;
                break;
            case DOWN:
                currentLocation.first += 1;
                break;
            case LEFT:
                currentLocation.second -= 1;
                break;
            case RIGHT:
                currentLocation.second += 1;
                break;
        }
}