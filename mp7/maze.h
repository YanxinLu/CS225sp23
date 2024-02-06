/* Your code here! */
#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <chrono>
using std::vector;
using cs225::PNG;
using cs225::HSLAPixel;

class SquareMaze{
    public:
    /*Makes a new SquareMaze of the given height and width.*/
    void makeMaze(int width, int height);
    /*Determine whether it is possible to travel in the given direction from the square at coordinates (x,y).*/
    bool canTravel(int x, int y, int dir) const;
    /*Sets whether or not the specified wall exists.*/
    void setWall(int x, int y, int dir, bool exists);
    /*Solves this SquareMaze and return a vector of path.*/
    vector<int> solveMaze();
    /*Draws the maze without the solution.*/
    PNG* drawMaze() const;
    /**Draws the maze with the solution.*/
    PNG* drawMazeWithSolution();
    private:
    vector<int> _down;
    vector<int> _right;
    int _height;
    int _width;
};

#endif