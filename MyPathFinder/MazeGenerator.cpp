#include "MazeGenerator.h"

#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <thread>

void MazeGenerator::Generate(EMazeGeneratorType type)
{
    std::cout << "\033[2J\033[H";
    
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
            GenerateWithSidewinder();
            break;
        case EMazeGeneratorType::Prim:
            GenerateWithPrim();
            break;
    }
}

void MazeGenerator::InitializeMaze()
{
    m_maze = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
}

void MazeGenerator::PrintMaze()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::cout << "\033[H";

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

    std::cout << std::flush;
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

    PrintMaze();

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

            PrintMaze();
            break;
        }

        if (!moved)
            stack.pop();
    }

    m_maze[HEIGHT - 2][WIDTH - 2] = 1;
    PrintMaze();
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

    PrintMaze();

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

            PrintMaze();
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

            if (y < HEIGHT -2)
                dir.emplace_back(0, 1); // South
            if (x < WIDTH -2)
                dir.emplace_back(1, 0); // East

            if (!dir.empty())
            {
                std::pair<int, int> pair = dir[rand() % dir.size()];
                int ny = y + pair.second;
                int nx = x + pair.first;
                m_maze[ny][nx] = 1;

                PrintMaze();
            }
        }
    }
}

void MazeGenerator::GenerateWithSidewinder()
{
    /*
     * Sidewinder
     *  1. 모든 셀을 벽으로 초기화
     *  2. 홀수 행을 왼쪽에서 오른쪽으로 순회
     *  3. 현재 행에서 연속된 통로를 만들기 위한 run 집합을 초기화
     *  4. 현재 셀에서 동쪽으로 길을 뚫을지, 아니면 run을 종료하고 남쪽으로 길을 뚫을지 무작위로 결정
     *  5. 4단계에서 결정한 방향에 따라 통로를 만들고 run 집합에 셀을 추가
     *  6. run에 포함된 셀 중 하나를 무작위로 선택해 그 셀과 아래쪽 셀을 연결해 통로 생성
     *  7. 아래쪽 길을 만든 후 run을 초기화 하고 다음 셀로 이동해 4~6단계를 반복
     *  8. 한 행이 끝났으면 다음 홀수 행으로 이동해 3단계로 회귀
     */
    
    InitializeMaze();

    for (int y = 1; y < HEIGHT - 1; y+= 2)
    {
        std::vector<int> run;

        for (int x = 1; x < WIDTH - 1; x +=2)
        {
            m_maze[y][x] = 1;

            PrintMaze();

            run.push_back(x);

            bool atEasternBoundary = (x + 2 >= WIDTH - 1);
            bool atSoutherBoundary = (y + 2 >= HEIGHT - 1);
            bool carveEast = !atEasternBoundary && (atSoutherBoundary || (rand() % 2 == 0));

            if (carveEast)
            {
                m_maze[y][x + 1] = 1;

                PrintMaze();
            }
            else
            {
                int randomIndex = rand() % run.size();
                int carveX = run[randomIndex];

                if (!atSoutherBoundary)
                {
                    m_maze[y + 1][carveX] = 1;
                    m_maze[y + 2][carveX] = 1;

                    PrintMaze();
                }

                run.clear();
            }
        }
    }
}

void MazeGenerator::GenerateWithPrim()
{
    /*
     * Prim
     *  1. 모든 셀을 벽으로 초기화
     *  2. 시작 셀을 통로로 만들고 방문 목록에 추가
     *  3. 현재 통로에 인접한 벽들을 목록에 추가
     *  4. 벽 목록에서 무작위로 하나의 벽을 선택
     *  5. 선택한 벽의 반대쪽 셀이 방문하지 않은 곳인지 확인
     *  6. 반대쪽 셀이 미로 영역 내에 있고 방문하지 않은 곳이라면 벽과 반대쪽 셀을 통로로 만듬
     *  7. 새로 열린 셀을 방문 목록에 추가하고, 그 셀과 인접한 벽들을 벽 목록에 추가
     *  8. 벽 목록이 빌 때까지 4~6단계를 반복
     */
    
    InitializeMaze();

    bool visited[HEIGHT][WIDTH] = { false };
    std::vector<std::pair<int, int>> wallList;

    m_maze[1][1] = 1;
    visited[1][1] = true;

    PrintMaze();

    const int dy[4] = { -2, 2, 0, 0 };
    const int dx[4] = { 0, 0, -2, 2 };
    
    auto addWalls = [&](int y, int x)
    {
        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny <= 0 || nx <= 0)
                continue;

            if (ny >= HEIGHT || nx >= WIDTH)
                continue;

            if (visited[ny][nx])
                continue;

            wallList.emplace_back(ny, nx);
        }
    };

    addWalls(1, 1);

    while (!wallList.empty())
    {
        int index = rand() % wallList.size();
        int wy = wallList[index].first;
        int wx = wallList[index].second;

        for (int i = 0; i < 4; i++)
        {
            int ny = wy + dy[i];
            int nx = wx + dx[i];

            if (ny <= 0 || nx <= 0)
                continue;

            if (ny >= HEIGHT || nx >= WIDTH)
                continue;

            if (visited[ny][nx] && !visited[wy][wx])
            {
                m_maze[wy][wx] = 1;
                m_maze[wy + dy[i] / 2][wx + dx[i] / 2] = 1;
                
                visited[wy][wx] = true;
                
                addWalls(wy, wx);

                PrintMaze();

                break;
            }
        }

        wallList.erase(wallList.begin() + index);
    }
}