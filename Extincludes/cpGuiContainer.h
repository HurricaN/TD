#ifndef CP_GUI_CONTAINER_H
#define CP_GUI_CONTAINER_H

namespace cp {

        class cpObject;

        class cpGuiContainer
        {
        public:
                cpGuiContainer();
                ~cpGuiContainer();
                void Register(cpObject* object);
                void Unregister(cpObject* object);
                void SetObjectFocus(cpObject* object, bool focused);
                void NextObjectFocus();
                void AcceptsKeys(bool accept, bool UseArrowKeys);
                void ProcessKeys(sf::Event *evt);
                void Show(bool show);
                bool GetShow();
                void ReleaseUnusedFonts();
                sf::Font* GetFont(std::string filename, unsigned int fontSize=20);

                std::vector<cpObject*> control;
                std::string defaultFilename;
                bool acceptsKeys, useArrowKeys, bShow;
                sf::Clock clock;

        private:
                typedef std::map<std::string, FontData> FontMap;
                std::map<std::string, FontData> fontMap;
                short rightleft;
                sf::Font *defaultFont;
        };

}

#endif
