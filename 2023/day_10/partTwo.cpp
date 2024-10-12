#include <iostream>
#include <string>
#include <fstream>
#include <utility>

const int GRID_SIZE = 140;
enum FacingDirection { UP, RIGHT, DOWN, LEFT };
const FacingDirection directions[] = { UP, RIGHT, DOWN, LEFT };

int findLoop(const char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction);
void stepForward(std::pair<int, int>& currentLocation, FacingDirection direction);
int findEnclosedArea(char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction);
void recursiveFillArea(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int& totalArea);

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
    }

    return 0;
}

int findLoop(const char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction) {
    const FacingDirection originalDirection = direction;

    std::pair<int, int> currentLocation(startPos);
    stepForward(currentLocation, direction);
    int steps = 1;

    char pipeSolution[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            pipeSolution[i][j] = '.';
        }
    }

    pipeSolution[startPos.first][startPos.second] = 'S';

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

                pipeSolution[currentLocation.first][currentLocation.second] = 'L';
                break;

            case 'J':
                if (direction == DOWN) { direction = LEFT; }
                else if (direction == RIGHT) { direction = UP; }
                else { return -1; }

                pipeSolution[currentLocation.first][currentLocation.second] = 'J';
                break;

            case '7':
                if (direction == UP) { direction = LEFT; }
                else if (direction == RIGHT) { direction = DOWN; }
                else { return -1; }

                pipeSolution[currentLocation.first][currentLocation.second] = '7';
                break;

            case 'F':
                if (direction == UP) { direction = RIGHT; }
                else if (direction == LEFT) { direction = DOWN; }
                else { return -1; }

                pipeSolution[currentLocation.first][currentLocation.second] = 'F';
                break;

            case '-':
                if (direction == UP || direction == DOWN) { return -1; }

                pipeSolution[currentLocation.first][currentLocation.second] = '-';
                break;

            case '|':
                if (direction == LEFT || direction == RIGHT) { return -1; }

                pipeSolution[currentLocation.first][currentLocation.second] = '|';
                break;
        }

        stepForward(currentLocation, direction);
        steps++;
    }

    int enclosedArea = findEnclosedArea(pipeSolution, startPos, originalDirection);
    if (enclosedArea != -1) {
        std::cout << enclosedArea << std::endl;
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

int findEnclosedArea(char grid[GRID_SIZE][GRID_SIZE], const std::pair<int, int>& startPos, FacingDirection direction) {
    std::pair<int, int> currentLocation(startPos);
    FacingDirection rightHand = static_cast<FacingDirection>((direction + 1) % 4);
    stepForward(currentLocation, direction);
    int enclosedArea = 0;

    while (currentLocation != startPos) {
        std::pair<int, int> searchingRay(currentLocation);
        stepForward(searchingRay, rightHand);
        if (grid[searchingRay.first][searchingRay.second] == '.') {
            recursiveFillArea(grid, searchingRay.first, searchingRay.second, enclosedArea);
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

        rightHand = static_cast<FacingDirection>((direction + 1) % 4);
        searchingRay = currentLocation;
        stepForward(searchingRay, rightHand);
        if (grid[searchingRay.first][searchingRay.second] == '.') {
            recursiveFillArea(grid, searchingRay.first, searchingRay.second, enclosedArea);
        }
        stepForward(currentLocation, direction);
    }
    
    return enclosedArea;
}

void recursiveFillArea(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int& totalArea) {
    grid[x][y] = 'O';
    totalArea++;
    if (grid[x + 1][y] == '.') { recursiveFillArea(grid, x + 1, y, totalArea); }
    if (grid[x - 1][y] == '.') { recursiveFillArea(grid, x - 1, y, totalArea); }
    if (grid[x][y + 1] == '.') { recursiveFillArea(grid, x, y + 1, totalArea); }
    if (grid[x][y + 1] == '.') { recursiveFillArea(grid, x, y - 1, totalArea); }
}