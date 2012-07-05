#include "Selector.h"
#include "SFMLMap.h"

void Selector::autoSetBord()
{
   Vector2<float> sommet = to2<float>(pos);
   if(!tiled)
		bord = Shape::Rectangle(sommet.x, sommet.y, sommet.x + TILE_DIM - fatness, sommet.y + TILE_DIM - fatness, Color(0, 0, 0, 0), fatness, col);
   else
		bord = Shape::Rectangle(sommet.x, sommet.y, sommet.x + TILE_DIM - fatness + 1, sommet.y + TILE_DIM - fatness + 1, Color(0, 0, 0, 0), fatness, col);
}


Selector::Selector(RenderWindow* App, pixPosition pos, bool active, bool tiled, int fatness, Color col) : App(App), pos(pos), active(active), tiled(tiled), fatness(fatness), col(col)
{
   autoSetBord();
   tile = Sprite();
}

Selector::~Selector()
{
   
}

void Selector::setBordColor(Color p_col)
{
   col = p_col;
   Vector2<float> sommet = to2<float>(pos);
   if(!tiled)
      bord = Shape::Rectangle(sommet.x, sommet.y, sommet.x + TILE_DIM - fatness, sommet.y + TILE_DIM - fatness, Color(0, 0, 0, 0), fatness, col);
   else
      bord = Shape::Rectangle(sommet.x, sommet.y, sommet.x + TILE_DIM - fatness + 1, sommet.y + TILE_DIM - fatness + 1, Color(0, 0, 0, 0), fatness, col);
}

void Selector::draw()
{
   if(active)
   {
		App->Draw(bord);
		if(tiled)
			App->Draw(tile);
   }
}


void Selector::move(deplacement<int> dep)
{
   if(active)
   {
		pos += (dep * TILE_DIM);
		tile.SetPosition(to2<float>(pos));
		autoSetBord();
   }
}

void Selector::move(pixPosition go)
{
   if(active)
   {
		pos = go;
		tile.SetPosition(to2<float>(pos));
		autoSetBord();
   }
}

void Selector::setTile(Sprite inTile, int iinTile)
{
   tile = inTile;
   iTile = iinTile;
   tile.SetPosition(to2<float>(pos));
   tiled = true;
}

void Selector::setTiled(bool doI)
{
   tiled = doI;
}

void Selector::setActive(bool doI)
{
   active = doI;
}

pixPosition Selector::getPos()
{
   return pixPosition(pos);
}
