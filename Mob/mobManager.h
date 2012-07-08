/*
 *  mobManager.h
 *  TD
 *
 *  Created by Tristan Stérin on 04/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_MOBMANAGER_H
#define DEF_MOBMANAGER_H

#include "common.h"
#include "mob.h"
#include "SFMLMap.h"
#include "ImageManager.h"

using namespace std;

class mobManager
{
	public:
	
		mobManager() {} 
		
		inline void setRW(RenderWindow* pApp) { App = pApp; }
		
		pixPosition convertSpawnPos(position pos);
		void popMobs(string mobDefName, int n=1);
		static void setImgManager(ImageManager *mgr) { imgManager = mgr; }
		
		void calculeMainChemin();
		bool milieuAtteint(pixPosition pos, position posCase, int orientationDebut);
		
		void draw();
		void drawTrajectoire();
		
		SFMLMap* mainMap;
	private:
	
		set<mob> mobList;
		static ImageManager* imgManager;
		RenderWindow* App;
		vector<pair<position, pair<int,int> > > mainChemin;
};

#endif