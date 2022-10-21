#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();

	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->base_color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.83);
	ofRotateY(ofGetFrameNum() * 1.3);

	int size = 60;
	for (int x = -300; x <= 300; x += size) {

		for (int y = -300; y <= 300; y += size) {

			for (int z = -300; z <= 300; z += size) {

				int color_index = (int)ofRandom(this->base_color_list.size());

				auto noise_value = ofNoise(x * 0.001, y * 0.001, z * 0.001, ofGetFrameNum() * 0.01);
				if (noise_value > 0.25 && noise_value < 0.5) {

					ofSetColor(0);
					ofFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.95);

					ofSetColor(255);
					ofNoFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.95);
				}
				else if(noise_value > 0.5 && noise_value < 0.75) {

					ofSetColor(this->base_color_list[color_index]);
					ofFill();
					ofDrawSphere(glm::vec3(x, y, z), size * 0.45);
				}
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