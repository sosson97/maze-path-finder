#include <utility>
#include <vector>

typedef std::pair<int,int> pos_t;

class Maze {
public:
    Maze(int rowCount, int colCount, float sparsity);
    ~Maze() {
        if (_data) {
            for (int i = 0; i < _rowCount; i++)
                delete[] _data[i];
            delete[] _data;
        }
    }
    void Generate();
    void Render(); // print maze after cleaning the screen
    void Render2(); // print maze after cleaning the screen
    int GetPoint(pos_t pos) { return _data[pos.first][pos.second]; }
    void SetPoint(pos_t pos, int val) { _data[pos.first][pos.second] =  val; }
    int GetRowCount() { return _rowCount; }
    int GetColCount() { return _colCount; }
    bool IsStart(pos_t pos) {return pos.first == 0 && pos.second == 0; }
    bool IsEnd(pos_t pos) { return pos.first == _rowCount-1 && pos.second == _colCount-1; }
    bool IsBlocked(pos_t pos) { return GetPoint(pos) == 1; }
    bool IsInBoundary(pos_t pos) {
        return pos.first >= 0 &&
            pos.second >= 0 &&
            pos.first < GetRowCount() &&
            pos.second < GetColCount();    
    }

    void SetPath(std::vector<pos_t> path) { _path = path; _path_cur = 0; }
    bool FollowPath();


private:
    int **_data;
    int _rowCount;
    int _colCount;
    float _sparsity;

    std::vector<pos_t> _path;
    int _path_cur;
    char char_table[3];
};