#include "Maze.hpp"
#include <vector>
#include <climits>
#include <cstdio>
#include <unistd.h>
#include <queue>
#include <algorithm>

static int row_dir[4] = {1, 0, -1, 0};
static int col_dir[4] = {0, 1, 0, -1};

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
    for (int i = 0; i < 4; i++) {
        pos_t new_pos = pos_t(pos.first + row_dir[i], pos.second + col_dir[i]);    
        if(IsSafe(maze, new_pos, visited))
            DFSFindShortestPathAt(maze, new_pos, visited, min_path, path);
    }
    
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

static void backtrack_min_path(Maze &maze, pos_t **prev_pos, std::vector<pos_t> &min_path) {
    pos_t pos = pos_t(maze.GetRowCount() - 1, maze.GetColCount() - 1);
    if (prev_pos[pos.first][pos.second].first == -1 &&
        prev_pos[pos.first][pos.second].second == -1 )
            return;


    while (!maze.IsStart(pos)) {
        if (pos.first == -1 || pos.second == -1)
            break;
        
        min_path.push_back(pos);
        
        pos = prev_pos[pos.first][pos.second];
    }

    min_path.push_back(pos_t(0,0));
    std::reverse(min_path.begin(), min_path.end());
}

static bool BFSFindShortestPath(Maze &maze, std::vector<pos_t> &min_path) {
    bool ret = false; 
    bool **visited = new bool*[maze.GetRowCount()];
    pos_t **prev_pos = new pos_t*[maze.GetRowCount()];

    for (int i = 0; i < maze.GetRowCount(); i++) {
        visited[i] = new bool[maze.GetColCount()];
        prev_pos[i] = new pos_t[maze.GetColCount()];
    }
    
    for (int i = 0; i < maze.GetRowCount(); i++) {
        for (int j = 0; j < maze.GetColCount(); j++) {
            visited[i][j] = false;
            prev_pos[i][j] = pos_t(-1,-1);
        }
    }

    std::queue<pos_t> q;
    q.push(pos_t(0,0));

    while(!q.empty()) {
        pos_t cur = q.front();
        q.pop();

        visited[cur.first][cur.second] = true;

        if (maze.IsEnd(cur)) {
            ret = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            pos_t new_pos = pos_t(cur.first + row_dir[i], cur.second + col_dir[i]);    
            if(IsSafe(maze, new_pos, visited)) {
                prev_pos[new_pos.first][new_pos.second] = cur;
                q.push(new_pos);
            }
        }   
    }


    backtrack_min_path(maze, prev_pos, min_path);

    return ret;
}



bool FindShortestPath(Maze &maze, std::vector<pos_t> &min_path) {
    return BFSFindShortestPath(maze, min_path);
}