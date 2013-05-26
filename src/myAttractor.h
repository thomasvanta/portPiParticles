/*
 *  myAttractor.h
 *  ofRaspPiPortfolio
 *
 *  Created by Thomas Van Ta on 13/04/13.
 *  Copyright 2013 __ThomasVanTa__. All rights reserved.
 *
 */

#ifndef MY_ATTRACTOR	// if this class hasn't been defined, the program can define it
#define MY_ATTRACTOR	// by using this if statement you prevent the class to be called more 
						// than once which would confuse the compiler

#include "ofMain.h"
#include "myParticle.h"

class myAttractor {
	
public:
	
	//properties
	float mass;
	float g;
	ofVec2f pos;
	
	bool action;
	
	//methods
	void update(ofVec2f, bool);
	void display(float, ofColor);
	
	ofVec2f attract(myParticle* , int);
	
	//constructor
	myAttractor();
	

private:
	
};

#endif