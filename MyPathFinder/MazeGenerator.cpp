#include "MazeGenerator.h"

#include <iostream>
#include <queue>
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
    
    m_maze[HEIGHT - 2][WIDTH - 2] = 1;

    PrintMaze();
}

void MazeGenerator::InitializeMaze()
{
    m_maze = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
}

void MazeGenerator::PrintMaze()
{
    const char* wall  = "\033[48;2;0;255;0m  \033[0m";      // 벽: 초록 배경 2칸 공백
    const char* path  = "\033[48;2;255;255;255m  \033[0m";  // 길: 흰 배경 2칸 공백
    const char* start = "\033[48;2;255;255;0m  \033[0m";    // 출발지: 노랑 배경 2칸 공백
    const char* end   = "\033[48;2;255;0;0m  \033[0m";      // 도착지: 빨강 배경 2칸 공백

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (x == 1 && y == 1)
                std::cout << start;
            else if (x == WIDTH - 2 && y == HEIGHT - 2)
                std::cout << end;
            else if (m_maze[y][x] == 0)
                std::cout << wall;
            else
                std::cout << path;
        }
        std::cout << '\n';
    }
}

void MazeGenerator::GenerateWithDFS()
{
    /*
     * DFS
     *  1. 모든 셀을 벽으로 초기화
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
    /*
     * BFS
     *  1. 모든 셀을 벽으로 초기화
     *  2. 시작 지점을 길로 설정하고, 큐에 추가
     *  3. 큐에서 현재 위치를 꺼냄
     *  4. 상화좌우 방향을 중복 없이 무작위로 선택
     *  5. 현재 위치 기준, 선택된 방향으로 2칸 떨어진 위치 탐색
     *  6. 벽이면 중간 벽 제거하여 길 뚫고, 뚫은 위치를 큐에 삽입
     *  7. 큐가 빌 때까지 2~6단계를 반복
     */
    
    InitializeMaze();

    std::queue<std::pair<int, int>> queue;
    queue.push({1, 1});
    m_maze[1][1] = 1;

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    const int dx[4] = { 0, 0, -2, 2 };
    const int dy[4] = { -2, 2, 0, 0 };

    while (!queue.empty())
    {
        std::pair<int, int> pos = queue.front();
        queue.pop();

        int x = pos.first;
        int y = pos.second;

        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::shuffle(dirs.begin(), dirs.end(), rng);

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
            queue.push({nx, ny});
        }
    }
}

void MazeGenerator::GenerateWithBinaryTree()
{
    /*
     * Binary Tree
     *  1. 모든 셀을 벽으로 초기화
     *  2. 시작 지점으로부터 홀수 행과 홀수 열을 순회하며 각 셀을 방문
     *  3. 방문한 셀을 길로 변경
     *  4. 현재 셀에서 북쪽 또는 동쪽 방향 중 하나를 선택
     *  5. 선택한 방향의 벽을 허물어 통로를 연결
     *  6. 미로 끝까지 4~5단계를 반복
     */
    
    InitializeMaze();

    for (int y = 1; y < HEIGHT; y += 2)
    {
        for (int x = 1; x < WIDTH; x += 2)
        {
            m_maze[y][x] = 1;
            std::vector<std::pair<int, int>> dir;

            if (y > 1)
                dir.emplace_back(0, -1); // north
            if (x < WIDTH -2)
                dir.emplace_back(1, 0);  // east

            if (!dir.empty())
            {
                std::pair<int, int> pair = dir[rand() % dir.size()];
                int ny = y + pair.second;
                int nx = x + pair.first;
                m_maze[ny][nx] = 1;
            }
        }
    }
}

void MazeGenerator::GenerateWithSidewinder()
{
    InitializeMaze();
}

void MazeGenerator::GenerateWithPrim()
{
    InitializeMaze();
}