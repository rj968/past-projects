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

    friend std::ostream& operator<< (std::ostream& out, const Fraction& fraction);
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

std::ostream& operator<< (std::ostream& out, const Fraction& fraction)
{
    out << fraction.m_numerator << "/" << fraction.m_denominator;
    return out;
}

std::istream& operator>> (std::istream& in, Fraction& fraction)
{
    int num{};
    int den{};
    char foo{};
    in >> num >> foo >> den;
    if(den==0)
    {
        in.setstate(std::ios_base::failbit);
    }
    if(in)
        fraction = Fraction{num,den};
    return in;
}

int main()
{
	Fraction f1{};
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2{};
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value

	return 0;
}