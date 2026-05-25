#include "Random.h"
#include <cstdint>
#include <limits> // for std::numeric_limits
#include <iostream>

namespace Constants {
    constexpr int maxTries {7};
}
namespace {
    uint16_t g_max {100};
    uint16_t g_min {0};
    uint16_t g_numberOfTries {7};
}

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }
        
        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

int getGuess(const int guessNumber)
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "\nGuess #" << guessNumber << "/" << g_numberOfTries << ": ";
        int x{};
        std::cin >> x;
        
        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

uint16_t getUint16()
{
    while (true) // Loop until user enters a valid input
    {
        int x{};
        std::cin >> x;
        if (clearFailedExtraction() || x < 0 || x > UINT16_MAX)
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return static_cast<uint16_t>(x);     // Return the value we extracted
    }
}


char getChoice()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter 'y' for YES and 'n' for NO: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)
        // Check whether the user entered meaningful input
        switch (operation)
        {
        case 'y':
        case 'n':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
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

void showSettings()
{
    std::cout << "\nMin: " << g_min << ". Max: " << g_max << ". Maximum number of tries: " 
    << g_numberOfTries << ".\n";
}

void setGameSetting()
{
    showSettings();
    std::cout << "Do you want to change game settings?(y/n): ";
    char choice {getChoice()};
    if(choice == 'y')
    {
        std::cout << "Enter the min value: ";
        int temp_g_min {getUint16()};
        std::cout << "Enter the max value: ";
        int temp_g_max {getUint16()};
        if (temp_g_max<=temp_g_min)
        {
            std::cout << "Invalid values entered. Using previous settings\n";
        }
        else
        {
            g_min = temp_g_min;
            g_max = temp_g_max;
        }

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
        else
            break;
    }
    
    return 0;
}