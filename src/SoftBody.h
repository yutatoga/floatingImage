//
//  SoftBody.h
//  floatingImageTimeTest
//
//  Created by SystemTOGA on 10/7/14.
//
//

#ifndef __floatingImageTimeTest__SoftBody__
#define __floatingImageTimeTest__SoftBody__

#include <iostream>

#endif /* defined(__floatingImageTimeTest__SoftBody__) */

#include "ofMain.h"
#include "ofxTimeMeasurements.h"
#define NODES 5

class SoftBody{
public:
		SoftBody(float x, float y, float dx, float dy, float r, ofColor col);
		void update();
		ofVec2f getCenter();
		float getRadius();
private:
		void drawShape();
		void moveShape();

		// center point
		ofVec2f center;
		ofVec2f start;
		ofVec2f destination;
		float startDistanceFromDestination;
		float radius;
		float rotAngle;
		float rotAngleStep;
		ofVec2f accel;
		float springing;
		float damping;
		ofColor bodyColor;
		
		//corner nodes
		ofVec2f nodeStart[NODES];
		ofVec2f node[NODES];
		float angle[NODES];
		float frequency[NODES];
		
		// soft-body dynamics
		float organicConstant;
};
