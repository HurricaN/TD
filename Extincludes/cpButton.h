#ifndef CP_BUTTON_H
#define CP_BUTTON_H

#include "cpObject.h"
#include "cpGuiContainer.h"

namespace cp {
        class cpButton : public cpObject
        {
        public:
                cpButton();
                cpButton(sf::RenderWindow* parent, cpGuiContainer *GUI, std::string label,
                        float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
                virtual void Draw();
                virtual bool SetSize(float width, float height);
                void SetPosition(float posx, float posy);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);
                void SetFontStyle(unsigned long TextStyle);
                void SetFontSize(unsigned int size);
                void SetLabelColor(sf::Color color);
                void SetLabelText(std::string text);
                void Show(bool show);
                virtual int CheckState(const sf::Input *input);

        protected:
                virtual void CreateRects(std::string label);
                void TestLabelFit();

                sf::Color backgroundColor2;
                sf::Color backgroundColor2Temp;

                sf::Shape gradient;
                bool labelInside;
        };
}

#endif

