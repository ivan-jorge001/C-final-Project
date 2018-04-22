//
//  human.hpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/19/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//

#ifndef human_hpp
#define human_hpp

#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "enemy.hpp"

const char HUMANCHIP = char(36);
const char VSI_CHIP = char(86);
const char INFECTED_VSI = char(48);
const char INFECED_ISI = char(79);

class Enemy;
class Human {
private:
    int positionX, positionY, action, actionToDefault, damagePerTurn;
    double life;
    char chip;
    bool infected;
public:
    Human(int x, int y) {
        this->positionX = x;
        this->positionY = y;
        this->action = 3;
        this->actionToDefault = 3;
        this->life = 100.00;
        this->chip = HUMANCHIP;
        this->infected = false;
        this->damagePerTurn = 0;
    }
    int getPosition(char);
    int getDamagePerTurn();
    double get_life();
    void restartAction();
    void removeLife(double);
    void render(Board);
    void renderOnSpot(Board);
    void playTurn(Board, Enemy&);
    void move(std::string, Board);
    void hasBeenInfectedBy(char, int);
    void attack(std::string, Enemy&);
    bool isInfected();
    bool isDead();
    char get_chip();
    void detached();

};

#endif /* human_hpp */
