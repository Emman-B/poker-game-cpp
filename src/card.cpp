#include "card.hpp"

#include <string>

card::card(unsigned char r, suit_t s)
{
    // error-check: is rank within range [1, 10]?
    if (r == 0 || r > 10)
    {
        throw std::runtime_error("card::card: rank out of range: " +
            static_cast<unsigned int>(r));
    }
    else
    {
        rank = r;
        suit = s;
    }
    
}

bool card::operator== (const card& that)
{
    // equality only if rank and suit match
    return (rank == that.rank && suit == that.suit);
}

std::ostream& operator<< (std::ostream& out, const card& c)
{
    // Format "rank_str of suit_str"
    std::string rank_str;
    std::string suit_str;

    // set rank_str
    if (c.rank == 1)
    {
        rank_str = "ace";
    }
    else
    {
        rank_str = std::to_string(static_cast<unsigned int>(c.rank));
    }

    // set suit_str
    switch (c.suit)
    {
        case card::suit_t::DIAMONDS:
            suit_str = "diamonds";
            break;
        case card::suit_t::CLUBS:
            suit_str = "clubs";
            break;        
        case card::suit_t::HEARTS:
            suit_str = "hearts";
            break;        
        case card::suit_t::SPADES:
            suit_str = "spades";
            break;
        default:
            // doesn't hurt to have this check
            throw std::runtime_error("card suit is invalid");
    }

    // write to output stream
    out << rank_str << " of " << suit_str;
    return out;
}