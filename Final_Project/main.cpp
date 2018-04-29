//
//  main.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "board.hpp"
#include "enemy.hpp"
#include "human.hpp"
#include "boardHelper.hpp"


const char infectedVSI = char(48);
const char infectedISI = char(79);

int main(int argc, const char * argv[]) {
    bool gameOn = false;
    bool isBoardRendered = false;
    int turns = 0;
    int number_of_enemies = 2;
    int type1 = 1;//VSI
    int type2 = 1; //"isi";
    int dimensionX = 30;
    int dimensionY = 20;

    // Random Number
    srand(time(NULL));

    //initialize Board
    Board board(dimensionX, dimensionY, 5);
    board.initBoard();
    isBoardRendered = true;

    // initialize Human
    Human player(0, 0, true);

    // Initialize Enemy
    std::vector <Enemy> enemies;
    enemies.reserve(number_of_enemies);

    for (int i = 0; i < type1; i++) {
        Enemy enemy(0, 0, "vsi", true);
        enemies.push_back(enemy);
    }
    for (int i = 0; i < type2; i++) {
        Enemy enemy(0, 0, "isi", true);
        enemies.push_back(enemy);
    }
        // Enemy vsi(0, 0, "vsi", true);
        // Enemy isi(0, 0, "isi", true);

    // RENDERING PLAYERS
    // 1- Human
    player.render(board);

    // 2- Enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i).render(board);
    }
    board.printBoard();

   do {
        if (isBoardRendered && !gameOn) {
            gameOn = true;
        }

        if (player.isInfected()) {
           std::cout << "Player Has Been Infected !!!"<< std::endl;
           int damagePerTurn = player.getDamagePerTurn();
           player.removeLife(damagePerTurn);
        }

        if (player.isDead()) {
            gameOn = false;
            std::cout << "You Have Lost"<< std::endl;
            return 0;
        }

       std::cout << "Player's Life: "<< player.get_life() << std::endl;
        // std::cout << "Enemies's Energy: "<< vsi.get_energy() << std::endl;

       std::cout << "Turns: "<< (turns + 1) << std::endl;
        player.playTurn(board, enemies);

        int enemyCreated = 0;
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies.at(i).isDead()) {
                board.clear(enemies.at(i).getPosition('x'), enemies.at(i).getPosition('y'));
                enemies.erase (enemies.begin() + i);
                board.printBoard();
                continue;
            }

            if (enemies.at(i).isAttached()) {
                int opp = boardHelper::checkPorcentage(50);
                if (enemies.at(i).get_chip() == VSI && opp && !enemyCreated) {
                    Enemy enemy(0, 0, "vsi", true);
                    enemy.render(board);
                    enemies.push_back(enemy);
                    enemyCreated++;
                }
            }

            if (enemies.at(i).isStun()) {
                enemies.at(i).erasedStun();
            }

            if (!enemies.at(i).isAttached()) {
                enemies.at(i).playTurn(board, player);
            }
        }

        if (!board.getHvt().size()) {
            gameOn = false;
            std::cout << "You Have LOST\n";
        }
        if (!enemies.size()) {
            gameOn = false;
            std::cout << "You Have WON\n";
        }
       turns++;

   } while(gameOn);
    // board.printBoard();



    // std::string direction = boardHelper::listenForKeyDown();
    // std::cout << direction;

    // if
    return 0;
}

