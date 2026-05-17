// IMPROVE CODE 
// DIVIDE INTO FUNCTIONS
// USE ENUMS AS RETURN VALS
// IMPLEMENT EXTRA CREDIT QUESTIONS
#include "Random.h"
#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <array>
#include <algorithm>
#include <string_view>

namespace returnVal
{
    enum Type
    {
        playerWins,dealerWins,draw,
        max_returnVal
    };
}

namespace PlayerType
{
    enum Type{
        player,dealer
    };
}

struct Card
{
    enum Rank
    {
        r_ace,
        r_2,r_3,r_4,r_5,r_6,r_7,r_8,r_9,r_10,
        r_king,
        r_queen,
        r_jack,
        max_ranks
    };
    enum Suit
    {
        spade,heart,club,diamond,
        max_suits
    };
    static constexpr size_t totalCards {static_cast<size_t>(Card::max_ranks) * static_cast<size_t>(Card::max_suits)};

    Suit suit{};
    Rank rank{};
    static constexpr std::array suits {spade,heart,club,diamond};
    static constexpr std::array ranks {
        r_ace,
        r_2,r_3,r_4,r_5,r_6,r_7,r_8,r_9,r_10,
        r_king,
        r_queen,
        r_jack
    };
    static_assert(suits.size() == Card::max_suits);
    static_assert(ranks.size() == Card::max_ranks);
    
    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array suits_name {'S','H','C','D'};
        static constexpr std::array ranks_name {
            'A','2','3','4','5','6','7','8','9'
            ,'T','K','Q','J'
        };
        out << suits_name[card.suit] << ranks_name[card.rank];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::size_t m_currentCard {Card::totalCards};
    std::array<Card,Card::totalCards> m_deck{};
public:
    Deck()
    {
        for(const auto& s: Card::suits)
            for(const auto& r: Card::ranks)
                m_deck[s*13 + r] = Card{s,r};
    }

    void shuffle()
    {
        std::shuffle(m_deck.begin(), m_deck.end(), Random::mt);
    }
    Card& deal() 
    {

        assert(m_currentCard != 0 && "Deck::dealCard ran out of cards");
        return m_deck[--m_currentCard];
    }
};

struct Player
{
    int m_score{};
    int m_aces{};
};

namespace Settings 
{
    constexpr int maxHandValue {21};
    constexpr int stopDealing {17};
}


void handleAces(Player& player)
{
    while(player.m_score>Settings::maxHandValue && player.m_aces != 0)
    {
        --player.m_aces;
        player.m_score -= 10;
    }
}

void dealCard(Player& player, Deck& deck, PlayerType::Type type)
{
    std::string_view name {};
    if(type == PlayerType::player)
        name = "Player";
    else if(type == PlayerType::dealer)
        name = "Dealer";

    const Card& card {deck.deal()};
    player.m_score += card.value();
    if(card.rank == Card::r_ace)
        ++player.m_aces;

    handleAces(player);
    std::cout << name <<" was dealt " << card 
    << ". " << name << " now has " << player.m_score << ".\n";
}

void clearLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

char getInput()
{
    char input{};
    std::cout << "(h) to hit, or (s) to stand: ";
    while(true)
    {
        std::cin >> input;
        if(!std::cin || (input != 'h' && input != 's'))
        {
            std::cin.clear();
            clearLine();
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        return input;
    }
}

bool dealerDrawOrBust(Player& dealer, Deck& deck)
{
    while(true)
    {
        dealCard(dealer, deck, PlayerType::dealer);
        if(dealer.m_score > Settings::maxHandValue)
        {
            std::cout << "Dealer bust!\n";
            return true;
        }
        if(dealer.m_score>=Settings::stopDealing)
            return false;
    }
}

returnVal::Type blackjack(Player& player, Player& dealer, Deck& deck)
{
    dealCard(dealer, deck, PlayerType::dealer);
    std::cout << '\n';
    dealCard(player,deck,PlayerType::player);
    dealCard(player,deck,PlayerType::player);
    
    while(true)
    {
        char input{getInput()};
        
        if(input == 'h')
        {
            dealCard(player,deck,PlayerType::player);
            
            if(player.m_score > Settings::maxHandValue)
            {
                std::cout << "Player bust!\n";
                return returnVal::dealerWins;
            }
        }
        else if (input == 's')
            break;
    }

    if(dealerDrawOrBust(dealer, deck))
        return returnVal::playerWins;

    if(player.m_score>dealer.m_score)
        return returnVal::playerWins;
    else if (player.m_score<dealer.m_score)
        return returnVal::dealerWins;
    else 
        return returnVal::draw;
}

int main()
{
    Deck deck{};
    deck.shuffle();
    Player player{};
    Player dealer{};

    int gameResult {blackjack(player, dealer, deck)};
    
    if(gameResult == returnVal::playerWins)
        std::cout << "Player Wins!\n";
    else if(gameResult == returnVal::dealerWins)
        std::cout << "Dealer Wins!\n";
    else if(gameResult == returnVal::draw)
        std::cout << "Draw!\n";

    return 0;
}