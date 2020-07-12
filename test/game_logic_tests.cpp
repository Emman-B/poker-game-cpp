#include "gtest/gtest.h"
#include "../src/game_logic.hpp"

// literals for easier card constructing:

card operator "" _S(unsigned long long rank) // card with suit: spades
{
    return card(static_cast<unsigned char>(rank), card::suit_t::SPADES);
}
card operator "" _H(unsigned long long rank) // card with suit: hearts
{
    return card(static_cast<unsigned char>(rank), card::suit_t::HEARTS);
}
card operator "" _C(unsigned long long rank) // card with suit: clubs
{
    return card(static_cast<unsigned char>(rank), card::suit_t::CLUBS);
}
card operator "" _D(unsigned long long rank) // card with suit: diamonds
{
    return card(static_cast<unsigned char>(rank), card::suit_t::DIAMONDS);
}


//===============================================================================================//
// HIGH =========================================================================================//
TEST (gamelogictest, high_card)
{
    // tests 3 hands: high card, flush, high card
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::HIGH, logic.verify_hand( {10_H, 4_C, 9_H, 13_H, 11_H} ));

    EXPECT_NE(hand_type::HIGH, logic.verify_hand( {1_D, 4_D, 3_D, 8_D, 13_D} ));

    EXPECT_EQ(hand_type::HIGH, logic.verify_hand( {1_C, 4_C, 3_D, 8_S, 13_H} ));
}

//===============================================================================================//
// ONE PAIR =====================================================================================//
TEST (gamelogictest, one_pair)
{
    // tests 3 hands: one pair, three of a kind, one pair
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::ONE_PAIR, logic.verify_hand( {3_C, 9_C, 2_D, 2_S, 8_H} ));

    EXPECT_NE(hand_type::ONE_PAIR, logic.verify_hand( {8_C, 2_C, 8_D, 8_S, 5_H} ));

    EXPECT_EQ(hand_type::ONE_PAIR, logic.verify_hand( {11_C, 12_C, 13_D, 4_S, 13_H} ));
}

//===============================================================================================//
// TWO PAIR =====================================================================================//
TEST (gamelogictest, two_pair)
{
    // tests 3 hands: two pair, three of a kind, two pair
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::TWO_PAIR, logic.verify_hand( {3_C, 3_S, 2_D, 2_S, 8_H} ));

    EXPECT_NE(hand_type::TWO_PAIR, logic.verify_hand( {8_C, 2_C, 8_D, 8_S, 5_H} ));

    EXPECT_EQ(hand_type::TWO_PAIR, logic.verify_hand( {11_C, 11_D, 13_D, 4_S, 13_H} ));
}

//===============================================================================================//
// THREE OF A KIND ==============================================================================//
TEST (gamelogictest, three_of_a_kind)
{
    // tests 3 hands: three of a kind, four of a kind, three of a kind
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::THREE_OF_A_KIND, logic.verify_hand( {3_C, 3_S, 3_D, 2_S, 8_H} ));

    EXPECT_NE(hand_type::THREE_OF_A_KIND, logic.verify_hand( {8_C, 8_S, 8_D, 8_H, 5_H} ));

    EXPECT_EQ(hand_type::THREE_OF_A_KIND, logic.verify_hand( {11_C, 13_C, 13_D, 4_S, 13_H} ));
}

//===============================================================================================//
// STRAIGHT =====================================================================================//
TEST (gamelogictest, straight)
{
    // tests 3 hands: straight, four of a kind, straight
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::STRAIGHT, logic.verify_hand( {3_C, 1_C, 4_D, 2_S, 5_H} ));

    EXPECT_NE(hand_type::STRAIGHT, logic.verify_hand( {8_C, 8_S, 8_D, 8_H, 5_H} ));

    EXPECT_EQ(hand_type::STRAIGHT, logic.verify_hand( {13_H, 1_C, 10_C, 12_D, 11_H} ));
}

//===============================================================================================//
// FLUSH ========================================================================================//
TEST (gamelogictest, flush)
{
    // tests 3 hands: flush, four of a kind, flush
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::FLUSH, logic.verify_hand( {9_C, 2_C, 3_C, 4_C, 5_C} ));

    EXPECT_NE(hand_type::FLUSH, logic.verify_hand( {8_C, 8_H, 8_D, 8_S, 5_H} ));

    EXPECT_EQ(hand_type::FLUSH, logic.verify_hand( {4_D, 10_D, 11_D, 12_D, 13_D} ));
}

//===============================================================================================//
// FULL HOUSE ===================================================================================//
TEST (gamelogictest, full_house)
{
    // tests 3 hands: full house, four of a kind, full house
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::FULL_HOUSE, logic.verify_hand( {9_C, 9_D, 11_S, 11_H, 11_D} ));

    EXPECT_NE(hand_type::FULL_HOUSE, logic.verify_hand( {8_C, 8_H, 8_D, 8_S, 5_H} ));

    EXPECT_EQ(hand_type::FULL_HOUSE, logic.verify_hand( {1_C, 1_D, 3_S, 3_H, 1_H} ));
}

//===============================================================================================//
// FOUR OF A KIND ===============================================================================//
TEST(gamelogictest, four_of_a_kind)
{
    // tests 3 hands: four of a kind, royal flush, four of a kind
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::FOUR_OF_A_KIND, logic.verify_hand( {11_C, 9_D, 11_S, 11_H, 11_D} ));

    EXPECT_NE(hand_type::FOUR_OF_A_KIND, logic.verify_hand( {1_D, 10_D, 11_D, 12_D, 13_D} ));

    EXPECT_EQ(hand_type::FOUR_OF_A_KIND, logic.verify_hand( {1_C, 1_D, 3_S, 1_H, 1_S} ));
}

//===============================================================================================//
// STRAIGHT FLUSH ===============================================================================//
TEST(gamelogictest, straight_flush)
{
    // tests 3 hands: straight flush, royal flush, straight flush
    game_logic logic {}; // initialize logic
    EXPECT_EQ(hand_type::STRAIGHT_FLUSH, logic.verify_hand( {4_S, 1_S, 5_S, 3_S, 2_S} ));

    EXPECT_NE(hand_type::STRAIGHT_FLUSH, logic.verify_hand( {1_D, 10_D, 11_D, 12_D, 13_D} ));

    EXPECT_EQ(hand_type::STRAIGHT_FLUSH, logic.verify_hand( {9_H, 10_H, 11_H, 12_H, 13_H} ));
}

//===============================================================================================//
// ROYAL FLUSH ==================================================================================//
TEST(gamelogictest, royal_flush)
{
    // tests 4 hands of royal flushes
    game_logic logic {}; // initialize logic
    for (size_t s = 0; s < 4; s++)
    {
        std::vector<card> hand = {
            card(1, static_cast<card::suit_t>(s)),
            card(10, static_cast<card::suit_t>(s)),
            card(11, static_cast<card::suit_t>(s)),
            card(12, static_cast<card::suit_t>(s)),
            card(13, static_cast<card::suit_t>(s))
        };
        EXPECT_EQ(hand_type::ROYAL_FLUSH, logic.verify_hand(hand));
    }
}