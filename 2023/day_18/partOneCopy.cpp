#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

typedef long long ll;
const int HEX_START = 2;
const int HEX_END = 7;

ll nonrecursiveFillArea(char** grid, std::pair<int, int> startingCoord);
int toDecimal(std::string hex);
char toDirection(std::string hex);

int main() {
    std::ifstream infile("test.txt");
    unsigned long long total = 0;
    int filler;
    char charFiller;
    std::string rgbCode;
    std::pair<ll, ll> currentCoordinates(0, 0);
    std::vector<std::pair<ll, ll>> lagoonPerimeter;
    ll minX = 0;
    ll maxX = 0;
    ll minY = 0;
    ll maxY = 0;
    int magnitude;
    char direction;

    infile >> direction >> magnitude >> rgbCode;
    while (infile) {
        switch (direction) {
            case 'U':
                currentCoordinates.first -= magnitude;
                if (currentCoordinates.first < minY) {
                    minY = currentCoordinates.first;
                }
                break;
            case 'D':
                currentCoordinates.first += magnitude;
                if (currentCoordinates.first > maxY) {
                    maxY = currentCoordinates.first;
                }
                break;
            case 'L':
                currentCoordinates.second -= magnitude;
                if (currentCoordinates.second < minX) {
                    minX = currentCoordinates.second;
                }
                break;
            default:
            case 'R':
                currentCoordinates.second += magnitude;
                if (currentCoordinates.second > maxX) {
                    maxX = currentCoordinates.second;
                }
                break;
        }

        lagoonPerimeter.push_back(currentCoordinates);
        infile >> direction >> magnitude >> rgbCode;
    }

    for (auto& coord : lagoonPerimeter) {
        coord.first -= minY;
        coord.second -= minX;
    }

    std::sort(lagoonPerimeter.begin(), lagoonPerimeter.end(), [](auto &left, auto &right) {
        if (left.second == right.second) {
            return left.first < right.first;
        }
        return left.second < right.second;
    });

    for (auto& i : lagoonPerimeter) {
        std::cout << '(' << i.second << ", " << i.first << ')' << std::endl;
    }

    std::vector<unsigned long long> valsToAdd;
    std::vector<ll> yValues;
    std::vector<ll> xValues;
    for (auto i = lagoonPerimeter.begin() + 1; i != lagoonPerimeter.end() + 1; i += 2) {
        if (std::find(yValues.begin(), yValues.end(), i->first) != yValues.end()) {
            auto y = std::find(yValues.begin(), yValues.end(), i->first);
            int relativeVectorPos = y - yValues.begin();
            bool pairMatching = (y - yValues.begin()) % 2 == 0 ? (*(y + 1) == (i - 1)->first) : (*(y - 1) == (i - 1)->first);
            if (pairMatching) {
                total += valsToAdd.at(relativeVectorPos) * (i->second - xValues.at(relativeVectorPos) + 1);
                *y = -1;
                *(y - 1) = -1;
                valsToAdd.at(relativeVectorPos) = 0;
                valsToAdd.at(relativeVectorPos - 1) = 0;
                xValues.at(relativeVectorPos) = -1;
                xValues.at(relativeVectorPos - 1) = -1;
            } else {
                total += valsToAdd.at(relativeVectorPos) * (i->second - xValues.at(relativeVectorPos));
                *y = (i - 1)->first;
                if (relativeVectorPos % 2 == 0) {
                    valsToAdd.at(relativeVectorPos) = (*(y + 1) - *y) + 1;
                    valsToAdd.at(relativeVectorPos + 1) = (*(y + 1) - *y) + 1;
                    xValues.at(relativeVectorPos) = i->second;
                    xValues.at(relativeVectorPos + 1) = i->second;
                } else {
                    valsToAdd.at(relativeVectorPos) = (*y - *(y - 1)) + 1;
                    valsToAdd.at(relativeVectorPos - 1) = (*y - *(y - 1)) + 1;
                    xValues.at(relativeVectorPos) = i->second;
                    xValues.at(relativeVectorPos - 1) = i->second;
                }
            }
        } else if (std::find(yValues.begin(), yValues.end(), (i - 1)->first) != yValues.end()) {
            auto y = std::find(yValues.begin(), yValues.end(), (i - 1)->first);
            int relativeVectorPos = y - yValues.begin();
            total += valsToAdd.at(relativeVectorPos) * ((i - 1)->second - xValues.at(relativeVectorPos));
            *y = i->first;
            if (relativeVectorPos % 2 == 0) {
                valsToAdd.at(relativeVectorPos) = (*(y + 1) - *y) + 1;
                valsToAdd.at(relativeVectorPos + 1) = (*(y + 1) - *y) + 1;
                xValues.at(relativeVectorPos) = i->second;
                xValues.at(relativeVectorPos + 1) = i->second;
            } else {
                valsToAdd.at(relativeVectorPos) = (*y - *(y - 1)) + 1;
                valsToAdd.at(relativeVectorPos - 1) = (*y - *(y - 1)) + 1;
                xValues.at(relativeVectorPos) = i->second;
                xValues.at(relativeVectorPos - 1) = i->second;
            }
        } else {
            for (auto j = yValues.begin(); j != yValues.end() + 1; j += 2) {
                if (i->first < *j && i->first > *(j - 1)) {
                    int relativeVectorPos = j - yValues.begin();
                    total += valsToAdd.at(relativeVectorPos) * ((i - 1)->second - xValues.at(relativeVectorPos));
                    *(j - 1) = i->first;
                    valsToAdd.at(relativeVectorPos) = (*j - *(j - 1)) + 1;
                    valsToAdd.at(relativeVectorPos - 1) = (*j - *(j - 1)) + 1;
                    xValues.at(relativeVectorPos) = i->second;
                    xValues.at(relativeVectorPos - 1) = i->second;
                    break;
                }
            }
            /* test for edge case in part one test*/

            yValues.push_back((i - 1)->first);
            yValues.push_back(i->first);
            xValues.push_back((i - 1)->second);
            xValues.push_back(i->second);
            valsToAdd.push_back(i->first - (i - 1)->first + 1);
            valsToAdd.push_back(i->first - (i - 1)->first + 1);
        }
    }

    std::cout << total;

    return 0;
}

int toDecimal(std::string hex) {
    int decimal = 0;

    for (int i = HEX_START; i < HEX_END; i++) {
        switch (hex.at(i)) {
            case '0':
                decimal += 0 * pow(16, HEX_END - i - 1);
                break;
            case '1':
                decimal += 1 * pow(16, HEX_END - i - 1);
                break;
            case '2':
                decimal += 2 * pow(16, HEX_END - i - 1);
                break;
            case '3':
                decimal += 3 * pow(16, HEX_END - i - 1);
                break;
            case '4':
                decimal += 4 * pow(16, HEX_END - i - 1);
                break;
            case '5':
                decimal += 5 * pow(16, HEX_END - i - 1);
                break;
            case '6':
                decimal += 6 * pow(16, HEX_END - i - 1);
                break;
            case '7':
                decimal += 7 * pow(16, HEX_END - i - 1);
                break;
            case '8':
                decimal += 8 * pow(16, HEX_END - i - 1);
                break;
            case '9':
                decimal += 9 * pow(16, HEX_END - i - 1);
                break;
            case 'a':
                decimal += 10 * pow(16, HEX_END - i - 1);
                break;
            case 'b':
                decimal += 11 * pow(16, HEX_END - i - 1);
                break;
            case 'c':
                decimal += 12 * pow(16, HEX_END - i - 1);
                break;
            case 'd':
                decimal += 13 * pow(16, HEX_END - i - 1);
                break;
            case 'e':
                decimal += 14 * pow(16, HEX_END - i - 1);
                break;
            case 'f':
                decimal += 15 * pow(16, HEX_END - i - 1);
                break;
        }
    }

    return decimal;
}

char toDirection(std::string hex) {
    switch (hex.at(HEX_END)) {
        case '0':
            return 'R';
        case '1':
            return 'D';
        case '2':
            return 'L';
        case '3':
            return 'U';
        default:
            return 'X';
    }
}

