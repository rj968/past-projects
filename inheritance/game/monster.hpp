#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "creature.hpp"

class Monster : public Creature
{
public:
    enum Type{
        dragon,
        orc,
        slime,
        max_types,
    };

    // constructors
    Monster(Type type)
    : Creature {monsterData[type]}
    {
    }

    static Monster getRandomMonster();

protected:

private:
    static inline Creature monsterData[]{
        {"dragon", 'D', 20, 4, 100},
        {"orc", 'o', 4, 2, 25},
        {"slime", 's', 1, 1, 10}
    };
};

#endif