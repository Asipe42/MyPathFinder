#include <iostream>
#include <string>
#include <vector>

#include "MazeDrawer.h"
#include "MazeGenerator.h"
#include "MazePathFinder.h"
#include "MenuUI.h"

int main()
{
    while (true)
    {
        MenuUI menu;
        MazeDrawer mazeDrawer;
        MazeGenerator mazeGenerator(mazeDrawer);
        MazePathFinder mazePathFinder(mazeDrawer);
        
        auto mazeType = menu.SelectMazeGenerator();
        auto pathType = menu.SelectPathfinder();
        
        std::vector<std::vector<int>> maze = mazeGenerator.Generate(mazeType);
        mazePathFinder.FindPath(maze, pathType);
    }
    
    return 0;
 }