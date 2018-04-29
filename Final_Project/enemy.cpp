//
//  enemy.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include <iostream>
#include "enemy.hpp"
#include "board.hpp"
#include "boardHelper.hpp"
#include "action.hpp"
#include "human.hpp"

// Movement
const std::string UP = "up";
const std::string LEFT = "left";
const std::string RIGHT = "right";
const std::string DOWN = "down";
const std::string UP_RIGHT = "up_right";
const std::string DOWN_RIGHT = "down_right";
const std::string UP_LEFT = "up_left";
const std::string DOWN_LEFT = "down_left";

// Actions
const std::string TYPE_MOVE = "move";
const char HUMAN = char(36);
const char EMPTY = char(46);
const char HVT = char(35);

int Enemy::getPosition(char x_or_y) {
    return x_or_y == 'x' ? this->positionX : this->positionY;
};

void Enemy::setPosition(char x_or_y, int x_or_y_position) {
    if (x_or_y == 'x') {
        this->positionX = x_or_y_position;
    } else if (x_or_y == 'y') {
        this->positionY = x_or_y_position;
    }
};

double Enemy::get_energy() {
    return this->energy;
}

char Enemy::get_chip() {
    return this->chip;
}

std::string Enemy::get_id() {
    return this->id;
}

void Enemy::removeEnergy(double damage) {
    this->energy -= damage;
    std::cout << "Enemy has recieved damage\n Current life: " << this->energy << std::endl;

}

void Enemy::render(Board& board) {
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

void Enemy::render(Board& board, int prevX, int prevY) {
    board.render(this->positionX, this->positionY, this->chip, prevX, prevY);
}

std::string Enemy::moveSmart(int playerX, int playerY) {
    if (playerX == this->positionX) { // same X line
        if (playerY > this->positionY) {
            return UP;
        } else {
            return DOWN;
        }
    }

    if (playerY == this->positionY) { // same Y line
        if (playerX > this->positionX) {
            return RIGHT;
        } else {
            return LEFT;
        }
    }

    if (playerX > this->positionX && playerY < this->positionY) { // top right corner
        return UP_RIGHT;
    }
    if (playerX < this->positionX && playerY < this->positionY) { // top left corner
        return UP_LEFT;
    }
    if (playerX > this->positionX && playerY > this->positionY) { // bottom right corner
        return DOWN_RIGHT;
    }
    return DOWN_LEFT; // bottom right corner
};

std::string Enemy::simulateKeydown() {
    int direction = boardHelper::randomNumber(8);

    switch (direction) {
        case 1:
            return UP;
            break;
        case 2:
            return LEFT;
            break;
        case 3:
            return RIGHT;
            break;
        case 4:
            return DOWN;
            break;
        case 5:
            return UP_RIGHT;
            break;
        case 6:
            return DOWN_RIGHT;
            break;
        case 7:
            return UP_LEFT;
            break;
        case 8:
            return DOWN_LEFT;
            break;
    }
    std::cout << "\nSHOULDNT BE HERE\n";
    return " ";
}

Action Enemy::simulateAction(int playerX, int playerY) {
    Action enemyAction;
    enemyAction.action = Enemy::simulateKeydown();
    if (this->chip == VSI) {
        enemyAction.action = Enemy::moveSmart(playerX, playerY);
    }
    enemyAction.type = TYPE_MOVE;
    return enemyAction;
}

bool Enemy::isAttached() {
    return this->attached;
}

void Enemy::playTurn(Board& board, Human& player) {
    if (this->attached || this->stunForTurns) return;

    int i = 0;
    int prevX = this->positionX;
    int prevY = this->positionY;
    int range = this->chip == VSI ? 2 : 1;
    do {
        Action enemyPlayer = Enemy::simulateAction(player.getPosition('x'), player.getPosition('y'));
        if (enemyPlayer.type == TYPE_MOVE) {

            char humanChar = player.isInfected() ? player.get_chip() : HUMAN;
            if (board.isNearMe(humanChar, range, this->positionX, this->positionY)) {
                bool vsiConditionToAttack = (boardHelper::checkPorcentage(90) &&
                                            board.isNearMe(humanChar, 1, this->positionX, this->positionY)) ||
                                            boardHelper::checkPorcentage(65);

                if (this->chip == VSI && vsiConditionToAttack) {
                    player.hasBeenInfectedBy(VSI, 40, this->id);
                    this->attached = true;
                    player.renderOnSpot(board);
                    i++;
                    break;
                }

                if (this->chip == ISI && boardHelper::checkPorcentage(75)) {
                    player.hasBeenInfectedBy(ISI, 25, this->id);
                    this->attached = true;
                    player.renderOnSpot(board);
                    i++;
                    break;
                }
            }

            if (board.isNearMe(HVT, 5, this->positionX, this->positionY)) {
                std::vector<HighValueTargets> hvt = board.getHvt();
                int hvtNumber = board.numberOfHvt();

                for (int hvtIndex = 0; hvtIndex < hvtNumber; hvtIndex++) {
                    std::cout <<  hvt[hvtIndex].x<< " = "<< hvt[hvtIndex].y << std::endl;
                    if (board.isNearMe(Enemy::get_chip(), 5, hvt[hvtIndex].x, hvt[hvtIndex].y)) {
                        board.ereasedHvt(hvtIndex);
                        i++;
                        break;
                    }
                }
            }

            boardHelper::move(enemyPlayer.action, board, this->positionX, this->positionY, this->chip);
            if (prevX != this->positionX || prevY != this->positionY) { // if position Changed means they Moved
                i++;
            }


        } else {
            std::cout << "Wrong Action" << std::endl;
        }

    } while(i < this->action);
}

bool Enemy::isDead() {
    return this->energy <= 0;
}

void Enemy::stun() {
    this->attached = false;
    this->stunForTurns += 1;
}

void Enemy::erasedStun() {
    this->stunForTurns -= 1;
}

bool Enemy::isStun() {
    return !!this->stunForTurns;
}
