// TODO
// 1. bool static variable in a checker function for correct letters entered
// 2. loop which prompts for guesses again and again
// 3. keep track of guesses using the member variable and checking if the guess was entered
// 4. play again logic
// 5. arragange wrong guesses in ascending order

#include "Random.h"

#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


namespace WordList{
    std::vector<std::string_view> words {
    "mystery",
    "broccoli" ,
    "account", 
    "almost", 
    "spaghetti", 
    "opinion",
    "beautiful", 
    "distance", 
    "luggage"
    };
    std::string_view pickRandomWord ()
    {
        return words[Random::get(0,words.size()-1)];
    }
}

class Session
{
public:
    Session(int guesses=7)
        :
        m_lives {guesses},
        m_answer {WordList::pickRandomWord()}
    {
        for([[maybe_unused]]auto e: m_answer)
            m_checker.push_back(0);
    }

    void beginSession() ;

private:
    bool playGame();
    bool displayWord() const;
    void displayWrongAnswers() const;
    char getLetter();
    void checkAnswer(const char guess);

    int m_lives {7};
    std::string m_answer {};
    std::string m_wrongAnswers {}; 
    std::string m_guesses{};
    std::vector<char> m_checker{};
};

void Session::beginSession()
{
    std::cout << "Welcome to C++man (a variant of Hangman).\n";
    std::cout << "To win: guess the word. To lose: run out of pluses.\n";
    playGame();
}

bool Session::playGame()
{
    do
    {
        bool state = displayWord();
        std::cout << '\t';
        displayWrongAnswers();
        std::cout << '\n';
        if(state)
        {
            std::cout << "You win. The answer was " << m_answer << ".\n";
            return true;
        }
        checkAnswer(getLetter());
    } while(m_lives);
    std::cout << "You lost. The word was: " << m_answer << ".\n";
    return false;
}

void Session::checkAnswer(const char guess)
{
    bool guessInWord {false};
    for(std::size_t i{0}; i < m_answer.size(); ++i)
    {
        if(guess == m_answer[i])
        {
            m_checker[i] = true;
            guessInWord = true;
        }
    }
    if(guessInWord) std::cout << "Yes, '" << guess << "' was in the word!\n";
    else
    {
        std::cout << "No, '" << guess << "' was not in the word!\n";
        m_wrongAnswers.push_back(guess);
        --m_lives;
    }
}

void Session::displayWrongAnswers() const
{
    std::cout << "Wrong guesses: ";
    for(std::size_t i = 0; i < static_cast<std::size_t>(m_lives); ++i)
        std::cout << '+';
    std::cout << m_wrongAnswers;
}

bool Session::displayWord() const
{
    bool win {true};
    std::cout << "The word: ";
    for(std::size_t i = 0; i < m_answer.size(); ++i)
    {
        if(m_checker[i]==1)
            std::cout << m_answer[i];
        else
        {
            std::cout << '_';
            win = false;
        }
    }
    return win;    
}

char Session::getLetter() 
{
    char letter;
    while (true)
    {
        bool breakLoop {false};
        std::cout << "Enter your next letter: ";
        std::cin >> letter;
        letter = std::tolower(letter);
        if(!std::cin || letter < 'a' || letter > 'z')
        {
            std::cout << "That was an invalid input.\tTry again.\n";
            breakLoop = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        for(auto e: m_guesses)
        {
            if(e==letter)
            {
                std::cout<<"You already guessed that.\tTry again\n";
                breakLoop = true;
            }
        }
        if(!breakLoop)
            break;
    }
        m_guesses.push_back(letter);
        return letter;
}

int main()
{
    Session session{};
    session.beginSession();
    return 0;
}

