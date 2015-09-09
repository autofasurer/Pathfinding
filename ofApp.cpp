#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gridsize = 48;
    tileSize = 20;
	drawCost = false;
	findCost = 0;
	controlNumber = 0;
    createRandomGrid(gridsize);
    }

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2-(tileSize*(gridsize/2)), ofGetHeight()/2-(tileSize*(gridsize/2)));
    
    //draw the grid
    for (int i = 0; i < tiles.size(); i++){
        tiles[i].draw();
		ofSetColor(255, 0, 0);
		if (drawCost){
		stringstream ss;
		ss << tiles[i].cost ;
			if (!tiles[i].wall){
		ofDrawBitmapString(ss.str().c_str(), tiles[i].pos.x, (tiles[i].pos.y+tileSize));
			}
		}
    }
    //draw the player
    ofSetColor(0, 0, 255);
    ofRect(player.x+tileSize/4, player.y+tileSize/4, tileSize/2, tileSize/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        createRandomGrid(gridsize);
    }
    else if (key == 'd'){
        drawCost = !drawCost;
    }
	else if (key == 'c'){
		calculateCost();
	}
	else if (key == 's'){
		step();
	}
}

//--------------------------------------------------------------
void ofApp::createRandomGrid(int gridsize){

tiles.assign(gridsize*gridsize, tile(0));
noWalls.clear();

//Initial grid generation - walls & open spaces
    
for (int i = 0; i < tiles.size(); i++){
    tiles[i].index = i;
    tiles[i].pos.x = (i % gridsize) * 20;
    tiles[i].pos.y = (i / gridsize) * 20;
    tiles[i].tileSize = tileSize;
	//Random walls
    
         int x = ofRandom(0, 100);
         tiles[i].wall = x%2;
}
	
//Fill vector with indexes of tiles that are walls & fill in gaps
for (int i = 0; i < tiles.size(); i++){
	//check whether the open squares all have 2 connecting open squares; this guarantees the possibility for the player to reach the goal.
	checkWalls(i);
		
	//fill in the gaps - if an empty tile is surrounded by 4 walls, make it a wall as well.
	if (tiles[i-1].wall && tiles[i+1].wall && tiles[i+gridsize].wall && tiles[i-gridsize].wall){
		tiles[i].wall = true;
	}

	//build a wall all around
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
	
	tiles[i].color = !tiles[i].wall * 255;
	
	//fill vector noWalls with the index values of all tiles that are not a wall
		if (!tiles[i].wall){
			noWalls.push_back(i);
		}
	}
	setStart();
}


//--------------------------------------------------------------
void ofApp::setStart(){
    int randomSquare = (int) ofRandom(0, noWalls.size());
    
    tiles[noWalls[randomSquare]].start = true;
    player = tiles[noWalls[randomSquare]].pos;
	startIndex = tiles[noWalls[randomSquare]].index;
    setGoal();
}

//--------------------------------------------------------------
void ofApp::setGoal(){
    int randomSquare = (int) ofRandom(0, noWalls.size());
    if (!tiles[noWalls[randomSquare]].start){
    tiles[noWalls[randomSquare]].start = true;
    tiles[noWalls[randomSquare]].color = ofColor(0,255,0);
        goalIndex = tiles[noWalls[randomSquare]].index;
    }
    else {setGoal();}
}

//--------------------------------------------------------------
void ofApp::calculateCost(){
    tiles[goalIndex].cost = 0;
	for (int i = 0; i < tiles.size(); i++){
		if (tiles[i].cost == findCost){
			if (!tiles[i-1].wall && (tiles[i-1].cost == -1)){
				tiles[i-1].cost = findCost+1;
			}
			if (!tiles[i+1].wall && (tiles[i+1].cost == -1)){
				tiles[i+1].cost = findCost+1;
			}
			if (!tiles[i-gridsize].wall && (tiles[i-gridsize].cost == -1)){
				tiles[i-gridsize].cost = findCost+1;
			}
			if (!tiles[i+gridsize].wall && (tiles[i+gridsize].cost == -1)){
				tiles[i+gridsize].cost = findCost+1;
			}
		}
	}
    findCost++;
	if (tiles[startIndex].cost != -1){
		playerDistance = tiles[startIndex].cost;
	}
}


//--------------------------------------------------------------
void ofApp::checkWalls(int i){

		if ((i-1)%gridsize == 0 || (i+2)%gridsize == 0 || (i-gridsize) < gridsize || (tiles.size()-(i+gridsize)) < gridsize){
		return;
		}
		else {
			int x = 0;
			if (tiles[i-1].wall){
				x += 1;
			}
			if (tiles[i+1].wall){
				x += 1;
			}
			if (tiles[i-gridsize].wall){
				x += 1;
			}
			if (tiles[i+gridsize].wall){
				x += 1;
			}
			if ( x >2 && tiles[i+1].wall){
				tiles[i+1].wall = false;
				return;
			}
			else if ( x >2 && tiles[i+gridsize].wall){
				tiles[i+gridsize].wall = false;
				return;
			}
		}

}

//--------------------------------------------------------------
void ofApp::step(){
	if (tiles[startIndex-1].cost < playerDistance && tiles[startIndex-1].cost > -1){
		player = tiles[startIndex-1].pos;
		playerDistance = tiles[startIndex-1].cost;
		tiles[startIndex-1].color = ofColor(255,255,0);
		startIndex = startIndex-1;
		return;
	}
	if (tiles[startIndex+1].cost < playerDistance && tiles[startIndex+1].cost > -1){
		player = tiles[startIndex+1].pos;
		playerDistance = tiles[startIndex+1].cost;
		tiles[startIndex+1].color = ofColor(255,255,0);
		startIndex = startIndex+1;
		return;
	}
	if (tiles[startIndex-gridsize].cost < playerDistance && tiles[startIndex-gridsize].cost > -1){
		player = tiles[startIndex-gridsize].pos;
		playerDistance = tiles[startIndex-gridsize].cost;
		tiles[startIndex-gridsize].color = ofColor(255,255,0);
		startIndex = startIndex-gridsize;
		return;
	}
	if (tiles[startIndex+gridsize].cost < playerDistance && tiles[startIndex+gridsize].cost > -1){
		player = tiles[startIndex+gridsize].pos;
		playerDistance = tiles[startIndex+gridsize].cost;
		tiles[startIndex+gridsize].color = ofColor(255,255,0);
		startIndex = startIndex+gridsize;
		return;
	}
}



