#include "Tile.h"

bool Tile::isPassable() const
{
    return type_ == GRND;
}

bool Tile::isDestroyable() const
{
    return type_ == EXPL;
}

bool Tile::isObstacle() const
{
    return type_ != GRND;
}

bool Tile::isWall() const
{
    return type_ == WALL;
}
