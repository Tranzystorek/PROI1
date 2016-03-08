namespace Constants
{
    typedef enum {EASY, HARD} Difficulty;
    //typedef enum {SMALL, MEDIUM, LARGE} Size;

    struct Dim
    {
        Dim(int ww, int hh) : w(ww), h(hh) {};

        int w;
        int h;
    };

    const Dim SIZES[] = {Dim(50, 50), Dim(100, 100), Dim(200, 200)};
}

class Map
{
public:

    Map(int w, int h, Constants::Size s, Constants::Difficulty d)
        : width_(w), height_(h), size_(s), difficulty_(d) {};

    int getWidth() const {return width_;}
    int getHeight() const {return height_;}

    Constants::Difficulty getDifficulty() const {return difficulty_;}

    Constants::Size getSize() const {return size_};

private:

    int width_;
    int height_;

    Constants::Difficulty difficulty_;
    Constants::Size size_;
};
