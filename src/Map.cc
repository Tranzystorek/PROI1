#include "Map.h"

Map::Map(Size s, Difficulty d)
{
    size_ = s;
    difficulty_ = d;

    dims_ = Constants::SIZES[s];
}

std::string Map::toString() const
{
    std::string res = "";

    for(int i=0;i<dims_.h;++i)
    {
        for(int j=0;j<dims_.w;++j)
            res += map_[i][j].getChar();

        res += '\n';
    }

    return res;
}
