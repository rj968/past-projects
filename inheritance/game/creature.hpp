#ifndef CREATURE_HPP
#define CREATURE_HPP


#include <string>

class Creature
{

public:

    // constructors
    Creature(std::string_view name, char symbol, int health, int attack, int gold);

    // getters
    std::string_view getName() const {return m_name;}
    char getSymbol() const {return m_symbol;}
    int getHealth() const {return m_health;}
    int getAttack() const {return m_attack;}
    int getGold() const {return m_gold;}

    void increaseAttack(int amount) {m_attack+=amount;}

    void reduceHealth(int damage);
    bool isDead();
    void addGold(int amount);

protected:

private:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_attack{};
    int m_gold{};
};
#endif /*creature_hpp*/