//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#ifndef MOONFINDER_PROGRAM_CLIENT_H
#define MOONFINDER_PROGRAM_CLIENT_H


class Client {
private:
    int id;
    int distance;
    Client *Next;

public:
    Client(int n, int d);

    int getId();

    int getDistance();

    Client *getNext();

    void setNext(Client *c);
};


#endif //MOONFINDER_PROGRAM_CLIENT_H
