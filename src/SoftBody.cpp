//
//  SoftBody.cpp
//  floatingImageTimeTest
//
//  Created by SystemTOGA on 10/7/14.
//
//

#include "SoftBody.h"

SoftBody::SoftBody(float x, float y, float dx, float dy, float r, ofColor col){
		// init
		center.set(x, y);
		start.set(x, y);
		destination.set(dx, dy);
		startDistanceFromDestination = ofDist(x, y, dx, dy);
		radius = r;
		rotAngle = -90;
		springing = 0.0009;
		damping = 0.98;
		organicConstant = 1;
		bodyColor = col;
		
		
    // iniitalize frequencies for corner nodes
    for (int i=0; i<NODES; i++){
				frequency[i] = ofRandom(5, 12);
				// debug
				angle[i] = 0;
				node[i] = ofVec2f(0, 0);
				nodeStart[i] = start;
    }
		//FIXME: resolution
		
//		ofSetCurveResolution(32);
//		ofSetPolyMode(OF_POLY_WINDING_ODD);
}

void SoftBody::drawShape() {
    //  calculate node  starting locations
    float distanceFromDestination = ofDist(center.x, center.y, destination.x, destination.y);
    float sizeDown = distanceFromDestination/startDistanceFromDestination;
    for (int i=0; i<NODES; i++){
				nodeStart[i].set(center.x+cos(DEG_TO_RAD*rotAngle)*radius*sizeDown*sizeDown*sizeDown,
												 center.y+sin(DEG_TO_RAD*rotAngle)*radius*sizeDown*sizeDown*sizeDown);
				rotAngle += 360.0/(float)NODES;
    }
		
    // draw polygon
    // FIXME: tightness?
		// curveTightness(organicConstant);
		
		
		ofPushStyle();
    ofFill();
		ofSetColor(bodyColor);
    ofBeginShape();
    for (int i=0; i<NODES; i++){
				ofCurveVertex(node[i].x, node[i].y);
    }
    for (int i=0; i<3; i++){
				ofCurveVertex(node[i].x, node[i].y);
    }
		ofEndShape();
		ofPopStyle();
}

void SoftBody::moveShape() {
    //move center point
		//A
		//    float deltaX = mouseX-centerX;
		//    float deltaY = mouseY-centerY;
		//B
		//    float deltaX = random(-200, 200);
		//    float deltaY = random(-100, -10);
		//DESTINATION
		ofVec2f delta((destination.x-center.x)*0.02, (destination.y-center.y)*0.02);
    // create springing effect
    delta *= springing;
    accel += delta;
		
    // move predator's center
    center += accel;
		
    // slow down springing
    accel *= damping;
		
    // change curve tightness
    organicConstant = 0;//1-((abs(accelX)+abs(accelY))*.1);
		
    //move nodes
    for (int i=0; i<NODES; i++){
				node[i].x = nodeStart[i].x+sin(DEG_TO_RAD*angle[i])*(accel.x*2);
				node[i].y = nodeStart[i].y+sin(DEG_TO_RAD*angle[i])*(accel.y*2);
				
				angle[i]+=frequency[i];
    }
}

void SoftBody::update(){
		ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
		drawShape();
		moveShape();
}

ofVec2f SoftBody::getCenter(){
    return center;
}


float SoftBody::getRadius(){
    return radius;
}
