//Group 8
//Lee Quan Sheng [S10198298], Eugene Long [S10193060J]

#include "Pathfinder.h"
#include "VArray.h"
#include "Vec2D.h"
#include "CoordinateMap.cpp"
#include "BHPriorityQueue.cpp"
#include "Board.h"
#include "Tile.h"
#include <math.h>
#include <climits>
#include <iostream>

Pathfinder::~Pathfinder() {}

VArray<Vec2D> reconstructPath(CoordinateMap<Vec2D> cameFrom, Vec2D current) {
    VArray<Vec2D> path;
    path.push(current);
    while(cameFrom.get(current) != NULL) {
        current = *cameFrom.get(current);
        path.push(current, 0);
    }
    return path;
}

int h(Vec2D startPos, Vec2D endPos) {
    return startPos.getL1DistanceTo(endPos);
}

int getValue(CoordinateMap<int> coordMap, Vec2D pos, int defaultVal) {
    int ret;
    int *storedVal = coordMap.get(pos);
    if(storedVal == nullptr) {
        ret = defaultVal;
    } else {
        ret = *storedVal;
    }
    return ret;
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
VArray<Vec2D> Pathfinder::getPathToTarget(Board* b, Vec2D startPos, Vec2D tgtPos) {

    // initialise the openSet, the set of all discovered nodes
    BHPriorityQueue<Vec2D> openSet;
    openSet.insert(0, startPos);

    //For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start to n currently known. 
    CoordinateMap<Vec2D> cameFrom;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    CoordinateMap<int> gScore;
    gScore.set(startPos, 0);

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.

    CoordinateMap<int> fScore;
    fScore.set(startPos, h(startPos, startPos));

    while(!openSet.isEmpty()) {
        Vec2D current = openSet.extract();
        //std::cout << (std::string) current << (std::string) tgtPos << std::endl;
        if(current == tgtPos) {
            return reconstructPath(cameFrom, current);
        }

        VArray<Vec2D> neighbours = b->neighboursForSpaceAt(current);
        // d(current,neighbor) is the weight of the edge from current to neighbor
        // tentative_gScore is the distance from start to the neighbor through current

        // get gScore gracefully
        int currGScore = getValue(gScore, current, INT_MAX);

        // iterate through neighbours
        for(int i=0; i<neighbours.getSize(); i++) {
            Vec2D neighbour = neighbours.get(i);
            Tile *tile = b->getTileAt(neighbour);

            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            int d = getScoreForTileState(tile->getState());
            int tentative_gScore = currGScore + d;

            int neighbourGScore = getValue(gScore, neighbour, INT_MAX);
            if(tentative_gScore < neighbourGScore) {

                // This path to neighbor is better than any previous one. Record it!
                cameFrom.set(neighbour, current);
                gScore.set(neighbour, tentative_gScore);

                int fscore = neighbourGScore + h(startPos, neighbour);
                fScore.set(neighbour, fscore);

                if(openSet.search(neighbour) == -1) {
                    openSet.insert(fscore, neighbour);
                }
            }
        }
    }

    std::cout << "Failed to find path!" << std::endl;
    return VArray<Vec2D>(); // failure, no path
}

void Pathfinder::recursiveSearchMoves(Board& b, int mp, Vec2D pos, BHPriorityQueue<Vec2D>& pScore) {

    // base case: mp > 0 after move

    // calculate mpcost for current tile
    int mpCost = b.getTileAt(pos)->movementCostForTile();

    // check that there is enough mp to make the current move
    if(mp - mpCost < 0) { return; }

    // if valid, calculate score and add to posScores
    // the lower the score, the better the move
    int score = getScoreForPosition(pos);
    pScore.insert(score, pos);

    // continue traversing board for moves
    VArray<Vec2D> neighbours = b.neighboursForSpaceAt(pos);
    for(int i=0; i<neighbours.getSize(); i++) {
        recursiveSearchMoves(b, mp, neighbours.get(i), pScore);
    }
}

Vec2D Pathfinder::bestMoveForUnit(Board& b, int mp, Vec2D pos) {
    BHPriorityQueue<Vec2D> posScore;
    recursiveSearchMoves(b, mp, pos, posScore);

    // returns a valid move with the best score
    return posScore.extract();
}