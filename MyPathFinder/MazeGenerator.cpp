#include "MazeGenerator.h"

#include <iostream>
#include <random>
#include <stack>

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
    // ANSI 색상 코드
    const char* orange = "\033[38;2;255;165;0m";   // RGB(255,165,0) 주황색
    const char* white  = "\033[38;2;255;255;255m"; // 흰색
    const char* reset  = "\033[0m";                // 색상 초기화

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (m_maze[y][x] == 0)
                std::cout << orange << "■" << reset;
            else
                std::cout << white << "□" << reset;
        }
        std::cout << '\n';
    }
}

void MazeGenerator::GenerateWithDFS()
{
    /*
     * DFS
     *  1. 모든 셀을 벽으로 초기화.
     *  2. 시작 위치 선정
     *  3. 상하좌우 방향을 중복 없이 무작위 선택
     *  4-1. 현재 위치 기준, 선택한 방향으로 2칸 떨어진 위치 탐색
     *  4-2. 벽이면 중간 벽 제거하고 길 뚫고, 재귀 호출하여 탐색 지속
     *  4-3. 벽이 아니면 다음 방향 시도. 시도할 방향이 없으면 재귀 호출 종료
     */
    
    InitializeMaze();

    std::stack<std::pair<int, int>> stack;
    stack.push({1, 1});
    m_maze[1][1] = 1;

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    const int dx[4] = { 0, 0, -2, 2 };
    const int dy[4] = { -2, 2, 0, 0 };

    while (!stack.empty())
    {
        std::pair<int, int> pos = stack.top();
        int x = pos.first;
        int y = pos.second;

        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::shuffle(dirs.begin(), dirs.end(), rng);

        bool moved = false;
        for (auto index : dirs)
        {
            int nx = x + dx[index];
            int ny = y + dy[index];

            if (nx <= 0 || ny <= 0)
                continue;

            if (nx >= WIDTH || ny >= HEIGHT)
                continue;

            if (m_maze[ny][nx] != 0)
                continue;

            m_maze[y + dy[index] / 2][x + dx[index] / 2] = 1;
            m_maze[ny][nx] = 1;
            stack.push({nx, ny});
            moved = true;
            break;
        }

        if (!moved)
            stack.pop();
    }
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