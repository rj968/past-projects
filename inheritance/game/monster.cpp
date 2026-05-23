#include "monster.hpp"
#include "../Random.h"

Monster Monster::getRandomMonster()
{
    Type randomType {static_cast<Type>(Random::get(0,max_types-1))};
    return Monster(randomType); 
}