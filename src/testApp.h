#pragma once

#include "ofMain.h"
#include "myParticle.h"
#include "myAttractor.h"
#include "ofxDelaunay.h"
#include "mySpring.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void drawFbo();
	
	ofColor color1;
	ofColor color2;
	ofColor color3;
	ofColor color4;
	ofColor color5;

	ofColor bgColor;
	ofColor partColor;
	ofColor backColor;
		
	//array of pointers of particles
	//myParticle** particles;
	vector<myParticle*> particles;
	vector<myParticle*> particlesBuffer;
	int nParticles;
	
	ofVec2f pos;
	
	//forces
	float windX;
	float gX;
	float gY;
	ofVec2f wind;
	ofVec2f gravity;
	bool grav;
	ofVec2f drag;
	float c;
	
	//Attr
	myAttractor *attractor;
	bool attract;
	ofColor attractColor;
	int strength;
	bool trails, trailsSpeed, oneTrail;
	
	//32 bits red, 32 bits green, 32 bits blue, from 0 to 1 in 'infinite' steps	
	ofFbo myFbo; // with alpha
	int fadeAmnt;
	
	ofxDelaunay *triangulator;
	ofxDelaunay *triangulatorSpeed;
	
	
};
