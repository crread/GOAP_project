#include <iostream>

#include "GameManager.h"

int main()
{
    unsigned int numberOfTurn;
    std::cout << "choose the numbers of turns for this game" << std::endl;
    std::cin >> numberOfTurn;

    GameManager gm = GameManager();
    gm.start(numberOfTurn);
}