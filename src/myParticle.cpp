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
	angle = ofRandomf()*TWO_PI; //takes a random number between -2*Pi and 2*Pi
    age = 0;
}

void myParticle::update()
{
	vel += acc;
	pos += vel;	
	edges();
	//reinitialization of the forces
	acc *= 0;
	age++;
	
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
	acc.limit(2);
}

ofVec2f myParticle::attraction(myAttractor* a, int strength)
{
	//Gravitational attraction
	ofVec2f dir = a->pos - pos;	//direction from attractor to particle
	float d = dir.length();		//distance from attractor to particle
	dir.normalize();
	d = ofClamp(d, 50, 600);	//range
	//float force = (strength * mass * p->mass) / (d*(d/2));	//gravitational force
	float force = (strength * mass * a->mass) / (d*d);	//gravitational force
	dir *= force;				//direction * magnitude = vector
	return dir;
}

void myParticle::randomize()
{
	angle += ofSignedNoise(pos.x, pos.y)*TWO_PI;
    vel.rotate(angle);
    oldPos = pos;
	
}

void myParticle::drawRandom()
{
	ofSetColor(col,ofMap(age,0,20,255,0,true));
    ofLine(oldPos,pos);
	
}

bool myParticle::isDead(int threshold)
{
	return (age >= threshold);	
}

bool myParticle::isAffectedBy(myAttractor* a, bool b, int radius)
{
	ofVec2f dir = pos - a->pos;	//vector from attractor to particle
	float d = dir.length();			//distancia entre ellos
	return (d < radius && b);		//si la distancia es menor que el radio y está activada se verifica	
}

bool myParticle::isMoving(float _speed)
{
	return (vel.length() > _speed);	
}

//esta función mantiene las partículas dentro de la ventana
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