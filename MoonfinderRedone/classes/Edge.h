//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#ifndef MOONFINDER_PROGRAM_EDGE_H
#define MOONFINDER_PROGRAM_EDGE_H

class Vertex;

class Edge {
private:
    int id;
    Vertex *a;
    Vertex *b;

public:
    Edge(int id, Vertex *a, Vertex *b);

    int getID();

    Vertex *getA();

    Vertex *getB();

    Vertex *getDestiny(Vertex *x);
};

#endif //MOONFINDER_PROGRAM_EDGE_H
