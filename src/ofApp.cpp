#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
		ofEnableSmoothing();
		ofSetFullscreen(true);
		
		shader.load( "shadersGL2/shaderVert.c", "shadersGL2/shaderFrag.c" );
		
		fbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
		fbo.begin();
		ofClear(0, 0, 0, 0);
		fbo.end();
		
		fbo2.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
		fbo2.begin();
		ofClear(0, 0, 0, 0);
		fbo2.end();
		
		image1.loadImage("old3.jpg");
		image2.loadImage("new3.jpg");
		
		for (int i=0; i<1000; i++) {
				ofVec2f start(ofRandom(-ofGetWidth(), 2*ofGetWidth()), ofRandom(0, ofGetHeight()));
				ofPtr<SoftBody> ptr(new SoftBody(start.x, start.y, start.x+ofRandom(-100, 100), -2000, ofRandom(7, 53), ofColor(255, 255, 255)));
				softBody.push_back(ptr);
		}
		TIME_SAMPLE_SET_FRAMERATE(60.0f);
		TIME_SAMPLE_SET_PRECISION(5);
		TIME_SAMPLE_SET_AVERAGE_RATE(0.1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
		float time = ofGetElapsedTimef();
		
		TS_START("other1");
		ofSetColor(255);
		image2.draw(0, 0);
		TS_STOP("other1");
		
		//1. Drawing input image into fbo buffer
		TS_START("fbo");
		fbo.begin();
		ofSetColor(255, 255, 255);
		image1.draw(0, 0);
		fbo.end();
		TS_STOP("fbo");
		
		//2. Drawing mask into fbo2 buffer
		TS_START("fbo2");
		fbo2.begin();
		ofBackground( 0, 0, 0 );
		ofSetColor( 255, 255, 255 );
		for (int i=0; i<softBody.size(); i++) {
				softBody[i]->update();
		}
		fbo2.end();
		TS_STOP("fbo2");
		
		//3. Drawing to screen through the shader
		ofEnableAlphaBlending();
		//NOTE: It is important to enable alpha blending for correct shader's working,
		//because shader performs masking by setting alpha-value of output color
		
		TS_START("shader");
		shader.begin();
		shader.setUniform1f( "time", time );	//Pass float parameter "time" to shader	 //Pass mask to shader (fbo2)
		shader.setUniformTexture( "texture1", fbo2.getTextureReference(), 1 );
		//Last parameter 1 is OpenGL texture identifier
		//Draw fbo image
		ofSetColor( 255, 255, 255 );
		fbo.draw( 0, 0 );
		shader.end();
		TS_STOP("shader");
		
		TS_START("other2");
		// debug
		stringstream ss;
    ss << "framerate: " << ofToString(ofGetFrameRate(), 0) << "\nnodeNum:" << ofToString(softBody.size());
    ofDrawBitmapString(ss.str(), 10, 20);

		inOrOut(softBody);
		ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));
		TS_STOP("other2");
}

void ofApp::inOrOut(vector<ofPtr<SoftBody> >& sb){
		for (int i=0; i<sb.size(); i++) {
				if (sb[i]->getCenter().y+sb[i]->getRadius() < 0) {
						sb.erase(sb.begin()+i);
						ofVec2f start(ofRandom(-ofGetWidth(), 2*ofGetWidth()), ofRandom(0, ofGetHeight()));
						ofPtr<SoftBody> ptr(new SoftBody(start.x, start.y, start.x+ofRandom(-100, 100), -2000, ofRandom(7, 53), ofColor(255, 255, 255)));
						sb.push_back(ptr);
				}
		}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
		ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
		
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
