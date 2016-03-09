class Tile
{
public:

    typedef enum {GRND = ' ', WALL = '#', EXPL = '@', MINE = 'X'} TileType;

    Tile(TileType t = GRND) : type_(t) {};

    char getType() const {return (char)type_;}

    bool isPassable() const;
    bool isObstacle() const;

private:

    TileType type_;
};
