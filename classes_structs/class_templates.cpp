/*Write a class template named Triad that has 3 private data members with
 independent type template parameters. The class should have a constructor,
 access functions, and a print() member function that is defined outside the class.*/
#include <string>
#include <iostream>

template <typename T, typename U, typename V>
class Triad
{
public:
    Triad(const T& x1, const U& x2, const V& x3)
        :
        m_x1 {x1},
        m_x2 {x2},
        m_x3 {x3}
    {
    }

    const T& first() const {return m_x1;}
    void setX1(T& x1){m_x1 = x1;}
    
    const T& second() const {return m_x2;}
    void setX2(T& x2){m_x1 = x2;}
    
    const T& third() const {return m_x3;}
    void setX3(T& x3){m_x1 = x3;}

    void print() const;
private:
    T m_x1 {};
    U m_x2 {};
    V m_x3 {};

};

template <typename T, typename U, typename V>
void Triad<T,U,V>::print() const
{
    std::cout << "[" << m_x1 << ", " << m_x2 << ", " << m_x3 << "]";
}

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}