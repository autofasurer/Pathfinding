#pragma once

#include "ofMain.h"
#include "tile.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    void createRandomGrid(int gridsize);
    void setStart();
    void setGoal();
    void calculateCost();
    void checkWalls(int i);
    void step();
    
    vector<tile> tiles;
    vector<int> noWalls;
    int gridsize, tileSize, goalIndex, startIndex, controlNumber, findCost;
    int playerDistance;
    ofPoint player;
    bool drawCost;
};
