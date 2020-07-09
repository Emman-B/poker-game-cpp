#ifndef CARD_HPP
#define CARD_HPP

#include <iostream> // ostream

class card
{
    /* friend declarations */
    friend std::ostream& operator<< (std::ostream&, const card&);

public:
    enum class suit_t
    {
        DIAMONDS = 0,
        CLUBS    = 1,
        HEARTS   = 2,
        SPADES   = 3
    };

private:
    /* fields */
    unsigned char rank; // general range: A-10,J,Q,K
    suit_t suit;        // four possible suits

public:
    /* constructor */
    card(unsigned char r, suit_t s);

    /* operator functions */
    bool operator== (const card&) const;

    /* functions */
    suit_t get_suit() const;
    unsigned char get_rank() const;
};

#endif