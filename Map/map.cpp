#include "map.h"

Map::Map()
{
	init();
}

Map::Map(dimension mapDim, pixPosition start, int space) : mapDim(mapDim), start(start), space(space)
{
	init();
}

Map::Map(const char *h_mapName, pixPosition start, int space) : start(start), space(space)
{
	init();
   
   if(!load(h_mapName))
      printf("Unable to load %s\n", finalMapPath.c_str());
}

Map::~Map()
{
}

void Map::init()
{
	tilesetNameForLayer[L_SOL] = "test.png";
	for(int y = 0 ; y < MAP_DIM_MAX ; y++)
		for(int x = 0 ; x < MAP_DIM_MAX ; x++)
			iTileOnCase[L_SOL][x][y] = 0;
   
	for(int y = 0 ; y < MAP_DIM_MAX ; y++)
		for(int x = 0 ; x < MAP_DIM_MAX ; x++)
			for(int iDir = 0 ; iDir < 4 ; iDir++)
				collisionMap[x][y][iDir] = 0;
   
	for(int y = 0 ; y < MAP_DIM_MAX ; y++)
		for(int x = 0 ; x < MAP_DIM_MAX ; x++)
			collisionMap[x][y][TOURABLE] = 1;
}

bool Map::valide(position pos)
{
	return pos.x >= 0 && pos.x < mapDim.first && pos.y >= 0 && pos.y < mapDim.second;
}

bool Map::load(const char *mapName)
{
   finalMapPath = mapPath+string(mapName);
   mapFile = fopen(finalMapPath.c_str(), "r");
   
   if(!mapFile)
      return false;
   char tilesetName[20];
	char spawnC[10];
   fscanf(mapFile, "%d%d%s%s", &mapDim.first, &mapDim.second, tilesetName, spawnC);
	int x =  atoi(strtok(spawnC, "[,"));
	int y =  atoi(strtok(NULL, ",]"));
	
	spawn.push_back(position(x,y));
	tilesetNameForLayer[L_SOL] = tilesetName;
   
	for(int x = 0 ; x < mapDim.first ; x++)
		for(int y = 0 ; y < mapDim.second ; y++)
         fscanf(mapFile, "%d", &iTileOnCase[L_SOL][y][x]);
	
	char collStr[MAP_DIM_MAX][MAP_DIM_MAX*11+1];
	for(int iLig = 0 ; iLig < mapDim.second ; iLig++)
		fscanf(mapFile, "%s", collStr[iLig]);
	
	for(int iLig = 0 ; iLig < mapDim.second ; iLig++)
	{
		int iPos = 1;
		for(int iCol = 0 ; iCol < mapDim.first ; iCol++)
		{
			for(int iDir = 0 ; iDir < 5 ; iDir++)
			{
				collisionMap[iCol][iLig][iDir] = collStr[iLig][iPos]-'0';
				iPos+=2;
			}
			iPos++;
		}
	}
	
   fclose(mapFile);
   return true;
}

pixPosition Map::getPixPosition(position posOnMap)
{
   return pixPosition(positionToPixPosition(posOnMap,start)+(posOnMap*space));
}

void Map::setSpawn(int x, int y)
{
   position here = pixPositionToPosition(x, y, start);
   vector<position>::iterator it;
   for(it = spawn.begin(); it != spawn.end(); it++)
      if(*(it) == here)
      {
         spawn.erase(it);
         return;
      }
   
   spawn.push_back(here);
}


void Map::save(const char *mapName)
{
   if(string(mapName)!="")
		finalMapPath = string(mapName);
   mapFile = fopen(finalMapPath.c_str(), "w+");
   
   fprintf(mapFile, "%d %d\n%s\n", mapDim.first, mapDim.second, tilesetNameForLayer[L_SOL].c_str());
   
   for(size_t i = 0; i < spawn.size(); i++)
      fprintf(mapFile, "[%d,%d] ", spawn[i].x, spawn[i].y);
   fprintf(mapFile, "\n");
   
   for(size_t y = 0 ; y < mapDim.second ; y++)
   {
		for(size_t x = 0 ; x < mapDim.first ; x++)
         fprintf(mapFile, "%d ", iTileOnCase[L_SOL][x][y]);
      fprintf(mapFile, "\n");
   }
   
	for(int y = 0 ; y < mapDim.second ; y++)
   {
		for(int x = 0 ; x < mapDim.first ; x++)
		{
			fprintf(mapFile, "(");
			for(int iDir = 0 ; iDir < 5 ; iDir++)
			{
				fprintf(mapFile, "%d", collisionMap[x][y][iDir]);
				if(iDir != 4)
					fprintf(mapFile, ",");
			}
			fprintf(mapFile, ")");
		}
      fprintf(mapFile, "\n");
   }
   
   
   fclose(mapFile);
}

void Map::flipColl(position where, int direction)
{
	collisionMap[where.x][where.y][direction] = !getColl(where,direction);
	position where_opposite = where+basic_dep[direction];
	collisionMap[where_opposite.x][where_opposite.y][opposite(direction)] = collisionMap[where.x][where.y][direction];
}




