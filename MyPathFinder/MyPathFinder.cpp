#include <iostream>
#include <string>
#include <vector>

#include "MazeGenerator.h"
#include "MenuManager.h"

int main()
{
    while (true)
    {
        MenuManager menu;
        EMazeGeneratorType mazeType = menu.SelectMazeGenerator();
        EPathfindingType pathfinder = menu.SelectPathfinder();
        
        MazeGenerator mazeGenerator;
        mazeGenerator.Generate(mazeType);
    }
    
    return 0;
}