#include "Generator.h"

#include <cstdlib>
#include <ctime>

//stupid method -> make sure that the wall doesn't exceed map bounds
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

void Generator::createWall(int x, int y, int length, int min_straight)
{

}//createWall

Map Generator::generateMap()
{

}//generateMap

void Generator::resetBuffer()
{

}//resetBuffer
