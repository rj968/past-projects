#include <functional>
#include <iostream>
#include <limits>

using AritmeticFunction = std::function<int(int,int)>;

void clearLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

int getInt()
{
    int input{};
    std::cout << "Enter an integer: ";
    while(true)
    {
        std::cin >> input;
        if(!std::cin)
        {
            std::cin.clear();
            clearLine();
            std::cout << "Invalid input! Try again: ";
            continue;
        }
        clearLine();
        return input;
    }
}

char getOperator()
{
    char sign {};
    do 
    {
        std::cout << "Enter a operator (+,-,*,/): ";
        std::cin >> sign;
        if(!std::cin)
        {
            std::cin.clear();
            clearLine();
            std::cout << "Invalid input! Try again: ";
            continue;
        }
    } while(sign != '+' && sign != '-' && sign != '*' && sign != '/' );
    return sign;
}

int add    (int x, int y) {return x+y;}
int sub    (int x, int y) {return x-y;}
int mult   (int x, int y) {return x*y;}
int divide (int x, int y) {return x/y;}

AritmeticFunction getArithmeticFunction(const char op)
{
    switch(op)
    {
        case '+': return &add;
        case '-': return &sub;
        case '*': return &mult;
        case '/': return &divide;
    }
    return nullptr;
}

int main()
{
    int x{getInt()};
    char op{getOperator()};
    int y{getInt()};

    AritmeticFunction func = getArithmeticFunction(op);
    std::cout << x <<' ' << op << ' ' << y << " = " << func(x,y) << '\n';
}