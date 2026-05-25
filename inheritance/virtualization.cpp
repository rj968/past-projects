#include <vector>
#include <iostream>
#include <algorithm> // for std::max
#include <memory>

class Point
{
private:
	int m_x{};
	int m_y{};

public:
	Point(int x, int y)
		: m_x{ x }, m_y{ y }
	{

	}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
	}
};

class Shape
{
public:
	virtual std::ostream& print(std::ostream& out) const = 0;

	friend std::ostream& operator<<(std::ostream& out, const Shape& p)
	{
		return p.print(out);
	}
	virtual ~Shape() = default;
};

class Triangle : public Shape
{
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;

public:
	Triangle(const Point& p1, const Point& p2, const Point& p3)
		: m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
	{
	}

	std::ostream& print(std::ostream& out) const override
	{
		return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
	}
};


class Circle : public Shape
{
private:
	Point m_center;
	int m_radius{};

public:
	Circle(const Point& center, int radius)
		: m_center{ center }, m_radius{ radius }
	{
	}

	std::ostream& print(std::ostream& out) const override
	{
		out << "Circle(" << m_center << ", radius " << m_radius << ')';
		return out;
	}

	int getRadius() const { return m_radius; }
};

int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& v)
{
	int largestRadius{ 0 };

	// Loop through all the shapes in the vector
	for (const auto& element : v)
	{
		// // Ensure the dynamic cast succeeds by checking for a null pointer result
		if (auto *c { dynamic_cast<const Circle*>(element.get()) })
		{
			largestRadius = std::max(largestRadius, c->getRadius());
		}
	}

	return largestRadius;
}
int main()
{
	std::vector<std::unique_ptr<Shape>> v;
	v.reserve(3);
	v.push_back(std::make_unique<Circle>(Point{1, 2}, 7));
	v.push_back(std::make_unique<Triangle>(Point{1, 2}, Point{3, 4}, Point{5, 6}));
	v.push_back(std::make_unique<Circle>(Point{7, 8}, 3));

	for (const auto& element : v) std::cout << *element << '\n';

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
}