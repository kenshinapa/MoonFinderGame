//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#ifndef MOONFINDER_PROGRAM_VERTEX_H
#define MOONFINDER_PROGRAM_VERTEX_H

#include "Edge.h"

class Vertex {
private:
    int id;
    bool checked;
    Edge *north;
    Edge *south;
    Edge *east;
    Edge *west;

public:
    Vertex(int i);

    int getId();

    bool getCheck();

    Edge *getN();

    Edge *getS();

    Edge *getE();

    Edge *getW();

    void setCheck();

    void setN(Edge *e);

    void setS(Edge *e);

    void setE(Edge *e);

    void setW(Edge *e);
};

#endif //MOONFINDER_PROGRAM_VERTEX_H
