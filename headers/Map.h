#include "Constants.h"
#include "Tile.h"

#include <string>

class Map
{
private:

    typedef Constants::Dims Dims;
    typedef Constants::Size Size;
    typedef Constants::Difficulty Difficulty;

public:

    Map(Size s = Constants::SMALL,
        Difficulty d = Constants::EASY);

    int getWidth() const {return dims_.w;}
    int getHeight() const {return dims_.h;}

    Difficulty getDifficulty() const {return difficulty_;}
    Size getSize() const {return size_;}

    std::string toString() const;

private:

    Tile map_[Constants::MAX_H][Constants::MAX_W];

    Dims dims_;
    Difficulty difficulty_;
    Size size_;

    friend class Generator;
};
