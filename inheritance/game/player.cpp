#include "player.hpp"

#include <iostream>

Player::Player(std::string_view name, int level)
:   Creature(name, '@', 10, 1, 0),
    m_level {level}
{
}

void Player::levelUp()
{
    ++m_level;
    increaseAttack(1);
}

bool Player::hasWon() const 
{
    std::cout << "Level up!\n";
    return m_level >= 20;
}

void Player::description() const
{
    {
        std::cout << "You have " << getHealth() << " health, you deal " 
    << getAttack() << " damage and carry " << getGold() << " gold.\n";
    }
}