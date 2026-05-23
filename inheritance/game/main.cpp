#include "../Random.h"

#include "creature.hpp"
#include "monster.hpp"
#include "player.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <string_view>

enum class Move {
  run,
  fight,
  max_Move,
};

std::string getPlayerName() {
  std::cout << "Enter your name: ";
  std::string name{};
  std::cin >> name;
  return name;
}

void greetPlayer(const Player &player) {
  std::cout << "Welcome, " << player.getName() << ".\n";
  player.description();
}

void clearLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Move getMove() {
  std::cout << "(R)un or (F)ight: ";
  char c{};
  while (true) {
    std::cin >> c;
    if (!std::cin || std::cin.eof()) {
      std::cin.clear();
      clearLine();
      std::cout << "Invalid input. Try again: ";
      continue;
    }
    clearLine();
    if (c == 'r' || c == 'R')
      return Move::run;
    else if (c == 'f' || c == 'F')
      return Move::fight;
    else
      std::cout << "Invalid input, Try again: ";
  }
}

Move fightMonster(Move move) {
  if (move == Move::run) {
    if (Random::get(1,2) == 1) {
      std::cout << "You successfully fled.\n";
      return Move::run;
    } else {
      std::cout << "You failed to flee.\n";
      return Move::max_Move;
    }
  } else if (move == Move::fight)
    return Move::fight;
  return Move::max_Move;
}

void attackMonster(Player &player, Monster &monster) {
  monster.reduceHealth(player.getAttack());
  std::cout << "You hit " << monster.getName() << " for " << player.getAttack()
            << ".\n";
  if (monster.isDead()) {
    std::cout << "You killed the " << monster.getName() << ".\n";

    player.levelUp();
    std::cout << "You are now " << player.getLevel() << ".\n";

    std::cout << "You found " << monster.getGold() << ".\n";
    player.addGold(monster.getGold());
  }
}

void attackPlayer(Monster &monster, Player &player) {
  player.reduceHealth(monster.getAttack());
  std::cout << "The " << monster.getName() << " hit you for "
            << monster.getAttack() << " damage.\n";
}

int main() {
  Player player(getPlayerName());
  greetPlayer(player);

  while (player.getLevel() < 20) {
    Monster monster{Monster::getRandomMonster()};
    std::cout << "You have encountered a " << monster.getName() << " ("
              << monster.getSymbol() << ").\n";

    while (true) {
      std::cout << "The " << monster.getName() << " has " << monster.getHealth()
                << " health.\n";
      Move move = fightMonster(getMove());
      if (move == Move::fight) 
      {
        attackMonster(player, monster);
      } 
      else if (move == Move::run)
      {
        break;
      }

      if (monster.isDead())
        break;

      attackPlayer(monster, player);

      if (player.isDead())
        break;
    }
    if (player.isDead())
      break;
    std::cout << '\n';
    player.description();
  }

  if (player.isDead()) {
    std::cout << "\n\nYou died at level " << player.getLevel() << " and with "
              << player.getGold() << " gold.\n";
    std::cout << "Too bad can't take it with you!\n";
  } else {
    std::cout << "\n\nCongratulations, You Won!\n";
    std::cout << "You take " << player.getGold() << " gold with you.\n";
  }

  return 0;
}