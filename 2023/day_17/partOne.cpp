#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
using std::get;

const int GRID_SIZE = 141;
const int MAX_STEPS = 3;
const int NUM_DIRECTIONS = 4;

// unused, but included for reference for corresponding directions
// enum FacingDirection { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

typedef std::tuple<int, int, int, int, int> quintuple;

struct Block {
    int heatLoss;
    int heatLossFromStart;
    bool visited;

    Block() {
        heatLoss = 0;
        heatLossFromStart = INT_MAX;
        visited = false;
    }

    Block operator=(const Block& second) {
        heatLoss = second.heatLoss;
        heatLossFromStart = second.heatLossFromStart;
        visited = second.visited;

        return *this;
    }
};

int shortestPath(Block**** map);
void enqueueNearbyBlocks(Block**** map, std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>>& blockQueue,
                         const std::tuple<int, int, int, int>& pos);

int main() {
    std::ifstream infile("puzzleInput.txt");

    Block**** map = new Block***[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        map[i] = new Block**[GRID_SIZE];

        for (int j = 0; j < GRID_SIZE; j++) {
            map[i][j] = new Block*[MAX_STEPS];

            for (int k = 0; k < MAX_STEPS; k++) {
                map[i][j][k] = new Block[NUM_DIRECTIONS];
            }
        }
    }

    char currentBlock;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            infile >> currentBlock;
            for (int k = 0; k < MAX_STEPS; k++) {
                for (int w = 0; w < NUM_DIRECTIONS; w++) {
                    map[i][j][k][w].heatLoss = currentBlock - '0';
                }
            }
        }
    }

    std::cout << shortestPath(map);

    return 0;
}

int shortestPath(Block**** map) {
    std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>> blocksToVisit;
    std::tuple<int, int, int, int> curPos;

    map[0][0][0][0].heatLossFromStart = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            for (int k = 0; k < MAX_STEPS; k++) {
                for (int w = 0; w < NUM_DIRECTIONS; w++) {
                    blocksToVisit.push(std::make_tuple(map[i][j][k][w].heatLossFromStart, i, j, k, w));
                }
            }
        }
    }

    while (!blocksToVisit.empty()) {
        quintuple curBlockInfo(blocksToVisit.top());
        curPos = std::make_tuple(get<1>(curBlockInfo), get<2>(curBlockInfo), get<3>(curBlockInfo), get<4>(curBlockInfo));
        Block* curBlock = &map[get<1>(curBlockInfo)][get<2>(curBlockInfo)][get<3>(curBlockInfo)][get<4>(curBlockInfo)];
        blocksToVisit.pop();

        if (!curBlock->visited && curBlock->heatLossFromStart < INT_MAX) {
            std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>> adjacentBlocks;
            curBlock->visited = true;

            enqueueNearbyBlocks(map, adjacentBlocks, curPos);

            while (!adjacentBlocks.empty()) {
                quintuple adjBlockInfo(adjacentBlocks.top());
                adjacentBlocks.pop();
                Block* adjBlock = &map[get<1>(adjBlockInfo)][get<2>(adjBlockInfo)][get<3>(adjBlockInfo)][get<4>(adjBlockInfo)];
                if (adjBlock->heatLossFromStart > curBlock->heatLossFromStart + adjBlock->heatLoss) {
                    adjBlock->heatLossFromStart = curBlock->heatLossFromStart + adjBlock->heatLoss;
                    blocksToVisit.push(std::make_tuple(adjBlock->heatLossFromStart, get<1>(adjBlockInfo), get<2>(adjBlockInfo), get<3>(adjBlockInfo), get<4>(adjBlockInfo)));
                }
            }
        }
    }

    int leastHeatLoss = INT_MAX;
    for (int k = 0; k < MAX_STEPS; k++) {
        for (int w = 0; w < NUM_DIRECTIONS; w++) {
            if (map[GRID_SIZE - 1][GRID_SIZE - 1][k][w].heatLossFromStart < leastHeatLoss) {
                leastHeatLoss = map[GRID_SIZE - 1][GRID_SIZE - 1][k][w].heatLossFromStart;
            }
        }
    }
    
    return leastHeatLoss;
}

void enqueueNearbyBlocks(Block**** map, std::priority_queue<quintuple, std::vector<quintuple>, std::greater<quintuple>>& blockQueue,
                         const std::tuple<int, int, int, int>& pos) {
    bool visitSameDirection = get<2>(pos) < MAX_STEPS - 1;

    if (get<0>(pos) != 0 && get<3>(pos) != 1) {
        if (get<3>(pos) != 0) {
            blockQueue.push(std::make_tuple(map[get<0>(pos) - 1][get<1>(pos)][0][0].heatLossFromStart,
                            get<0>(pos) - 1, get<1>(pos), 0, 0));
        } else if (visitSameDirection) {
            blockQueue.push(std::make_tuple(map[get<0>(pos) - 1][get<1>(pos)][get<2>(pos) + 1][0].heatLossFromStart,
                            get<0>(pos) - 1, get<1>(pos), get<2>(pos) + 1, 0));
        }
    }
    if (get<0>(pos) != GRID_SIZE - 1 && (get<3>(pos) != 0 || pos == std::make_tuple(0, 0, 0, 0))) {
        if (get<3>(pos) != 1) {
            blockQueue.push(std::make_tuple(map[get<0>(pos) + 1][get<1>(pos)][0][1].heatLossFromStart,
                            get<0>(pos) + 1, get<1>(pos), 0, 1));
        } else if (visitSameDirection) {
            blockQueue.push(std::make_tuple(map[get<0>(pos) + 1][get<1>(pos)][get<2>(pos) + 1][1].heatLossFromStart,
                            get<0>(pos) + 1, get<1>(pos), get<2>(pos) + 1, 1));
        }
    }
    if (get<1>(pos) != 0 && get<3>(pos) != 3) {
        if (get<3>(pos) != 2) {
            blockQueue.push(std::make_tuple(map[get<0>(pos)][get<1>(pos) - 1][0][2].heatLossFromStart,
                            get<0>(pos), get<1>(pos) - 1, 0, 2));
        } else if (visitSameDirection) {
            blockQueue.push(std::make_tuple(map[get<0>(pos)][get<1>(pos) - 1][get<2>(pos) + 1][2].heatLossFromStart,
                            get<0>(pos), get<1>(pos) - 1, get<2>(pos) + 1, 2));
        }
    }
    if (get<1>(pos) != GRID_SIZE - 1 && get<3>(pos) != 2) {
        if (get<3>(pos) != 3) {
            blockQueue.push(std::make_tuple(map[get<0>(pos)][get<1>(pos) + 1][0][3].heatLossFromStart,
                            get<0>(pos), get<1>(pos) + 1, 0, 3));
        } else if (visitSameDirection) {
            blockQueue.push(std::make_tuple(map[get<0>(pos)][get<1>(pos) + 1][get<2>(pos) + 1][3].heatLossFromStart,
                            get<0>(pos), get<1>(pos) + 1, get<2>(pos) + 1, 3));
        }
    }
}