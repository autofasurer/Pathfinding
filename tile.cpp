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
}
void update(){
    
}

void tile::draw(){
    ofSetColor(!wall*255);
    ofRect(pos.x, pos.y, tileSize, tileSize);
}