#ifndef CARD_HPP
#define CARD_HPP

#include <iostream> // ostream

class card
{
    /* friend declarations */
    friend class deck;
        // allow deck to access enum class suit_t, rank, and suit per card

    friend std::ostream& operator<< (std::ostream&, const card&);

private:
    enum class suit_t;

    /* fields */
    unsigned char rank; // general range: A-10,J,Q,K
    suit_t suit;        // four possible suits

public:
    enum class suit_t
    {
        DIAMONDS = 0,
        CLUBS    = 1,
        HEARTS   = 2,
        SPADES   = 3
    };

    /* constructor */
    card(unsigned char r, suit_t s);

    bool operator== (const card&) const;
};

#endif