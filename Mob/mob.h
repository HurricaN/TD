/*
 *  mob.h
 *  TD
 *
 *  Created by Tristan Stérin on 04/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_MOB_H
#define DEF_MOB_H

#include "common.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class mob
{
	public:
	
		mob() :  mobDefName(""), pos(pixPosition()) {}
		mob(string mobDefName, pixPosition pos) : mobDefName(mobDefName), pos(pos) {}
	
		void loadCharset(Image* img);
		bool operator < (const mob& autre) const
		{
			return pos.x < autre.pos.x;
		}
	
		Sprite mobS;
	private: 
	
		string charsetName, mobDefName;
		pixPosition pos;
};

#endif