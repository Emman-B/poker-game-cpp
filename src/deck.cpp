#include "deck.hpp"

#include <algorithm> // random_shuffle

/* friend func */
std::ostream& operator<< (std::ostream& out, const deck& d)
{
    if (d.cards.size() > 0)
    {
        for(auto const &cd : d.cards)
        {
            // print card with newline until last item
            out << cd << ( (cd == *d.cards.rbegin())?"":"\n" ) << std::flush;
        }
    }
    return out;
}

/*** Functions ***/
void deck::shuffle()
{
    std::random_shuffle<std::vector<card>::iterator> (cards.begin(), cards.end());
}

// add functions
void deck::add(const card&) // 1 card
{
    static_assert(false);
}
void deck::add(std::vector<card>::iterator, std::vector<card>::iterator) // range
{
    static_assert(false);
}

card deck::draw_card()
{
    static_assert(false);
}

void deck::clear()
{
    static_assert(false);
}

/*** Non-member Functions ***/
deck make_52_card_deck()
{
    deck d;
    for (size_t suit_n = 0; suit_n < 4; suit_n++)
    {
        for (unsigned char rank_n = 1; rank_n <= 13; rank_n++)
        {
            card newcard(rank_n, static_cast<card::suit_t>(suit_n));
            d.add(newcard);
        }
    }
}