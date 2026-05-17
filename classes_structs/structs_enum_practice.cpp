#include <iostream>
#include <string>
#include <string_view>


enum class Monsters
{
    noName,
    ogre,
    dragon,
    orc,
    gaint_spider,
    slime,
};

std::string_view printMonsterType(Monsters type);

struct Monster
{
    Monsters type {};
    std::string name {printMonsterType(type)};
    int health {100};
};

std::string_view printMonsterType(Monsters type)
{
    using enum Monsters;
    switch (type) 
    {
        case ogre: return "ogre";
        case dragon: return "dragon";
        case orc: return "orc";
        case gaint_spider: return "gaint spider";
        case slime: return "slime";
        default: return "???";
    }
}

void printMonster(Monster target)
{
    std::cout << "This " << printMonsterType(target.type) << " is named " << target.name
    << " and has " << target.health << " health.\n";
}

int main()
{
    Monster ogre  {Monsters::ogre,"Torg",145};
    Monster slime {Monsters::slime, "Blurp", 23};
    Monster x{};
    printMonster(ogre);
    printMonster(slime);
    printMonster(x);
    return 0;
}