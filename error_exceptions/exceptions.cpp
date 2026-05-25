#include <ostream>
#include <iostream>
#include <stdexcept>

class Fraction
{
public:

    Fraction(int numerator = 0, int denominator = 1)
    :   m_numerator{numerator}, m_denominator{denominator}
    {
        if(m_denominator == 0)
            throw std::runtime_error{"Invalid Denominator.\n"};
    }

    int getNum() const {return m_numerator;}
    int getDen() const {return m_denominator;}

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.getNum() << "/" << fraction.getDen();
        return out;
    }

private:
    int m_numerator{0};
    int m_denominator{1};
};

int main()
{
    std::cout << "Enter the numerator: ";
    int num{}; std::cin >> num;
    
    std::cout << "Enter the denominator: ";
    int den{}; std::cin >> den;
    
    try
    {
        Fraction fraction{num,den} ;
        std::cout << fraction << '\n';
    }
    catch(const std::exception& exception)
    {
        std::cerr << exception.what();
    }
    
    return 0;
}