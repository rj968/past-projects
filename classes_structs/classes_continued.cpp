#include <iostream>

class Fraction
{

public:
    explicit Fraction(int numerator = 0, int denominator = 1)
        :
        m_numerator {numerator},
        m_denominator {denominator}
    {
    }

    void getFraction();

    void setNumerator (int numerator) {m_numerator = numerator;}
    void setDenominator (int denominator) {m_denominator = denominator;}

    int getNumerator() const {return m_numerator;}
    int getDenominator() const {return m_denominator;}

    void printFraction() const;
    Fraction multiply(const Fraction& f2);

private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
};


// Make this a member function and just std::cin >> m_num etc
// this reduces the need to create 2 temp vars and makes the code more concise
// NOTE: my previous attempt used set functions and temp vars to return a fraction object
// Though my attempt may be favoured as it allows the user to directly create an object 
// instead of first declaring it and then defining it
void Fraction::getFraction()
{
    std::cout << "Enter a value for numerator: ";
    std::cin >> m_numerator;
    std::cout << "Enter a value for denominator: ";
    std::cin >> m_denominator;
}

Fraction Fraction::multiply(const Fraction& f2)
{
    return Fraction{ getNumerator() * f2.getNumerator(), getDenominator() * f2.getDenominator() };
}

void Fraction::printFraction() const
{
    std::cout << getNumerator() << '/' << getDenominator() << '\n';
}

int main()
{
    Fraction f1 {};
    f1.getFraction();
    Fraction f2 { };
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";

    f1.multiply(f2).printFraction();

    return 0;
}