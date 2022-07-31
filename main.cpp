#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <random>
#include "maze.hpp" 
#include "path_finder.hpp"
#include <chrono>
#include <thread>

int main(void) {
    int rowCount = 20;
    int colCount = 20;
    float sparsity = 0.32;
    std::vector<pos_t> path;

    std::cout << "Start!" << std::endl;

    Maze maze(rowCount, colCount, sparsity);
    do {
        maze.Generate();
    } while(!FindShortestPath(maze, path));

    maze.SetPath(path);

    do {
        maze.Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } while (maze.FollowPath());
}