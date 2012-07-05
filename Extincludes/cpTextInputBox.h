#ifndef CPTEXTINPUTBOX
#define CPTEXTINPUTBOX

#include "cpGUI_base.h"
#include "cpGuiContainer.h"
#include "cpObject.h"

namespace cp
{
        class cpTextInputBox : public cpObject
        {
        public:
                cpTextInputBox();
                cpTextInputBox(sf::RenderWindow *parent, cpGuiContainer *GUI, std::string label,
                        float posx=0, float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT,
                        int Style=CP_TXT_LEFT_ALIGN);
                void Draw();
                int CheckState(const sf::Input *input);
                bool SetSize(float width, float height);
                void SetPosition(float posx, float posy);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);
                void SetFontStyle(unsigned long TextStyle);
                void SetFontSize(unsigned int size);
                void SetLabelColor(sf::Color color);
                void SetLabelText(std::string text);
                void ProcessTextInput(sf::Event *evt);


        private:
                void CreateRects(std::string label);
                bool CheckTextFit();

                sf::Shape caret;
                bool bTooBig, caretOn;
                std::string tempText;
                sf::String tempLabel;
                float elapsedTime;
                int style;
        };
}

#endif
