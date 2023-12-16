#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string currentStep;
    int total = 0;

    getline(infile, currentStep, ',');
    while (infile) {
        unsigned int asciiSum = 0;
        for (char ch : currentStep) {
            asciiSum += ch;
            asciiSum *= 17;
        }

        total += asciiSum % 256;
        getline(infile, currentStep, ',');
    }

    std::cout << total;

    return 0;
}