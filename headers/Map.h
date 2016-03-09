#include "Tile.h"

namespace Constants
{
    typedef enum {EASY, NORMAL, HARD} Difficulty;
    typedef enum {SMALL, MEDIUM, LARGE} Size;

    struct Dims
    {
        Dims(int ww = 0, int hh = 0) : w(ww), h(hh) {};

        int w;
        int h;
    };

    const Dims SIZES[] = {Dims(50, 15), Dims(70, 20), Dims(100, 40)};

    const int MAX_W = 100;
    const int MAX_H = 40;
}

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

    Constants::Difficulty getDifficulty() const {return difficulty_;}
    Constants::Size getSize() const {return size_;}

private:

    Tile map_[Constants::MAX_H][Constants::MAX_W];

    Dims dims_;
    Difficulty difficulty_;
    Size size_;
};
