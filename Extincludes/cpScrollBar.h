#ifndef CP_SCROLL_BAR_H
#define CP_SCROLL_BAR_H

#include "cpGuiContainer.h"
#include "cpButton.h"

namespace cp {
        class cpScrollBar
        {
        public:
                cpScrollBar();
                cpScrollBar(sf::RenderWindow *parent, cpGuiContainer *GUI, float length,
                        int ViewableLines, int TotalLines, float posx, float posy);
                ~cpScrollBar();
                void Draw();
                int CheckState(const sf::Input *input);
                void MoveSlider(short direction);
                void Repopulate(int ViewableLines, int TotalLines);
                void SetPosition(float posx, float posy);
                void SetSize(float length, int ViewableLines);

        private:
                void MoveLines();
                void CreateRects();
                void CheckSliderValid();
                bool CheckMouseEntered(const sf::Input *input);
                int CheckMouseSlider(const sf::Input *input);

                sf::RenderWindow *Parent;
                sf::Shape groove, sliderShape, upArrow, downArrow, line1, line2, line3;
                sf::Clock clock, clock2;
                sf::Color backgroundColor, backgroundColor2;
                cpGuiContainer *gui;
                cpButton *upButton, *downButton;
                float Length, PosX, PosY, lineInc, currentPosition, slLength, mouseY;
                int viewableLines, totalLines;
                bool mouseDown, clickGroove, sliderDrag, slDown;
        };
}

#endif
