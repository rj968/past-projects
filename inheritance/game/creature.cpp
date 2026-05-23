#include "creature.hpp"

Creature::Creature(std::string_view name, char symbol, int health, int attack, int gold)
    :   m_name {name},
        m_symbol {symbol},
        m_health {health},
        m_attack {attack},
        m_gold {gold}
    {
    }

void Creature::reduceHealth(int damage)
{
    m_health -= damage;
}

bool Creature::isDead()
{
    return m_health <= 0;
}

void Creature::addGold(int amount)
{
    m_gold += amount;
}