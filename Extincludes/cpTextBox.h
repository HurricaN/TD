#ifndef CPTEXTBOX
#define CPTEXTBOX

#include "cpGUI_base.h"
#include "cpObject.h"
#include "cpScrollBar.h"

namespace cp
{
        class cpTextBox : public cpObject
        {
        public:
                cpTextBox(sf::RenderWindow *parent, cpGuiContainer *GUI, float posx=0,
                        float posy=0, float width=CP_DEFAULT, float height=CP_DEFAULT);
                ~cpTextBox();
                void Draw();
                void LoadFile( const char* const filename);
                int CheckState(const sf::Input *input);

                bool SetSize(float width, float height);
                void SetPosition(float posx, float posy);
                void SetFont(std::string filename, unsigned int size);
                void SetBackgroundColor(sf::Color color);
                void SetFontStyle(unsigned long TextStyle);
                void SetFontSize(unsigned int size);
                void SetLabelColor(sf::Color color);


        private:
                std::vector<std::string> lineStrings;
                std::vector<sf::String> lineSFStrings;
                const char* Filename;
                int viewableLines, totalLines, startingLine;
                unsigned int fontSize;
                cpScrollBar *scrollbar;
                sf::Clock clock;
        };
}

#endif
