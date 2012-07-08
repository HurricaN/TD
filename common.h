#ifndef COMMON_H_
#define COMMON_H_
//coucou
#include <cstdio>
#include <string>
#include <vector>
#include <set>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

static string mapPath("datas/maps/");
static string tilesetPath("datas/maps/tilesets/");
static string mobCharsetPath("datas/mobs/charsets/");
static string mobCharsetDefPath("datas/mobs/charsetsDef/");
static string mobDefPath("datas/mobs/mobDef/");

static const int INFINI = 1e9;

static const int GAME_H = 750;
static const int GAME_W = 800;
static const int ACTION_H = 110;

// Indice des layers
static const int N_LAYER = 3;
static const int L_COLL  = 0;
static const int L_SOL   = 1;
static const int L_TOUR  = 2;

//  Description du veteur mouvement + Indices des directions
static const int RIGHT = 0;
static const int LEFT  = 1;
static const int UP    = 2;
static const int DOWN  = 3;
static const int TOURABLE = 4;
static const int X = 0;
static const int Y = 0;
static int dir[5 /* sens du mouvenement */ ][2 /* 0 : x; 1 : y */] = {{1,0},{-1,0},{0,-1},{0,1},{0,0}};

static int opposite(int iDir)
{
	switch(iDir)
	{
		case RIGHT:
			return LEFT;
			break;
		case LEFT:
			return RIGHT;
			break;
		case UP:
			return DOWN;
			break;
		case DOWN:
			return UP;
			break;
		case TOURABLE:
			return TOURABLE;
			break;
	}
}

// Dimension des tuiles
static const int TILE_DIM    = 32;
static const int MAP_DIM_MAX = 20;

typedef pair<int,int> dimension;

template<typename T>
struct deplacement
{
   T x, y;
   deplacement(T x=0, T y=0) : x(x), y(y) {}
   
   deplacement<T> operator*(T a)
   {
      return deplacement<T>(x*a, y*a);
   }
};

static deplacement<int> basic_dep[5] = {deplacement<int>(1,0),deplacement<int>(-1,0),deplacement<int>(0,-1),deplacement<int>(0,1),deplacement<int>(0,0)};

struct position
{
   int x, y;
   position(int x=0, int y=0) : x(x), y(y) {}
   position(const position& toCopy) : x(toCopy.x), y(toCopy.y) {}
   
   position operator+(int a)
   {
      return position(x + a, y + a);
   }
   
   position& operator+=(deplacement<int> a)
   {
      x += a.x;
      y += a.y;
      return *this;
   }
   
	position operator+(deplacement<int> a)
   {
	   return position(x+a.x, y+a.y);
   }
   
   position operator*(int a)
   {
      return position(x*a, y*a);
   }
   
   bool operator<(int a)
   {
      return x < a || y < a;
   }
   
   bool operator==(position posIn)
   {
      return x == posIn.x && y == posIn.y;
   }
   
};

struct pixPosition
{
   int x, y;
   pixPosition(int x=0, int y=0) : x(x), y(y) {}
   pixPosition(const pixPosition& toCopy) : x(toCopy.x), y(toCopy.y) {}
   
   pixPosition operator+(int a)
   {
      return pixPosition(x + a*TILE_DIM, y + a*TILE_DIM);
   }
	
	pixPosition operator*(int a)
   {
      return pixPosition(x*a, y*a);
   }
   
   
   pixPosition& operator+=(deplacement<int> a)
   {
      x += a.x;
      y += a.y;
      return *this;
   }
   
	pixPosition operator+(deplacement<int> a)
   {
	   return pixPosition(x+a.x, y+a.y);
   }

   
   pixPosition operator+(pixPosition rightOp)
   {
      return pixPosition(x + rightOp.x, y + rightOp.y);
   }
   
   pixPosition operator+(position rightOp)
   {
      return pixPosition(x + rightOp.x, y + rightOp.y);
   }
};

template<typename T>
static Vector2<T> to2(pixPosition p) { return Vector2<T>((T)p.x, (T)p.y); }
template<typename T>
static Vector2<T> to2(position p) { return Vector2<T>((T)p.x, (T)p.y); }


// Passe d'un indice de tileset a ses coordonnées sur le tileset
static position indiceToPosition(int iCase, int width)
{
   return position(iCase % width, iCase / width);
}


static int positionToIndice(position posIn, int width)
{
   return posIn.x + posIn.y * width;
}

static pixPosition positionToPixPosition(position posIn, pixPosition start = pixPosition())
{
   return start+(posIn*TILE_DIM);
}

static position pixPositionToPosition(pixPosition posIn, pixPosition start = pixPosition())
{
   
   return position((posIn.x-start.x) / TILE_DIM, (posIn.y-start.y) / TILE_DIM);
}

static position pixPositionToPosition(int x, int y, pixPosition start = pixPosition())
{
   
   return position((x-start.x) / TILE_DIM, (y-start.y) / TILE_DIM);
}

static int char_to_int(char a)
{
   return a-'0';
}

static int string_to_int(string a)
{
   int coeff = 1;
   for(int i = 0 ; i < a.size()-1 ; i++)
      coeff *= 10;
   
   int res = 0;
   
   for(int i = 0 ; i < a.size() ; i++)
   {
      res += char_to_int(a[i])*coeff;
      coeff/=10;
   }
   
   return res;
}

enum event_type
{
   DRAW_TEXT = 0,
};

static int* genMelangeAleatoire(int n)
{
	int *tab = new int[n];
	for(int i = 0 ; i < n ; i++)
		tab[i] = i;
	for(int i = 0 ; i < n ; i++)
	{
		int swapI = rand()%n;
		int tmp = tab[swapI];
		tab[swapI] = tab[i];
		tab[i] = tmp;
	}
	
	return tab;
}

static bool isInRect(pixPosition p, IntRect r)
{
	return p.x >= r.Left && p.x <= r.Right && p.y >= r.Top && p.y <= r.Bottom;
}

#endif /* COMMON_H_ */
