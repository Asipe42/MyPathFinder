#include "MazeDrawer.h"

#include <iostream>
#include <thread>
#include <vector>

#include "MazeConfig.h"

void MazeDrawer::Draw(const std::vector<std::vector<int>>& maze) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::cout << "\033[H";
    
    const char* wall       = "\033[48;2;0;255;0m  \033[0m";     // 벽: 초록 배경 2칸 공백
    const char* path       = "\033[48;2;255;255;255m  \033[0m"; // 길: 흰 배경 2칸 공백
    const char* start      = "\033[48;2;255;255;0m  \033[0m";   // 출발지: 노랑 배경 2칸 공백
    const char* end        = "\033[48;2;255;0;0m  \033[0m";     // 도착지: 빨강 배경 2칸 공백
    const char* currentPos = "\033[48;2;255;0;0m  \033[0m";     // 현재 위치: 빨간 배경 2칸 공백 

    for (int y = 0; y < MazeConfig::HEIGHT; ++y)
    {
        for (int x = 0; x < MazeConfig::WIDTH; ++x)
        {
            if (x == 1 && y == 1)
                std::cout << start;
            else if (x == MazeConfig::WIDTH - 2 && y == MazeConfig::HEIGHT - 2)
                std::cout << end;
            else if (maze[y][x] == 0)
                std::cout << wall;
            else if (maze[y][x] == 1)
                std::cout << path;
            else if (maze[y][x] == 2)
                std::cout << currentPos;
        }
        std::cout << '\n';
    }

    std::cout << std::flush;
}
