//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#ifndef MOONFINDER_PROGRAM_PLAYER_H
#define MOONFINDER_PROGRAM_PLAYER_H

#include "Vertex.h"

class Player {
private:
    int id;
    int moonScore;
    Vertex *v;

public:
    Player(int i);

    int getId();

    int getMoonScore();

    Vertex *getV();

    void increaseMoonScore();

    void resetMoonScore();

    void setV(Vertex *v);

};

#endif //MOONFINDER_PROGRAM_PLAYER_H
