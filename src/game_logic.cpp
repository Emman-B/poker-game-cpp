#include "game_logic.hpp"

#include <set>
#include <cassert> // assert()

/* Private Functions */
bool game_logic::has_flush() const
{
    // check to see if there are 5 cards in the hand first
    if (hand_cache.size() != 5) return false;

    auto hand_cache_itor = hand_cache.cbegin();
    // ensure that hand_cache wasn't empty
    assert(hand_cache_itor != hand_cache.cend());

    // create target suit to compare other hands
    const card::suit_t suit_compare_target = hand_cache_itor->get_suit();
    ++hand_cache_itor;

    // start comparing all the handsd to suit_compare_target
    while (hand_cache_itor != hand_cache.cend())
    {
        if (hand_cache_itor->get_suit() != suit_compare_target)
        {
            return false;
        }
        ++hand_cache_itor;
    }

    // if loop is passed, then all 5 cards match the suit
    return true;
}

bool game_logic::has_straight() const
{
    // check to see if there are 5 cards in the hand first
    if (hand_cache.size() != 5) return false;

    // put ranks into sorted set
    std::set<unsigned char> ranks{};
    for (auto itor = hand_cache.cbegin(); itor != hand_cache.cend(); ++itor)
    {
        ranks.insert(itor->get_rank());
    }

    // if set size < 5, then there is a pair, return false
    if (ranks.size() < 5) return false;

    //*** verifying straights ***//

    // check the highest straight (A,10,J,Q,K)
    if (ranks.find(1) != ranks.end() && ranks.find(10) != ranks.end() && 
            ranks.find(11) != ranks.end() && ranks.find(12) != ranks.end() &&
            ranks.find(13) != ranks.end())
    {
        return true;
    }

    // check for other straights by going through set
    auto itor = ranks.cbegin();
    unsigned char prev_value = *itor;
    ++itor;
    for (; itor != ranks.cend(); ++itor)
    {
        if (*itor - prev_value != 1)
        {
            return false;
        }
        prev_value = *itor;
    }
}

hand_type game_logic::verify_hand(const std::vector<card> cards)
{
    // first reset all the bits in the hands_fulfilled bitset
    for (size_t idx = 0; idx < 9; idx++)
    {
        hands_fulfilled.reset(idx);
    }
    // ensure that the hand has 5 cards
    assert(cards.size() == 5);

    // put the cards in the vector into the hand_cache vector
    for (auto card : cards)
    {
        hand_cache.push_back(card);
    }

    //** find pairs/triples using an unordered map **//
    // unordered map is a pair where key = rank, value = count of that rank
    std::unordered_map<unsigned char, size_t> ranks{};
    for (auto card : hand_cache)
    {
        // if the specific rank is in the unordered_map, then increment its count value
        auto query = ranks.find(card.get_rank());
        if (query != ranks.cend())
        {
            query->second++;
        }
        // otherwise, we add it to the unordered map
        else
        {
            ranks.insert( {card.get_rank(), 1} );
        }
    }

    //** Test for all hands that have cards of the same rank (pair, full house, etc) **//
    // if the ranks map has less than 5 elements, then there is at least a pair
    if (ranks.size() < 5)
    {
        // go through the rank counts
        for (auto ranks_itor = ranks.cbegin(); ranks_itor != ranks.cend(); ++ranks_itor)
        {
            switch(ranks_itor->second)
            {
            case 2: // pair or two-pair
                if (hands_fulfilled.test(static_cast<size_t>(hand_type::ONE_PAIR)))
                {
                    hands_fulfilled.set(static_cast<size_t>(hand_type::TWO_PAIR));
                    break;
                }
                else
                {
                    hands_fulfilled.set(static_cast<size_t>(hand_type::ONE_PAIR));
                }
                break;
            case 3: // three of a kind
                hands_fulfilled.set(static_cast<size_t>(hand_type::THREE_OF_A_KIND));
                break;
            case 4: // four of a kind
                hands_fulfilled.set(static_cast<size_t>(hand_type::FOUR_OF_A_KIND));
                break;
            default:
                break;
            }
        }
    }

    // test for full house hand (one pair + three of a kind)
    hands_fulfilled.set( hands_fulfilled.test(static_cast<size_t>(hand_type::ONE_PAIR)) &&
            hands_fulfilled.test(static_cast<size_t>(hand_type::THREE_OF_A_KIND)) );
    
    //** Test for the other hands dealing with straights and/or flushes **//
    // straight
    hands_fulfilled.set( static_cast<size_t>(hand_type::STRAIGHT), has_straight() );
    // flush
    hands_fulfilled.set( static_cast<size_t>(hand_type::FLUSH), has_flush() );
    // straight flush
    hands_fulfilled.set( static_cast<size_t>(hand_type::STRAIGHT_FLUSH),
            hands_fulfilled.test(static_cast<size_t>(hand_type::STRAIGHT)) &&
                    hands_fulfilled.test(static_cast<size_t>(hand_type::FLUSH)) );
    // royal flush (check for straight flush with A and 10)
    if ( hands_fulfilled.test(static_cast<size_t>(hand_type::STRAIGHT_FLUSH)) )
    {
        if ( ranks.find(1) != ranks.cend() && ranks.find(10) != ranks.cend());
        {
            hands_fulfilled.set(static_cast<size_t>(hand_type::ROYAL_FLUSH));
        }
    }

    //** Return the highest hand_type value **//
    for (size_t idx = hands_fulfilled.size() - 1; idx > 0; idx--)
    {
        if ( hands_fulfilled.test(idx) )
        {
            // hand_type is just a size_t with a specific value
            return static_cast<hand_type>(idx);
        }
    }

    // return high card
    return hand_type::HIGH;
}