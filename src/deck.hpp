#ifndef DECK_HPP
#define DECK_HPP

/* Includes */
#include <vector>

#include "card.hpp"

/* Class declaration*/
class deck
{
    /* friend declarations */
    friend std::ostream& operator<< (std::ostream&, const deck&);

private:
    /* fields */
    std::vector<card> cards; // holds cards
public:
    /* constructor */
    deck(); // places 52 card objects in cards vector

    /*** Functions ***/
    void shuffle(); // calls random_shuffle on cards vector
};

#endif