struct Tile{
	struct Tile* up;
	struct Tile* down;
	struct Tile* left;
	struct Tile* right;
};
struct Tile* maze[36];
void create_maze(void);