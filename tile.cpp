//
//  tile.cpp
//  Pathfinding
//
//  Created by Brecht Debackere on 08/09/15.
//
//

#include "tile.h"

tile::tile(){ //constructor
    pos.set(0, 0, 0);
    tileSize = 10;
    wall = 0;
    start = goal = false;
    cost = NULL; 
}
void update(){
    
}

void tile::draw(){
    ofSetColor(color);
    ofRect(pos.x, pos.y, tileSize, tileSize);
}