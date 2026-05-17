// 2 PROBLEMS HERE

// #include <algorithm>
// #include <array>
// #include <functional>
// #include <iostream>
// #include <string_view>

// struct Student
// {
//     std::string_view name{};
//     int points{};
// };

// int main()
// {
//     std::array<Student, 8> arr{
//     { { "Albert", 3 },
//         { "Ben", 5 },
//         { "Christine", 2 },
//         { "Dan", 8 }, // Dan has the most points (8).
//         { "Enchilada", 4 },
//         { "Francis", 1 },
//         { "Greg", 3 },
//         { "Hagrid", 5 } }
//     };

//     auto greater {
//         [](const Student& x, const Student& y)
//         {
//             return x.points<y.points;
//         }
//     };

//     const auto foo(std::max_element(arr.begin(),arr.end(),greater));
//     std::cout << foo->name << '\n';
//     return 0;
// }

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

struct Season
{
  std::string_view name{};
  double averageTemperature{};
};

int main()
{
  std::array<Season, 4> seasons{
    { { "Spring", 285.0 },
      { "Summer", 296.0 },
      { "Fall", 288.0 },
      { "Winter", 263.0 } }
  };

   std::sort(seasons.begin(),seasons.end(),
        [](const auto& x, const auto& y){
            return x.averageTemperature < y.averageTemperature;
        }
    );

  for (const auto& season : seasons)
  {
    std::cout << season.name << '\n';
  }

  return 0;
}
