#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using std::vector;

bool allZeroes(const vector<int>& v);

int main() {
    vector<vector<vector<int>>> sequences;
    std::ifstream infile("puzzleInput.txt");
    std::stringstream currentLine;
    std::string line;
    int total;

    getline(infile, line);
    while (infile) {
        currentLine << line;
        vector<int> origSequence;
        while (!currentLine.eof()) {
            int num;
            currentLine >> num;
            origSequence.push_back(num);
        }
        currentLine.clear();

        vector<vector<int>> sequenceSubset;
        sequenceSubset.emplace_back(origSequence);
        sequences.emplace_back(sequenceSubset);

        getline(infile, line);
    }

    for (vector<vector<vector<int>>>::iterator i = sequences.begin(); i != sequences.end(); i++) {
        for (int j = 0; j < i->size(); j++) {
            vector<int> nextIteration;
            int newSequenceTerm;
            
            for (vector<int>::iterator k = i->at(j).begin() + 1; k != i->at(j).end(); k++) {
                newSequenceTerm = *k - *(k - 1);
                nextIteration.push_back(newSequenceTerm);
            }

            i->emplace_back(nextIteration);
            if (allZeroes(nextIteration)) { break; }
        }
    }

    for (vector<vector<vector<int>>>::iterator i = sequences.begin(); i != sequences.end(); i++) {
        int value;
        for (vector<vector<int>>::iterator j = i->end() - 1; j != i->begin(); j--) {
            (j - 1)->push_back(j->back() + (j - 1)->back());
            value = (j - 1)->back();
        }

        total += value;
    }

    std::cout << total;

    return 0;
}

bool allZeroes(const vector<int>& v) {
    for (int i : v) {
        if (i != 0) {
            return false;
        }
    }

    return true;
}