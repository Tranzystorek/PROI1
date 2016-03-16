#include "Map.h"

class Generator
{
public:

    typedef enum {NORMAL, VERT = 0x01, INV = 0x02} WallFlag;

public:

    Map getCurrentMap() const {return result_;}

    Map generateMap();

    void createWall(int x, int y, int length, int segment_len = 2);

private:

    void createWallStrip(int x, int y, int length, unsigned char flags = NORMAL);

    void resetBuffer();

private:

    Map buffer_;
    Map result_;
};