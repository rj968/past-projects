// MODULARISE YOUR CODE YOU FOOL!

#include "Random.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

namespace multSettings 
{
    int minMult = 2;
    int maxMult = 4;
    int getMult()
    {
        return Random::get(multSettings::minMult,multSettings::maxMult);
    }
}

int getInput()
{
    int input{};
    std::cin >> input;
    while(true)
    {

        if(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Invalid input, Try again: ";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return input;
    }
}

void generateNumbers(int start, const std::size_t countNumbers, std::vector<int>& numbers,const int mult)
{
    for(std::size_t i {0}; i<countNumbers; ++i, ++start)
    {
        numbers[i] = start*start*mult;
    }
}

int main()
{
    std::cout << "Start where? ";
    const int start{getInput()};

    std::cout << "How many? ";
    int countNumbers {getInput()};
    if (countNumbers<=0)
    {
        std::cout << "Invalid input!\n";
        return 1;
    }

    const int mult{multSettings::getMult()};

    std::vector<int> numbers(countNumbers);
    generateNumbers(start, countNumbers, numbers, mult);

    std::cout << "I generated " << countNumbers 
    << " square numbers. Do you know what each number is after multiplying it by " 
    << mult << "?\n";   

    int guess {};

    auto nearestfunc {
        [&guess](auto x, auto y){
            return std::abs(x-guess) < std::abs(y-guess);
        }
    };

    while(countNumbers>1)
    {
        guess = getInput();
        auto found {std::find(numbers.begin(),numbers.end(),guess)};
        if(found!=numbers.end())
        {
            numbers.erase(found);
            --countNumbers;
            std::cout << "Nice " << countNumbers << " number(s) left.\n"; 
        }
        else
        {
            auto nearestNum {std::min_element(numbers.begin(),numbers.end(),nearestfunc)};
            std::cout << guess << " is wrong! Try " << *nearestNum << " next time.\n";
            break;
        }
    }
}