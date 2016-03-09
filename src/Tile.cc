#include "Tile.h"

bool Tile::isPassable() const
{
    return type_ == GRND;
}

bool Tile::isObstacle() const
{
    return type_ != GRND;
}
