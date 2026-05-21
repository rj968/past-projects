
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>

class IntArray
{
private:
	int m_lenght{0};
	int* m_array{};

public:
	// Default constructor
	IntArray(int length = 0)
	{
		assert(length > 0);
		if(length > 0)
		{
			m_array = new int[static_cast<std::size_t>(length)]{};
			m_lenght = length;
		}
	}

	// Copy constructor for a deep copy
	IntArray(const IntArray& arr)
	{
		// DON'T USE THIS METHOD AS IT CREATES UNNECESSARY COPIES AND OVERHEAD
		// *this = arr; // We use the overloaded operator= here
		assert(arr.m_lenght);
		
		m_lenght = arr.m_lenght;
		m_array = new int[static_cast<std::size_t>(arr.m_lenght)] {};

		for (int i {0}; i < m_lenght; ++i)
			m_array[i] = arr.m_array[i];
	}

	// defining overloaded operator= for a deep copy
	IntArray& operator=(const IntArray& arr);

	// Destructor
	~IntArray()
	{
		delete[] m_array;
	}

	int getLength() const {return m_lenght;}

	int& operator[](int index);

};

int& IntArray::operator[](int index)
{
	assert(index >= 0 && index<m_lenght && "Invalid Index");
	return m_array[static_cast<std::size_t>(index)];
}

IntArray& IntArray::operator=(const IntArray& arr)
{
	if(this != &arr) // self assignment guard
	{
		assert(arr.m_array != nullptr && arr.m_lenght > 0); // validating array
		
		if(m_array){delete[] m_array;} // deleting any previous data

		m_array = new int[static_cast<std::size_t>(arr.m_lenght)]{};
		m_lenght = arr.m_lenght;
		
		for(int i {0}; i < m_lenght; ++i)
			m_array[i] = arr.m_array[i];
	}
	
	return *this;
}

std::ostream& operator<<(std::ostream& out, IntArray& arr)
{
	int length = arr.getLength();
	if(length>0)
	{
		for(int i {0}; i < length; ++i)
			out << arr[i] << ' '; 
	}
	return out;
}


IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}