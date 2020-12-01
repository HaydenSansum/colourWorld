#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Set up FBO
    ww = 800;
    hh = 800;
    canvas.allocate(ww, hh, GL_RGBA);
    
    // Parameters
    grid_size = (int) ww / grid_num;
    ofSetFrameRate(8);
    
    // Build a random initial grid with a solitary white pixel
    
    for (int i = 0; i < grid_num; i++){
        for (int j = 0; j < grid_num; j++){
                
            float random_val = ofRandom(1);
            if (random_val < 0.2) {
                grid[i][j] = 1;
                grid_history[i][j] = 1;
            } else {
                grid[i][j] = 0;
                grid_history[i][j] = 0;
            }

        }
    }
   ofSleepMillis(1000);
}

//--------------------------------------------------------------
void ofApp::update(){

    simulate_grid();
    draw_grid();
    capture_history();
    
    // With a very small chance inject a random color
//    float rand_num = ofRandom(1);
//    if (rand_num < 0.15) {
//        int rand_i = ofRandom(grid_num);
//        int rand_j = ofRandom(grid_num);
//        int rand_color = ofRandom(2);
//        grid[rand_i][rand_j] = rand_color;
//    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    canvas.draw(0,0);
   
}

//--------------------------------------------------------------
void ofApp::draw_grid(){

    canvas.begin();
    ofBackground(0);
    for (int i = 0; i < grid_num; i++){
        for (int j = 0; j < grid_num; j++){
            
            int x = ofMap(i, 0, grid_num, 0, ww+1);
            int y = ofMap(j, 0, grid_num, 0, hh+1);
            
            int grid_value = grid_history[i][j];
        
            ofColor cur_color;
            if (grid_value == 0) {
                cur_color = ofColor(0);
            } else {
                cur_color = ofColor(0);
                cur_color.setHsb(70 + grid_value, 180 - (grid_value/5), 180 - (grid_value/2));
            }
            
            ofSetColor(cur_color);
            ofDrawRectangle(x, y, grid_size, grid_size);
            
        }
    }
    
    canvas.end();
   
}

//--------------------------------------------------------------
void ofApp::simulate_grid(){

    int sum_neighbours;
    
    // Assign to temp grid
    for (int i = 0; i < grid_num; i++){
        for (int j = 0; j < grid_num; j++){
            temp_grid[i][j] = grid[i][j];
        }
    }
    
    
    for (int i = 0; i < grid_num; i++){
        for (int j = 0; j < grid_num; j++){
            
            // Calculate neighbouring values
            sum_neighbours = calculate_neighbouring_values(i, j);
            
            if (grid[i][j] == 1) {
                if (sum_neighbours == 2 || sum_neighbours == 3) {
                    grid[i][j] = 1;
                } else {
                    grid[i][j] = 0;
                }
            } else {
                if (sum_neighbours == 3) {
                    grid[i][j] = 1;
                } else {
                    grid[i][j] = 0;
                }
            }
            
            
            
            
        }
    }
    
}

//--------------------------------------------------------------
int ofApp::calculate_neighbouring_values(int i, int j){
    
    int sum_neighbours;
    
    if (i == 0 && j == 0) {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i][j + 1] + temp_grid[i + 1][j + 1];
    } else if (i == (grid_num-1) && j == (grid_num-1)) {
        sum_neighbours = temp_grid[i - 1][j] + temp_grid[i][j - 1] + temp_grid[i - 1][j - 1];
    } else if (i == 0 && j == (grid_num-1)) {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i][j - 1] + temp_grid[i + 1][j - 1];
    } else if (i == (grid_num-1) && j == 0) {
        sum_neighbours = temp_grid[i - 1][j] + temp_grid[i][j + 1] + temp_grid[i - 1][j + 1];
    } else if (i == 0) {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i][j + 1] + temp_grid[i][j - 1] + temp_grid[i + 1][j + 1] + temp_grid[i + 1][j - 1];
    } else if (j == 0) {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i - 1][j] + temp_grid[i][j + 1] + temp_grid[i + 1][j + 1] + temp_grid[i - 1][j + 1];
    } else if (i == (grid_num-1)) {
        sum_neighbours = temp_grid[i - 1][j] + temp_grid[i][j + 1] + temp_grid[i][j - 1] + temp_grid[i - 1][j - 1] + temp_grid[i - 1][j + 1];
    } else if (j == (grid_num-1)) {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i - 1][j] + temp_grid[i][j - 1] + + temp_grid[i - 1][j - 1] + + temp_grid[i + 1][j - 1];
    } else {
        sum_neighbours = temp_grid[i + 1][j] + temp_grid[i - 1][j] + temp_grid[i][j + 1] + temp_grid[i][j - 1] + temp_grid[i + 1][j + 1] + temp_grid[i + 1][j - 1] + temp_grid[i - 1][j + 1] + temp_grid[i - 1][j - 1];
    }
    
    return sum_neighbours;
}

//--------------------------------------------------------------
void ofApp::capture_history(){
    
    for (int i = 0; i < grid_num; i++){
        for (int j = 0; j < grid_num; j++){
            
            int current_val = grid[i][j];
            int historic_val = grid_history[i][j];
            
            if (current_val == 1) {
                grid_history[i][j] = 1;
            } else if (grid_history[i][j] > 0) {
                grid_history[i][j] = grid_history[i][j] + 1;
            } else {
                grid_history[i][j] = 0;
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
            ofPixels p;
            canvas.readToPixels(p);
            ofSaveImage(p, ofGetTimestampString() + ".png");
        }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
