#include <iostream>
#include <string>

int fact(int x)
{
    if(x<=0) return 1;
    return fact(x-1) * x;
}

int sumOfDigits(int x)
{
    if(x/10==0) return x;
    return sumOfDigits(x/10) + (x%10);
}

void intToBin(unsigned int x)
{
    if(x<2)
    {
        std::cout << x%2;
        return;
    } 
    intToBin(x/2);
    std::cout<<x%2;
}

int main()
{
    int input{-15};
    intToBin(input);
    std::cout << '\n';
    return 0;
}