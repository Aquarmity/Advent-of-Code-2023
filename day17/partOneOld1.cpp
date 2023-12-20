#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

const int GRID_SIZE = 13;
enum FacingDirection { UP, DOWN, LEFT, RIGHT, NODIRECTION };
typedef std::tuple<int, int, int, int, FacingDirection> quintuple;

struct Block {
    int heatLoss;
    unsigned int heatLossFromStart;
    std::pair<int, int> prevBlock;
    bool visited;
    int stepsWithoutTurning;
    FacingDirection direction;

    Block() {
        heatLoss = 0;
        heatLossFromStart = -1;
        prevBlock = std::make_pair(-1, -1);
        visited = false;
        stepsWithoutTurning = 0;
        direction = NODIRECTION;
    }
};

unsigned int shortestPath(Block map[GRID_SIZE][GRID_SIZE]);
void enqueueNearbyBlocks(const Block map[GRID_SIZE][GRID_SIZE], std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>>& blocksToVisit,
                         const std::pair<int, int>& pos, const FacingDirection direction, const int stepsWithoutTurning);

int main() {
    std::ifstream infile("test.txt");
    Block map[GRID_SIZE][GRID_SIZE];
    char currentBlock;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            infile >> currentBlock;
            map[i][j].heatLoss = currentBlock - '0';
        }
    }

    std::cout << shortestPath(map);

    return 0;
}

unsigned int shortestPath(Block map[GRID_SIZE][GRID_SIZE]) {
    std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>> blocksToVisit;
    std::pair<int, int> curPos;
    FacingDirection direction = RIGHT;
    int stepsWithoutTurning = 0;

    map[0][0].heatLossFromStart = 0;
    blocksToVisit.push(std::make_tuple(map[curPos.first][curPos.second].heatLoss, curPos.first, curPos.second, stepsWithoutTurning, direction));

    while (!blocksToVisit.empty()) {
        quintuple currentBlock(blocksToVisit.top());
        curPos = std::make_pair(std::get<1>(currentBlock), std::get<2>(currentBlock));

        if (!map[curPos.first][curPos.second].visited) {
            std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>> adjacentBlocks;
            map[curPos.first][curPos.second].direction = std::get<4>(currentBlock);
            map[curPos.first][curPos.second].stepsWithoutTurning = std::get<3>(currentBlock);
            map[curPos.first][curPos.second].visited = true;

            enqueueNearbyBlocks(map, adjacentBlocks, curPos, map[curPos.first][curPos.second].direction, map[curPos.first][curPos.second].stepsWithoutTurning);

            while (!adjacentBlocks.empty()) {
                quintuple adjBlock(adjacentBlocks.top());
                std::pair<int, int> adjPos(std::get<1>(adjBlock), std::get<2>(adjBlock));
                if (map[adjPos.first][adjPos.second].heatLossFromStart > map[curPos.first][curPos.second].heatLossFromStart + map[adjPos.first][adjPos.second].heatLoss) {
                    map[adjPos.first][adjPos.second].heatLossFromStart = map[curPos.first][curPos.second].heatLossFromStart + map[adjPos.first][adjPos.second].heatLoss;
                    map[adjPos.first][adjPos.second].prevBlock = std::make_pair(curPos.first, curPos.second);
                }

                adjacentBlocks.pop();
            }

            enqueueNearbyBlocks(map, blocksToVisit, curPos, map[curPos.first][curPos.second].direction, map[curPos.first][curPos.second].stepsWithoutTurning);
        }

        if (curPos == std::make_pair(GRID_SIZE - 1, GRID_SIZE - 1));

        blocksToVisit.pop();
    }

    return map[GRID_SIZE - 1][GRID_SIZE - 1].heatLossFromStart;
}

void enqueueNearbyBlocks(const Block map[GRID_SIZE][GRID_SIZE], std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>>& blocksToVisit,
                         const std::pair<int, int>& pos, const FacingDirection direction, const int stepsWithoutTurning) {
    if (pos.first < GRID_SIZE - 1 && !(direction == UP && stepsWithoutTurning == 3) && direction != map[pos.first + 1][pos.second].direction) {
        if (direction == DOWN) {
            blocksToVisit.push(std::make_tuple(map[pos.first + 1][pos.second].heatLoss, pos.first + 1, pos.second, stepsWithoutTurning + 1, DOWN));
        } else {
            blocksToVisit.push(std::make_tuple(map[pos.first + 1][pos.second].heatLoss, pos.first + 1, pos.second, 0, DOWN));
        }
    }
    if (pos.first > 0 && !(direction == DOWN && stepsWithoutTurning == 3) && direction != map[pos.first - 1][pos.second].direction) {
        if (direction == UP) {
            blocksToVisit.push(std::make_tuple(map[pos.first - 1][pos.second].heatLoss, pos.first - 1, pos.second, stepsWithoutTurning + 1, UP));
        } else {
            blocksToVisit.push(std::make_tuple(map[pos.first - 1][pos.second].heatLoss, pos.first - 1, pos.second, 0, UP));
        }
    }
    if (pos.second < GRID_SIZE - 1 && !(direction == RIGHT && stepsWithoutTurning == 3) && direction != map[pos.first][pos.second + 1].direction) {
        if (direction == RIGHT) {
            blocksToVisit.push(std::make_tuple(map[pos.first][pos.second + 1].heatLoss, pos.first, pos.second + 1, stepsWithoutTurning + 1, RIGHT));
        } else {
            blocksToVisit.push(std::make_tuple(map[pos.first][pos.second + 1].heatLoss, pos.first, pos.second + 1, 0, RIGHT));
        }
    }
    if (pos.second > 0 && !(direction == LEFT && stepsWithoutTurning == 3) && direction != map[pos.first][pos.second - 1].direction) {
        if (direction == LEFT) {
            blocksToVisit.push(std::make_tuple(map[pos.first][pos.second - 1].heatLoss, pos.first, pos.second - 1, stepsWithoutTurning + 1, LEFT));
        } else {
            blocksToVisit.push(std::make_tuple(map[pos.first][pos.second - 1].heatLoss, pos.first, pos.second - 1, 0, LEFT));
        }
    }
}