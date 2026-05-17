// Write a program that:

//     Asks the user how many names they wish to enter.
//     Dynamically allocates a std::string array.
//     Asks the user to enter each name.
//     Calls std::sort to sort the names
//     Prints the sorted list of names.

#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <string>


std::size_t getInput()
{
    std::size_t input{};

    while(true)
    {
        std::cin>>input;
        if(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

int main()
{
    std::cout << "How many names do you wish to enter: ";
    std::size_t input{getInput()};
    auto* array {new std::string[input]{}};
    for(std::size_t i {0}; i < input; ++i)
    {
        std::cout << "Enter the " << i << " name: ";
        std::getline(std::cin, array[i]);
    }
    std::sort(array, array+input);
    for(std::size_t i {0}; i < input; ++i)
        std::cout << array[i] << '\n';
    delete[] array;

    return 0;
}