class Tile
{
public:

    typedef enum {GRND = ' ', WALL = '#', EXPL = '@', MINE = 'X'} TileType;

public:

    Tile(TileType t = GRND) : type_(t) {}; //Tile() = GRND

    char getChar() const {return (char)type_;}

    bool isPassable() const;
    bool isDestroyable() const;
    bool isObstacle() const;
    bool isWall() const;

private:

    TileType type_;
};
