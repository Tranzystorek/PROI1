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
