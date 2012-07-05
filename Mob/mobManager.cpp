/*
 *  mobManager.cpp
 *  TD
 *
 *  Created by Tristan Stérin on 04/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "mobManager.h"

ImageManager* mobManager::imgManager = NULL;

void mobManager::popMobs(string charset, string desc, int n)
{
	for(int iMob = 0 ; iMob < n ; iMob++)
	{
		mob curr(charset, desc, positionToPixPosition(spawn[0],start));
		curr.loadSprite(imgManager->getResource(mobCharsetPath+charset));
		mobList.insert(curr);
	}
}

void mobManager::draw()
{
	for(set<mob>::iterator curr = mobList.begin() ; curr != mobList.end() ; ++curr)
		App->Draw(curr->mobS);
}