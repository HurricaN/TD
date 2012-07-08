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

pixPosition mobManager::convertSpawnPos(position pos)
{
	pixPosition toReturn = positionToPixPosition(pos,mainMap->getStart());
	/*A S OCCUPER DE*/
	toReturn.x += rand()%32;
	return toReturn;
}

void mobManager::popMobs(string mobDefName, int n)
{
	mob newMob(mobDefName, convertSpawnPos(mainMap->spawn[0]));
	
	/*GENERATION DE TRAJECTOIRE*/
	
}

int orientationInitiale(position pos)
{
	if(pos.y == 0)
		return DOWN;
	return UP;
}

void mobManager::calculeMainChemin()
{
	position debut = mainMap->spawn[0];
	queue<pair<position,int> > aVisiter;
	bool dejaVu[MAP_DIM_MAX][MAP_DIM_MAX];
	for(int i = 0 ; i < MAP_DIM_MAX ; i++)
		for(int j = 0 ; j < MAP_DIM_MAX ; j++)
			dejaVu[i][j] = false;
	
	aVisiter.push(make_pair(debut, orientationInitiale(debut)));
	dejaVu[debut.x][debut.y] = true;
	
	while(!aVisiter.empty())
	{
		pair<position,int> curr = aVisiter.front();
		aVisiter.pop();
		pair<position,int> voisin;
		for(int iDir = 0 ; iDir < 4 ; iDir++)
		{
			voisin.first = curr.first + basic_dep[iDir];
			if(mainMap->getColl(curr.first,iDir) && mainMap->valide(voisin.first))
				if(!dejaVu[voisin.first.x][voisin.first.y])
				{
					dejaVu[voisin.first.x][voisin.first.y] = true;
					voisin.second = iDir;
					aVisiter.push(voisin);
				}
		}
		mainChemin.push_back(make_pair(curr.first,make_pair(curr.second, voisin.second)));
	}
}

void mobManager::draw()
{
	for(set<mob>::iterator curr = mobList.begin() ; curr != mobList.end() ; ++curr)
		App->Draw(curr->mobS);
}