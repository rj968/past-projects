
#include <iostream>
#include <string>
#include <string_view>


class Fruit
{
private:
	std::string m_name {};
	std::string m_color {};

public:
	Fruit(std::string_view name="", std::string_view color="")
	:	m_name {name}, m_color {color}
	{
	}

	// NOT NEEDED
	// Fruit(std::string_view color)
	// : Fruit("", color)
	// {
	// }

	std::string_view getName() const {return m_name;}
	std::string_view getColor() const {return m_color;}
};

class Apple : public Fruit
{
public:
	Apple(std::string_view name = "Apple",std::string_view color = "red")
	: Fruit(name,color)
	{
	}
};

class GrannySmith : public Apple
{
public:
	GrannySmith(std::string_view color = "green")
	: 	Apple("Granny Smith apple",color)
	{
	}
};

class Banana : public Fruit
{
public:
	Banana(std::string_view name = "Banana", std::string_view color = "Yellow")
	:	Fruit(name,color)
	{
	}
};



int main()
{
	Apple a{ "red" };
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}