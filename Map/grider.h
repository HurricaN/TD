#ifndef GRIDER_H_
#define GRIDER_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "../common.h"

using namespace std;
using namespace sf;

class grider
{
   public:

   grider() {}
   grider(RenderWindow* App, int maxWidth = 0, int maxHeight = 0) : App(App), maxWidth(maxWidth), maxHeight(maxHeight), showCircles(false) {}

   void addSeparator(int xOry, bool isVertical, int weight, Color col);
   void genGrid(pixPosition p_leftTop, int width, int height, int weight, Color col);
   Vector2<float> getCircle(position where, int side) { return circle[where.x][where.y][side].second; }
   void setCircleCol(position where, int direction, Color col) { circle[where.x][where.y][direction].first = Shape::Circle(circle[where.x][where.y][direction].second,4,col); }
   void draw();

   bool showCircles;

   private:

   pixPosition leftTop;
    vector<Shape> line;
   pair<Shape,Vector2<float> > circle[MAP_DIM_MAX][MAP_DIM_MAX][4+1];
   static bool Vertical;
   static bool Horizontal;
   int maxWidth, maxHeight;
   dimension dim;
   RenderWindow* App;
};

#endif /* GRIDER_H_ */
