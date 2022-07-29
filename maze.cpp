#include "maze.hpp"
#include <unistd.h>
#include <iostream>
#include <random>
#include <cassert>
#include <time.h>

Maze::Maze(int rowCount, int colCount, float sparsity) {
    std::cout << "Maze generation starts" << std::endl;

    _rowCount = rowCount;
    _colCount = colCount;
    _sparsity = sparsity;
    _data = NULL;

    char_table[0] = 32; 
    char_table[1] = 35;
    char_table[2] = 64;
}

void Maze::Generate() {
    if (!_data) {
        _data = new int*[_rowCount];  
        for (int i = 0; i < _rowCount; i++)
            _data[i] = new int[_colCount]; 
    }

    srand(time(NULL));
    
    for (int i = 0; i < _rowCount; i++) {
        for (int j = 0; j < _colCount; j++) {
            int randNum = rand()%100;
            _data[i][j] = randNum > 100*_sparsity ? 0 : 1;
        }
    }

    if (_data[_rowCount-1][_colCount-1] == 1)
        _data[_rowCount-1][_colCount-1] = 0;

    _data[0][0] = 2;
}


void Maze::Render() {
    system("cls");
    for (int j = 0; j < _colCount+2; j++)
        std::cout << "--"; 
    std::cout << std::endl; 

    for (int i = 0; i < _rowCount; i++) {
        for (int j = -1; j < _colCount+1; j++) {
            if (j == -1 || j == _colCount)
                std::cout << "|";
            else
                std::cout << (char)char_table[_data[i][j]] << " ";
        }
        std::cout << std::endl;
    }
    
    for (int j = 0; j < _colCount+2; j++)
        std::cout << "--"; 
    std::cout << std::endl; 
 
}

bool Maze::FollowPath() {
    assert(_path.size() > 0);
    if (_path_cur == _path.size() - 1)
        return false; // reach end

    pos_t cur = _path[_path_cur];
    pos_t next = _path[++_path_cur];

    SetPoint(cur, 0);
    SetPoint(next, 2);

    return true;
}