// MY SOLUTION

#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    std::size_t arr_length {arr.size()};
    for (std::size_t index = 0; index < arr_length; ++index)
    {
        std::cout << arr[index] << " ";
    }
    std::cout << '\n';
}

template <typename T>
T searchElement(const std::vector<T>& arr, T element)
{
    std::size_t arr_length {arr.size()};
    for (std::size_t index = 0; index < arr_length; ++ index)
    {
        if(arr[index] == element)
            return element;
    }
    return -1;
}

int main()
{
    int t{};
    while(true)
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> t;
        if (std::cin )
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if (t <= 9 && t >= 1)
                break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArray(arr);
    int searchResult {searchElement(arr, t)};
    if(searchResult != 0)
    {
        std::cout << "The number " << t << " was found at " << searchResult << '\n';
    }
    else {
    std::cout << "The number " << t << "was not found.\n";
    }
    // Add your code here

    return 0;
}

// GIVEN SOLUTION
/*
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        std::cout << arr[index] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';
}

template <typename T>
int findIndex(const std::vector<T>& arr, T val)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        if (arr[index] == val)
            return static_cast<int>(index);
    }

    return -1; // -1 is not a valid index, so we can use it as an error return value
}

// Passing in low and high allows the compiler to infer the type of the input we want
template <typename T>
T getValidNumber(std::string_view prompt, T low, T high)
{
    // First, read in valid input from user
    T val {};
    do
    {
        std::cout << prompt;
        std::cin >> val;

        // if the user entered an invalid character
        if (!std::cin)
            std::cin.clear(); // reset any error flags

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extra characters in the input buffer (regardless of whether we had an error or not)

    } while (val < low || val > high);

    return val;
}

int main()
{
    std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };

    auto num { getValidNumber("Enter a number between 1 and 9: ", 1.0, 9.0) };

    printArray(arr);

    int index { findIndex(arr, num) };

    if (index != -1)
        std::cout << "The number " << num << " has index " << index << '\n';
    else
        std::cout << "The number " << num << " was not found\n";

    return 0;
}
*/