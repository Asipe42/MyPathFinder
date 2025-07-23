#pragma once
#include <vector>

#include "MenuManager.h"

class MazeGenerator
{
public:
    void Generate(EMazeGeneratorType type);

private:
    static constexpr int WIDTH = 25;
    static constexpr int HEIGHT = 25;
    std::vector<std::vector<int>> m_maze;

    void InitializeMaze();
    void PrintMaze();
    
    void GenerateWithDFS();
    void GenerateWithBFS();
    void GenerateWithBinaryTree();
    void GenerateWithSidewinder();
    void GenerateWithPrim();
};
