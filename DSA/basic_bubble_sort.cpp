#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <utility>
int main()
{
    int arr[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr std::size_t length{std::size(arr)};
    for(auto e: arr)
        std::cout << e << " ";
    std::cout <<'\n';
    for(std::size_t i = 0; i < length-1 ;i++)
    {
        bool sorted{true};
        for(std::size_t j = 0; j < length-i-1; j++)
            if(arr[j]>arr[j+1])
            {
                std::swap(arr[j],arr[j+1]);
                sorted = false;
            }
        if(sorted)
        {
            std::cout << "Early termination on iteration " << i+1 << '\n';
            break;
        }

        for(auto e: arr)
            std::cout << e << " ";
        std::cout << '\n';
    }
    for(auto e: arr)
        std::cout << e << " ";
    std::cout <<'\n';
}