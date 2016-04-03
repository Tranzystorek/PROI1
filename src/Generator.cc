#include "Generator.h"

#include <cstdlib>
#include <ctime>

//#include <iostream>

//stupid method -> make sure that the wall doesn't exceed map bounds
//writes to buffer only
void Generator::createWallStrip(int x, int y, int length, unsigned char flags)
{
    //using bit flags for options
    if(flags & VERT)
    {
        if(flags & INV)
        {
            const int yend = y - length;

            for(int ypos = y; ypos > yend; --ypos)
                buffer_.map_[ypos][x] = Tile(Tile::WALL);
        }

        else
        {
            const int yend = y + length;

            for(int ypos = y; ypos < yend; ++ypos)
                buffer_.map_[ypos][x] = Tile(Tile::WALL);
        }
    }

    else
    {
        if(flags & INV)
        {
            const int xend = x - length;

            for(int xpos = x; xpos > xend; --xpos)
                buffer_.map_[y][xpos] = Tile(Tile::WALL);
        }

        else
        {
            const int xend = x + length;

            for(int xpos = x; xpos < xend; ++xpos)
                buffer_.map_[y][xpos] = Tile(Tile::WALL);
        }
    }
}//createWallStrip

void Generator::createWall(int x, int y, int length, int min_straight, int max_straight)
{
    if(!max_straight)
        max_straight = length;

    enum Direction {N = 1, S, W, E} dir;

    int currL = 0; //current length
    int currX = x; //current x
    int currY = y; //current y

    int l; //local randomized value

    srand(time(NULL));

    dir = (Direction)(rand() % E + 1);

    while(currL < length)
    {
        if(dir == N || dir == S)
            dir = (Direction)(W + rand() % 2);

        else
            dir = (Direction)(N + rand() % 2);

        l = rand() % (max_straight - min_straight + 1) + min_straight - 1;

        switch(dir)
        {
            case N:
                if(currY - l < 0)
                {
                    dir = W;
                    continue;
                }

                createWallStrip(currX, currY, l, VERT | INV);
                currY -= l;
                break;
            //CASE N

            case S:
                if(currY + l >= buffer_.getHeight())
                {
                    dir = W;
                    continue;
                }

                createWallStrip(currX, currY, l, VERT);
                currY += l;
                break;
            //CASE S

            case W:
                if(currX - l < 0)
                {
                    dir = N;
                    continue;
                }

                createWallStrip(currX, currY, l, INV);
                currX -= l;
                break;
            //CASE W

            case E:
                if(currX + l >= buffer_.getWidth())
                {
                    dir = N;
                    continue;
                }

                createWallStrip(currX, currY, l);
                currX += l;
                break;
            //CASE E
        }//switch

        currL += l;
    }//while

    result_ = buffer_;
}//createWall

bool Generator::isPlayable()
{
    const int W = buffer_.getWidth();
    const int H = buffer_.getHeight();
    const int LEN = W * H;

    bool *visited = new bool[LEN];

    for(int i=0;i<LEN;i++)
    {
        if(buffer_.map_[i / W][i % W].isObstacle())
            visited[i] = true;

        else
            visited[i] = false;
    }

    struct Pos
    {
        Pos(int xx=0, int yy=0) : x(xx), y(yy) {}

        int x;
        int y;
    } *stack = new Pos[LEN];

    int it = 0; //stack navigation

    Pos currPos; //current position
    int nPos;

    bool stop = false;

    //find first passable tile
    for(int j=0;j<H;j++)
    {
        for(int i=0;i<W;i++)
            if(buffer_.map_[j][i].isPassable())
            {
                stack[it].x = i;
                stack[it++].y = j;

                stop = true;

                break;
            }//if

        if(stop)
            break;
    }//for

    while(it)
    {
        //std::cout << "stack: " << it << std::endl;

        currPos = stack[it - 1];
        it--;

        //std::cout << currPos.x << " " << currPos.y << std::endl;

        nPos = currPos.x + currPos.y * W;

        if(!visited[nPos])
        {
            visited[nPos] = true;

            if(currPos.x > 0
                && !visited[currPos.x - 1 + currPos.y * W])

                stack[it++] = Pos(currPos.x - 1, currPos.y);

            if(currPos.x < W - 1
                && !visited[currPos.x + 1 + currPos.y * W])

                stack[it++] = Pos(currPos.x + 1, currPos.y);

            if(currPos.y > 0
                && !visited[currPos.x + (currPos.y - 1) * W])

                stack[it++] = Pos(currPos.x, currPos.y - 1);

            if(currPos.y < H - 1
                && !visited[currPos.x + (currPos.y + 1) * W])
                stack[it++] = Pos(currPos.x, currPos.y + 1);
        }//if
    }//while

    for(int i=0;i<LEN;i++)
        if(!visited[i])
            return false;

    return true;
}//isPlayable

Map Generator::generateMap()
{

}//generateMap

void Generator::resetBuffer()
{

}//resetBuffer
