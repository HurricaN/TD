#ifndef MAP_H_
#define MAP_H_

#include "../common.h"

class Map
{
   public :
   
	Map();
	Map(dimension mapDim, pixPosition start = pixPosition(0, 0), int space = 0);
	Map(const char *h_mapName, pixPosition start = pixPosition(0, 0), int space = 0);
	virtual ~Map();
	void init();
   
	pixPosition getPixPosition(position posOnMap);
	bool load(const char *mapName);
	void save(const char *mapName);
	void save();
	void setSpawn(int x, int y);
   
	inline void setSpace(int s) { space = s; }
	inline int& setiTile(position where, int layer=L_SOL) { return iTileOnCase[layer][where.x][where.y]; }
	inline void setiTile(int iTile, position where, int layer=L_SOL) { iTileOnCase[layer][where.x][where.y] = iTile; }
	inline int getiTile(position where, int layer=L_SOL) { return iTileOnCase[layer][where.x][where.y]; }
	inline int getiTile(pixPosition where, int layer=L_SOL) { return iTileOnCase[layer][where.x/TILE_DIM][where.y/TILE_DIM]; }
	inline int getWidth() { return mapDim.first; }
	pixPosition getStart() { return start; }
   
	bool valide(position pos);
	
	bool isFlipable(position where, int direction)
	{
		where += basic_dep[direction];
		return where.x >= 0 && where.y >= 0 && where.x < mapDim.first && where.y < mapDim.second;
	}
   
	void flipColl(position where, int direction);
	inline bool getColl(position where, int direction) { return collisionMap[where.x][where.y][direction]; }
   
   /*A SOCCUPER DE*/
	vector<position> spawn;
   
   protected :
   
	string tilesetNameForLayer[N_LAYER];
	dimension mapDim;
	int space;
	string finalMapPath;
	pixPosition start;
	
   private :
   
	FILE *mapFile;
	int iTileOnCase[N_LAYER][MAP_DIM_MAX][MAP_DIM_MAX];
	bool collisionMap[MAP_DIM_MAX][MAP_DIM_MAX][4+1];
};

#endif /* MAP_H_ */
