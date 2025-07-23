#pragma once
#include "MazeConfig.h"

class MenuUI
{
public:
    static constexpr int MazeGeneratorMin = 0;
    static constexpr int MazeGeneratorMax = 6;
    static constexpr int PathfindingMin = 1;
    static constexpr int PathfindingMax = 4;
    
    void ShowMazeGeneratorMenu() const;
    void ShowPathfindingMenu() const;
    
    int GetUserChoice(int min, int max) const;
    MazeConfig::EMazeType SelectMazeGenerator() const;
    MazeConfig::EPathType SelectPathfinder() const;
};
