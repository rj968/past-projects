// RANGED BASED FOR LOOPS

#include <iostream>
#include <string_view>
#include <string>
#include <vector>

template <typename T>
bool isValueInArray(const std::vector<T>& vector, const T& input)
{
    for(const auto& element: vector)
    {
        if(element == input)
            return true;
    }
    return false;
}

int main()
{
    std::vector<std::string_view> names {"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};
    std::cout << "Enter a name: ";
    std::string input{};
    std::cin >> input;
    bool output = false;
    if(isValueInArray<std::string_view>(names, input))
        std::cout << input << " was found.\n";
    else
        std::cout << input << " was not found.\n";
    return 0;
}
