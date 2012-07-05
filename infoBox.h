#ifndef DEF_INFO_BOX_H
#define DEF_INFO_BOX_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../common.h"

using namespace std;
using namespace sf;

class infoBox
{
   public:

      infoBox() {}
      infoBox(RenderWindow* App, position upLeft, position upRight, string font_path) : App(App), upLeft(upLeft), upRight(upRight)
      {
         nbEndl = 0;
         boxDim.first = upRight.x-upLeft.x;
         boxDim.second = 0;
         font.LoadFromFile(font_path);
      }

      void addItem(string txt, int size, int align, Color col=Color::White, int return_space=0)
      {
         if(return_space == 0)
            return_space = size;
         String curr;
         curr.SetText(txt);
         curr.SetFont(font);
         curr.SetSize(size);
         curr.SetColor(col);

         if(align == Center)
            curr.SetPosition((boxDim.first-(curr.GetRect().Right-curr.GetRect().Left))/2, upLeft.y+nbEndl*return_space);
         else if(align == Left)
            curr.SetPosition(upLeft.x,upLeft.y+nbEndl*return_space);

         item.push_back(curr);
         if(txt[txt.size()-1] == '\n')
            nbEndl++;
         boxDim.second += curr.GetRect().GetHeight();
      }

      void draw()
      {
         for(int iItem = 0 ; iItem < item.size() ; iItem++)
            App->Draw(item[iItem]);
      }

      position upLeft, upRight;
      dimension boxDim;
      Font font;
      vector<String> item;
      int nbEndl;

      static int Center;
      static int Left;

      RenderWindow* App;
};

int infoBox::Center = 0;
int infoBox::Left = 1;

#endif
