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

    /*** Functions ***/
    void shuffle(); // calls random_shuffle on cards vector

    // add cards to deck
    void add(const card&);
    void add(std::vector<card>::iterator, std::vector<card>::iterator);

    card draw_card();

    void clear();
};

/*** Non-member functions ***/
deck make_52_card_deck();

#endif