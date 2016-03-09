#include "Map.h"

Map::Map(Size s, Difficulty d)
{
    size_ = s;
    difficulty_ = d;

    dims_ = Constants::SIZES[s];
}
