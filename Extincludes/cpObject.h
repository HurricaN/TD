#ifndef CP_OBJECT_H
#define CP_OBJECT_H

#include "cpGuiContainer.h"

namespace cp {
        class cpObject
        {
        public:
                cpObject(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
                        float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
                virtual bool SetSize(float width, float height);
                virtual void SetPosition(float posx, float posy);
                virtual void SetFont(std::string filename, unsigned int size);
                virtual void SetBackgroundColor(sf::Color color);
                virtual void SetFontStyle(unsigned long TextStyle);
                virtual void SetFontSize(unsigned int size);
                virtual void SetLabelColor(sf::Color color);
                virtual void SetLabelText(std::string text);
                virtual int CheckState(const sf::Input *input);
                virtual void Show(bool show);
                void SetFocus(bool focus);
                void SetMouseoverColor(sf::Color color);
                bool GetShow();
                sf::Vector2f GetSize();
                sf::Vector2f GetPosition();
                sf::Color GetBackgroundColor();
                sf::Color GetMouseoverColor();
                unsigned long GetFontStyle();
                sf::Color GetLabelColor();
                std::string GetLabelText();

                bool hasFocus, useWheel;
                int wheelDelta, keyCode;
                std::string Font;
                sf::Font *textFont;

        protected:
                virtual void CreateRects(std::string label);
                bool CheckMouseEntered(const sf::Input *input);
                void DrawDashedLine(sf::Vector2f start, sf::Vector2f end);
                void DrawDashedRect(float posx, float posy, float width, float height);
                void SetUseWheel(bool use);

                float Width, Height, PosX, PosY, labelX, labelY;
                sf::RenderWindow* Parent;
                sf::Color backgroundColor, backgroundColorTemp, textColor, outlineColor;
                sf::Color outlineColorTemp, mouseoverColor;
                sf::String Label, tempLabel;
                sf::Shape backRect;
                bool bDefaultSize, mouseIn, lbuttonDown, returnDown, bShow;
                cpGuiContainer *gui;
        };

}

#endif
