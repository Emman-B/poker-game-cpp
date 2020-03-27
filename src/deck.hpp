#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

#include "card.hpp"

class deck
{
    /* friend declarations */
    // for printing
    friend std::ostream& operator<< (std::ostream&, const deck&);

private:
    std::vector<card> cards;
public:
    // ctor
    deck();

    // ** Functions ** //
    // shuffles all the cards in the deck (vector of cards)
    void shuffle();
};

#endif