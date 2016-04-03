#include "Generator.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

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

        std::cout<<dir<<" "<<l<<std::endl;

        currL += l;
    }//while

    result_ = buffer_;
}//createWall

Map Generator::generateMap()
{

}//generateMap

void Generator::resetBuffer()
{

}//resetBuffer
