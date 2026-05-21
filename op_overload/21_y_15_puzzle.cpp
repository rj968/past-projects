// THINGS TO IMPROVE
// 1. Separating code into files
// 2. make more use of functions for readability
// 3. treating main as a main logic stream
// 4. applying const, constexpr and static wherever helpful

#include "Random.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <ostream>
#include <utility>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

// helper class Direction
class Direction
{
public:
	enum Type
	{
		up,down,left,right,
		max_direction,
	};

	Direction(Type direction) : m_direction{direction}
	{
	}

	Type getDirection() {return m_direction;}

	Direction operator-();
	friend std::ostream& operator<<(std::ostream& out, const Direction& direction);

	static Direction generateRandomDirection();

private:
	Type m_direction{};
};

Direction Direction::operator-()
{
	switch (m_direction) {
	case up: return Direction{down};
	case down: return Direction{up};
	case left: return Direction{right};
	case right: return Direction{left};
	default: break;
	}
	assert(0 && "Unsupported direction was passed!");
    return Direction{ up };
}

std::ostream& operator<<(std::ostream& out, const Direction& direction)
{
	switch (direction.m_direction) {
	case Direction::up: out << "up"; return out;
	case Direction::down: out << "down"; return out;
	case Direction::left: out << "left"; return out;
	case Direction::right: out << "right"; return out;
	default: out<<"???";
	}
	return out;
}

Direction Direction::generateRandomDirection()
{
	auto dir {static_cast<Direction::Type>(Random::get(0,3))};
	return Direction{dir};
}

struct Point
{
int x{};
int y{};

friend bool operator==(const Point& p1, const Point& p2);
friend bool operator!=(const Point& p1, const Point& p2) {return !(operator==(p1,p2));}

Point getAdjacentPoint(Direction::Type direction);
};

bool operator==(const Point& p1, const Point& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

Point Point::getAdjacentPoint(Direction::Type direction)
{
	switch (direction) 
	{
		case Direction::up		: return Point{x-1  ,y};
		case Direction::down	: return Point{x+1  ,y};
		case Direction::left	: return Point{x  ,y-1};
		case Direction::right	: return Point{x  ,y+1};
		default: break;
	}
	assert(0 && "invalid direction entered");
	return *this;
}

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num { 0 };
};

std::ostream& operator<<(std::ostream& stream, Tile tile)
{
    if (tile.getNum() > 9) // if two digit number
        stream << " " << tile.getNum() << " ";
    else if (tile.getNum() > 0) // if one digit number
        stream << "  " << tile.getNum() << " ";
    else if (tile.getNum() == 0) // if empty spot
        stream << "    ";
    return stream;
}

class Board
{
public:

    Board() = default;

    friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space.
        for (int i = 0; i < g_consoleLines; ++i)
            std::cout << '\n';

        for (int y = 0; y < s_size; ++y)
        {
            for (int x = 0; x < s_size; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

	bool moveTile(Direction::Type direction);

	friend bool operator==(const Board& f1, const Board& f2)
    {
        for (int y = 0; y < s_size; ++y)
            for (int x = 0; x < s_size; ++x)
                if (f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
                    return false;

        return true;
    }

	// BETTER APPROACH BELOW
	// bool isSolved()
	// {
	// 	if(!m_tiles[3][3].isEmpty())
	// 		return false;
	// 	for(int i {0}; i < 4; ++i)
	// 	{
	// 		for(int j {0}; j < 4; ++j)
	// 		{
	// 			if(i == 3 && j == 3)
	// 				continue;
	// 			if (m_tiles[i][j].getNum() != 4*i + j + 1)
	// 				return false;
	// 		}
	// 	}
	// 	return true;
	// }
	bool isSolved() const
	{
		static Board s_solved{};
		return s_solved == *this;
	}


private:
    static constexpr int s_size { 4 };
    Tile m_tiles[s_size][s_size]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

bool Board::moveTile(Direction::Type direction)
{
	Point pos{};
	for (int i {0}; i < 4; ++i) 
	{
		for (int j {0}; j < 4; ++j)
		{
			if(m_tiles[i][j].isEmpty())
			{
				pos = Point {i,j};
			}
		}
	}
	Point adj{pos.getAdjacentPoint(direction)};
	if(adj.x >= 0 && adj.x < 4 && adj.y >= 0 && adj.y < 4)
	{
		std::swap(m_tiles[pos.x][pos.y],m_tiles[adj.x][adj.y]);
		return true;
	}
	return false;
}

namespace UserInput
{
	bool checkInput(char input)
	{
		switch (input) {
		case 'w':
		case 'a':
		case 's':
		case 'd':
		case 'q':
			return true;
		default: return false;
		}
	}

	Direction::Type getDirection(char input)
	{
		switch (input) {
		case 'w':	return Direction::up;
		case 's':	return Direction::down;
		case 'a':	return Direction::left;
		case 'd':	return Direction::right;
		case 'q': return Direction::max_direction;
		default: return Direction::max_direction;
		}
	}

	void clearLine() {std::cin.ignore(std::numeric_limits<std::size_t>::max(), '\n');}

	Direction::Type getUserInput()
	{
		char input{};
		while(true)
		{
			std::cin >> input;
			if(!std::cin)
			{
				std::cin.clear();
				clearLine();
				std::cout << "Invalid input. Try again: ";
				continue;
			}
			clearLine();
			if(checkInput(input))
				return getDirection(input);
		}
	}
}

int main()
{
    Board board{};
	
	std::cout << "Generating random board. ";
	for(int i {0}; i < 4; ++i)
	{
		board.moveTile(Direction::generateRandomDirection().getDirection());
	}
	
	std::cout << board;
	while (true)
	{
		Direction input{UserInput::getUserInput()};
		
		if(input.getDirection() == Direction::max_direction)
			break;
		if(board.moveTile(input.getDirection()))
			std::cout << board;
		if(board.isSolved())
		{
			std::cout << "\n\n You Won! \n\n";
			break;
		}
	}

	std::cout << "\n\n Bye! \n\n";

    return 0;
}