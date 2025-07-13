#include <iostream>
#include <string>
#include <vector>

#include "MenuManager.h"

int main()
{
    MenuManager menu;
    EMazeGeneratorType maze = menu.SelectMazeGenerator();
    EPathfindingType pathfinder = menu.SelectPathfinder();

    return 0;
}