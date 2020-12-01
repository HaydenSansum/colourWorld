#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void draw_grid();
        void simulate_grid();
        void capture_history();
        int calculate_neighbouring_values(int i, int j);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Set up
    ofFbo canvas;
    int ww;
    int hh;
    
    // Params
    int grid_num = 400;
    int grid [400][400];
    int temp_grid [400][400];
    int grid_history [400][400];
    ofColor colours[9] = {ofColor::fromHex(0x000003), ofColor::fromHex(0xee8012), ofColor::fromHex(0x0098d8),
                          ofColor::fromHex(0xde3d83), ofColor::fromHex(0xe4bd0b), ofColor::fromHex(0xf54123),
                          ofColor::fromHex(0x457c39), ofColor::fromHex(0xc7943e), ofColor::fromHex(0xbfbabe)};
    int grid_size;
		
};
