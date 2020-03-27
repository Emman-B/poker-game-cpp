#include "deck.hpp"

#include <algorithm> // random_shuffle

deck::deck()
{
    // constructs a deck with 52 cards
    for (size_t suit_n = 0; suit_n < 4; suit_n++)
    {
        for (unsigned char rank_n = 1; rank_n <= 13; rank_n++)
        {
            cards.emplace_back(rank_n, suit_n);
        }
    }
}

void deck::shuffle()
{
    std::random_shuffle<std::vector<card>::iterator> (cards.begin(), cards.end());
}

std::ostream& operator<< (std::ostream& out, const deck& d)
{
    if (d.cards.size() > 0)
    {
        for(auto& cd : d.cards)
        {
        }
    }
}