#include "game.h"

game::game()
{
   isRunning = true;
	mainWindow.Create(VideoMode(GAME_W,GAME_H), "Tower Defense");
	
	SFMLMap::setImgManager(&mainImageManager);
	mobManager::setImgManager(&mainImageManager);
	
	mainMap = SFMLMap(&mainWindow, "testbon.map", 0, true);
	
	mainMobManager.setRW(&mainWindow);
	
	/*TEMPORAIRE*/
	mainMobManager.spawn = mainMap.spawn;
	mainMobManager.start = mainMap.start;
}

void game::run()
{
	mainMobManager.popMobs("1.mob", 1);
   while(isRunning)
   {
		Event event;
		while(mainWindow.GetEvent(event))
		{
			switch(event.Type)
			{
				case Event::Closed:
					stop();
               break;
			}
		}
      
		mainWindow.Clear();
		mainMap.draw();
		mainMobManager.draw();
		mainWindow.Display();
   }
}

void game::stop()
{
   isRunning = false;
}

game::~game()
{
   
}
