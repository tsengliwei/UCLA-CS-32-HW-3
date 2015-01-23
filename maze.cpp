//
//  maze.cpp
//  HW 3
//
//  Created by Li-Wei Tseng on 5/6/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include <iostream>
#include <cassert>
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


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '#';
    
    if(maze[sr-1][sc] == '.') //try to move NORTH
    {
        if(pathExists(maze, sr-1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc+1] == '.') //try to move EAST
    {
        if(pathExists(maze, sr, sc+1, er, ec))
            return true;    }
    if(maze[sr+1][sc] == '.') //try to move SOUTH
    {
        if(pathExists(maze, sr+1, sc, er, ec))
            return true;    }
    if(maze[sr][sc-1] == '.') //try to move WEST
    {
        if(pathExists(maze, sr, sc-1, er, ec))
            return true;    }
    
    return false;
}




//#define MAZE
#ifdef MAZE

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','.','X','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    assert(pathExists(maze, 6,4, 1,1));
    char maze1[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','X','.','.','X','.','.','.','X'},
        { 'X','.','X','X','.','X','.','X','X','X'},
        { 'X','.','.','.','.','X','.','X','.','X'},
        { 'X','X','.','X','.','X','.','.','.','X'},
        { 'X','X','X','.','.','X','.','X','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','X','.','.','X','.','X','X'},
        { 'X','.','.','.','.','X','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    assert(pathExists(maze1, 8, 6, 1, 1));
    char maze2[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','X','.','.','X','.','.','.','X'},
        { 'X','X','X','X','.','X','.','X','X','X'},
        { 'X','.','.','.','.','X','.','X','.','X'},
        { 'X','X','.','X','.','X','.','.','.','X'},
        { 'X','X','X','.','.','X','.','X','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','X','.','.','X','.','X','X'},
        { 'X','.','.','.','.','X','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
        
    };
    assert(!pathExists(maze2, 8, 6, 1, 1));
    char maze3[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','X','.','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','.','.','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','.','X','X','X','.','.','X'},
        { 'X','X','X','X','.','.','X','.','.','X'},
        { 'X','X','.','.','.','.','X','.','.','X'},
        { 'X','.','.','.','.','.','.','.','X','X'},
        { 'X','.','.','X','X','X','X','X','X','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
        
    };
    assert(pathExists(maze3, 4, 3, 7, 1));
    char maze4[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','X','.','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','.','.','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','.','X','X','X','.','.','X'},
        { 'X','X','X','X','.','.','X','.','.','X'},
        { 'X','X','.','.','.','.','X','.','.','X'},
        { 'X','.','X','.','.','.','.','.','X','X'},
        { 'X','.','.','X','X','X','X','X','X','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    assert(!pathExists(maze4, 4, 3, 7, 1));
    cerr << "pass all test!" << endl;

}

#endif //MAZE

