#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream infile("puzzleinput.txt");
    std::string filler;
    char letter;
    int id;
    int total = 0;
    int numberOfColor = 0;
    bool validID = true;
    
    infile >> filler;
    while (infile) {
        infile >> id;
        infile >> filler;
        
        while (filler != "lue" && filler != "ed" && filler != "reen" && filler != "Game" && infile && validID) {
            infile >> numberOfColor;
            infile >> letter;
            if (numberOfColor > 14
                || (numberOfColor > 12 && letter == 'r')
                || (numberOfColor > 13 && letter == 'g')) {
                while (filler != "Game" && infile) {
                    infile >> filler;
                    validID = false;
                }
            } else {
                infile >> filler;
            }
        }
        
        if (validID == true) {
            total += id;
        } else {
            validID = true;
        }
        if (filler != "Game") {
            infile >> filler;
        }
    }

    std::cout << total;

    return 0;
}