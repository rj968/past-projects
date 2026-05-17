#include <iostream>
template <typename T>
struct Triad
{
    T a{};
    T b{};
    T c{};
};

// If using C++17, we need to provide a deduction guide (not required in C++20)
// A Triad with three arguments of the same type should deduce to a Triad<T>:

// template <typename T>
// Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const Triad<T>& t)
{
    std::cout << "[" << t.a << ", " << t.b << ", " << t.c << "]\n";
}

int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}