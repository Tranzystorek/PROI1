#include "Map.h"

class Generator
{
public:

    typedef enum {NORMAL, VERT = 0x01, INV = 0x02} WallFlag;

public:

    Generator(Constants::Size s = Constants::SMALL,
              Constants::Difficulty d = Constants::EASY);

    Map getCurrentMap() const {return result_;}

    void generateMap();

    void createWall(int x, int y, int length, int min_straight = 2, int max_straight = 0);

    bool isPlayable();

    bool isGenerated() const {return generated_;}

    void editTile(int x, int y, Tile::TileType t);

    void reset();

private:

    void createWallStrip(int x, int y, int length, unsigned char flags = NORMAL);

    void placeObstacles(int n, Tile::TileType t);

private:

    int numberOfWalls;

    bool generated_;

    Map buffer_;
    Map result_;
};
