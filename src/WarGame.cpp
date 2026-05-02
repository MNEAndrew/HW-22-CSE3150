#include "WarGame.h"
#include <iostream>

WarGame::WarGame(Deck& deck, const std::string& outputPath)
    : round_(1), writer_(outputPath) {
    auto [a, b] = deck.split();
    deckA_ = std::move(a);
    deckB_ = std::move(b);
}

void WarGame::play() {
    std::cout << "Starting War\n";
    while (!deckA_.empty() && !deckB_.empty()) {
        std::cout << "Round " << round_ << "\n";
        playRound();
        writer_.writeRound(round_, deckA_, deckB_);
        round_++;
    }
    std::cout << "Game Over\n";
    if (deckA_.size() > deckB_.size()) {
        std::cout << "Player A wins with " << deckA_.size() << " cards!\n";
    } else if (deckB_.size() > deckA_.size()) {
        std::cout << "Player B wins with " << deckB_.size() << " cards!\n";
    } else {
        std::cout << "It's a tie!\n";
    }
}

void WarGame::playRound() {
    auto cardA = deckA_.draw();
    auto cardB = deckB_.draw();
    if (!cardA || !cardB) return;

    std::cout << "Player A plays: " << *cardA << "\n";
    std::cout << "Player B plays: " << *cardB << "\n";

    // B's card <= A's card: A wins; add A's card then B's card to A's deck
    if (*cardB < *cardA || *cardB == *cardA) {
        deckA_.addToBottom(std::move(cardA));
        deckA_.addToBottom(std::move(cardB));
    } else {
        // B wins; add B's card then A's card to B's deck
        deckB_.addToBottom(std::move(cardB));
        deckB_.addToBottom(std::move(cardA));
    }
}
