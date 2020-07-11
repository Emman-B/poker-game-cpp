#include "gtest/gtest.h"
#include "../src/deck.hpp"

TEST(decktest, op_equals)
{
    // tests operator== for decks

    // op== on 2 equal decks
    deck d1 {};
    deck d2 {};
    d1.add({8, card::suit_t::CLUBS});
    d2.add({8, card::suit_t::CLUBS});

    EXPECT_TRUE(d1 == d2);

    // op== on 1 empty and 1 non-empty deck
    deck d3 {};
    deck d4 {};
    d3.add({12, card::suit_t::CLUBS});
    EXPECT_FALSE(d3 == d4);

    // op== on 2 non-empty decks
    EXPECT_FALSE(d1 == d3);
}

TEST(decktest, add_card_itors)
{
    // tests adding cards using std::vector<card>::iterator/const_iterator
    card c1 (8, card::suit_t::DIAMONDS);
    card c2 (11, card::suit_t::CLUBS);
    card c3 (4, card::suit_t::SPADES);
    std::vector<card> cards = {
        {8, card::suit_t::DIAMONDS},
        {11, card::suit_t::CLUBS},
        {4, card::suit_t::SPADES}
    };
    
    // adds cards normally
    deck control {};
    control.add(c1);
    control.add(c2);
    control.add(c3);

    // add cards with const_iterator
    deck itor_add1 {};
    itor_add1.add(cards.cbegin(), cards.cend());
    EXPECT_TRUE(control == itor_add1);
    // add cards with iterator
    deck itor_add2 {};
    itor_add2.add(cards.begin(), cards.end());
    EXPECT_TRUE(control == itor_add2);
}

TEST(decktest, draw_card1)
{
    // tests draw_card from deck of one card
    deck d {};
    d.add( {10, card::suit_t::HEARTS} ); // construct card

    EXPECT_EQ(d.draw_card(), card(10, card::suit_t::HEARTS));
}

TEST(decktest, draw_card2)
{
    // tests draw_card from deck of more than one card
    deck d {};
    d.add( {5, card::suit_t::CLUBS} );
    d.add( {8, card::suit_t::HEARTS} );
    d.add( {2, card::suit_t::SPADES} );
    EXPECT_EQ(d.draw_card(), card(2, card::suit_t::SPADES));
    EXPECT_EQ(d.draw_card(), card(8, card::suit_t::HEARTS));
    EXPECT_EQ(d.draw_card(), card(5, card::suit_t::CLUBS));
}

TEST(decktest, draw_card_error)
{
    // combines tests "draw_card1" and "draw_card2" to test for drawing cards from empty deck
    deck d1 {};
    d1.add( {10, card::suit_t::HEARTS} ); // construct card
    EXPECT_EQ(d1.draw_card(), card(10, card::suit_t::HEARTS));
    deck d2 {};
    d2.add( {5, card::suit_t::CLUBS} );
    d2.add( {8, card::suit_t::HEARTS} );
    d2.add( {2, card::suit_t::SPADES} );
    EXPECT_EQ(d2.draw_card(), card(2, card::suit_t::SPADES));
    EXPECT_EQ(d2.draw_card(), card(8, card::suit_t::HEARTS));
    EXPECT_EQ(d2.draw_card(), card(5, card::suit_t::CLUBS));

    // test error being thrown if draw_card is called on empty deck
    EXPECT_ANY_THROW(d1.draw_card());
    EXPECT_ANY_THROW(d2.draw_card());
}

TEST(decktest, clear_deck)
{
    // tests clear function
    deck d1 {};
    deck d2 {};

    d1.add( {9, card::suit_t::SPADES} );
    EXPECT_FALSE(d1 == d2);

    d1.clear();
    EXPECT_TRUE(d1 == d2);
}

TEST(decktest, make_52_card_deck_test)
{
    deck d1 = make_52_card_deck();
    deck d2 {};
    // add 52 cards with loop
    for (size_t s = 0; s < 4; s++)
    {
        for (unsigned char r = 1; r < 14; r++)
        {
            d2.add( {r, static_cast<card::suit_t>(s) } );
        }
    }

    EXPECT_TRUE(d1 == d2);
}

TEST(decktest, shuffle_test)
{
    std::vector<card> cards {};
    // add 52 cards with loop
    for (size_t s = 0; s < 4; s++)
    {
        for (unsigned char r = 1; r < 14; r++)
        {
            cards.push_back( {r, static_cast<card::suit_t>(s) } );
        }
    }
    // tests shuffle function

    /**
     * as there is a possibility that shuffle could shuffle cards into the same
     * unshuffled order, the test will be run multiple times and on a deck of
     * 5 copies of a 52-card deck (260 cards total)
     */
    deck control_deck  {};
    deck shuffled_deck {};
    for (int i = 0; i < 5; i++)
    {
        control_deck.add(cards.cbegin(), cards.cend());
        shuffled_deck.add(cards.cbegin(), cards.cend());
    }

    // first ensure that both decks are currently equal
    ASSERT_TRUE(control_deck == shuffled_deck);

    // shuffle the shuffled_deck up to 10 times, stops early when control_deck != shuffled_deck
    bool test_result = false;
    for (int i = 0; i < 10; i++)
    {
        shuffled_deck.shuffle();
        if ( !(control_deck == shuffled_deck) )
        {
            test_result = true;
            break;
        }
    } 
    EXPECT_TRUE(test_result);
}