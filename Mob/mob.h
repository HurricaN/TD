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

struct mob
{
	string charset, desc;
	pixPosition pos;
	Sprite mobS;
	
	void loadSprite(Image* img);
	
	mob() : charset(""), desc(""), pos(pixPosition()) {}
	mob(string charset, string desc, pixPosition pos) : charset(charset), desc(desc), pos(pos) {}
	
	bool operator < (const mob& autre) const
	{
		return pos.x < autre.pos.x;
	}
};

#endif