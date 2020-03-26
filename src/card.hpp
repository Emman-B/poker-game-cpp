#ifndef CARD_HPP
#define CARD_HPP

#include <iostream> // ostream

class card
{
private:
    enum class suit_t;  // forward declaration

    // fields
    unsigned char rank; // general range: A-10
    suit_t suit;        // four possible suits

public:
    // suit_t for the four suits of cards
    enum class suit_t
    {
        DIAMONDS, CLUBS, HEARTS, SPADES
    };

    // ctors
    card(unsigned char r, suit_t s);

    // overload operator<< for printing
    friend std::ostream& operator<< (std::ostream&, const card&);

    // overload operator== for checking equality
    bool operator== (const card&);
};

#endif