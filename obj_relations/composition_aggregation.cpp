#include <algorithm>
#include <functional>
#include <iostream>

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>

class Teacher
{
private:
  std::string m_name{};

public:
  Teacher(std::string_view name)
      : m_name{ name }
  {
  }

  const std::string& getName() const { return m_name; }
};

class Department
{
private:
	std::vector<std::reference_wrapper<const Teacher>> m_teacher{};

public:
  Department() = default;

  void add(const Teacher& teacher)
  {
	m_teacher.emplace_back(teacher);
  }

  friend std::ostream& operator<<(std::ostream& out, const Department& department)
  {
	out << "Department: ";
	for(auto teacher: department.m_teacher)
	{
		out << teacher.get().getName() << ' ';
	}
	out << '\n';
	return out;
  }
};

int main()
{
  // Create a teacher outside the scope of the Department
  Teacher t1{ "Bob" };
  Teacher t2{ "Frank" };
  Teacher t3{ "Beth" };

  {
    // Create a department and add some Teachers to it
    Department department{}; // create an empty Department

    department.add(t1);
    department.add(t2);
    department.add(t3);

    std::cout << department;

  } // department goes out of scope here and is destroyed

  std::cout << t1.getName() << " still exists!\n";
  std::cout << t2.getName() << " still exists!\n";
  std::cout << t3.getName() << " still exists!\n";

  return 0;
}