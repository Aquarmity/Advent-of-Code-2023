#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

const int GRID_SIZE = 110;
enum FacingDirection { UP, DOWN, LEFT, RIGHT, NODIRECTION };
const FacingDirection directions[] = { UP, DOWN, LEFT, RIGHT };

void traceLightPath(const char grid[GRID_SIZE][GRID_SIZE], FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction);
void stepForward(std::pair<int, int>& currentLocation, FacingDirection direction);
int tryAllTracesFromEdge(const char grid[GRID_SIZE][GRID_SIZE], FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE], FacingDirection direction);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::pair<int, int> location;
    char grid[GRID_SIZE][GRID_SIZE];
    FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE];
    int total = 0;
    int maxTotal = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            infile >> grid[i][j];
        }
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                visitedTiles[j][k] = NODIRECTION;
            }
        }

        traceLightPath(grid, visitedTiles, std::make_pair(i, 0), RIGHT);

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                if (visitedTiles[j][k] != NODIRECTION) {
                    total++;
                }
            }
        }

        if (total > maxTotal) {
            maxTotal = total;
        }
        total = 0;
    }

    

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                visitedTiles[j][k] = NODIRECTION;
            }
        }

        traceLightPath(grid, visitedTiles, std::make_pair(i, GRID_SIZE - 1), LEFT);

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                if (visitedTiles[j][k] != NODIRECTION) {
                    total++;
                }
            }
        }

        if (total > maxTotal) {
            maxTotal = total;
        }
        total = 0;
    }

    

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                visitedTiles[j][k] = NODIRECTION;
            }
        }

        traceLightPath(grid, visitedTiles, std::make_pair(0, i), DOWN);

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                if (visitedTiles[j][k] != NODIRECTION) {
                    total++;
                }
            }
        }

        if (total > maxTotal) {
            maxTotal = total;
        }
        total = 0;
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                visitedTiles[j][k] = NODIRECTION;
            }
        }

        traceLightPath(grid, visitedTiles, std::make_pair(GRID_SIZE - 1, i), UP);

        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < GRID_SIZE; k++) {
                if (visitedTiles[j][k] != NODIRECTION) {
                    total++;
                }
            }
        }

        if (total > maxTotal) {
            maxTotal = total;
        }
        total = 0;
    }

    std::cout << maxTotal;

    return 0;
}

void traceLightPath(const char grid[GRID_SIZE][GRID_SIZE], FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction) {
    std::pair<int, int> currentLocation(startPos);

    while (currentLocation.first < GRID_SIZE && currentLocation.first >= 0 && currentLocation.second < GRID_SIZE && currentLocation.second >= 0) {
        if (visitedTiles[currentLocation.first][currentLocation.second] == direction) { return; }
        if (visitedTiles[currentLocation.first][currentLocation.second] == NODIRECTION) {
            visitedTiles[currentLocation.first][currentLocation.second] = direction;
        }

        switch (grid[currentLocation.first][currentLocation.second]) {
            case '.':
            default:
                break;

            case '/':
                if (direction == UP) { direction = RIGHT; }
                else if (direction == DOWN) { direction = LEFT; }
                else if (direction == LEFT) { direction = DOWN; }
                else { direction = UP; }
                break;

            case '\\':
                if (direction == UP) { direction = LEFT; }
                else if (direction == DOWN) { direction = RIGHT; }
                else if (direction == LEFT) { direction = UP; }
                else { direction = DOWN; }
                break;

            case '|':
                if (direction == LEFT || direction == RIGHT) {
                    direction = UP;
                    std::pair<int, int> newLocation = currentLocation;
                    traceLightPath(grid, visitedTiles, currentLocation, DOWN);
                }
                break;

            case '-':
                if (direction == UP || direction == DOWN) {
                    direction = LEFT;
                    traceLightPath(grid, visitedTiles, currentLocation, RIGHT);
                }
                break;
        }
        
        stepForward(currentLocation, direction);
    }
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