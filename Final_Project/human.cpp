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

void Human::render(Board& board) {
    bool keepLoopGoing = true;
    do {
        this->positionX = boardHelper::randomNumber(board.getDimensionX());
        this->positionY = boardHelper::randomNumber(board.getDimensionY());

        if (boardHelper::isRandomNumInBoard(board.getDimensionX(), this->positionX) &&
            boardHelper::isRandomNumInBoard(board.getDimensionY(), this->positionY) &&
            board.isPositionAvailable(this->positionX, this->positionY)) {
                keepLoopGoing = false;
        }

    } while(keepLoopGoing);

    board.render(this->positionX, this->positionY, this->chip);
}

void Human::renderOnSpot(Board& board) {
   board.renderOnSpot(this->positionX, this->positionY, this->chip);
}

void Human::restartAction() {
    this->action = this->actionToDefault;
}

void Human::move(std::string direction, Board& board) {

    if (direction == UP) {
        this->positionY -=1;
    }

    if (direction == DOWN) {
        this->positionY +=1;
    }

    if (direction == LEFT) {
        this->positionY -=1;
    }

    if (direction == RIGHT) {
        this->positionY +=1;
    }

    board.render(this->positionX, this->positionY, this->chip);
}

void Human::handleHumanInfected(Board& board, std::vector<Enemy>& enemies, int humanPrevX, int humanPrevY) {
    int oldEnemyPosX = 0;
    int oldEnemyPosY = 0;
    bool firstAttachedFound = false;
    for (int i = 0; i < this->attachedToIds.size(); i++) {
        for (int d = 0; d < enemies.size(); d++) {
            if (this->attachedToIds.at(i) == enemies.at(d).get_id()) {
                if (!firstAttachedFound) {
                    oldEnemyPosX = enemies.at(d).getPosition('x');
                    oldEnemyPosY = enemies.at(d).getPosition('y');
                    enemies.at(d).setPosition('x', humanPrevX);
                    enemies.at(d).setPosition('y', humanPrevY);
                    std::cout << board.getDimensionX() << std::endl;
                    enemies.at(d).render(board, oldEnemyPosX, oldEnemyPosY);
                    firstAttachedFound = true;
                } else {
                    int oldX = enemies.at(d).getPosition('x');
                    int oldY = enemies.at(d).getPosition('y');
                    enemies.at(d).setPosition('x', oldEnemyPosX);
                    enemies.at(d).setPosition('y', oldEnemyPosY);
                    enemies.at(d).render(board, oldX, oldY);
                    oldEnemyPosX = oldX;
                    oldEnemyPosY = oldY;
                }
            }
        }
    }
}

void Human::playTurn(Board& board, std::vector<Enemy>& enemies) {
    int i = 0;
    do {
        int humanPrevX = this->positionX;
        int humanPrevY = this->positionY;
        Action playerAction = boardHelper::listenForKeyDown();
        if (playerAction.type == TYPE_MOVE) {
            boardHelper::move(playerAction.action, board, this->positionX, this->positionY, this->chip);

            // if Human position is diff than prev one do next
            if (humanPrevX != this->positionX || humanPrevY != this->positionY) {

                if (this->infected) { // if is infected the enemies will move after Human
                    Human::handleHumanInfected(board, enemies, humanPrevX, humanPrevY);
                }
                i++;
            }

        } else if (playerAction.type == TYPE_ATTACK) {
            if (board.isNearMe(VSI, 4, this->positionX, this->positionY) ||
                board.isNearMe(ISI, 4, this->positionX, this->positionY))
            {

                for (int enemyIndex = 0; enemyIndex < enemies.size(); enemyIndex++) {
                    int currentEnemyPosX = enemies.at(enemyIndex).getPosition('x');
                    int currentEnemyPosY = enemies.at(enemyIndex).getPosition('y');
                    if (board.isNearMe(this->chip, 4, currentEnemyPosX, currentEnemyPosY)) {
                        Human::attack(playerAction.action, enemies.at(enemyIndex), board);
                    }
                }
            }

            // Human::attack(playerAction.action, enemy);
            std::cout << "adding actions" << std::endl;
            i++;
        } else {
            std::cout << "Wrong Action" << std::endl;
        }

    } while(i < this->action);
}

void Human::hasBeenInfectedBy(char byWho, int damagePerTurn, std::string idOfEnemy) {
    std::cout << "oh nooo!!!, You have been Infected\n";
    this->chip = (byWho == VSI_CHIP) ? INFECTED_VSI : INFECED_ISI;
    int effectOnAction = (byWho == VSI_CHIP) ? 1 : 2;
    this->action = this->action - effectOnAction;
    this->infected = true;
    this->damagePerTurn = damagePerTurn;
    this->attachedToIds.push_back(idOfEnemy);
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

void Human::attack(std::string weaponUsed, Enemy& enemy , Board& board) {
    if (weaponUsed == ATTACK_NETFILTER) {
        bool conditionToAttack = (board.isNearMe(ISI, 2, this->positionX, this->positionY) && boardHelper::checkPorcentage(33)) ||
                                 (board.isNearMe(ISI, 1, this->positionX, this->positionY) && boardHelper::checkPorcentage(66)) ||
                                 (board.isNearMe(VSI, 2, this->positionX, this->positionY) && boardHelper::checkPorcentage(33)) ||
                                 (board.isNearMe(VSI, 1, this->positionX, this->positionY) && boardHelper::checkPorcentage(66));

        if (conditionToAttack) { // talk to teacher
            std::cout << "You have Stunt the enemy\n";
            enemy.stun(); // aply range
            Human::detached();
        } else {
            std::cout << "You missed the target Attack fail\n";
        }
    }

    if (weaponUsed == ATTACK_SNOOP_DESTROYER) {
        bool conditionToAttack = (board.isNearMe(ISI, 3, this->positionX, this->positionY) && boardHelper::checkPorcentage(75)) ||
                                 (board.isNearMe(VSI, 3, this->positionX, this->positionY) && boardHelper::checkPorcentage(63) && enemy.get_energy() >= 50) ||
                                 (board.isNearMe(VSI, 3, this->positionX, this->positionY) && boardHelper::checkPorcentage(77) && enemy.get_energy() <= 50);
        if (conditionToAttack) {
            std::cout << "You have Used SNOOP_DESTROYER on the enemy\n";
            enemy.removeEnergy(50);
            if (Human::isInfected() && enemy.isDead()) {
                Human::detached();
            }
            board.printBoard();
        } else {
            std::cout << "You have Used SNOOP_DESTROYER but FAILED\n";
        }
    }
}

void Human::detached() {
    std::cout << "You have been detached\n";
    this->chip = HUMANCHIP;
    this->action = 3;
    this->infected = false;
    this->damagePerTurn = 0;
}
