#include "Maze.hpp"
#include <vector>
#include <climits>
#include <cstdio>
#include <unistd.h>

static bool IsSafe(Maze &maze, pos_t pos, bool **visited) {
     if (!maze.IsInBoundary(pos))
        return false;
    if (maze.IsBlocked(pos))
        return false;
    if (visited[pos.first][pos.second])
        return false;

    return true;
}

static void DFSFindShortestPathAt(Maze &maze, 
            pos_t pos, 
            bool **visited, 
            std::vector<pos_t> &min_path, 
            std::vector<pos_t> &path) {
    
    path.push_back(pos);
    
    int dist = path.size();
    int min_dist = min_path.size();

    if (dist > min_dist) {
        path.pop_back();
        return;
    }

    if (maze.IsEnd(pos)) {
        if (dist < min_dist)
            min_path = path;
        path.pop_back();
        return;
    }

    visited[pos.first][pos.second] = true;

    pos_t new_pos = pos_t(pos.first+1, pos.second);    
    if(IsSafe(maze, new_pos, visited))
        DFSFindShortestPathAt(maze, new_pos, visited, min_path, path);
    
    new_pos = pos_t(pos.first, pos.second+1);    
    if(IsSafe(maze, new_pos, visited))
        DFSFindShortestPathAt(maze, new_pos, visited, min_path, path);
    
    new_pos = pos_t(pos.first-1, pos.second);    
    if(IsSafe(maze, new_pos, visited))
        DFSFindShortestPathAt(maze, new_pos, visited, min_path, path);
    
    new_pos = pos_t(pos.first, pos.second-1);    
    if(IsSafe(maze, new_pos, visited))
        DFSFindShortestPathAt(maze, new_pos, visited, min_path, path);

    visited[pos.first][pos.second] = false;
    path.pop_back();
}


static bool DFSFindShortestPath(Maze &maze, std::vector<pos_t> &min_path){
    bool **visited = new bool*[maze.GetRowCount()];
    std::vector<pos_t> path;
    int max_size = maze.GetRowCount() * maze.GetColCount() + 1;
    min_path.resize(max_size);

    for (int i = 0; i < maze.GetRowCount(); i++) 
        visited[i] = new bool[maze.GetColCount()];
    
    for (int i = 0; i < maze.GetRowCount(); i++)
        for (int j = 0; j < maze.GetColCount(); j++)
            visited[i][j] = false;

    DFSFindShortestPathAt(maze, pos_t(0,0), visited, min_path, path);

    return min_path.size() == max_size ? false : true;
}

bool FindShortestPath(Maze &maze, std::vector<pos_t> &min_path) {
    return DFSFindShortestPath(maze, min_path);
}