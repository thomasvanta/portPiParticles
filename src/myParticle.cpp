/*
 *  myParticle.cpp
 *  ofPortfolio
 *
 *  Created by Thomas Van Ta on 12/04/13.
 *  Copyright 2013 __ThomasVanTa__. All rights reserved.
 *
 */

#include "myParticle.h"

//constructor
myParticle::myParticle(ofVec2f _pos, float _m)
{
	pos = _pos;
	mass = _m;
	diam = mass*30;
	vel.set (0,0);
	acc.set (0,0);
}

void myParticle::update()
{
	vel += acc;
	pos += vel;	
	edges();
	
	//reinitialization of the forces
	acc *= 0;
	
}

void myParticle::display(ofColor _c)
{
	col = _c;
	ofSetColor(col,113);
	ofNoFill();
	ofEllipse(pos.x, pos.y, diam, diam);
}

void myParticle::applyForce(ofVec2f _f)
{
	//variable para multiples fuerzas + newtons 2nd law
	force = _f/mass;
	//ejecucion de la fuerza
	acc += force;
	acc.limit(2.5);
}

bool myParticle::isAffected(bool a, int radius)
{
	ofVec2f dir = pos - ofPoint(ofGetMouseX(),ofGetMouseY());
	float d = dir.length();
	if (d < radius && a) {
		return true;
	} else {
		return false;
	}
	
}

void myParticle::edges()
{
	if (pos.x > (ofGetWidth()-(diam/2))) {
		pos.x = ofGetWidth()-(diam/2);
		vel.x *= -1;
	}
	
	if (pos.x < (0+(diam/2))) {
		pos.x = 0+(diam/2);
		vel.x *= -1;
	}
	
	if (pos.y > (ofGetHeight()-(diam/2))) {
		pos.y = ofGetHeight()-(diam/2);
		vel.y *= -1;
	}
	
	if (pos.y < (0+(diam/2))) {
		pos.y = 0+(diam/2);
		vel.y *= -1;
	}
}