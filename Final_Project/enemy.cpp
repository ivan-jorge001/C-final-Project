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

const std::string UP = "up";
const std::string LEFT = "left";
const std::string RIGHT = "right";
const std::string DOWN = "down";
const std::string TYPE_MOVE = "move";
const char HUMAN = char(36);
const char EMPTY = char(46);

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

void Enemy::removeEnergy(double damage) {
    this->energy -= damage;
}

void Enemy::render(Board board) {
    board.render(this->positionX, this->positionY, this->chip);
}

void Enemy::render(Board board, int prevX, int prevY) {
    board.render(this->positionX, this->positionY, this->chip, prevX, prevY);
}

std::string Enemy::simulateKeydown() {
    int direction = boardHelper::randomNumber(4);

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
    }
    std::cout << "\nSHOULDNT BE HERE\n";
    return " ";
}

Action Enemy::simulateAction() {
    Action enemyAction;
    enemyAction.action = Enemy::simulateKeydown();
    enemyAction.type = TYPE_MOVE;
    return enemyAction;
}

bool Enemy::isAttached() {
    return this->attached;
}

void Enemy::playTurn(Board board, Human& player) {
    if (this->attached || this->stunForTurns) return;

    int i = 0;
    int prevX = this->positionX;
    int prevY = this->positionY;
    int range = this->chip == VSI ? 2 : 1;
    do {
        Action enemyPlayer = Enemy::simulateAction();
        if (enemyPlayer.type == TYPE_MOVE) {
            boardHelper::move(enemyPlayer.action, board, this->positionX, this->positionY, this->chip);

            if (prevX != this->positionX || prevY != this->positionY) { // if position Changed means they Moved
                // DELETE std::cout << "=======================" << std::endl;
                i++;
            }
            if (board.isNearMe(HUMAN, range, this->positionX, this->positionY)) {
                if (this->chip == VSI) {
                    player.hasBeenInfectedBy(VSI, 40);
                    this->attached = true;
                    player.renderOnSpot(board);
                    return;
                }

                if (this->chip == ISI) {
                    player.hasBeenInfectedBy(ISI, 25);
                }
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
