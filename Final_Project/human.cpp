//
//  human.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/19/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include <iostream>
#include "human.hpp"
#include "board.hpp"
#include "boardHelper.hpp"
#include "action.hpp"
// #include "enemy.hpp"

const std::string UP = "up";
const std::string LEFT = "left";
const std::string RIGHT = "right";
const std::string DOWN = "down";
const std::string TYPE_MOVE = "move";
const std::string TYPE_ATTACK = "attack";
const std::string ATTACK_NETFILTER = "NF";
const std::string ATTACK_SNOOP_DESTROYER = "SD";

int Human::getPosition(char x_or_y) {
    return x_or_y == 'x' ? this->positionX : this->positionY;
};

int Human::getDamagePerTurn() {
    return this->damagePerTurn;
};

double Human::get_life() {
    return this->life;
}

void Human::removeLife(double damage) {
    this->life -= damage;
}

void Human::render(Board board) {
   board.render(this->positionX, this->positionY, this->chip);
}

void Human::renderOnSpot(Board board) {
   board.renderOnSpot(this->positionX, this->positionY, this->chip);
}

void Human::restartAction() {
    this->action = this->actionToDefault;
}

void Human::move(std::string direction, Board board) {

    if (direction == UP) {
        this->positionX -=1;
    }

    if (direction == DOWN) {
        this->positionX +=1;
    }

    if (direction == LEFT) {
        this->positionY -=1;
    }

    if (direction == RIGHT) {
        this->positionY +=1;
    }

    board.render(this->positionX, this->positionY, this->chip);
}

void Human::playTurn(Board board, Enemy& enemy) {
    int i = 0;
    do {
        int prevX = this->positionX;
        int prevY = this->positionY;
        Action playerAction = boardHelper::listenForKeyDown();
        if (playerAction.type == TYPE_MOVE) {
            boardHelper::move(playerAction.action, board, this->positionX, this->positionY, this->chip);

            if (prevX != this->positionX || prevY != this->positionY) { // if position Changed means they Moved
                if (this->infected) {
                    int oldEnemyPosX = enemy.getPosition('x');
                    int oldEnemyPosY = enemy.getPosition('y');
                    enemy.setPosition('x', prevX);
                    enemy.setPosition('y', prevY);
                    enemy.render(board, oldEnemyPosX, oldEnemyPosY);
                }
                // std::cout << "=======================" << std::endl;
                i++;
            }

        } else if (playerAction.type == TYPE_ATTACK) {
            Human::attack(playerAction.action, enemy);
            i++;
        } else {
            std::cout << "Wrong Action" << std::endl;
        }

    } while(i < this->action);
}

void Human::hasBeenInfectedBy(char byWho, int damagePerTurn) {
    std::cout << "oh nooo!!!, You have been Infected\n";
    this->chip = (byWho == VSI_CHIP) ? INFECTED_VSI : INFECED_ISI;
    this->action = (byWho == VSI_CHIP) ? 1 : 2;
    this->infected = true;
    this->damagePerTurn = damagePerTurn;
}

char Human::get_chip() {
    return this->chip;
}

bool Human::isDead() {
    return this->life <= 0;
}
bool Human::isInfected() {
    return this->chip != HUMANCHIP;
}

void Human::attack(std::string weaponUsed, Enemy& enemy) {
    if (weaponUsed == ATTACK_NETFILTER) {
        std::cout << "You have Stunt the enemy\n";
        enemy.stun(); // aply range
        Human::detached();
    }
    if (weaponUsed == ATTACK_SNOOP_DESTROYER) {
        std::cout << "You have Used SNOOP_DESTROYER on the enemy\n";
        enemy.removeEnergy(50);
    }
}

void Human::detached() {
    std::cout << "You have been detached\n";
    this->chip = HUMANCHIP;
    this->action = 3;
    this->infected = false;
    this->damagePerTurn = 0;
}
