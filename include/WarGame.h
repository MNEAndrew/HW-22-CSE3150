#pragma once
#include "Deck.h"
#include "FileWriter.h"
#include <string>

class WarGame {
public:
    WarGame(Deck& deck, const std::string& outputPath);
    void play();
private:
    void playRound();
    Deck deckA_;
    Deck deckB_;
    int round_;
    FileWriter writer_;
};
