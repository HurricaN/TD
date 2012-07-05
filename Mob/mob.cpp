/*
 *  mob.cpp
 *  TD
 *
 *  Created by Tristan Stérin on 04/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "mob.h"

void mob::loadSprite(Image* img)
{
	mobS.SetPosition(to2<float>(pos));
	img->CreateMaskFromColor(img->GetPixel(0,0),0);
	mobS.SetImage(*img);
}