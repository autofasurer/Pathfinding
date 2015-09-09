//
//  tile.h
//  Pathfinding
//
//  Created by Brecht Debackere on 08/09/15.
//
//
#pragma once

#include "ofMain.h"

#ifndef Pathfinding_tile_h
#define Pathfinding_tile_h

class tile{
public:
    //constructor
    tile();
    //methods
    void draw();
    void update();
    //variables
    bool wall;
    bool start;
    bool goal;
    int cost;
    ofPoint pos;
    int tileSize;
    ofColor color;
    
private:
};

#endif
