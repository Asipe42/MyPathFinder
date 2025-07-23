#include "MazePathFinder.h"

#include <immintrin.h>
#include <iostream>
#include <queue>
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
     *  2. 스택이 비거나 도착지에 도달할 때까지 다음 단계를 반복
     *  3-1. 스택에서 값을 꺼내 현재 위치로 설정
     *  3-2. 현재 위치를 기준으로 인접 셀을 확인
     *  3-2. 인접 셀이 방문되지 않았고 벽이 아니라면 스택에 넣고 방문 처리
     */

    std::stack<std::pair<int, int>> stack;
    bool visited[MazeConfig::HEIGHT][MazeConfig::WIDTH] = { false };

    const std::pair<int, int> start = { 1, 1 };
    const std::pair<int, int> end = { MazeConfig::WIDTH - 2, MazeConfig::HEIGHT - 2 };
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
    /*
     * BFS
     *  1. 시작 지점을 방문하고 큐에 넣음
     *  2. 큐가 비거나 도착지에 도달할 때까지 다음 단계를 반복
     *  3-1. 큐에서 값을 꺼내 현재 위치로 설정
     *  3-2. 현재 위치를 기준으로 인접 셀을 확인
     *  3-2. 인접 셀이 방문되지 않았고 벽이 아니라면 큐에 넣고 방문 처리
     */

    std::queue<std::pair<int, int>> queue;
    bool visited[MazeConfig::HEIGHT][MazeConfig::WIDTH] = { false };

    const std::pair<int, int> start = { 1, 1 };
    const std::pair<int, int> end = { MazeConfig::WIDTH - 2, MazeConfig::HEIGHT - 2 };
    queue.push(start);
    
    visited[start.second][start.first] = true;
    m_maze[start.second][start.first] = 2;
    m_mazeDrawer.Draw(m_maze);

    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };

    while (!queue.empty())
    {
        std::pair<int, int> current = queue.front();
        queue.pop();

        if (current == end)
            break;

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
            queue.push(next);
            
            visited[ny][nx] = true;
            m_maze[ny][nx] = 2;
            m_mazeDrawer.Draw(m_maze);
        }
    }
}

void MazePathFinder::FindPathWithDijkstar()
{
    /*
     * Dijkstra
     *  1. 시작 지점의 거리를 0으로 설정, 나머지는 무한대로 초기화
     *  2. 시작 지점을 거리가 짧은 순서로 처리하는 우선순위 큐에 넣음
     *  3. 큐가 비거나 도착지에 도달할 때까지 다음 단계를 반복
     *  4-1. 큐에서 가장 거리가 짧은 셀을 꺼내고 방문 처리
     *  4-2. 해당 셀에 인접한 셀을 검사
     *  4-3. 인접 셀이 방문되지 않았고 벽이 아니며, 현재 경로보다 더 짧은 경우 거리를 갱신 후 큐에 넣음
     */
    
    int distance[MazeConfig::HEIGHT][MazeConfig::WIDTH];
    bool visited[MazeConfig::HEIGHT][MazeConfig::WIDTH] = { false };
    
    std::fill(&distance[0][0], &distance[0][0] + MazeConfig::HEIGHT * MazeConfig::WIDTH, INT_MAX);
    
    const std::pair<int, int> start = { 1, 1 };
    const std::pair<int, int> end = { MazeConfig::WIDTH - 2, MazeConfig::HEIGHT - 2 };
    distance[start.second][start.first] = 0;

    using Node = std::pair<int, std::pair<int, int>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({0, start});

    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };

    while (!pq.empty())
    {
        Node current = pq.top();
        int dist = current.first;
        std::pair<int, int> cell = current.second;
        
        pq.pop();

        int x = cell.first;
        int y = cell.second;

        if (visited[y][x])
            continue;

        visited[y][x] = true;
        m_maze[y][x] = 2;
        m_mazeDrawer.Draw(m_maze);

        if (cell == end)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx <= 0 || ny <= 0)
                continue;

            if (nx >= MazeConfig::HEIGHT || ny >= MazeConfig::WIDTH)
                continue;;
            
            if (visited[ny][nx])
                continue;

            if (m_maze[ny][nx] == 0)
                continue;

            int newDist = dist + 1;
            if (newDist < distance[ny][nx])
            {
                distance[ny][nx] = newDist;
                pq.push({newDist, {nx, ny}});
            }
        }
    }
}

void MazePathFinder::FindPathWithAStar()
{
    /*
     * AStar
     *  1. 시작 지점의 f, g, h를 구함
     *  2. 시작 지점을 f가 가장 작은 순서로 처리하는 우선순위 큐에 넣음
     *  3. 큐가 비거나 도착지에 도달할 때까지 다음 단계를 반복
     *  4-1. 큐에서 가장 f가 작은 셀을 꺼내고 방문 처리
     *  4-2. 해당 셀의 인접 셀을 검사
     *  4-3. 인접 셀이 방문되지 않았고 벽이 아니며, g가 더 작다면 g와 h를 갱신 후 큐에 넣음
     */

    struct Node
    {
        int x, y;
        int g;  // 시작점으로부터의 거리
        int h;  // 도착지까지 추정 거리
        
        int f() const { return g + h; }
        bool operator>(const Node& other) const
        {
            return f() > other.f();
        }
    };

    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open;
    bool visited[MazeConfig::HEIGHT][MazeConfig::WIDTH] = { false };
    int gScore[MazeConfig::HEIGHT][MazeConfig::WIDTH];
    std::fill(&gScore[0][0], &gScore[0][0] + MazeConfig::HEIGHT * MazeConfig::WIDTH, INT_MAX);

    auto Heuristic = [](std::pair<int, int> start, std::pair<int, int> end)
    {
        return std::abs(start.first - end.first) + std::abs(start.second - end.second);
    };

    const std::pair<int, int> start = { 1, 1 };
    const std::pair<int, int> end = { MazeConfig::WIDTH - 2, MazeConfig::HEIGHT - 2 };

    gScore[start.second][start.first] = 0;
    open.push({ start.first, start.second, 0, Heuristic(start, end)});

    while (!open.empty())
    {
        Node current = open.top();
        open.pop();

        if (visited[current.y][current.x])
            continue;

        visited[current.y][current.x] = true;
        m_maze[current.y][current.x] = 2;
        m_mazeDrawer.Draw(m_maze);
        
        if (current.x == end.first && current.y == end.second)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx <= 0 || ny <= 0)
                continue;

            if (nx >= MazeConfig::HEIGHT || ny >= MazeConfig::WIDTH)
                continue;;

            if (m_maze[ny][nx] == 0)
                continue;
            
            if (visited[ny][nx])
                continue;

            int tentativeG = gScore[current.y][current.x] + 1;
            if (tentativeG < gScore[ny][nx])
            {
                gScore[ny][nx] = tentativeG;
                int h = Heuristic({nx, ny}, end);
                open.push({nx, ny, tentativeG, h});
            }
        }
    }
}
