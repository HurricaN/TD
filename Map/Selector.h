#ifndef SELECTOR_H_
#define SELECTOR_H_

#include "../common.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Selector
{
public :

   Selector() { App = NULL; }
   Selector(RenderWindow* App, pixPosition pos = pixPosition(), bool active = true, bool tiled = false, int fatness = 1, Color col = Color::Red);
   ~Selector();

   void draw();
   pixPosition getPos();
   Sprite getTile() { return tile; }
   int getiTile() { return iTile; }
   void move(deplacement<int> dep);
   void move(pixPosition go);
   void setTile(Sprite tile, int iiTile);
   void setTiled(bool doI);
   void setActive(bool doI);
   void setBordColor(Color p_col);

   inline bool isTiled() {return tiled;}
   inline bool isActive() {return active;}

private :

   void autoSetBord();

   pixPosition pos;
   Sprite tile;
   int iTile;
   Shape bord;
   int fatness;
   Color col;
   RenderWindow* App;
   bool tiled;
   bool active;

};

#endif /* SELECTOR_H_ */
