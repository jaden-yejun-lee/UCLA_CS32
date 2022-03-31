#include <queue>
#include <iostream>
using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {

    // declare a queue of coords
    queue<Coord> coordQueue;

    // push starting coordinate onto the queue and update maze
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '*';

    // while queue is not empty
    while (!coordQueue.empty()) {

        // current Coord
        Coord q = coordQueue.front();

        // pop the top
        cerr << "(" << q.r() << ", " << q.c() << ")" << endl;
        coordQueue.pop();

        // if current (r, c) is equal to ending coordinate return true
        if (q.r() == er && q.c() == ec) {
            return true;
        }

        // if able to move west and havent encountered that cell yet
        if (maze[q.r()][q.c() - 1] == '.') {
            //push (r, c-1) and update maze
            coordQueue.push(Coord(q.r(), q.c() - 1));
            maze[q.r()][q.c() - 1] = '*';
        }

        // if able to move south ""
        if (maze[q.r() + 1][q.c()] == '.') {
            coordQueue.push(Coord(q.r() + 1, q.c()));
            maze[q.r() + 1][q.c()] = '*';
        }

        // if able to move east ""
        if (maze[q.r()][q.c() + 1] == '.') {
            coordQueue.push(Coord(q.r(), q.c() + 1));
            maze[q.r()][q.c() + 1] = '*';
        }

        // if able to move north ""
        if (maze[q.r() - 1][q.c()] == '.') {
            coordQueue.push(Coord(q.r() - 1, q.c()));
            maze[q.r() - 1][q.c()] = '*';
        }


    }
    // no solution so return false
    return false;

}


int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "X....XXX.X",
        "X.XXXX.X.X",
        "X......XXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}