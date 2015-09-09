#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gridsize = 16;
    tileSize = 20;
    createRandomGrid(gridsize);
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
    ofSetColor(0, 0, 255);
    ofRect(player.x+tileSize/4, player.y+tileSize/4, tileSize/2, tileSize/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        createRandomGrid(gridsize);
    }
    else if (key == 'r'){
        //setStart();
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
    //cout << "X mouse : " << ofGetMouseX() << endl;
    //cout << "Y mouse : " << ofGetMouseY()   << endl;

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

//--------------------------------------------------------------
void ofApp::createRandomGrid(int gridsize){

tiles.assign(gridsize*gridsize, tile());
noWalls.clear();

//Initial grid generation - walls & open spaces
    
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
            noWalls.push_back(i);
            }
            else {
                int x = ofRandom(0, 100);
                tiles[i].wall = x%2;
                if (!(x%2)){
                    noWalls.push_back(i);
                }
            }
        }
    tiles[i].color = !tiles[i].wall * 255;
    }
    setStart();
}

//--------------------------------------------------------------
void ofApp::setStart(){
    int randomSquare = (int) ofRandom(0, noWalls.size());
    
    tiles[noWalls[randomSquare]].start = true;
    tiles[noWalls[randomSquare]].color = ofColor(255,0,0);
    player = tiles[noWalls[randomSquare]].pos;
    setGoal();
}

//--------------------------------------------------------------
void ofApp::setGoal(){
    int randomSquare = (int) ofRandom(0, noWalls.size());
    if (!tiles[noWalls[randomSquare]].start){
    tiles[noWalls[randomSquare]].start = true;
    tiles[noWalls[randomSquare]].color = ofColor(0,255,0);
    }
    else {setGoal();}
}

//--------------------------------------------------------------
void ofApp::calculateCost(){
    
}





