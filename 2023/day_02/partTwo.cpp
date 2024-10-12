#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string filler;
    char letter;
    int powerSum = 0;
    int redMax = 0;
    int blueMax = 0;
    int greenMax = 0;
    int numberOfColor = 0;
    
    infile >> filler;
    while (infile) {
        infile >> filler;
        
        while (filler != "lue" && filler != "ed" && filler != "reen" && infile) {
            infile >> numberOfColor;
            infile >> letter;
            if (letter == 'r' && numberOfColor > redMax) {
                redMax = numberOfColor;
            } else if (letter == 'b' && numberOfColor > blueMax) {
                blueMax = numberOfColor;
            } else if (letter == 'g' && numberOfColor > greenMax) {
                greenMax = numberOfColor;
            }
            
            infile >> filler;
        }
        powerSum += redMax * blueMax * greenMax;
        
        infile >> filler;
        redMax = 0;
        blueMax = 0;
        greenMax = 0;
    }

    std::cout << powerSum;

    return 0;
}