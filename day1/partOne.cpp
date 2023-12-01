#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

const int TEN = 10;

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string curLine;
    int firstDigit = 0;
    int secondDigit = 0;
    int total = 0;
    
    infile >> curLine;
    while (infile) {
        for (int i = 0; i < curLine.length(); i++) {
            if (isdigit(curLine.at(i))) {
                firstDigit = static_cast<int>(curLine.at(i) - '0');
                break;
            }
        }
        for (int i = curLine.length() - 1; i >= 0; i--) {
            if (isdigit(curLine.at(i))) {
                secondDigit = static_cast<int>(curLine.at(i) - '0');
                break;
            }
        }

        total += (TEN * firstDigit) + secondDigit;
        firstDigit = 0;
        secondDigit = 0;

        infile >> curLine;
    }

    std::cout << total;

    return 0;
}