/*
In this quiz, implement the game as follows:
    Numbers divisible by only 3 should print “fizz”.
    Numbers divisible by only 5 should print “buzz”.
    Numbers divisible by only 7 should print “pop”.
    Numbers divisible by only 11 should print “bang”.
    Numbers divisible by only 13 should print “jazz”.
    Numbers divisible by only 17 should print “pow”.
    Numbers divisible by only 19 should print “boom”.
Numbers divisible by more than one of the above should print 
each of the words associated with its divisors.
Numbers not divisible by any of the above should just print the number.

Use a std::vector to hold the divisors, and another std::vector to hold
the words (as type std::string_view). If the arrays do not have the same
length, the program should assert. Produce output for 150 numbers.
*/

#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

int main()
{
    std::vector<int> divisors{3,5,7,11,13,17,19};
    std::vector<std::string_view> words{"fizz","buzz","pop","bang","jazz","pow","boom"};
    assert(divisors.size()==words.size() && "lengths don't match.");
    
    for(int i = 1; i <= 150; ++i)
    {
        int val = 0;
        for(std::size_t index = 0; index < divisors.size(); ++index)
        {
            if(i%divisors[index]==0)
            {
                std::cout << words[index]; 
                ++val;
            }
        }
        if(!val)
            std::cout << i;
        std::cout << '\n';
    }
    
    return 0;
}