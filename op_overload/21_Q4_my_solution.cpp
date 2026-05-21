#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <istream>
#include <ostream>

namespace Settings 
{
	int fixedPoint {2};
}

class FixedPoint2
{
private:
	std::int16_t m_numerical{};
	std::int8_t m_decimal{};

public:
	FixedPoint2(double num);

	friend bool operator==(const FixedPoint2& p1, const FixedPoint2& p2);
	friend FixedPoint2 operator+(const FixedPoint2& p1, const FixedPoint2 p2);

	friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& p);
	friend std::istream& operator>> (std::istream& in, const FixedPoint2& p);

	operator double() const 
	{
		return m_numerical + ( static_cast<double>(m_decimal) / std::pow(10, Settings::fixedPoint) );
	}
	
	FixedPoint2 operator-()
	{
		return FixedPoint2 {-static_cast<double>(*this)};
	}
};

FixedPoint2::FixedPoint2(double num)
{
	// We assign the decimal digits to the required precision
	int number = std::round(num*pow(10,Settings::fixedPoint)); // rounding for precision
	
	
	for(int i {0}; i < Settings::fixedPoint; ++i)
	{
		m_decimal += ((number % 10) * std::pow(10,i)) ; 
		number /= 10;
	}

	// adding the numerical part
	for(int i {0}; std::abs(number) > 0; ++i)
	{
		m_numerical += (number % 10) * std::pow(10,i);
		number/=10;
	}
}

std::istream& operator>> (std::istream& in, FixedPoint2& p)
{
	double temp{};
	in >> temp;
	p = FixedPoint2{temp};
	return in;
}

std::ostream& operator<< (std::ostream& out, const FixedPoint2& p)
{
	out << p.m_numerical << "." << +p.m_decimal;
	return out;
}

bool operator==(const FixedPoint2& p1, const FixedPoint2& p2)
{
	return p1.m_numerical == p2.m_numerical && p1.m_decimal == p2.m_decimal;
}

FixedPoint2 operator+(const FixedPoint2& p1, const FixedPoint2 p2)
{
	return FixedPoint2 {static_cast<double>(p1) + static_cast<double>(p2)};
}


/* TEST 1
#include <cassert>
#include <iostream>

int main()
{
	FixedPoint2 a{ 0.01 };
	assert(static_cast<double>(a) == 0.01);

	FixedPoint2 b{ -0.01 };
	assert(static_cast<double>(b) == -0.01);

	FixedPoint2 c{ 1.9 }; // make sure we handle single digit decimal
	assert(static_cast<double>(c) == 1.9);

	FixedPoint2 d{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	assert(static_cast<double>(d) == 5.01);

	FixedPoint2 e{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	assert(static_cast<double>(e) == -5.01);

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 f { 106.9978 }; // should be stored with base 107 and decimal 0
	assert(static_cast<double>(f) == 107.0);

	// Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
	FixedPoint2 g { -106.9978 }; // should be stored with base -107 and decimal 0
	assert(static_cast<double>(g) == -107.0);

	return 0;
}
*/ // TEST 1


/* TEST 2
int main()
{
	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);

	return 0;
}
*/ // TEST 2