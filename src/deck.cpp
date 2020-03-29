#include "deck.hpp"

#include <algorithm> // random_shuffle

/*** random_device + rng initialization ***/
std::random_device deck::rd{};
std::mt19937 deck::rng(rd());

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
    std::shuffle(cards.begin(), cards.end(), rng);
}

// add functions
void deck::add(const card& cd) // 1 card
{
    cards.push_back(cd);
}
void deck::add(std::vector<card>::iterator b, std::vector<card>::iterator e) // range
{
    for (auto current = b; current != e; ++current)
    {
        cards.push_back(*current);
    }
}

card deck::draw_card()
{
    card drawn_card = cards.back();
    cards.pop_back();
    return drawn_card;
}

void deck::clear()
{
    cards.clear();
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
    return d;
}