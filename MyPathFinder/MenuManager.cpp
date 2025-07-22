#include "MenuManager.h"
#include <iostream>
#include <limits>

void MenuManager::ShowMazeGeneratorMenu() const
{
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║     Select Maze Generation     ║\n";
    std::cout << "╠════════════════════════════════╣\n";
    std::cout << "║ 1. DFS                         ║\n";
    std::cout << "║ 2. BFS                         ║\n";
    std::cout << "║ 3. Binary Tree                 ║\n";
    std::cout << "║ 4. Sidewinder                  ║\n";
    std::cout << "║ 5. Prim                        ║\n";
    std::cout << "╚════════════════════════════════╝\n";
}

void MenuManager::ShowPathfindingMenu() const
{
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║  Select Pathfinding Algorithm  ║\n";
    std::cout << "╠════════════════════════════════╣\n";
    std::cout << "║ 1. DFS                         ║\n";
    std::cout << "║ 2. BFS                         ║\n";
    std::cout << "║ 3. Dijkstra                    ║\n";
    std::cout << "║ 4. A*                          ║\n";
    std::cout << "╚════════════════════════════════╝\n";
}

int MenuManager::GetUserChoice(int min, int max) const
{
    int input;
    
    while (true)
    {
        std::cout << "Enter a number (" << min << " - " << max << "): ";
        std::cin >> input;

        if (!std::cin.fail() && input >= min && input <= max)
            return input;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    }
    
    return input;
}

EMazeGeneratorType MenuManager::SelectMazeGenerator() const
{
    ShowMazeGeneratorMenu();
    int choice = GetUserChoice(MazeGeneratorMin, MazeGeneratorMax);
    return static_cast<EMazeGeneratorType>(choice);
}

EPathfindingType MenuManager::SelectPathfinder() const
{
    ShowPathfindingMenu();
    int choice = GetUserChoice(PathfindingMin, PathfindingMax);
    return static_cast<EPathfindingType>(choice);
}