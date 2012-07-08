#include "SFMLMap.h"
#include <cmath>

ImageManager* SFMLMap::imgManager = NULL;

SFMLMap::SFMLMap(RenderWindow* p_App, dimension mapDim, pixPosition p_start, bool showGrille, bool activeSelector, bool tiledSelector, int p_space) : Map(mapDim, p_start, p_space), App(p_App), showGrille(showGrille)
{
   Select = Selector(App, start, activeSelector, tiledSelector);
   grille = grider(App);
   grille.genGrid(start,mapDim.first,mapDim.second,1,Color::White);
}

SFMLMap::SFMLMap(RenderWindow* p_App, string p_mapName, int p_space, bool showGrille) : Map(p_mapName.c_str(), pixPosition(), p_space), App(p_App), showGrille(showGrille)
{
   loadTilesetImage();
   start = pixPosition((GAME_W)/2-(mapDim.first*32)/2,(GAME_H-ACTION_H)/2-(mapDim.second*32)/2);
   Select = Selector(App, start);
   grille = grider(p_App);
   grille.genGrid(start,mapDim.first,mapDim.second,1,Color::White);
   cutTileset();
   Select.setActive(0);
}

SFMLMap::SFMLMap(RenderWindow* p_App, string p_mapName, pixPosition start, int p_space, bool showGrille) : Map(p_mapName.c_str(), start, p_space), App(p_App), showGrille(showGrille)
{
   loadTilesetImage();
   Select = Selector(App, start);
   grille = grider(p_App);
   grille.genGrid(start,mapDim.first,mapDim.second,1,Color::White);
   cutTileset();
}


IntRect SFMLMap::getTileRect(int iTile)
{
   pixPosition pixPosOut = positionToPixPosition(indiceToPosition(iTile, tilesetImage->GetWidth() / TILE_DIM));
   return IntRect(pixPosOut.x, pixPosOut.y, (pixPosOut + 1).x, (pixPosOut + 1).y);
}

void SFMLMap::setSprite(int iTile, position at, int layer)
{
   Sprite spr;
   spr.SetImage(*tilesetImage);
   spr.SetPosition(to2<float>(getPixPosition(at)));
   spr.SetSubRect(getTileRect(iTile));
   spriteOnLayer[layer][at.x][at.y] = spr;
}

void SFMLMap::setSprite(Sprite spr, position at, int layer)
{
   spriteOnLayer[layer][at.x][at.y] = spr;
}

void SFMLMap::cutTileset()
{
	for(int x = 0 ; x < mapDim.first ; x++)
		for(int y = 0 ; y < mapDim.second ; y++)
		{
			if(x == 3 && y == 0)
				printf("iTile : %d\n", getiTile(position(x,y)));
         setSprite(getiTile(position(x,y)), position(x,y));
		}
}

void SFMLMap::setSpriteFromSelector()
{
   setSprite(Select.getTile(), pixPositionToPosition(Select.getPos(), start));
   setiTile(Select.getiTile(), pixPositionToPosition(Select.getPos(), start));
}

void SFMLMap::setSpriteFromMouse(int x, int y, int iTile)
{
   setSprite(iTile, pixPositionToPosition(x, y, start));
   setiTile(iTile, pixPositionToPosition(x, y, start));
}

void SFMLMap::flipCollAndCol(position where, int direction)
{
	flipColl(where,direction);
	bool c = getColl(where,direction);
	Color col= Color::Green;
	if(!c)
		col = Color::Red;
	grille.setCircleCol(where, direction, col);
	if(direction != TOURABLE)
		grille.setCircleCol(where+basic_dep[direction], opposite(direction), col);
}

void SFMLMap::draw()
{
	for(int x = 0 ; x < mapDim.first ; x++)
		for(int y = 0 ; y < mapDim.second ; y++)
			App->Draw(getSprite(position(x,y)));
	
	if(showGrille)
		grille.draw();
   
	Select.draw();
}

void SFMLMap::loadTilesetImage()
{
   tilesetImage = imgManager->getResource(tilesetPath+tilesetNameForLayer[L_SOL]);
	tilesetImage->CreateMaskFromColor(tilesetImage->GetPixel(0,0),0);
}

void SFMLMap::moveSelector(int& x, int& y)
{
   pixPosition Spos = Select.getPos();
   if(Spos.x+x >= start.x
      && Spos.y+y >= start.y
      && Spos.x+x*TILE_DIM < (mapDim.first+(start.x/TILE_DIM))*TILE_DIM
      && Spos.y+y*TILE_DIM < (mapDim.second+(start.y/TILE_DIM))*TILE_DIM)
		Select.move(deplacement<int>(x, y));
}

void SFMLMap::moveAndSetFromSelector(position pos, bool set)
{
   if(pos.x >= 0
      && pos.y >= 0
      && pos.x < mapDim.first
      && pos.y < mapDim.second)
		Select.move(positionToPixPosition(pos, start));
   if(set)
      setSpriteFromSelector();
}

SFMLMap* SFMLMap::switchActiveSelector(SFMLMap* m1, SFMLMap* m2)
{
   m1->switchSelector();
   m2->switchSelector();
   return SFMLMap::activeMap(m1, m2);
}

SFMLMap* SFMLMap::activeMap(SFMLMap* m1, SFMLMap* m2)
{
   if(m1->Select.isActive())
		return m1;
   else
		return m2;
}

void SFMLMap::flipCollMouse(int x, int y)
{
   position here = pixPositionToPosition(x, y, start);
   for(int dir = RIGHT; dir <= TOURABLE; dir++)
   {
      float dist = pow((grille.getCircle(here, dir).x - x), 2) + pow((grille.getCircle(here, dir).y - y), 2);
      if(dist - 25 < 0)
      {
         flipCollAndCol(here, dir);
         break;
      }
   }
}

void SFMLMap::giveTile(SFMLMap* cible)
{
   cible->Select.setTile(getSprite(Select.getPos()),getiTile(Select.getPos()));
}

