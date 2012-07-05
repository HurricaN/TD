#ifndef CPGUI_BASE
#define CPGUI_BASE

#include <cmath>
#include <cstring>

#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>

namespace cp
{
        enum
        {
                CP_DEFAULT = -1,
                CP_ST_MOUSE_ENTER,
                CP_ST_MOUSE_EXIT,
                CP_ST_MOUSE_IN,
                CP_ST_MOUSE_LBUTTON_DOWN,
                CP_ST_MOUSE_LBUTTON_RELEASED,
                CP_ST_CHANGED,
                CP_ST_NONE,
                CP_TXT_RIGHT_ALIGN,
                CP_TXT_LEFT_ALIGN,
                CP_TXT_CENTER_ALIGN
        };

        struct FontData
        {
                sf::Font *myFont;
                short timesUsed;
        };

}

#endif
