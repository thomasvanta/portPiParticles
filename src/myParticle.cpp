/*
 *  myParticle.cpp
 *  ofRaspPiPortfolio
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
	ofSetColor(col,255);
	ofNoFill();
	ofEllipse(pos.x, pos.y, diam, diam);
}

void myParticle::applyForce(ofVec2f _f)
{
	//variable para multiples fuerzas + newtons 2nd law
	force = _f/mass;
	//ejecucion de la fuerza
	acc += force;
	//limit for not getting crazy velocity
	acc.limit(3);
}

bool myParticle::isAffected(bool a, int radius)
{
	ofVec2f dir = pos - ofPoint(ofGetMouseX(),ofGetMouseY());//vector entre 'attractor' y particula
	float d = dir.length();			//distancia entre ellos
	if (d < radius && a) {			//si la distancia es menor que el radio y está activada
		return true;				//retornar verdadero
	} else {
		return false;
	}
	
}

bool myParticle::isMoving(float _speed)
{
	if (vel.length() > _speed) {
		return true;
	} else {
		return false;
	}

	
}

//esta función mantiene las partículas en la ventana
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