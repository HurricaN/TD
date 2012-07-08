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

void mobManager::popMobs(string mobDefName, int n)
{

}

void mobManager::draw()
{
	for(set<mob>::iterator curr = mobList.begin() ; curr != mobList.end() ; ++curr)
		App->Draw(curr->mobS);
}