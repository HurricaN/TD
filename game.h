#ifndef GAME_H_
#define GAME_H_

#include <cstdio>
#include "common.h"

#include "SFMLMap.h"
#include "Extincludes/RessourceManager.h"
#include "mobManager.h"

using namespace sf;

class game
{
public:
   
   game();
   ~game();
   
   void run(); //Boucle principale
   void stop(); //Pour que les engine puissent arreter le jeu
   
private:
   
   bool isRunning; //Condition d'arret
	RenderWindow mainWindow;
	SFMLMap mainMap;
	ImageManager mainImageManager;
	mobManager mainMobManager;
};



#endif /* GAME_H_ */
