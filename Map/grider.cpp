#include "grider.h"
#include "SFMLMap.h"

bool grider::Vertical = true;
bool grider::Horizontal = false;

void grider::addSeparator(int xOry, bool isVertical, int weight, Color col)
{
   if(isVertical)
      line.push_back(Shape::Line(xOry, 0, xOry, maxHeight, weight, col));
   else
      line.push_back(Shape::Line(0, xOry, maxWidth, xOry, weight, col));
}

void grider::genGrid(pixPosition p_leftTop, int width, int height, int weight, Color col)
{
   int xStart = p_leftTop.x;
   int yStart = p_leftTop.y;
   
	dim.first = width;
	dim.second = height;
   
   leftTop = p_leftTop;
   
   for(int i = 0 ; i <= width ; i++)
      line.push_back(Shape::Line(xStart+(TILE_DIM)*i,yStart,xStart+(TILE_DIM)*i,yStart+(TILE_DIM)*height,weight,col));
   for(int i = 0 ; i <= height ; i++)
      line.push_back(Shape::Line(xStart,yStart+(TILE_DIM)*i,xStart+(TILE_DIM)*width,yStart+(TILE_DIM)*i,weight,col));
   
	for(int y = 0 ; y < height ; y++)
		for(int x = 0 ; x < width ; x++)
		{
			Color c_left = Color::Red, c_right = Color::Red, c_top = Color::Red, c_down = Color::Red;
         
			if(y == 0)
				c_top = ourColor::Grey;
			if(y == height-1)
				c_down = ourColor::Grey;
			if(x == 0)
				c_left = ourColor::Grey;
			if(x == width-1)
				c_right = ourColor::Grey;
         
			pixPosition topLeftCase = positionToPixPosition(position(x,y),p_leftTop);
			pixPosition topRightCase = positionToPixPosition(position(x+1,y),p_leftTop);
			pixPosition downLeftCase = positionToPixPosition(position(x,y+1),p_leftTop);
			pixPosition downRightCase = positionToPixPosition(position(x+1,y+1),p_leftTop);
         
			pixPosition upCircle = pixPosition((topLeftCase.x+topRightCase.x)/2, topLeftCase.y);
			circle[x][y][UP].first = (Shape::Circle(to2<float>(upCircle),4,c_top));
			circle[x][y][UP].second = (to2<float>(upCircle));
         
			pixPosition downCircle = pixPosition((downLeftCase.x+downRightCase.x)/2, downLeftCase.y);
			circle[x][y][DOWN].first = (Shape::Circle(to2<float>(downCircle),4,c_down));
			circle[x][y][DOWN].second = (to2<float>(downCircle));
         
			pixPosition leftCircle = pixPosition(topLeftCase.x, (topLeftCase.y+downLeftCase.y)/2);
			circle[x][y][LEFT].first = (Shape::Circle(to2<float>(leftCircle),4,c_left));
			circle[x][y][LEFT].second = (to2<float>(leftCircle));
         
			pixPosition rightCircle = pixPosition(topRightCase.x, (topRightCase.y+downRightCase.y)/2);
			circle[x][y][RIGHT].first = (Shape::Circle(to2<float>(rightCircle),4,c_right));
			circle[x][y][RIGHT].second = to2<float>(rightCircle);
         
			pixPosition centerCircle = pixPosition((topLeftCase.x+topRightCase.x)/2,(topRightCase.y+downRightCase.y)/2);
			circle[x][y][TOURABLE].first = (Shape::Circle(to2<float>(centerCircle),4,Color::Green));
			circle[x][y][TOURABLE].second = to2<float>(centerCircle);
		}
}

void grider::draw()
{
   for(size_t i = 0 ; i < line.size() ; i++)
		App->Draw(line[i]);
   
	if(showCircles)
		for(int y = 0 ; y < dim.second ; y++)
			for(int x = 0 ; x < dim.first ; x++)
			{
				for(int iDir = 0 ; iDir < 4 ; iDir++)
					App->Draw(circle[x][y][iDir].first);
				App->Draw(circle[x][y][TOURABLE].first);
			}
}
