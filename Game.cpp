//Group 8
//Lee Quan Sheng [S10198298], Eugene Long [S10193060J]

#include "Game.h"
#include "FSMStack.h"
#include "VArray.cpp"
#include "Tile.h"
#include "EntityClasses.h"
#include "Vec2D.h"
#include "CSVParser.h"
#include "Queue.cpp"

#include <math.h>
#include <string>
#include <iostream>

Game::Game() : Stateful() {
    b = nullptr;
    pushState(mainMenu);
}

Game::~Game() {
    // Deallocator
}

//Adds the game state using the FSMStack 
//pre: None
//Post: None
void Game::pushState(GameStates state) {
    switch(state) {
        case mainMenu:
            fsmStack.pushState("mainmenu");
            break;
        case running:
            fsmStack.pushState("running");
            break;
        case quit:
            fsmStack.pushState("quit");
            break;
    }
}

//Gets the game state from the FSMStack 
//pre: None
//Post: None
GameStates Game::getState() {
    std::string state = fsmStack.popState();
    if(state == "mainmenu") { return mainMenu; }
    else if(state == "running") { return running; }
    else { return quit; }
}

//Keeps track of the game state 
//pre: None
//Post: None
void Game::runState() {
    switch(getState()) {
        case mainMenu:
            runMenu();
            runState();
            break;
        case running:
            initGame();
            // return to main menu after game ends
            pushState(mainMenu);
            runState();
            break;
        case quit:
            // stops recursively running current State
            break;
    }
}

//Displays menu of the game
//pre: None
//Post: None
void displayMenu() {
    std::cout << "\n\n\nObjective Survive" << std::endl;
    std::cout << "[1] Start Game" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    std::cout << "> ";
}

//displayed menu with FSMStack implemented to update the state 
//pre: None
//Post: None
void Game::runMenu() {
    int option;
    while(true) {
        displayMenu();
        std::cin >> option;

        if(option == 1) {
            pushState(running);
            break;
        } else if (option == 0) {
            pushState(quit);
            break;
        } else {
            std::cout << "Invalid option!\n" << std::endl;
            pushState(mainMenu);
        }
    }
}

//Intialization of the game when user selects 1
//pre: None
//Post: None
void Game::initGame() {
    std::string filename;
    std::cout << "Enter filename of map to load: ";
    std::cin >> filename;

    b = CSVParser::parseMapFile(filename);
    runGame();
}

//Reset
//pre: None
//Post: None
void Game::finishGame() {
    // reset any variables used in the game
}

//Runs the state of the actors 
//pre: None
//Post: None
void Game::runStep() {
    b->runActors();
}

//Gets Location for spawn target from a random or specific location
//pre: None
//Post: None
Vec2D getLocationForSpawnTarget() {
    int uin;
    std::cout << "\nSpawn Options:" << std::endl;
    std::cout << "[1] Random Location" << std::endl;
    std::cout << "[2] Specific Location" << std::endl;
    std::cout << "> ";
    std::cin >> uin;

    switch(uin) {
        case 1:
            return Vec2D(-1, -1);
        case 2: {
            int x, y = 0;
            std::cout << "\nEnter coordinates[format:x (space) y, e.g '1 2']: ";
            std::cin >> x >> y;
            return Vec2D(x, y);
        }
    }

    std::cout << "\nOption outside of range, spawining target at random position!" << std::endl;
    return Vec2D(-1, -1);
}

//Run the game application
//pre: None
//Post: None
void Game::runGame() {
    // main application loop
    bool keepRunning = true;

    while(keepRunning) {
        b->display();
        //TODO: Print menu bar and show available actions
        std::cout << "Simulation Controls" << std::endl;
        std::cout << "[1] Simulation Step" << std::endl;
        std::cout << "[2] Run Until Targets Destroyed" << std::endl;
        std::cout << "[9] Spawn New Target" << std::endl;
        std::cout << "[0] End Simulation" << std::endl;
        std::cout << "> ";

        int uin;
        std::cin >> uin;

        switch(uin) {
            case 1:
                runStep();
                break;
            case 2: {
                int loopCounter = 0;
                while(b->getTargets().getSize() > 0) {
                    if(loopCounter == INT_MAX) {
                        break;
                    }
                    runStep();
                    loopCounter++;
                }
                break;
            }
            case 9: {
                Vec2D tgtPos = getLocationForSpawnTarget();
                if(tgtPos == Vec2D(-1, -1)) {
                    // spawn at random location
                    b->spawnTarget();
                } else {
                    // coordinates were specified
                    // check validity of coordinates
                    if(b->posIsValidSpawnLocation(tgtPos)) {
                        // spawn at specified location
                        b->spawnTarget(tgtPos);
                    } else {
                        // display error message
                        std::cout << "\nInvalid Spawn Location!" << std::endl;
                    }
                }
                break;
            }
            case 0:
                keepRunning = false;
                break;
            default:
                break;
        }
    }
    
    finishGame();
}

void Game::start() {
    runState();
}