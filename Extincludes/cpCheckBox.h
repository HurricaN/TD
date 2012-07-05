#ifndef CPCHECKBOX
#define CPCHECKBOX

#include "cpGUI_base.h"
#include "cpButton.h"

namespace cp
{
        class cpCheckBox : public cpButton
        {
        public:
                cpCheckBox();
                cpCheckBox(sf::RenderWindow* parent, cpGuiContainer *GUI, std::string label,
                        float posx=0, float posy=0);
                void Draw();
                int CheckState(const sf::Input *input);
                bool SetSize(float width, float height);
                void SetChecked(bool checked);
                bool GetChecked();

        private:
                void CreateRects(std::string label);

                sf::Shape line1, line2, line3;
                bool isChecked;

        };
}

#endif

