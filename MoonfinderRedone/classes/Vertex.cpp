//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(int i) {
    this->id = i;
    this->checked = false;
    this->north = 0;
    this->south = 0;
    this->east = 0;
    this->west = 0;
}

int Vertex::getId() {
    return this->id;
}

bool Vertex::getCheck() {
    return this->checked;
}

Edge *Vertex::getN() {
    return this->north;
}

Edge *Vertex::getS() {
    return this->south;
}

Edge *Vertex::getE() {
    return this->east;
}

Edge *Vertex::getW() {
    return this->west;
}

void Vertex::setCheck() {
    this->checked = !this->checked;
}

void Vertex::setN(Edge *e) {
    this->north = e;
}

void Vertex::setS(Edge *e) {
    this->south = e;
}

void Vertex::setE(Edge *e) {
    this->east = e;
}

void Vertex::setW(Edge *e) {
    this->west = e;
}
