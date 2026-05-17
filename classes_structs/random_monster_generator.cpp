#include "Random.h"
#include <string>
#include <string_view>
#include <iostream>

class Monster{
public:
    enum Type
    {
        Dragon, Goblin, Ogre, Orc, Skeleton, Troll, Vampire, Zombie,
        maxMonsterType,
    };

    explicit Monster(Type type, std::string_view name, std::string_view roar, int hp)
        :
        m_type {type},
        m_name {name},
        m_roar {roar},
        m_hp   {hp}
        {
        }
    void print() const;
private:
    Type        m_type {};
    std::string m_name {"???"};
    std::string m_roar {"???"};
    int         m_hp   {};
};

std::string_view getTypeString(Monster::Type type)
{
    switch (type)
    {
    case Monster::Dragon: return "Dragon";
    case Monster::Goblin: return "Goblin";
    case Monster::Ogre  : return "Ogre";
    case Monster::Orc   : return "Orc";
    case Monster::Skeleton: return "Skeleton";
    case Monster::Troll : return "troll";
    case Monster::Vampire: return "Vampire";
    case Monster::Zombie: return "Zombie";
    default: return "???";
    }
}

void Monster::print() const
{
    if(m_hp<=0)
        std::cout << m_name << " the " << getTypeString(m_type) << " is dead.\n";
    else
    {
        std::cout << m_name << " the " << getTypeString(m_type) << " has "
        << m_hp << " hit points and says " << m_roar << ".\n";    
    }
}

namespace MonsterGenerator 
{
    std::string_view getName(int name)
    {
        switch (name) 
        {
            case 0: return "0";
            case 1: return "1";
            case 2: return "2";
            case 3: return "3";
            case 4: return "4";
            case 5: return "5";
            default: return "???";
        }
    }

    std::string_view getRoar(int roar)
    {
        switch (roar) 
        {
            case 0: return "0";
            case 1: return "1";
            case 2: return "2";
            case 3: return "3";
            case 4: return "4";
            case 5: return "5";
            default: return "???";
        }
    }

    Monster generate()
    {
        return 
            Monster{
             static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterType-1)),
             getName(Random::get(0,5)), 
             getRoar(Random::get(0,5)),
             Random::get(0,100)
            };
    }
}

int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}




