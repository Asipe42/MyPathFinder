#pragma once
#include <vector>

#include "MazeDrawer.h"
#include "MenuUI.h"

class MazePathFinder
{
public:
    MazePathFinder(MazeDrawer mazeDrawer);
    void FindPath(std::vector<std::vector<int>> maze, MazeConfig::EPathType type);

private:
    MazeDrawer m_mazeDrawer;
    std::vector<std::vector<int>> m_maze;
    
    void FindPathWithDFS();
    void FindPathWithBFS();
    void FindPathWithDijkstar();
    void FindPathWithAStar();
};
