#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	
	//global stuff
	ofHideCursor();
	ofEnableSmoothing();
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofSetCircleResolution(128);
	ofSetWindowTitle("Thomas Van Ta");
	
	//my colors from colourlovers.com
	color1 = (33, 20, 38);
	color2 = (65, 84, 59);
	color3 = (101, 111, 140);
	color4 = (155, 191, 171);
	color5 = (242,239,223);
	
	//assingning colors
	partColor = color1;
	backColor = color5;
	ofBackground(backColor);
	
	//set the number of particles
	nParticles = 1;
	
	//forces variables
	windX = 0.0;
	gX = 0;
	gY = 0.03;
	grav = false;
	drag.set (0,0);
	c = -0.005; //drag coeficient
	
	//array of pointers for the Particles
	//particles = new myParticle*[nParticles];
	particles.resize(nParticles);
	//for (int i = 0; i < nParticles; i++) {
	for (int i = 0; i < particles.size(); i++) {
		//differentiate them
		pos.set (ofRandom(ofGetWidth()-20),ofRandom(ofGetHeight()-20));
		float mass = ofNoise(ofRandom(i));
		
		particles[i] = new myParticle(pos,mass);
	}
	
	//Attractor
	attractColor = ofColor(0,0,0,0);
	strength = 50;
	attractor = new myAttractor;
	attract = false;
	
	//trails
	trails = false;
	trailsSpeed = false;
	oneTrail = false;
	
	//myFbo.allocate(ofGetWidth, ofGetHeight, GL_RGBA32F_ARB);
	// with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	ofFbo::Settings s;
	s.width	= ofGetScreenWidth();
	s.height = ofGetScreenHeight();
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	myFbo.allocate(s);
	myFbo.begin();
	ofClear(color5);	
    myFbo.end();
	
	//connections between particles
	triangulator = new ofxDelaunay;
	triangulatorSpeed = new ofxDelaunay;
		
}

//--------------------------------------------------------------
void testApp::update(){
	
	//calculo de las particulas --------------
	wind.set (windX,0);
	gravity.set (gX,gY);
	//cout << "gX: " << gX	 << endl;
	//cout << "gY: " << gY	 << endl;
	
	triangulator->reset();
	triangulatorSpeed->reset();
	
	for (int i = 0; i < particles.size(); i++) {
		
		drag.set(particles[i]->vel.getNormalized());//copy of the velocity vectors direction
		float speed = particles[i]->vel.length();	//get the vectors length in order to:
		drag.scale(c*speed);						//multiply it by coeficient
		particles[i]->applyForce(drag);				//to get the drag force
		
		//particles[i]->applyForce(wind);
		if (grav) {
			particles[i]->applyForce(gravity);		//apply gravity if selected
		}
		
		if (attract) {
			ofVec2f attForce = particles[i]->attraction(attractor, strength);//calculate attractor
			particles[i]->applyForce(attForce);			//apply attractor
		}
		
		//particles affected by Attractor range
		/*if (particles[i]->isAffectedBy(attractor, attract, 100)) {
		 particles[i]->applyForce(wind);
		 }*/

		particles[i]->update();		
		//particles[i]->randomize();
		
		triangulator->addPoint(particles[i]->pos);
		
		//if the particle is faster enough, we add it to the particles buffer
		if (particles[i]->isMoving(0.4)) {
			particlesBuffer.push_back(new myParticle (particles[i]->pos,particles[i]->mass*2));
		}
		
	}
	
	//update the particles in the buffer and add the points to the triangulation
	for (int i = 0; i < particlesBuffer.size(); i++) {
		particlesBuffer[i]->update(); //for edges purposes
		triangulatorSpeed->addPoint(particles[i]->pos);
	}
	
	attractor->update(ofPoint(ofGetMouseX(),ofGetMouseY()));
	
	triangulator->triangulate();
	//don't triangulate the buffer till there is a minimum of particles in there
	if (particlesBuffer.size() >= 3) {
		triangulatorSpeed->triangulate();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	ofBackground(backColor); //for color modes
	
	//FBO drawing for the degradation effect on lines
	myFbo.begin();
	drawFbo();
	myFbo.end();
	myFbo.draw(0,0);
	
	//Draw methods for the particles
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->display(partColor);
		//particles[i]->drawRandom();
	}
	
	if (trailsSpeed) {
		for (int i = 0; i < particlesBuffer.size(); i++) {
			particlesBuffer[i]->display(ofColor(255, 255, 255, 255));
		}
	}
	
	//drawing the attractor with a random size
	//attractor->display(ofNoise(ofRandom(40))*40, attractColor);
	//attractor->display(ofRandom(40), attractColor);
	attractor->display(70, attractColor);

	
	
	particlesBuffer.clear();	//reset the buffer every frame

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
		switch (key) {
	
			case 'f':
				ofToggleFullscreen();
				break;
			case '1':
				partColor = color1;
				backColor = color5;
				break;
			case '2':
				partColor = color5;
				backColor = color1;
				break;
			case '3':
				partColor = ofColor(255);
				backColor = ofColor(0);
				break;
			case 'g':
				grav = !grav;
				break;
			case '5':
				strength = 3;
				break;
			case '6':
				strength = 10;
				break;
			case '7':
				strength = 50;
				break;
			case '8':
				strength = 100;
				break;
			case '9':
				strength = 500;
				break;
			case 'o':
				nParticles = 10;
				break;
			case 'p':
				nParticles = 100;
				break;
			case 'i':
				nParticles = 3;
				break;
			case 'u':
				nParticles = 2;
				break;
			case 't':
				trails = !trails;
				oneTrail = false;
				break;
			case 'y':
				trailsSpeed = !trailsSpeed;
				oneTrail = false;
				break;
			case 'r':
				oneTrail = !oneTrail;
				break;
			case 'm':
				if (particles.size() > 0) {
					particles.pop_back();
				}
				break;
			case 'n':
				//Add new particles
				particles.push_back( new myParticle(ofPoint(ofRandom(ofGetWidth()-40),ofRandom(ofGetHeight()-40)),ofRandom(0.5,1)) );
				break;
			case ',':
				//Add a big particle
				particles.push_back( new myParticle(ofPoint(ofGetWidth()/2,ofGetHeight()/2),4) );
				break;

		}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	attract = true;
	attractColor = color3;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	attract = false;
	attractColor = ofColor(0,0,0,0);

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::drawFbo(){
	//we clear the fbo if v is pressed. 
	//this completely clears the buffer so you won't see any trails
	if( ofGetKeyPressed('v') ){
		ofClear(backColor.r, backColor.g, backColor.b, 0);
	}	
	
	//some different alpha values for fading the fbo
	//the lower the number, the longer the trails will take to fade away.
	fadeAmnt = 30;
	if(ofGetKeyPressed('z')){
		fadeAmnt = 1;
	}else if(ofGetKeyPressed('x')){
		fadeAmnt = 5;
	}else if(ofGetKeyPressed('c')){
		fadeAmnt = 15;
	}  
	
	//1 - Fade Fbo -------------------------------------------
	
	//this is where we fade the fbo
	//by drawing a rectangle the size of the fbo with a small alpha value,
	//we can slowly fade the current contents of the fbo. 
	ofFill();
	ofSetColor(ofColor(backColor.r, backColor.g, backColor.b, fadeAmnt));
	ofRect(0,0,ofGetWidth(),ofGetHeight());
	
	//2 - Draw graphics --------------------------------------
	ofNoFill();
	ofSetColor(color5);
	//draw the mesh of triangles
	if (trails) {
		ofPushStyle();
		ofSetColor(color5);
		ofSetLineWidth(1.2);
		triangulator->draw();
		ofPopStyle();
	}
	
	//draw the mesh of triangles for the particles in movement
	if (trailsSpeed) {
		ofPushStyle();
		ofSetColor(color4);
		ofSetLineWidth(1.4);
		triangulatorSpeed->draw();
		ofPopStyle();
	}
	
	//connect the two first particles in the vector
	if (oneTrail) {
		ofPushStyle();
		ofSetColor(partColor);
		ofSetLineWidth(1.3);
		ofLine(particles[0]->pos.x, particles[0]->pos.y, particles[1]->pos.x, particles[1]->pos.y);
		ofPopStyle();
	}

}
