#include "MazePathFinder.h"

#include <iostream>
#include <smmintrin.h>
#include <stack>

#include "MazeConfig.h"
#include "MazeGenerator.h"

MazePathFinder::MazePathFinder(MazeDrawer mazeDrawer)
{
    this->m_mazeDrawer = mazeDrawer;
}

void MazePathFinder::FindPath(std::vector<std::vector<int>> maze, MazeConfig::EPathType type)
{
    m_maze = maze;
    
    std::cout << "\033[2J\033[H";
    
    switch (type)
    {
        case MazeConfig::EPathType::DFS:
            FindPathWithDFS();
            break;
        case MazeConfig::EPathType::BFS:
            FindPathWithBFS();
            break;
        case MazeConfig::EPathType::Dijkstra:
            FindPathWithDijkstar();
            break;
        case MazeConfig::EPathType::AStar:
            FindPathWithAStar();
            break;
    }
}

void MazePathFinder::FindPathWithDFS()
{
    /*
     * DFS
     *  1. 시작 지점을 방문하고 스택에 넣음
     *  2. 스택에 있는 값을 꺼내 현재 위치로 설정
     *  3. 아직 방문하지 않은 이웃 셀(상, 하, 좌, 우)를 확인
     *  4-1. 방문 가능한 이웃이 있다면 그 셀을 방문 후 스택에 넣고 3단계로 회귀
     *  4-2. 방문 가능한 이웃이 없다면 2단계로 회귀
     *  4-3. 현재 위치가 도착지거나 스택이 비었으면 탐색 종료
     */

    std::stack<std::pair<int, int>> stack;
    bool visited[MazeConfig::WIDTH][MazeConfig::HEIGHT] = { false };

    std::pair<int, int> start = { 1, 1 };
    std::pair<int, int> end = { MazeConfig::WIDTH - 2, MazeConfig::HEIGHT - 2 };
    stack.push(start);
    
    visited[start.second][start.first] = true;
    m_maze[start.second][start.first] = 2;
    m_mazeDrawer.Draw(m_maze);

    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };
    
    while (!stack.empty())
    {
        std::pair<int, int> current = stack.top();

        if (current == end)
            break;

        bool moved = false;

        for (int i = 0; i < 4; i++)
        {
            int nx = current.first + dx[i];
            int ny = current.second + dy[i];

            if (nx <= 0 || ny <= 0)
                continue;

            if (nx >= MazeConfig::HEIGHT || ny >= MazeConfig::WIDTH)
                continue;;
            
            if (visited[ny][nx])
                continue;

            if (m_maze[ny][nx] == 0)
                continue;
            
            std::pair<int, int> next = { nx, ny };
            stack.push(next);
            
            visited[ny][nx] = true;
            m_maze[ny][nx] = 2;
            m_mazeDrawer.Draw(m_maze);
            
            moved = true;
            break;
        }

        if (!moved)
            stack.pop();
    }
}

void MazePathFinder::FindPathWithBFS()
{
}

void MazePathFinder::FindPathWithDijkstar()
{
}

void MazePathFinder::FindPathWithAStar()
{
}
