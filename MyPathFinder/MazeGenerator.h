#pragma once
#include <vector>

#include "MazeDrawer.h"
#include "MenuUI.h"

class MazeGenerator
{
public:
    MazeGenerator(MazeDrawer mazeDrawer);
    std::vector<std::vector<int>> Generate(MazeConfig::EMazeType type);

private:
    std::vector<std::vector<int>> m_maze;
    MazeDrawer m_mazeDrawer;

    void InitializeMaze();
    
    void GenerateWithDFS();
    void GenerateWithBFS();
    void GenerateWithBinaryTree();
    void GenerateWithSidewinder();
    void GenerateWithPrim();
};
