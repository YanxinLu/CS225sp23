/* Your code here! */
#include "maze.h"
#include <queue>
using std::queue;

/*Makes a new SquareMaze of the given height and width.*/
void SquareMaze::makeMaze(int width, int height){
    //resize width and height
    _width = width;
    _height = height;
    int newsize = width*height;
    _down.resize(newsize);
    _right.resize(newsize);
    DisjointSets visited;
    visited.addelements(newsize);
    //set all the walls, 0 represents a wall
    for(size_t i = 0; i < _down.size(); i++){
        _down[i] = 0;
        _right[i] = 0;
    }
    //randomly remove walls
    int walls = 0;
    while(walls<newsize-1){
        srand(std::chrono::system_clock::now().time_since_epoch().count());
        int rwidth = rand()%width;
        srand(std::chrono::system_clock::now().time_since_epoch().count());
        int rheight = rand()%height;
        int rsize = rwidth+width*rheight;
        if(_down[rsize]&&_right[rsize]) continue;
        srand(std::chrono::system_clock::now().time_since_epoch().count());
        int random = rand()%2;
        //right has wall
        if(random){
            if(_right[rsize]) continue;
            if(rwidth==width-1) continue;
            if(visited.find(rsize)==visited.find(rsize+1)) continue;
            visited.setunion(rsize,rsize+1);
            _right[rsize] = 1;
            walls++;
        }
        //down has wall
        else{
            if(_down[rsize]) continue;
            if(rheight==height-1) continue;
            if(visited.find(rsize)==visited.find(rsize+width)) continue;
            visited.setunion(rsize,rsize+width);
            _down[rsize] = 1;
            walls++;
        }
    }
}

/*Determine whether it is possible to travel in the given direction from the square at coordinates (x,y).*/
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir==0) return _right[x+y*_width];
    else if(dir==1) return _down[x+y*_width];
    else if(dir==2){
        //out of maze
        if(x==0) return false;
        return _right[x-1+y*_width];
    }
    else if(dir==3){
        //out of maze
        if(y==0) return false;
        return _down[x+(y-1)*_width];
    }
    //dir is not 0,1,2,3
    return false;
}

/*Sets whether or not the specified wall exists.*/
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    //right
    if(dir==0){
        if(x==_width-1) return;
        if(exists) _right[x+y*_width] = 0;
        else _right[x+y*_width] = 1;
    }
    //down
    else if(dir==1){
        if(y==_height-1) return;
        if(exists) _down[x+y*_width] = 0;
        else _down[x+y*_width] = 1;
    }
}

/*Solves this SquareMaze and return a vector of path.*/
vector<int> SquareMaze::solveMaze(){
    vector<int> visited;
    vector<int> pre;
    vector<int> dir;
    vector<int> dist;
    visited.insert(visited.end(), _width*_height, 0);
    pre.insert(pre.end(),_width*_height,0);
    dir.insert(dir.end(),_width*_height,0);
    dist.insert(dist.end(),_width*_height,0);
    for(int x = 0; x<_width; x++){
        for(int y = 0; y<_height; y++){
            if(visited[x+y*_width]) continue;
            visited[x+y*_width] = 1;
            queue<int> q;
            q.push(x+y*_width);
            while(!q.empty()){
                int curr = q.front();
                q.pop();
                int xcurr = curr%_width;
                int ycurr = curr/_width;
                if(canTravel(xcurr,ycurr,0)&&visited[xcurr+ycurr*_width+1]==0){
                    pre[xcurr+ycurr*_width+1] = curr;
                    dir[xcurr+ycurr*_width+1] = 0;
                    dist[xcurr+ycurr*_width+1] = dist[curr]+1;
                    visited[xcurr+ycurr*_width+1] = 1;
                    q.push(xcurr+ycurr*_width+1);
                }
                if(canTravel(xcurr,ycurr,1)&&visited[xcurr+(ycurr+1)*_width]==0){
                    pre[xcurr+(ycurr+1)*_width] = curr;
                    dir[xcurr+(ycurr+1)*_width] = 1;
                    dist[xcurr+(ycurr+1)*_width] = dist[curr]+1;
                    visited[xcurr+(ycurr+1)*_width] = 1;
                    q.push(xcurr+(ycurr+1)*_width);
                }
                if(canTravel(xcurr,ycurr,2)&&visited[xcurr+ycurr*_width-1]==0){
                    pre[xcurr+ycurr*_width-1] = curr;
                    dir[xcurr+ycurr*_width-1] = 2;
                    dist[xcurr+ycurr*_width-1] = dist[curr]+1;
                    visited[xcurr+ycurr*_width-1] = 1;
                    q.push(xcurr+ycurr*_width-1);
                }
                if(canTravel(xcurr,ycurr,3)&&visited[xcurr+(ycurr-1)*_width]==0){
                    pre[xcurr+(ycurr-1)*_width] = curr;
                    dir[xcurr+(ycurr-1)*_width] = 3;
                    dist[xcurr+(ycurr-1)*_width] = dist[curr]+1;
                    visited[xcurr+(ycurr-1)*_width] = 1;
                    q.push(xcurr+(ycurr-1)*_width);
                }
            }
        }
    }
    //max distance
    int destination = _width*(_height-1);
    for(int x=0; x<_width; x++){
        if(dist[destination]<dist[x+_width*(_height-1)]) destination = x+_width*(_height-1);
    }
    vector<int> ret;
    while(destination!=0){
        ret.insert(ret.begin(), dir[destination]);
        destination = pre[destination];
    }
    return ret;
}

/*Draws the maze without the solution.*/
PNG* SquareMaze::drawMaze() const{
    PNG* ret = new PNG(_width*10+1, _height*10+1);
    //draw top line and left line of the maze
    for(int x=10; x<_width*10+1; x++) ret->getPixel(x,0)->l = 0;
    for(int y=0; y<_height*10+1; y++) ret->getPixel(0,y)->l = 0;
    //draw lines for maze square
    for(int x=0; x<_width; x++){
        for(int y=0; y<_height; y++){
            if(!_down[x+y*_width]){
                for(int k=0; k<=10; k++){
                    ret->getPixel(x*10+k,(y+1)*10)->l = 0;
                }
            }
            if(!_right[x+y*_width]){
                for(int k=0; k<=10; k++){
                    ret->getPixel((x+1)*10,y*10+k)->l = 0;
                }
            }
        }
    }
    return ret;
}

/**Draws the maze with the solution.*/
PNG* SquareMaze::drawMazeWithSolution(){
    PNG* ret = drawMaze();
    vector<int> soln = solveMaze();
    HSLAPixel red(0,1,0.5,1);
    int xcurr = 0;
    int ycurr = 0;
    for(size_t i=0; i<soln.size(); i++){
        //right
        if(soln[i]==0){
            for(int k=0; k<=10; k++){
                *(ret->getPixel(5+xcurr*10+k,5+ycurr*10)) = red;
            }
            xcurr++;
        }
        //down
        else if(soln[i]==1){
            for(int k=0; k<=10; k++){
                *(ret->getPixel(5+xcurr*10,5+ycurr*10+k)) = red;
            }
            ycurr++;
        }
        //left
        else if(soln[i]==2){
            for(int k=0; k<=10; k++){
                *(ret->getPixel(5+xcurr*10-k,5+ycurr*10)) = red;
            }
            xcurr--;
        }
        //up
        else if(soln[i]==3){
            for(int k=0; k<=10; k++){
                *(ret->getPixel(5+xcurr*10,5+ycurr*10-k)) = red;
            }
            ycurr--;
        }
    }
    //exit
    for(int k=1; k<10; k++) ret->getPixel(xcurr*10+k,(ycurr+1)*10)->l = 1;
    return ret;
}