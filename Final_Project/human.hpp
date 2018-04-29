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
#include <vector>
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
    bool infected, randomPosition;
    std::vector <std::string> attachedToIds;
public:
    Human(int x, int y, bool randomize) {
        this->positionX = x;
        this->positionY = y;
        this->randomPosition = randomize;
        this->action = 3;
        this->actionToDefault = 3;
        this->life = 1000.00;
        this->chip = HUMANCHIP;
        this->infected = false;
        this->damagePerTurn = 0;
    }
    int getPosition(char);
    int getDamagePerTurn();
    double get_life();
    void restartAction();
    void removeLife(double);
    void render(Board&);
    void renderOnSpot(Board&);
    void playTurn(Board&, std::vector<Enemy>&);
    void move(std::string, Board&);
    void hasBeenInfectedBy(char, int, std::string);
    void attack(std::string, Enemy&, Board&);
    void handleHumanInfected(Board&, std::vector<Enemy>&, int humanPrevX, int humanPrevY);
    bool isInfected();
    bool isDead();
    char get_chip();
    void detached();

};

#endif /* human_hpp */
