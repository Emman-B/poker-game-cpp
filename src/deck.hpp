#ifndef DECK_HPP
#define DECK_HPP

/* Includes */
#include <vector>
#include <random> // mt19937

#include "card.hpp"

/* Class declaration*/
class deck
{
    /* friend declarations */
    friend std::ostream& operator<< (std::ostream&, const deck&);

private:
    /* fields */
    std::vector<card> cards; // holds cards

    // used for random number generation
    static std::random_device rd;
    static std::mt19937 rng;
public:
    /* constructor */
    deck() = default; // makes empty deck

    /* functions */
    void shuffle(); // calls shuffle() on cards vector

    // add cards to deck
    void add(const card&);
    void add(std::vector<card>::iterator, std::vector<card>::iterator);

    // remove card from back of cards vector
    card draw_card();

    // clear cards vector
    void clear();

    /* operator functions */
    bool operator==(const deck&);
};

/*** Non-member functions ***/
deck make_52_card_deck();

#endif