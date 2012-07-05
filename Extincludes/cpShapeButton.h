#ifndef CPSHAPEBUTTON
#define CPSHAPEBUTTON

#include "cpGUI_base.h"
#include "cpObject.h"

namespace cp
{
        class cpShapeButton : public cpObject
        {
        public:
                cpShapeButton(sf::RenderWindow *parent, cpGuiContainer *GUI, sf::Shape *shape,
                        float posx=0, float posy=0);
                cpShapeButton();
                void Draw();
                int CheckState(const sf::Input *input);
                void SetPosition(float posx, float posy);
                void SetShape(sf::Shape *shape);

                bool SetSize(float width, float height);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);
                void SetFontStyle(unsigned long TextStyle);
                void SetFontSize(unsigned int size);
                void SetLabelColor(sf::Color color);
                void SetLabelText(std::string text);

        private:
                void CreateRects(std::string label);
                void ComputeRectDimensions();

                sf::Shape *button;
                float relX, relY;
        };
}

#endif
