#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Lens {
    public:
        Lens(std::string l, int f) {
            focalLength = f;
            label = l;
        }

        std::string getLabel() {
            return label;
        }

        int getFocalLength() {
            return focalLength;
        }

        int updateFocalLength(int inFocalLength) {
            focalLength = inFocalLength;
            return focalLength;
        }

    private:
        int focalLength;
        std::string label;
};

class Box {
    public:
        Box(){
            lenses = std::vector<Lens>();
        }

        bool remove(std::string inLabel) {
            for (auto i = lenses.begin(); i != lenses.end(); i++) {
                if (i->getLabel() == inLabel) {
                    lenses.erase(i);
                    return true;
                }
            }

            return false;
        }

        void insert(std::string inLabel, int inFocalLength) {
            for (auto i = lenses.begin(); i != lenses.end(); i++) {
                if (i->getLabel() == inLabel) {
                    i->updateFocalLength(inFocalLength);
                    return;
                }
            }

            lenses.push_back(Lens(inLabel, inFocalLength));
        }

        int getTotalFocusingPower() {
            int focusingPower = 0;
            for (int i = 0; i < lenses.size(); i++) {
                focusingPower += (i + 1) * lenses.at(i).getFocalLength();
            }

            return focusingPower;
        }

        int getLensCount() {
            return lenses.size();
        }

    private:
        std::vector<Lens> lenses;
};

int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string currentStep;
    Box boxes[256];
    int total = 0;

    getline(infile, currentStep, ',');
    while (infile) { 
        unsigned int asciiSum = 0; 
        std::stringstream step(currentStep);
        std::string label;

        if (currentStep.at(currentStep.length() - 1) == '-') {
            getline(step, label, '-');
            for (char ch : label) {
                asciiSum += ch;
                asciiSum *= 17;
            }
            asciiSum %= 256;

            boxes[asciiSum].remove(label);
        } else {
            int focalLength;
            getline(step, label, '=');
            for (char ch : label) {
                asciiSum += ch;
                asciiSum *= 17;
            }
            asciiSum %= 256;

            step >> focalLength;
            boxes[asciiSum].insert(label, focalLength);
        }
        getline(infile, currentStep, ',');
    }

    for (int i = 0; i < 256; i++) {
        total += (1 + i) * boxes[i].getTotalFocusingPower();
    }

    std::cout << total;

    return 0;
}