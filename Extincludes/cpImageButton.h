#ifndef CPIMAGEBUTTON
#define CPIMAGEBUTTON

#include "cpGUI_base.h"
#include "cpObject.h"

namespace cp
{
        class cpImageButton : public cpObject
        {
        public:
                cpImageButton();
                cpImageButton(sf::RenderWindow *parent, cpGuiContainer *GUI,
                        sf::Image *image, float posx=0, float posy=0);
                void Draw();
                int CheckState(const sf::Input *input);
                bool SetSize(float width, float height);
                void SetPosition(float posx, float posy);
                void SetBackgroundColor(sf::Color color);
                void SetImage(sf::Image *image);
                void Show(bool show);

        private:
                sf::Sprite sprite;
        };
}

#endif
