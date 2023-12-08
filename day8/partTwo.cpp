#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <numeric>

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string LRinstructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodesAndPaths;
    std::string node;
    std::string left;
    std::string right;
    std::vector<std::string> curNodes;
    std::vector<int> stepsPerNode;
    char filler;

    
    infile >> LRinstructions;
    infile >> node;
    while (infile) {
        if (node.at(2) == 'A') {
            curNodes.push_back(node);
        }

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

    for (std::string& n : curNodes) {        
        int steps = 0;
        while (n.at(2) != 'Z') {
            for (int i = 0; i < LRinstructions.length(); i++) {
                if (LRinstructions.at(i) == 'L') {
                    n = nodesAndPaths.at(n).first;
                } else {
                    n = nodesAndPaths.at(n).second;
                }

                steps++;
                if (n.at(2) == 'Z') { break; }
            }
        }
        stepsPerNode.push_back(steps);
    }

    // requires C++17. Alternatively, use WolframAlpha to find LCM of each i in stepsPerNode
    unsigned long long totalSteps = stepsPerNode.at(0);
    for (int i : stepsPerNode) {
        if (i == totalSteps) { continue; }
        totalSteps = (totalSteps * i)/(std::gcd(totalSteps, i));
    }

    std::cout << totalSteps;

    return 0;
}