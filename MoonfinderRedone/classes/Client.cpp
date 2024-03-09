//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#include "Client.h"

Client::Client(int n, int d) {
    this->id = n;
    this->distance = d;
    this->Next = 0;
}

int Client::getId() {
    return this->id;
}

int Client::getDistance() {
    return this->distance;
}

Client *Client::getNext() {
    return this->Next;
}

void Client::setNext(Client *c) {
    this->Next = c;
}
