#include <iostream>
struct Ad
{
    int views {};
    double clicks {};
    double earnings {};
};

void printAd(Ad ad)
{
    std::cout << "Ads Watched: " << ad.views << ".\n";
    std::cout << "clicks through rate: " << ad.clicks << "%.\n";
    std::cout << "Average earnings per ad: $" << ad.earnings << ".\n";
    std::cout << "Earnings for the day: $" << ad.views * ad.clicks * ad.earnings << ".\n";
}

Ad getAd()
{
    Ad temp{};
    std::cout << "Enter the number of ads watched: ";
    std::cin >> temp.views;
    std::cout << "Enter the click through rate: ";
    std::cin >> temp.clicks;
    std::cout << "Enter the average earnings: ";
    std::cin >> temp.earnings;
    return temp;
}

int main()
{
    Ad day1 {getAd()};
    printAd(day1);
    return 0;
}