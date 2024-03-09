//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#include "Player.h"
#include "Vertex.h"

Player::Player(int i) {
    this->id = i;
    this->moonScore = 0;
    this->v = 0;
}

int Player::getId() {
    return this->id;
}

int Player::getMoonScore() {
    return this->moonScore;
}

Vertex *Player::getV() {
    return this->v;
}

void Player::increaseMoonScore() {
    this->moonScore++;
}

void Player::resetMoonScore() {
    this->moonScore = 0;
}

void Player::setV(Vertex *v) {
    this->v = v;
}
