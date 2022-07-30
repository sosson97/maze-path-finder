#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <random>
#include "maze.hpp" 
#include "path_finder.hpp"
#include <chrono>
#include <thread>

int main(void) {
    int rowCount = 12;
    int colCount = 14;
    float sparsity = 0.33;
    std::vector<pos_t> path;

    std::cout << "Start" << std::endl;

    Maze maze(rowCount, colCount, sparsity);
    do {
        maze.Generate();
    } while(!FindShortestPath(maze, path));

    maze.SetPath(path);

    do {
        maze.Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    } while (maze.FollowPath());
}