//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#include "Edge.h"
#include "Vertex.h"

Edge::Edge(int id, Vertex *a, Vertex *b) {
    this->id = id;
    this->a = a;
    this->b = b;
}

int Edge::getID() { return this->id; }

Vertex *Edge::getA() { return this->a; }

Vertex *Edge::getB() { return this->b; }

Vertex *Edge::getDestiny(Vertex *x) {
    if (x == this->a) {
        return this->b;
    }

    if (x == this->b) {
        return this->a;
    }

    return 0;
}
