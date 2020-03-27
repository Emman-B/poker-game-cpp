#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

#include "card.hpp"

class deck
{
private:
    std::vector<card> cards;
public:
    // ctor
    deck();
};

#endif