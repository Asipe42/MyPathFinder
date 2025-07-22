#pragma once

enum class EMazeGeneratorType
{
    None,
    DFS,
    BFS,
    BinaryTree,
    Sidewinder,
    Prim
};

enum class EPathfindingType
{
    None,
    DFS,
    BFS,
    Dijkstra,
    AStar
};

class MenuManager
{
public:
    static constexpr int MazeGeneratorMin = 1;
    static constexpr int MazeGeneratorMax = 6;
    static constexpr int PathfindingMin = 1;
    static constexpr int PathfindingMax = 4;
    
    void ShowMazeGeneratorMenu() const;
    void ShowPathfindingMenu() const;
    
    int GetUserChoice(int min, int max) const;
    EMazeGeneratorType SelectMazeGenerator() const;
    EPathfindingType SelectPathfinder() const;
};