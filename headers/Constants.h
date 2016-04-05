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

    //map dimensions for specific sizes
    const Dims SIZES[] = {Dims(50, 15), Dims(70, 20), Dims(100, 30)};

    const int MAX_W = 100;
    const int MAX_H = 40;

    //caps for specific difficulties as per cent of all tiles
    const int WALL_CAPS[] = {10, 13, 16};
    const int MINE_CAPS[] = {1, 3, 4};
    const int EXPL_CAPS[] = {4, 2, 0};

    //per cent of total wall tiles per single wall
    const int SINGLE_WALL_PERCENT = 10;

    //per cent of single wall tiles per minimum and maximum segment length
    const int MIN_WALL_PERCENT = 20;
    const int MAX_WALL_PERCENT = 40;
}
