/*
 *  mobManager.cpp
 *  TD
 *
 *  Created by Tristan St√©rin on 04/07/12.
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

bool mobManager::milieuAtteint(pixPosition pos, position posCase, int orientationDebut)
{
	IntRect rectCase = mainMap->getCaseRect(posCase);
	pixPosition milieu = pixPosition((rectCase.Right+rectCase.Left)/2,(rectCase.Top+rectCase.Bottom)/2);
	
	switch(orientationDebut)
	{
		case DOWN:
			return pos.y >= milieu.y;
			break;
		case UP:
			return pos.y <= milieu.y;
			break;
		case RIGHT:
			return pos.x >= milieu.x;
			break;
		case LEFT:
			return pos.x <= milieu.x;
			break;
		
		default:
			return 0;
			break;
	}
}

int orientationInitiale(position pos)
{
	if(pos.y == 0)
		return DOWN;
	return UP;
}


void mobManager::popMobs(string mobDefName, int n)
{


	for(int iMob = 0 ; iMob < n ; iMob++)
	{
	mob newMob(mobDefName, convertSpawnPos(mainMap->spawn[0]));
	
	/*GENERATION DE TRAJECTOIRE*/
	
	/*Concept : on divise les cases en deux par rapport au milieu, on a une orientation en entrant dans la case
	et une en sortant de milieu, c'est pour gerer les angles et ca permettra de changer facilement l'animation quand y'a un tournant.
	
	Donc la trajectoire c'est un vector de pair qui contient 1 : la position à l'instant t
	2 : une paire d'orientation : l'orientation que j'ai quand j'entre dans la case et celle quand je sors
	
	*/
	
	
	//Case du mileu
	IntRect rectCase = mainMap->getCaseRect(mainMap->spawn[0]);
	pixPosition milieu = pixPosition((rectCase.Right+rectCase.Left)/2,(rectCase.Top+rectCase.Bottom)/2);
	
	
	//Les trajectoires sont bien gérées (juste les bails pour la case de départ cf en dessous) quand la case de spawn est en en haut, il faut généraliser le machin, pas très dur
	//Pour placer la premiere position de maniere random : on ajoute + ou - un nombre entre 1 et 10 au x du milieu
	int coeff = rand()%5;
	if(rand()%2)
		coeff*=-1;
	//Premiere position du mob
	newMob.pos = pixPosition(milieu.x+coeff, mainMap->getStart().y);
	pixPosition currPos = newMob.pos;
	
	//qu'on ajoute à la trajectoire
	newMob.trajectoire.push_back(make_pair(newMob.pos,make_pair(orientationInitiale(mainMap->spawn[0]),orientationInitiale(mainMap->spawn[0]))));
	
	//Pour chaque case du chemin qu'on a trouvé avec calculeMainChemin() on va trouver des points aléatoires à la trajectoire en deux parties, 
	//D'abord du début au milieu puis du milieu à la fin de la case
	for(int iCase = 0 ; iCase < mainChemin.size() ; iCase++)
	{
		while(!milieuAtteint(currPos,mainChemin[iCase].first,mainChemin[iCase].second.first))
		{
			//Ordre aléatoire pour les directions : donne l'aspect aléatoire à la trajectoire
			int *ordreDeTest = genMelangeAleatoire(4);
			pixPosition voisin = currPos+(basic_dep[mainChemin[iCase].second.first]*newMob.attributes.velocity);
			for(int i = 0 ; i < 4 ; i++)
			{
				if(ordreDeTest[i] == opposite(mainChemin[iCase].second.first))
					continue;
				voisin += basic_dep[ordreDeTest[i]]*newMob.attributes.velocity;
				if(isInRect(voisin,mainMap->getCaseRect(mainChemin[iCase].first)))
					break;
			}
			
			currPos = voisin;
			
			newMob.trajectoire.push_back(make_pair(currPos,make_pair(mainChemin[iCase].second.first,mainChemin[iCase].second.first)));
			delete[] ordreDeTest;
		}
		
		while(isInRect(currPos,mainMap->getCaseRect(mainChemin[iCase].first)))
		{
			int *ordreDeTest = genMelangeAleatoire(4);
			pixPosition voisin = currPos+(basic_dep[mainChemin[iCase].second.second]*newMob.attributes.velocity);
			for(int i = 0 ; i < 4 ; i++)
			{
				if(ordreDeTest[i] == opposite(mainChemin[iCase].second.second))
					continue;
				voisin += basic_dep[ordreDeTest[i]]*newMob.attributes.velocity;
				if(isInRect(voisin,mainMap->getCaseRect(mainChemin[iCase].first)))
					break;
			}
			
			currPos = voisin;
			if(isInRect(currPos,mainMap->getCaseRect(mainChemin[iCase].first)))
				newMob.trajectoire.push_back(make_pair(currPos,make_pair(mainChemin[iCase].second.first,mainChemin[iCase].second.first)));
			delete[] ordreDeTest;
		}

	}
	
	mobList.insert(newMob);
	}
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

void mobManager::drawTrajectoire()
{
	Color c[3] = {Color::Red, Color::Black, Color::Blue};
	int iC = 0;
	for(set<mob>::iterator curr = mobList.begin() ; curr != mobList.end() ; ++curr)
	{
		for(int i = 0 ; i < curr->trajectoire.size() ; i++)
			App->Draw(Shape::Circle(to2<float>(curr->trajectoire[i].first),1,c[iC]));
		iC++;
	}
}


