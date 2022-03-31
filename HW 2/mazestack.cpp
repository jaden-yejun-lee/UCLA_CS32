#include <stack>
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

    // declare a stack of coords
    stack<Coord> coordStack;

    // push starting corrdinate onto the coordinate stack
    coordStack.push(Coord(sr, sc));

    // updates start position
    maze[sr][sc] = '*';

    // while coordStack is not empty
    while (!coordStack.empty()) {

        // current coord
        Coord c = coordStack.top();

        // pop the top coordinate off the stack
        coordStack.pop();

        // if current (r, c) is equal to ending coordinate, return true
        if (c.r() == er && c.c() == ec) {
            return true;
        }

        // if able to move west and havent encountered that cell yet
        if (maze[c.r()][c.c() - 1] == '.') {
            // push (r, c-1) and update maze
            coordStack.push(Coord(c.r(), c.c() - 1));
            maze[c.r()][c.c() - 1] = '*';
        }

        // if able to move south ""
        if (maze[c.r() + 1][c.c()] == '.') {
            coordStack.push(Coord(c.r() + 1, c.c()));
            maze[c.r() + 1][ c.c()] = '*';
        }

        // if able to move east ""
        if (maze[c.r()][c.c() + 1] == '.') {
            coordStack.push(Coord(c.r(), c.c() + 1));
            maze[c.r()][ c.c() + 1] = '*';
        }

        // if able to move north ""
        if (maze[c.r() - 1][c.c()] == '.') {
            coordStack.push(Coord(c.r() - 1, c.c()));
            maze[c.r() - 1][ c.c()] = '*';
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