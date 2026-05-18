#include <cassert>
#include <iostream>
#include <numeric>

class Fraction 
{
private: 
    int m_numerator {0};
    int m_denominator {1};
public:
    explicit Fraction(int numerator = 0, int denominator = 1)
        :
        m_numerator {numerator},
        m_denominator{denominator}
        {
            assert(denominator !=0 && "Denominator cannot be 0.");
            reduce();
        }

    void print() const {std::cout << m_numerator << "/" << m_denominator << '\n';}

    void reduce() {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd)
        {
            m_numerator/=gcd;m_denominator/=gcd;
        }
    }

    friend Fraction operator* (const Fraction& x, const Fraction& y);
    friend Fraction operator* (const Fraction& x, int y);
    friend Fraction operator* (int x, const Fraction& y);
};

Fraction operator* (const Fraction& x, const Fraction& y)
{
    return Fraction {x.m_numerator * y.m_numerator, x.m_denominator * y.m_denominator};
}

Fraction operator* (const Fraction& x, int y)
{
    return Fraction {x.m_numerator * y, x.m_denominator};
}

Fraction operator* (int x, const Fraction& y)
{
    return Fraction{y * x};
}

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();

    return 0;
}