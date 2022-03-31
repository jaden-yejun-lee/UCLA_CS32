
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {

    if (sr == er && sc == ec) {
        return true;
    }

    maze[sr][sc] = '*';

    // west
    if (maze[sr][sc - 1] == '.') {
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
            return true;
        }
    }

    // south
    if (maze[sr + 1][sc] == '.') {
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
            return true;
        }
    }

    // east
    if (maze[sr][sc + 1] == '.') {
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
            return true;
        }
    }

    // north
    if (maze[sr - 1][sc] == '.') {
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) {
            return true;
        }
    }

    return false;

}

