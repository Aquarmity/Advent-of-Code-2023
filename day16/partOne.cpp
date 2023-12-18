#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

const int GRID_SIZE = 110;
enum FacingDirection { UP, DOWN, LEFT, RIGHT, NODIRECTION };

void traceLightPath(const char grid[GRID_SIZE][GRID_SIZE], FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction);
void stepForward(std::pair<int, int>& currentLocation, FacingDirection direction);

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::pair<int, int> location;
    char grid[GRID_SIZE][GRID_SIZE];
    FacingDirection visitedTiles[GRID_SIZE][GRID_SIZE];
    int total = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            infile >> grid[i][j];
            visitedTiles[i][j] = NODIRECTION;
        }
    }

    traceLightPath(grid, visitedTiles, std::make_pair(0, 0), RIGHT);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (visitedTiles[i][j] != NODIRECTION) {
                total++;
            }
        }
    }

    std::cout << total;

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