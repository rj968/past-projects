
#include "Random.h"
#include <cstdint>
#include <iostream>

namespace Constants {
    constexpr int maxTries {7};
}
namespace {
    uint16_t g_max {100};
    uint16_t g_min {0};
    uint16_t g_numberOfTries {7};
}

int getGuess(const int guessNumber)
{
    std::cout << "\nGuess #" << guessNumber << "/" << g_numberOfTries << ": ";
    int x;
    std::cin >> x;
    return x;
}

bool checkAnswer(const int guess, const int answer)
{
    if (guess > answer)
    {
        std::cout << "Your guess is too high.\n";
        return false;
    }
    else if (guess < answer)
    {
        std::cout << "Your guess is too low.\n";
        return false;
    }
    else
    {
        std::cout << "Correct! You win!\n";
        return true;
    }
}

uint16_t getUint16()
{
    uint16_t x;
    std::cin >> x;
    return x;
}

void showSettings()
{
    std::cout << "\nMin: " << g_min << ". Max: " << g_max << ". Maximum number of tries: " 
    << g_numberOfTries << ".\n";
}

void setGameSetting()
{
    showSettings();
    std::cout << "Do you want to change game settings?(y/n): ";
    char choice;
    std::cin >> choice;
    if(choice == 'y')
    {
        std::cout << "Enter the min value: ";
        g_min = getUint16();
        std::cout << "Enter the max value: ";
        g_max = getUint16();
        std::cout << "Enter the maximum number of tries: ";
         g_numberOfTries = getUint16();
        showSettings();
    }
}

void playGame()
{
    int answer {Random::get(g_min,g_max)};
    for (int i = 0; i < g_numberOfTries; ++i)
    {
        int guess {getGuess(i+1)};
        if(checkAnswer(guess, answer))
            return;
    }
    std::cout << "\nSorry, you lose. The correct number was " << answer << ".\n";
}

int main()
{
    std::cout << "Let's play a game. I'm thinking of a number between "
    << g_min << " and " << g_max << ". You have " << g_numberOfTries
    << " tries to guess what it is.\n";
    setGameSetting();
    while (true)
    {
        playGame();
        std::cout << "Would you like to play again (y/n)? ";
        char choice {};
        std::cin >> choice;
        if(choice == 'y')
            continue;
        else if (choice == 'n')
            break;
    }
    
    return 0;
}