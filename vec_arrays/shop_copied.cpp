// MOST OF THE CODE WAS COPIED FROM THE SOLUTION
// FORGIVE ME :(

#include "Random.h"
#include <array>
#include <ios>
#include <iostream>
#include <limits>



namespace Potion
{
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        max_potion_type
    };
    
    using  namespace std::string_view_literals;
    constexpr std::array types { healing, mana, speed, invisibility };
    constexpr std::array names {"healing"sv,"mana"sv,"speed"sv,"invisibility"sv};
    constexpr std::array prices {20,30,12,50};
    
    static_assert(max_potion_type==types.size());
    static_assert(max_potion_type==prices.size());
    static_assert(max_potion_type == names.size());
    
}



class Player{
    private:
    std::string m_name{};
    int m_gold{};
    std::array<int, Potion::max_potion_type> m_inventory {};

public:
    explicit Player(std::string_view name)
        :
        m_name {name},
        m_gold {Random::get(80,120)}
        {
        }
    int gold() const {return m_gold;}
    int inventory(Potion::Type p) const {return m_inventory[p];}
    bool buy(Potion::Type type)
    {
        if (m_gold < Potion::prices[type])
            return false;
        m_gold -= Potion::prices[type];
        ++m_inventory[type];
        return true;
    }

};
Potion::Type getInput();
void shop(Player& player)
{
    while(true)
    {
        std::cout << "Here is our selection for the day:\n";
        for(auto e: Potion::types)
            std::cout << e << ") " << Potion::names[e] << " costs " << Potion::prices[e] << '\n';
        Potion::Type potion {getInput()};
        if(potion == Potion::max_potion_type)
            return;
        if(player.buy(potion))
            std::cout << "You purchased a potion of " << Potion::names[potion] << ".  You have " << player.gold() << " gold left.\n\n";
        else
            std::cout << "You can not afford that.\n\n";
    }
}

Potion::Type getInput()
{
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char input{}; 
    while(true)
    {
        std::cin >> input;
        // checking if extraction succeeded and the input was valid
        if(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input. Try again:m";    
            continue;
        }
        if (std::cin.eof())
            std::exit(0);
        if (!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        if(input == 'q')
            return Potion::max_potion_type;
        int val{input - '0'};
        if(val >= 0 && val < Potion::max_potion_type)
            return static_cast<Potion::Type>(val);
        std::cout << "Invalid input. Try again: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void printInventory(Player& player)
{
    std::cout << "Your inventory contains:\n\n";
    for(auto e: Potion::types)
    {
        if(player.inventory(e) > 0)
            std::cout << player.inventory(e) << "x potion of " << Potion::names[e] << '\n';
    }
    std::cout << "You have " << player.gold() << " remaining.\n";
}


int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";
    std::string name{};
    std::getline(std::cin,name);
    Player player{name};
    std::cout << "Hello, " << name << " you have " << player.gold() << " gold.\n\n";
    
    shop(player);
    std::cout << '\n';
    printInventory(player);
    std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";
}