#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "creature.hpp"
#include <string_view>

class Player: public Creature
{
public:
    // Constructor
    Player(std::string_view name, int level = 1);

    // getters
    int getLevel() const {return m_level;}

    void levelUp();
    bool hasWon() const;

    void description() const;
    

protected:

private:
    int m_level{1};
};

#endif