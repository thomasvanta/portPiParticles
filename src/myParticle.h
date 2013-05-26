/*
 *  myParticle.h
 *  ofRaspPiPortfolio
 *
 *  Created by Thomas Van Ta on 12/04/13.
 *  Copyright 2013 __ThomasVanTa__. All rights reserved.
 *
 */

#ifndef MY_PARTICLE	// if this class hasn't been defined, the program can define it
#define MY_PARTICLE	// by using this if statement you prevent the class to be called more 
					// than once which would confuse the compiler

#include "ofMain.h"

class myParticle {
	
public:
	
	//properties
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;
	ofVec2f force;
	float mass;
	float diam;
	ofColor col;
	
	//methods
	void update();
	void display(ofColor);
	
	void applyForce(ofVec2f);
	void edges();
	
	bool isAffected(bool, int);
	bool isMoving(float);
	
	//constructor
	myParticle(ofVec2f, float);
	
	
private:
	
};

#endif