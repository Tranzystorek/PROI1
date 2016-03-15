#include "Map.h"

class Generator
{
public:

    Map getCurrentMap() const {return result_;}

    Map generateMap();
    void createWall(int x, int y, int length, int min_straight = 1);

    void undoAction();

private:

    Map buffer_;
    Map result_;
};
