#include "gtest/gtest.h"
#include "../src/card.hpp"

#include <string>
#include <sstream>

TEST(cardtest, card_equals_op)
{
    // test equality of two constructed cards
    card c1(1, card::suit_t::HEARTS);
    card c2 (1, card::suit_t::HEARTS);
    EXPECT_EQ(c1, c2);
}

TEST(cardtest, card_getter_funcs)
{
    // test the getter functions for the card class
    card c (8, card::suit_t::DIAMONDS);
    EXPECT_EQ(8, c.get_rank());
    EXPECT_EQ(card::suit_t::DIAMONDS, c.get_suit());
}

TEST(cardtest, card_bad_ctor_args)
{
    // test bad constructor arguments
    EXPECT_ANY_THROW(card c(25, static_cast<card::suit_t>(5)));
    EXPECT_ANY_THROW(card c(-3, static_cast<card::suit_t>(-1)));
}

TEST(cardtest, card_output_str)
{
    // test operator<< for proper output
    std::ostringstream output_str;
    for (unsigned int idx = 1; idx < 14; idx++)
    {
        card c (idx, card::suit_t::CLUBS);
        output_str << c;
        switch (idx)
        {
        case 1:
            EXPECT_EQ(output_str.str(), std::string("ace of clubs"));
            output_str.str(std::string());
            output_str.clear();
            break;
        case 11:
            EXPECT_EQ(output_str.str(), std::string("jack of clubs"));
            output_str.str(std::string());
            output_str.clear();
            break;
        case 12:
            EXPECT_EQ(output_str.str(), std::string("queen of clubs"));
            output_str.str(std::string());
            output_str.clear();
            break;
        case 13:
            EXPECT_EQ(output_str.str(), std::string("king of clubs"));
            output_str.str(std::string());
            output_str.clear();
            break;
        default:
            EXPECT_EQ(output_str.str(), std::string(std::to_string(idx) + " of clubs"));
            output_str.str(std::string());
            output_str.clear();
            break;
        }
    }
}