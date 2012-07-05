#ifndef SFMLMAP_H_
#define SFMLMAP_H_

#include <SFML/Graphics.hpp>
#include "map.h"
#include "ImageManager.h"
#include "grider.h"
#include "Selector.h"
using namespace sf;

namespace ourColor
{
	static sf::Color Grey = Color(142,142,142);
};

class SFMLMap : public Map
{
public:
   
	SFMLMap() {}
	SFMLMap(RenderWindow* p_App, dimension mapDim, pixPosition p_start = pixPosition(), bool showGrille = true, bool activeSelector = false, bool tiledSelector = false, int p_space = 0);
	SFMLMap(RenderWindow* p_App, string p_mapName, int p_space = 0, bool showGrille=true);
   SFMLMap(RenderWindow* p_App, string p_mapName, pixPosition start, int p_space = 0, bool showGrille=true);
   
	void setSprite(int iTile, position at, int layer=L_SOL);
	void setSprite(Sprite spr, position at, int layer=L_SOL);
	void setSpriteFromMouse(int x, int y, int iTile);
	void setSpriteFromSelector();
	inline Sprite getSprite(position where, int layer=L_SOL) { return spriteOnLayer[layer][where.x][where.y]; }
	inline Sprite getSprite(pixPosition where, int layer=L_SOL) { return spriteOnLayer[layer][where.x/TILE_DIM][where.y/TILE_DIM]; }
   
	void loadTilesetImage();
	static void setImgManager(ImageManager *mgr) { imgManager = mgr; }
	void moveSelector(int& x, int& y);
	void moveAndSetFromSelector(position pos, bool set = true);
	IntRect getTileRect(int iTile);
	void switchSelector() { Select.setActive(!Select.isActive()); }
	void cutTileset();
	void giveTile(SFMLMap* cible);
	void tiledSelector(bool on=true) { Select.setTiled(on); }
	void setSelectorColor(Color col) { Select.setBordColor(col); }
	position getSelectorPos() { return pixPositionToPosition(Select.getPos(),start); }
	void draw();
   
	static SFMLMap* activeMap(SFMLMap* m1, SFMLMap* m2);
	static SFMLMap* switchActiveSelector(SFMLMap* m1, SFMLMap* m2);
   
	inline void setCollCircles(bool on=true) { grille.showCircles = on; }
	void flipCollAndCol(position where, int direction);
	void flipCollMouse(int x, int y);
   
private:
   
	void getTile(Sprite tile);
	Selector Select;
	Image* tilesetImage;
	static ImageManager* imgManager;
	RenderWindow* App;
	Sprite spriteOnLayer[N_LAYER][MAP_DIM_MAX][MAP_DIM_MAX];
	grider grille;
	bool showGrille;
};

#endif /* SFMLMAP_H_ */

