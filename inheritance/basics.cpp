#include <ostream>
#include <string>
#include <string_view>
class Fruit
{
private:
	std::string m_name{};
	std::string m_color{};

public:
	Fruit(std::string_view name="", std::string_view color = "")
	:	m_name {name}, m_color{color}
	{
	}
	
	std::string_view getName() const {return m_name;}
	std::string_view getColor() const {return m_color;}
};

class Apple : Fruit
{
private:
	double m_fiber{};
public:
	Apple(std::string_view name, std::string_view color, double fiber)
	:	Fruit{name, color},
		m_fiber{fiber}
	{
	}

	double getFiber() const {return m_fiber;}

	friend std::ostream& operator<<(std::ostream& out, const Apple& apple)
	{
		out << "Apple(" << apple.getName() << ", " << apple.getColor() << ", " << apple.getFiber() << ")";
		return out;
	}
};

class Banana : Fruit
{
public:
	Banana(std::string_view name, std::string_view color)
	:	Fruit {name, color}
	{
	}
	friend std::ostream& operator<< (std::ostream& out, const Banana& banana)
	{
		out << "Banana(" << banana.getName() << ", " << banana.getColor() << ")";
		return out;
	}
};

#include <iostream>

int main()
{
	const Apple a{ "Red delicious", "red", 4.2 };
	std::cout << a << '\n';

	const Banana b{ "Cavendish", "yellow" };
	std::cout << b << '\n';

	return 0;
}