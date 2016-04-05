#include "Generator.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

Generator::Generator(Constants::Size s, Constants::Difficulty d)
{
    buffer_ = Map(s, d);
    result_ = Map(s, d);

    numberOfWalls = 0;

    generated_ = false;
}

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

//writes to buffer only
void Generator::placeObstacles(int n, Tile::TileType t)
{
    const int W = buffer_.getWidth();
    const int H = buffer_.getHeight();

    int tx, ty;
    int i = 0;

    srand(time(NULL));

    while(i < n)
    {
        tx = rand() % W;
        ty = rand() % H;

        if(buffer_.map_[ty][tx].isObstacle())
            continue;

        buffer_.map_[ty][tx] = Tile(t);

        //std::cout << i << " obstacles " << (char)t << std::endl;

        i++;
    }
}//placeMines

//see createWallStrip
//final wall length is APPROXIMATELY equal to the length argument
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
}//createWall

//simple DFS algorithm
//updates numberOfWalls on true
bool Generator::isPlayable()
{
    const int W = buffer_.getWidth();
    const int H = buffer_.getHeight();
    const int LEN = W * H;

    bool *visited = new bool[LEN];

    Tile *temp;
    int wallCounter = 0;

    //mark appropriate tiles as visited and update numberOfWalls
    for(int i=0;i<LEN;i++)
    {
        temp = &buffer_.map_[i / W][i % W];

        if(temp->isWall())
            wallCounter++;

        if(temp->isObstacle() && !temp->isDestroyable())
            visited[i] = true;

        else
            visited[i] = false;
    }

    //local structure for storing position
    struct Pos
    {
        Pos(int xx=0, int yy=0) : x(xx), y(yy) {}

        int x;
        int y;
    } *stack = new Pos[LEN];

    int it = 0; //stack navigation (points at the free space on top)

    Pos currPos; //current position
    int nPos;

    bool stop = false; //escape outer for loop

    //find first passable tile
    for(int j=0;!stop && j<H;j++)
    {
        for(int i=0;i<W;i++)
            if(buffer_.map_[j][i].isPassable())
            {
                stack[it].x = i;
                stack[it++].y = j;

                stop = true;

                break;
            }//if
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

    delete[] stack;

    for(int i=0;i<LEN;i++)
        if(!visited[i])
        {
            delete[] visited;

            return false;
        }

    delete[] visited;

    numberOfWalls = wallCounter;

    return true;
}//isPlayable

//generator main logic
void Generator::generateMap()
{
    if(generated_)
        return;

    const int W = buffer_.getWidth();
    const int H = buffer_.getHeight();
    const int NTILES = W * H;

    const Constants::Difficulty D = buffer_.getDifficulty();

    const int NWALLS = Constants::WALL_CAPS[D] * NTILES / 100;
    const int NMINES = Constants::MINE_CAPS[D] * NTILES / 100;
    const int NEXPLS = Constants::EXPL_CAPS[D] * NTILES / 100;

    const int SINGLE_WALL = NWALLS * Constants::SINGLE_WALL_PERCENT / 100;
    const int MIN_WALL_SEGM = SINGLE_WALL * Constants::MIN_WALL_PERCENT / 100;
    const int MAX_WALL_SEGM = SINGLE_WALL * Constants::MAX_WALL_PERCENT / 100;

    std::cout << NTILES << " tiles" << std::endl
              << NWALLS << " walls" << std::endl
              << NMINES << " mines" << std::endl
              << NEXPLS << " expls" << std::endl;

    int tx, ty;

    srand(time(NULL));

    Map copy;

    int previous;
    int percent;

    while(numberOfWalls <= NWALLS)
    {
        copy = buffer_;

        tx = rand() % W;
        ty = rand() % H;

        createWall(tx, ty, SINGLE_WALL, MIN_WALL_SEGM, MAX_WALL_SEGM);

        if(!isPlayable())
            buffer_ = copy;

        if(previous != numberOfWalls)
        {
            previous = numberOfWalls;

            percent = 100 * numberOfWalls / NWALLS;

            std::cout << (percent > 100 ? 100 : percent) << '%' << std::endl;
        }
    }

    copy = buffer_;

    do {
        buffer_ = copy;

        placeObstacles(NMINES, Tile::MINE);
    }
    while(!isPlayable());

    placeObstacles(NEXPLS, Tile::EXPL);

    result_ = buffer_;

    generated_ = true;
}//generateMap

//stupid method -> verify coordinates before calling
void Generator::editTile(int x, int y, Tile::TileType t)
{
    result_.map_[x][y] = Tile(t);

    isPlayable();
}//editTile

void Generator::reset()
{
    result_ = buffer_ = Map(buffer_.getSize(), buffer_.getDifficulty());

    numberOfWalls = 0;

    generated_ = false;
}//reset
