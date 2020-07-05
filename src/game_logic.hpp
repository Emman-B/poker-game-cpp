#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <bitset>
#include <unordered_map>
#include <vector>

#include "card.hpp"

enum class hand_type: size_t
{
    /** HIGH is set to 128, and ONE_PAIR is set to 0
     *  so that the bitset hands_fulfilled has its first
     *  index corresponding to ONE_PAIR and not HIGH
     */
    HIGH = 128,
    ONE_PAIR = 0, TWO_PAIR, THREE_OF_A_KIND,
    STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND,
    STRAIGHT_FLUSH, ROYAL_FLUSH
};

// class for verifying specific card hands
class game_logic
{
private:
    /* fields */
    std::bitset<9> hands_fulfilled{};   // bitset of hands won (ignore HIGH)
    std::vector<card> hand_cache{};     // update cache for each call to verify_hand()

    /* functions */
    // both has_flush and has_straight are called in verify_hand()
    //      and uses hand_cache
    bool has_flush() const;
    bool has_straight() const;
public:
    /* functions */
    hand_type verify_hand(const std::vector<card> cards);
};

#endif