#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

const int HAND_SIZE = 5;
const std::unordered_map<char, int> cardValues = {
    {'J', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'Q', 11},
    {'K', 12},
    {'A', 13}
};

int  countNumOfCardInHand(const std::string hand, char valToCheck);
bool containsPair(const std::string hand);
bool containsTwoPair(const std::string hand);
bool containsThreeOfaKind(const std::string hand);
bool containsFullHouse(const std::string hand);
bool containsFourOfaKind(const std::string hand);
bool containsFiveOfaKind(const std::string hand);
int checkAllHands(const std::string hand);

class CamelHand {
    public:
        std::string cards;
        std::string cardsWithoutJokers;
        int bet;

        CamelHand(std::string c, int b) {
            cards = c;
            bet = b;

            cardsWithoutJokers = c;
            replaceJokers();
        }

        CamelHand operator=(const CamelHand& second) {
            cards = second.cards;
            bet = second.bet;
            cardsWithoutJokers = second.cardsWithoutJokers;
            return *this;
        }

        void replaceJokers() {
            int highestCardCount = 0;
            int currentCardCount;
            char replacementChar = 'J';
            for (auto v : cardValues) {
                currentCardCount = countNumOfCardInHand(cards, v.first);
                if (v.first == 'J') { continue; }
                if (currentCardCount > highestCardCount) {
                    highestCardCount = currentCardCount;
                    replacementChar = v.first;
                }
            }
            for (int i = 0; i < HAND_SIZE; i++) {
                if (cardsWithoutJokers[i] == 'J') {
                    cardsWithoutJokers[i] = replacementChar;
                }
            }
        }
};


int main() {
    std::ifstream infile("puzzleInput.txt");
    std::string cards;
    bool validID = true;
    std::vector<CamelHand*> hands;
    CamelHand* hand;
    int bet;
    int maxPositionOffset = 1;
    int total = 0;
    
    infile >> cards; 
    while (infile) {
        infile >> bet;
        hand = new CamelHand(cards, bet);
        hands.push_back(hand);
        infile >> cards;
    }

    std::sort(hands.begin(), hands.end(), 
        [](const CamelHand* first, const CamelHand* second) {
            int firstHand = checkAllHands(first->cardsWithoutJokers);
            int secondHand = checkAllHands(second->cardsWithoutJokers);
            if (firstHand < secondHand) {
                return true;
            } else if (firstHand == secondHand) {
                for (int i = 0; i < HAND_SIZE; i++) {
                    if (cardValues.at(first->cards.at(i)) < cardValues.at(second->cards.at(i))) {
                        return true;
                    } else if (cardValues.at(first->cards.at(i)) > cardValues.at(second->cards.at(i))) {
                        return false;
                    }
                }
            }

            return false;
        });

    for (int i = 0; i < hands.size(); i++) {
        total += hands.at(i)->bet * (i + 1);
    }

    std::cout << total;

    return 0;
}

int checkAllHands(const std::string hand) {
    if (containsFiveOfaKind(hand)) { return 6; }
    else if (containsFourOfaKind(hand)) { return 5; }
    else if (containsFullHouse(hand)) { return 4; }
    else if (containsThreeOfaKind(hand)) { return 3; }
    else if (containsTwoPair(hand)) { return 2; }
    else if (containsPair(hand)) { return 1; }
    return 0;
}

int countNumOfCardInHand(const std::string hand, char valToCheck) {
    int cardCount = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        if (hand[i] == valToCheck) {
            cardCount++;
        }
    }

    return cardCount;
}

bool containsPair(const std::string hand) {
    for (auto v : cardValues) {
        if (countNumOfCardInHand(hand, v.first) == 2) {
            return true;
        }
    }
    return false;
}

bool containsTwoPair(const std::string hand) {
    int pairCount = 0;

    for (auto v : cardValues) {
        if (countNumOfCardInHand(hand, v.first) == 2) {
            pairCount++;
        }
    }

    return pairCount >= 2;
}

bool containsThreeOfaKind(const std::string hand) {
    for (auto v : cardValues) {
        if (countNumOfCardInHand(hand, v.first) == 3) {
            return true;
        }
    }
    return false;
}

bool containsFullHouse(const std::string hand) {
    return containsPair(hand) && containsThreeOfaKind(hand);
}

bool containsFourOfaKind(const std::string hand) {
    for (auto v : cardValues) {
        if (countNumOfCardInHand(hand, v.first) == 4) {
            return true;
        }
    }
    return false;
}

bool containsFiveOfaKind(const std::string hand) {
    for (auto v : cardValues) {
        if (countNumOfCardInHand(hand, v.first) == 5) {
            return true;
        }
    }
    return false;
}