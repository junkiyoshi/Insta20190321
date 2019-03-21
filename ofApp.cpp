#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->locations.clear();

	int radius = 300;
	for (int i = 0; i < 500; i++) {

		auto base_location = glm::vec3(ofRandom(-radius, radius), (int)(ofRandom(-radius, radius) + ofGetFrameNum() * 5) % (radius * 2) - radius, ofRandom(-radius, radius));
		glm::vec3 location = glm::normalize(base_location) * radius;
		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofGetFrameNum() % 300, 0, 300, -PI, PI), glm::vec3(0, 1, 0));
		location = glm::vec4(location, 0) * rotation_y;
		this->locations.push_back(location);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	for (auto& location : this->locations) {

		ofDrawSphere(location, 3);
		for (auto& other : this->locations) {

			if (location == other) { continue; }
			float distance = glm::distance(location, other);
			if(distance < 50){
				
				ofDrawLine(location, other);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}