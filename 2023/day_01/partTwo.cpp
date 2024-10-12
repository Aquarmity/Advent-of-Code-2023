#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

const int TEN = 10;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;

int numberWordCheck(const std::string curLine, const int firstLetterIndex);
int reverseNumberWordCheck(const std::string curLine, const int lastLetterIndex);

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string curLine;
    int firstDigit = 0;
    int secondDigit = 0;
    int total = 0;
    int wordNumber = -1;
    
    infile >> curLine;
    while (infile) {
        for (int i = 0; i < curLine.length(); i++) {
            if (isdigit(curLine.at(i))) {
                firstDigit = static_cast<int>(curLine.at(i) - '0');
                break;
            } else {
                wordNumber = numberWordCheck(curLine, i);
                if (wordNumber != -1) {
                    firstDigit = wordNumber;
                    break;
                }
            }
        }
        for (int i = curLine.length() - 1; i >= 0; i--) {
            if (isdigit(curLine.at(i))) {
                secondDigit = static_cast<int>(curLine.at(i) - '0');
                break;
            } else {
                wordNumber = reverseNumberWordCheck(curLine, i);
                if (wordNumber != -1) {
                    secondDigit = wordNumber;
                    break;
                }
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

int numberWordCheck(const std::string curLine, const int firstLetterIndex) {
    std::string substrToCheck;
    if (firstLetterIndex + FOUR < curLine.length()) {
        substrToCheck = curLine.substr(firstLetterIndex, FIVE);
        if (substrToCheck == "three") { return 3; }
        if (substrToCheck == "seven") { return 7; }
        if (substrToCheck == "eight") { return 8; }
    }
    if (firstLetterIndex + THREE < curLine.length()) {
        substrToCheck = curLine.substr(firstLetterIndex, FOUR);
        if (substrToCheck == "zero") { return 0; }
        if (substrToCheck == "four") { return 4; }
        if (substrToCheck == "five") { return 5; }
        if (substrToCheck == "nine") { return 9; }
    }
    if (firstLetterIndex + TWO < curLine.length()) {
        substrToCheck = curLine.substr(firstLetterIndex, THREE);
        if (substrToCheck == "one") { return 1; }
        if (substrToCheck == "two") { return 2; }
        if (substrToCheck == "six") { return 6; }
    }

    return -1;
}

int reverseNumberWordCheck(const std::string curLine, const int lastLetterIndex) {
    std::string substrToCheck;
    if (lastLetterIndex - FOUR >= 0) {
        substrToCheck = curLine.substr(lastLetterIndex - FOUR, FIVE);
        if (substrToCheck == "three") { return 3; }
        if (substrToCheck == "seven") { return 7; }
        if (substrToCheck == "eight") { return 8; }
    }
    if (lastLetterIndex - THREE >= 0) {
        substrToCheck = curLine.substr(lastLetterIndex - THREE, FOUR);
        if (substrToCheck == "zero") { return 0; }
        if (substrToCheck == "four") { return 4; }
        if (substrToCheck == "five") { return 5; }
        if (substrToCheck == "nine") { return 9; }
    }
    if (lastLetterIndex - TWO >= 0) {
        substrToCheck = curLine.substr(lastLetterIndex - TWO, THREE);
        if (substrToCheck == "one") { return 1; }
        if (substrToCheck == "two") { return 2; }
        if (substrToCheck == "six") { return 6; }
    }

    return -1;
}