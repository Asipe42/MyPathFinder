#pragma once

namespace MazeConfig
{
    constexpr int WIDTH = 25;
    constexpr int HEIGHT = 25;

    enum class EMazeType
    {
        None,
        DFS,
        BFS,
        BinaryTree,
        Sidewinder,
        Prim
    };

    enum class EPathType
    {
        None,
        DFS,
        BFS,
        Dijkstra,
        AStar
    };
}