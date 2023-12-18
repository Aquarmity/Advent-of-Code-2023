#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

const int GRID_SIZE = 13;
enum FacingDirection { UP, DOWN, LEFT, RIGHT, NODIRECTION };
typedef std::tuple<int, int, int, FacingDirection> quadruple;

struct Block {
    int heatLoss;
    int tempHeatLoss;
    unsigned int heatLossFromStart;
    std::pair<int, int> prevBlock;
    bool visited;
    FacingDirection direction;

    Block() {
        heatLoss = 0;
        tempHeatLoss = 0;
        heatLossFromStart = -1;
        prevBlock = std::make_pair(-1, -1);
        visited = false;
        direction = NODIRECTION;
    }
};

unsigned int shortestPath(Block map[GRID_SIZE][GRID_SIZE]);
void enqueueNearbyBlocks(const Block map[GRID_SIZE][GRID_SIZE], std::priority_queue<quadruple, std::vector<quadruple>, std::greater<quadruple>>& blocksToVisit,
                         const std::pair<int, int>& pos, const FacingDirection direction);

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
    std::priority_queue<quadruple, std::vector<quadruple>, std::greater<quadruple>> blocksToVisit;
    std::pair<int, int> curPos(0, 0);
    FacingDirection direction = NODIRECTION;

    map[0][0].heatLossFromStart = 0;
    blocksToVisit.push(std::make_tuple(map[curPos.first][curPos.second].heatLoss, curPos.first, curPos.second, direction));

    while (!blocksToVisit.empty()) {
        quadruple currentBlock(blocksToVisit.top());
        curPos = std::make_pair(std::get<1>(currentBlock), std::get<2>(currentBlock));
        blocksToVisit.pop();

        if (!map[curPos.first][curPos.second].visited) {
            std::priority_queue<quadruple, std::vector<quadruple>, std::greater<quadruple>> adjacentBlocks;
            map[curPos.first][curPos.second].tempHeatLoss = std::get<0>(currentBlock);
            map[curPos.first][curPos.second].direction = std::get<3>(currentBlock);
            map[curPos.first][curPos.second].visited = true;

            enqueueNearbyBlocks(map, adjacentBlocks, curPos, map[curPos.first][curPos.second].direction);

            while (!adjacentBlocks.empty()) {
                quadruple adjBlock(adjacentBlocks.top());
                adjacentBlocks.pop();
                std::pair<int, int> adjPos(std::get<1>(adjBlock), std::get<2>(adjBlock));
                map[adjPos.first][adjPos.second].tempHeatLoss = std::get<0>(adjBlock);
                if (map[adjPos.first][adjPos.second].heatLossFromStart > map[curPos.first][curPos.second].heatLossFromStart + map[adjPos.first][adjPos.second].tempHeatLoss) {
                    map[adjPos.first][adjPos.second].heatLossFromStart = map[curPos.first][curPos.second].heatLossFromStart + map[adjPos.first][adjPos.second].tempHeatLoss;
                    map[adjPos.first][adjPos.second].prevBlock = std::make_pair(curPos.first, curPos.second);
                }
            }

            enqueueNearbyBlocks(map, blocksToVisit, curPos, map[curPos.first][curPos.second].direction);
        }

        /*if (curPos == std::make_pair(GRID_SIZE - 1, GRID_SIZE - 1)) {
            break;
        }*/
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            std::cout << map[i][j].heatLossFromStart << ' ';
        }
        std::cout << std::endl;
    }

    return map[GRID_SIZE - 1][GRID_SIZE - 1].heatLossFromStart;
}

void enqueueNearbyBlocks(const Block map[GRID_SIZE][GRID_SIZE], std::priority_queue<quadruple, std::vector<quadruple>, std::greater<quadruple>>& blocksToVisit,
                         const std::pair<int, int>& pos, const FacingDirection direction) {
    int downHeatLoss = 0;
    int upHeatLoss = 0;
    int rightHeatLoss = 0;
    int leftHeatLoss = 0;
    for (int i = 1; i <= 3; i++) {
        if (direction != UP && direction != DOWN) {
            if (pos.first + i < GRID_SIZE) {
                downHeatLoss += map[pos.first + i][pos.second].heatLoss;
                blocksToVisit.push(std::make_tuple(downHeatLoss, pos.first + i, pos.second, DOWN));
            }
            if (pos.first - i >= 0) {
                upHeatLoss += map[pos.first - i][pos.second].heatLoss;
                blocksToVisit.push(std::make_tuple(upHeatLoss, pos.first - i, pos.second, UP));
            }
        }
        if (direction != LEFT && direction != RIGHT) {
            if (pos.second + i < GRID_SIZE) {
                rightHeatLoss += map[pos.first][pos.second + i].heatLoss;
                blocksToVisit.push(std::make_tuple(rightHeatLoss, pos.first, pos.second + i, RIGHT));
            }
            if (pos.second - i >= 0) {
                leftHeatLoss += map[pos.first][pos.second - i].heatLoss;
                blocksToVisit.push(std::make_tuple(leftHeatLoss, pos.first, pos.second - i, LEFT));
            }
        }
    }
}