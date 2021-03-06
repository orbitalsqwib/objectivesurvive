//Group 8
//Lee Quan Sheng [S10198298], Eugene Long [S10193060J]

#include "Tile.h"
#include "FSMStack.h"
#include <string>
#include <iostream>

Tile::Tile() {
    state = normal;
}

Tile::~Tile() {}

//Sets state of the tiles (N - Normal. H - Hole, W - Water)
void Tile::setState(TileState tileState) {
    state = tileState;
}

//Gets the state of the tiles 
TileState Tile::getState() {
    return state;
}

//Displays the tiles according to its type 
void Tile::display() {
    switch(state) {
        case normal:
            std::cout << ".";
            break;
        case hole:
            std::cout << " ";
            break;
        case water:
            std::cout << "~";
            break;
    }
}

int Tile::movementCostForTile() {
    switch(state) {
        case normal: return 1;
        case hole: return 999;
        case water: return 2;
    }
}