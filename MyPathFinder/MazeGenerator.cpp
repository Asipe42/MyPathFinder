#include "MazeGenerator.h"

#include <iostream>

void MazeGenerator::Generate(EMazeGeneratorType type)
{
    switch (type)
    {
        case EMazeGeneratorType::DFS:
            GenerateWithDFS();
            break;
        case EMazeGeneratorType::BFS:
            GenerateWithBFS();
            break;
        case EMazeGeneratorType::BinaryTree:
            GenerateWithBinaryTree();
            break;
        case EMazeGeneratorType::Sidewinder:
            GenerateWithPrim();
            break;
        case EMazeGeneratorType::Prim:
            GenerateWithSidewinder();
            break;
    }

    PrintMaze();
}

void MazeGenerator::InitializeMaze()
{
    m_maze = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
}

void MazeGenerator::PrintMaze()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (m_maze[y][x] == 0)
                std::cout << "██";
            else
                std::cout << "  ";
        }
        std::cout << '\n';
    }
}


void MazeGenerator::GenerateWithDFS()
{
    InitializeMaze();
}

void MazeGenerator::GenerateWithBFS()
{
    InitializeMaze();
}

void MazeGenerator::GenerateWithBinaryTree()
{
    InitializeMaze();
}

void MazeGenerator::GenerateWithSidewinder()
{
    InitializeMaze();
}

void MazeGenerator::GenerateWithPrim()
{
    InitializeMaze();
}