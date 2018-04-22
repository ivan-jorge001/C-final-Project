//
//  enemy.hpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <iostream>
#include <stdio.h>
#include "board.hpp"
#include "action.hpp"
#include "human.hpp"

const char VSI = char(86);
const char ISI = char(73);
class Human;
class Enemy {
private:
    int positionX, positionY, action;
    double energy;
    bool attached;
    int stunForTurns;
    char chip; // VSI or ISI
public:
    Enemy();
    Enemy(int x, int y, std::string type)
    {
        this->positionX = x;
        this->positionY = y;
        this->chip = (type == "vsi" ? VSI : ISI );
        this->action = (type == "vsi" ? 2 : 1);
        this->energy = 100.00;
        this->attached = false;
        this->stunForTurns = 0;
    }
    int getPosition(char);
    void stun();
    void erasedStun();
    void setPosition(char, int);
    double get_energy();
    void removeEnergy(double);
    void getCloserTo(Board, int, int);
    bool isDead();
    void render(Board);
    void render(Board, int, int);
    void playTurn(Board, Human&);
    std::string simulateKeydown();
    Action simulateAction();
    bool isAttached();
    bool isStun();

};


#endif /* enemy_hpp */
