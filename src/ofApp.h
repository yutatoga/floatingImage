#pragma once

#include "ofxVectorGraphics.h"
#include "ofMain.h"
#include "softbody.h"
class ofApp : public ofBaseApp{
		
public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofShader shader;	//Shader
		ofFbo fbo;			//First buffer for input image
		ofFbo fbo2;			//Second buffer for mask
		
		ofImage image1, image2;		//Sunflower image
		
		//vectr graphics sample
		ofxVectorGraphics output;
		bool capture;
		bool bFill;
		
		vector <ofPoint> pts;
		vector<ofPtr<SoftBody> > softBody;
		
		
private:
		void inOrOut(vector<ofPtr<SoftBody> >& sb);
};
