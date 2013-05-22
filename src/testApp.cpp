#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	
	ofHideCursor();
	//my colors from colourlovers.com
	color1 = (33, 20, 38);
	color2 = (65, 84, 59);
	color3 = (101, 111, 140);
	color4 = (155, 191, 171);
	color5 = (242,239,223);
	
	partColor = color1;

	backColor = color5;
	ofBackground(backColor);
	
	ofEnableSmoothing();
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	
	//set the number of particles
	nParticles = 100;
	
	//forces variables
	windX = 0.0;
	gX = 0;
	gY = 0.03;
	grav = true;
	drag.set (0,0);
	c = -0.005; //drag coeficient
	
	//array of pointers for the Particles
	particles = new myParticle*[nParticles];
	for (int i = 0; i < nParticles; i++) {
		//differentiate
		pos.set (ofRandom(ofGetWidth()-40),ofRandom(ofGetHeight()-40));
		float mass = ofNoise(ofRandom(i));
		
		particles[i] = new myParticle(pos,mass);
	}
	
	//Attractor
	attractColor = ofColor(0,0,0,0);
	strength = 50;
	attractor = new myAttractor;
	attract = false;
	trails = false;
	oneTrail = false;
	
	//trails
	//rgbaFboFloat.allocate(400, 400, GL_RGBA32F_ARB);
	// with alpha, 32 bits red, 32 bits green, 32 bits blue, 32 bits alpha, from 0 to 1 in 'infinite' steps
	ofFbo::Settings s;
	s.width			= ofGetScreenWidth();
	s.height			= ofGetScreenHeight();
	s.internalformat   = GL_RGBA;
	s.useDepth			= true;
	rgbaFboFloat.allocate(s);
	rgbaFboFloat.begin();
	ofClear(color5);	
    rgbaFboFloat.end();
	
	triangulator = new ofxDelaunay;

	
}

//--------------------------------------------------------------
void testApp::update(){
	
	//calculo de las particulas
	//wind.set (windX,0);
	wind.set (1,0);
	gravity.set (gX,gY);
	//cout << "gX: " << gX	 << endl;
	//cout << "gY: " << gY	 << endl;
	
	triangulator->reset();
	
	for (int i = 0; i < nParticles; i++) {
		//particles[i]->applyForce(wind);
		if (grav) {
			particles[i]->applyForce(gravity);
		}
		drag.set(particles[i]->vel.getNormalized());//copy of the velocity vectors direction
		float speed = particles[i]->vel.length();	//get the vectors length in order to:
		drag.scale(c*speed);						//multiply it by coeficient
		particles[i]->applyForce(drag);
		ofVec2f attForce = attractor->attract(particles[i], strength);
		particles[i]->applyForce(attForce);
		particles[i]->update();
		
		triangulator->addPoint(particles[i]->pos);
		
		if (particles[i]->isAffected(attract, 100)) {
			//particles[i]->applyForce(wind);
		}
		
	}
	
	attractor->update(ofPoint(ofGetMouseX(),ofGetMouseY()), attract);
	
	triangulator->triangulate();
	
	rgbaFboFloat.begin();
	drawFboTest();
	rgbaFboFloat.end();

}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	ofBackground(backColor);
	rgbaFboFloat.draw(0,0);
	
	for (int i = 0; i < nParticles; i++) {
		particles[i]->display(partColor);
	}
	
	attractor->display(ofNoise(ofRandom(40))*40, attractColor);
	//attractor->display(ofRandom(40), attractColor);
	//attractor->display(40, attractColor);

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
			case 'g':
				grav = !grav;
				break;
			case '3':
				strength = 3;
				break;
			case '4':
				strength = 10;
				break;
			case '5':
				strength = 50;
				break;
			case '6':
				strength = 100;
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
				break;
			case 'r':
				oneTrail = !oneTrail;
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
	//gravity.set(0.0);
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

void testApp::drawFboTest(){
	//we clear the fbo if c is pressed. 
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
	
	//1 - Fade Fbo
	
	//this is where we fade the fbo
	//by drawing a rectangle the size of the fbo with a small alpha value, we can slowly fade the current contents of the fbo. 
	ofFill();
	ofSetColor(ofColor(backColor.r, backColor.g, backColor.b, fadeAmnt));
	ofRect(0,0,ofGetWidth(),ofGetHeight());
	
	//2 - Draw graphics
	
	ofNoFill();
	ofSetColor(color5);
	if (trails) {
		triangulator->draw();
	}
	
	if (oneTrail) {
		ofLine(particles[0]->pos.x, particles[0]->pos.y, particles[1]->pos.x, particles[1]->pos.y);
	}

}
