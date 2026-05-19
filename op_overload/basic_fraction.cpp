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
            m_numerator/=gcd; m_denominator/=gcd;
            // ensure denominator is positive
            if (m_denominator < 0) {
                m_numerator = -m_numerator;
                m_denominator = -m_denominator;
            }
        }
    }
    
    friend Fraction operator* (const Fraction& x, const Fraction& y);
    friend Fraction operator* (const Fraction& x, int y);
    friend Fraction operator* (int x, const Fraction& y);

    friend bool operator== (const Fraction& a, const Fraction& b);
    friend bool operator< (const Fraction& a, const Fraction& b);

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
    return Fraction{y.m_numerator * x, y.m_denominator};
}

// comparison operators
bool operator== (const Fraction& a, const Fraction& b)
{
    return a.m_numerator == b.m_numerator && a.m_denominator == b.m_denominator;
}

bool operator!= (const Fraction& a, const Fraction& b)
{
    return !(a == b);
}

bool operator< (const Fraction& a, const Fraction& b)
{
    return (static_cast<double>(a.m_numerator) / a.m_denominator) < (static_cast<double>(b.m_numerator) / b.m_denominator);
}

bool operator> (const Fraction& a, const Fraction& b)
{
    return b < a;
}

bool operator<= (const Fraction& a, const Fraction& b)
{
    return !(b < a);
}

bool operator>= (const Fraction& a, const Fraction& b)
{
    return !(a < b);
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
	Fraction f1{ 3, 2 };
	Fraction f2{ 5, 8 };

	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
	std::cout << f1 << ((f1 < f2)  ? " < "  : " not < " ) << f2 << '\n';
	std::cout << f1 << ((f1 > f2)  ? " > "  : " not > " ) << f2 << '\n';
	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
	return 0;
}