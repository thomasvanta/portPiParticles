/*
 *  myAttractor.cpp
 *  ofRaspPiPortfolio
 *
 *  Created by Thomas Van Ta on 13/04/13.
 *  Copyright 2013 __ThomasVanTa__. All rights reserved.
 *
 */

#include "myAttractor.h"

myAttractor::myAttractor()
{

}

void myAttractor::update(ofVec2f _pos)
{
	pos = _pos;
}

void myAttractor::display(float _mass, ofColor _c)
{
	mass = _mass;
	ofSetColor(_c);
	ofNoFill();
	ofEllipse(pos.x, pos.y, mass, mass);

}