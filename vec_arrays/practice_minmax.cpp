// ALL THE BAD DESIGNE CHOICES HERE:
// 1. Over complitcating the solution
// 2. Not separating the things into callable funtions
// 3. Not using a namespace for unscoped enum
// 4. Over complicating the solution and spelling complicating wrong the first time
// 5. Handle error handling for input
// 6. Akward use of enum

// Given solution at end

#include <cstddef>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

enum Structure
{
    index,value
};
template <typename T>
struct Postion
{
    std::pair<int,T> min {};
    std::pair<int,T> max {};
};

template <typename T>
constexpr std::size_t toUZ(T a)
{
    static_assert(std::is_integral<T>() || std::is_enum<T>());
    return static_cast<std::size_t>(a);
}


template<typename T>
Postion<T> minMax(const std::vector<T>& vector)
{
    Postion<T> postion {
        {0,vector[0]},
        {0,vector[0]}
    };

    for(int i = 0; toUZ(i) < vector.size(); i++)
    {
        if(vector[toUZ(i)] > std::get<value>(postion.max))
            postion.max = {i,vector[toUZ(i)]};
        else if (vector[toUZ(i)] < std::get<value>(postion.min))
            postion.min = {i,vector[toUZ(i)]}; 
    }
    return postion;
}

template <typename T>
std::ostream& operator<<(std::ostream& os,const std::vector<T>& vector)
{
    for(int i = 0; toUZ(i) + 1 < std::size(vector);++i)
        os << vector[toUZ(i)] << ", ";
    os << vector[std::size(vector)-1];
    return os;
}

template <typename T>
void solution(const std::vector<T>& v1)
{
    if(v1.size()==0)
    {
        std::cout << "The array has no elements.\n";
        return;
    }
    std::cout << "With array ( " << v1 << " ):\n";
    Postion position { minMax(v1)};
    std::cout << "The min element has index " << std::get<index>(position.min) 
    << " and value " << std::get<value>(position.min) << ".\n";
    std::cout << "The max element has index " << std::get<index>(position.max) 
    << " and value " << std::get<value>(position.max) << ".\n";
}


std::vector<int> getInput()
{
    std::vector<int> input{};
    std::cout << "Enter numbers to add (use -1 to stop): ";
    int temp{};
    do 
    {
        std::cin >> temp;
        input.push_back(temp);
    } while (temp!=-1);
    input.pop_back();
    return input;
}

int main()
{
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    solution(v1);
    solution(v2);
    solution(getInput());
    return 0;      
}

/*
#include <iostream>
#include <vector>

template <typename T>
std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
{
    // Assume element 0 is the minimum and the maximum
    std::size_t minIndex { 0 };
    std::size_t maxIndex { 0 };

    // Look through the remaining elements to see if we can find a smaller or larger element
    for (std::size_t index { 1 }; index < v.size(); ++index)
    {
        if (v[index] < v[minIndex])
            minIndex = index;
        if (v[index] > v[maxIndex])
            maxIndex = index;
    }

    return { minIndex, maxIndex };
}

template <typename T>
void printArray(const std::vector<T>& v)
{
    bool comma { false };
    std::cout << "With array ( ";
    for (const auto& e: v)
    {
        if (comma)
            std::cout << ", ";

        std::cout << e;
        comma = true;
    }
    std::cout << " ):\n";
}

int main()
{
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    printArray(v1);

    auto m1 { findMinMaxIndices(v1) };
    std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
    std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

    std::cout << '\n';

    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    printArray(v2);

    auto m2 { findMinMaxIndices(v2) };
    std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
    std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';

    return 0;
}
*/