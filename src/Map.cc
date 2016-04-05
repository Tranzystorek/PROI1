#include "Map.h"

Map::Map(Size s, Difficulty d)
{
    size_ = s;
    difficulty_ = d;

    dims_ = Constants::SIZES[s];
}//constructor

std::string Map::toString() const
{
    std::string res = " ";

    //generate frame
    for(int i=0;i<dims_.w;i++)
        res += '_';

    res += '\n';

    //copy map contents w/frame
    for(int i=0;i<dims_.h;++i)
    {
        res += '|';

        for(int j=0;j<dims_.w;++j)
            res += map_[i][j].getChar();

        res += "|\n";
    }

    //generate frame (continued)
    res += ' ';

    for(int i=0;i<dims_.w;i++)
        res += '^';

    res += '\n';

    return res;
}//toString
