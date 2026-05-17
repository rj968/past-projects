#include <iostream>
#include <optional>
#include <string_view>


enum class Animal
{
    pig,
    chicken, 
    goat, 
    cat, 
    dog, 
    duck,
};

std::optional<std::string_view> getAnimalName (Animal animal)
{
    using enum Animal;
    switch (animal) 
    {
        case pig: return "pig";
        case chicken: return "chicken";
        case goat: return "goat";
        case cat: return "cat";
        case dog: return "dog";
        case duck: return "duck";
        default: return {};
    }
}

std::optional<int> getNumberOfLegs (Animal animal)
{
    using enum Animal;
    switch (animal) 
    {
        case pig: return 4;
        case chicken: return 2;
        case goat: return 4;
        case cat: return 4;
        case dog: return 4;
        case duck: return 2;
        default: return {};
    }
}

void printNumberOfLegs (Animal animal)
{
    if (getNumberOfLegs(animal) && getAnimalName(animal))
        std::cout << "A " << *getAnimalName(animal) << " has " << *getNumberOfLegs(animal) << " legs." <<'\n';
    else
        std::cerr << "You have entered an Invalid Name.\n";
}

int main()
{
    Animal cat {Animal::cat};
    [[maybe_unused]] Animal chicken {Animal::chicken};
    printNumberOfLegs(cat);
    printNumberOfLegs(chicken);
    printNumberOfLegs(static_cast<Animal>(6));
    return 0;
}