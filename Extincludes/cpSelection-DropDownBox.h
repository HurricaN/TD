#ifndef CPSELECTIONBOX
#define CPSELECTIONBOX

#include "cpGUI_base.h"
#include "cpScrollBar.h"

namespace cp
{
        class cpSelectionBox : public cpObject
        {
        public:
                cpSelectionBox(sf::RenderWindow *parent, cpGuiContainer *GUI, float posx=0,
                        float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
                cpSelectionBox();
                ~cpSelectionBox();
                void Draw();
                void AddChoice(std::string choice);
                void RemoveLastChoice();
                int CheckState(const sf::Input *input);
                void SetSelection(int sel);
                int GetSelection();
                bool SetSize(float width, float height);
                void SetFontSize(unsigned int size);
                void SetFontStyle(unsigned long TextStyle);
                void CheckTextWidth();
                void SetPosition(float posx, float posy);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);

                std::vector<sf::String> choices;
                int viewableLines;

        private:
                void CreateRects(std::string label);
                int currentSelection, currentStartingLine;
                unsigned int fontSize;
                sf::Shape selBox;
                sf::Clock clock;
                bool mouseDown, keyDown;
                cp::cpScrollBar *scrollbar;
        };

        class cpDropDownBox : public cpObject
        {
        public:
                cpDropDownBox(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
                        float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
                ~cpDropDownBox();
                void CreateRects(std::string label);
                void Draw();
                int CheckState(const sf::Input *input);
                void AddChoice(std::string choice);
                void RemoveLastChoice();
                void SetSelection(int sel);
                int GetSelection();
                bool SetSize(float width, float height);
                void SetFontSize(unsigned int size);
                void SetFontStyle(unsigned long TextStyle);
                void SetPosition(float posx, float posy);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);
                void SetMaxDepth(float depth);
                void SetLabelColor(sf::Color color);


        private:
                void CheckTextWidth();
                void MoveButton();

                cpButton *downBtn;
                cpSelectionBox *sBox;
                sf::Shape downArrow;
                sf::Color btnBackground, tempTextColor;
                float maxDepth, depth;

        };
}

#endif

