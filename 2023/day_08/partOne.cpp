#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string LRinstructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodesAndPaths;
    std::string node;
    std::string left;
    std::string right;
    std::string curNode = "AAA";
    int steps = 0;
    char filler;

    
    infile >> LRinstructions;
    infile >> node;
    while (infile) {
        infile >> filler;

        infile >> filler;
        infile >> left;
        left = left.substr(0, 3);

        infile >> right;
        right = right.substr(0, 3);

        
        std::pair<std::string, std::string> leftAndRight(left, right);

        nodesAndPaths.insert(std::make_pair(node, leftAndRight));

        infile >> node;
    }

    while (curNode != "ZZZ") {
        for (int i = 0; i < LRinstructions.length(); i++) {
            if (LRinstructions.at(i) == 'L') {
                curNode = nodesAndPaths.at(curNode).first;
            } else {
                curNode = nodesAndPaths.at(curNode).second;
            }

            steps++;

            if (curNode == "ZZZ") { break; }
        }
    }

    std::cout << steps;


    return 0;
}