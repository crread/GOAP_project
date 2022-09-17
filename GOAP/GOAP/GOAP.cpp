#include <iostream>

#include "GameManager.h"

int main()
{
    GameManager* gm = new GameManager();
    gm->thick();
    delete gm;
    return 0;
}