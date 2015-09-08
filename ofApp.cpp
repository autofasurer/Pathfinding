#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gridsize = 16;
    tileSize = 20;
    tiles.assign(gridsize*gridsize, tile());
    for (int i = 0; i < tiles.size(); i++){
        tiles[i].pos.x = (i % gridsize) * 20;
        tiles[i].pos.y = (i / gridsize) * 20;
        tiles[i].tileSize = tileSize;
        if (i%gridsize == 0){
            tiles[i].wall = 1;
        }
        else if ((i+1)%gridsize == 0){
            tiles[i].wall = 1;
        }
        else if (i < gridsize){
            tiles[i].wall = 1;
        }
        else if (tiles.size()-i < gridsize){
            tiles[i].wall = 1;
        }
        else {
            if (tiles[i+1].wall && tiles[i-1].wall && tiles[i-gridsize].wall && tiles[i+gridsize].wall){
            tiles[i].wall = 0;
                cout << "all wall!" << endl;
            }
            else {
                int x = ofRandom(0, 100);
                tiles[i].wall = x%2;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2-(tileSize*(gridsize/2)), ofGetHeight()/2-(tileSize*(gridsize/2)));
    
    for (int i = 0; i < tiles.size(); i++){
        tiles[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
