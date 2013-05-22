/*
 *  myAttractor.cpp
 *  ofPortfolio
 *
 *  Created by Thomas Van Ta on 13/04/13.
 *  Copyright 2013 __ThomasVanTa__. All rights reserved.
 *
 */

#include "myAttractor.h"

myAttractor::myAttractor()
{
	action = false;

}

void myAttractor::update(ofVec2f _pos, bool _action)
{
	pos = _pos;
	action = _action;

}

void myAttractor::display(float _mass, ofColor _c)
{
	mass = _mass;
	ofSetColor(_c);
	ofNoFill();
	ofEllipse(pos.x, pos.y, mass, mass);

}

ofVec2f myAttractor::attract(myParticle* p, int strength)
{
	//Gravitational attraction
	ofVec2f dir = pos - p->pos;	//direction from attractor to particle
	float d = dir.length();		//distance from attractor to particle
	dir.normalize();
	d = ofClamp(d, 50, 600);	//range
	//float force = (strength * mass * p->mass) / (d*(d/2));	//gravitational force
	float force = (strength * mass * p->mass) / (d*d);	//gravitational force

	dir *= force;
	if (action) {
		return dir;
	} else {
		return ofPoint(0,0);
	}

	
}