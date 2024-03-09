//
// Created by Arturo Padilla Ayala on 06/03/24.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "classes/Vertex.h"
#include "classes/Edge.h"
#include "classes/Player.h"
#include "classes/Client.h"

#define KEY_UP 'U'
#define KEY_DOWN 'D'
#define KEY_LEFT 'L'
#define KEY_RIGHT 'R'

using namespace std;

#define PRESS_ENTER_TO_CONTINUE_AFTER_INPUT { \
    cout << "\033[1;32mPress enter to continue"; \
    cin.get(); \
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); \
    system("clear");\
}

#define PRESS_ENTER_TO_CONTINUE_NO_PREVIOUS_INPUT { \
    cout << "\033[1;32mPress enter to continue"; \
    cin.get();                    \
    system("clear");\
}

bool dummyMode = false;

int board_size; // Size of the board which is a square of board_size x board_size
int moon;
vector<Vertex *> board(0);
vector<Edge *> boardEdge(0);

Client *First = nullptr;
Client *Last = nullptr;

void CreateBoard() {
    for (int i = 0; i < (board_size * board_size); i++) {
        board[i] = new Vertex(1 + i);
    }
}

void AssembleBoard() {
    int vertexId;
    int n = 0;

    for (int i = 0; i < (board_size * board_size); i++) { // will go through all the vertices of the board
        vertexId = i + 1;

        // For vertex ids before the last row
        if (vertexId + board_size <= (board_size * board_size)) {
            boardEdge[n] = new Edge(n, board.at(i), board.at(i + board_size)); // Vertical edge
            (board[i])->setS(boardEdge.at(n));
            (board[i + board_size])->setN(boardEdge.at(n));

            n++;
        }

        if (vertexId % board_size != 0) { // For vertex ids that are not at the right edge of the board
            boardEdge[n] = new Edge(n, board.at(i), board.at(i + 1)); // Horizontal edge
            (board[i])->setE(boardEdge.at(n));
            (board[i + 1])->setW(boardEdge.at(n));

            n++;
        }
    }
}

void NewMoon(int x) {
    moon = x;
}

int RollDice() {
    int result;
    srand(time(nullptr));
    result = 1 + rand() % (6);

    return result;
}

void PrintPlayerStatus(Player *p) {
    Vertex *v = p->getV();

    // Player id
    cout << "\033[1;36mPlayer " << p->getId() << endl << endl;

    // North Arrow
    cout << "    ";
    if (p->getV()->getN() == nullptr) { cout << " "; }
    else { cout << "A"; }
    cout << "    " << endl;
    cout << "    ";
    if (p->getV()->getN() == nullptr) { cout << " "; }
    else { cout << "|"; }
    cout << "    " << endl;

    // West Arrow
    if (v->getW() == nullptr) { cout << " "; }
    else { cout << "<"; }
    if (v->getW() == nullptr) { cout << " "; }
    else { cout << "-"; }

    // Position
    cout << "[";
    if (v->getId() < 100) { cout << "0"; }
    if (v->getId() < 10) { cout << "0"; }
    cout << (v)->getId();
    cout << "]";
    //EastArrow
    if (v->getE() == nullptr) { cout << " "; }
    else { cout << "-"; }
    if (v->getE() == nullptr) { cout << " "; }
    else { cout << ">"; }
    cout << endl;

    //South Arrow
    cout << "    ";
    if (v->getS() == nullptr) { cout << " "; }
    else { cout << "|"; }
    cout << "    " << endl;
    cout << "    ";
    if (v->getS() == nullptr) { cout << " "; }
    else { cout << "V"; }

    //Moon Score of the p
    cout << endl;
    cout << "Moons=" << p->getMoonScore() << endl;
}

char getArrowKey() {
    struct termios old_tio, new_tio;
    unsigned char key;

    // get the terminal settings for stdin
    tcgetattr(STDIN_FILENO, &old_tio);

    // we want to keep the old setting to restore them at the end
    new_tio = old_tio;

    // disable canonical mode (buffered i/o) and local echo
    new_tio.c_lflag &= (~ICANON & ~ECHO);

    // set the new settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    do {
        key = getchar();
    } while (key != 27); // loop until escape key is pressed

    // we got an escape key. Check for arrow keys
    if (getchar() == '[') {
        switch (getchar()) {
            case 'A':
                // Up
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                return 'U';
            case 'B':
                // Down
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                return 'D';
            case 'C':
                // Right
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                return 'R';
            case 'D':
                // Left
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
                return 'L';
        }
    }

    // restore the former settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    // we have not recognized the key press
    return 'N';
}

bool PlayerMove(Player *player) {
    Vertex *CurrentPos = player->getV();

    char arrow = getArrowKey();

    switch (arrow) {
        case KEY_UP:
            if (CurrentPos->getN() != nullptr) {
                player->setV(CurrentPos->getN()->getDestiny(CurrentPos));
                return true;
            }
            return false;
        case KEY_DOWN:
            if (CurrentPos->getS() != nullptr) {
                player->setV(CurrentPos->getS()->getDestiny(CurrentPos));
                return true;
            }
            return false;
        case KEY_LEFT:
            if (CurrentPos->getW() != nullptr) {
                player->setV(CurrentPos->getW()->getDestiny(CurrentPos));
                return true;
            }
            return false;
        case KEY_RIGHT:
            if (CurrentPos->getE() != nullptr) {
                player->setV(CurrentPos->getE()->getDestiny(CurrentPos));
                return true;
            }
            return false;
        default:
            cout << "null" << endl;
            return false;
    }
}

bool CheckIfMoonFound(int position) {
    return position == moon;
}

//Queue Functions
void Add(Vertex *v, int distance) {
    auto *NewCl = new Client(v->getId(), distance);

    if (First == nullptr) {
        First = NewCl;
        Last = NewCl;
    } else {
        Last->setNext(NewCl);
        Last = NewCl;
    }
}

void DeleteClient() {
    Client *victimClient;

    if (First != nullptr) {
        if (First == Last) { Last = nullptr; }
        victimClient = First;

        First = First->getNext();
        delete victimClient;
    } else {
        cout << "Sin registros" << endl;
    }
}

void HotOrCold(int X) {
    double Level0 = 0;
    double Level1 = (((board_size) - 1) * 2) * 0.20;
    double Level2 = (((board_size) - 1) * 2) * 0.40;
    double Level3 = (((board_size) - 1) * 2) * 0.60;
    double Level4 = (((board_size) - 1) * 2) * 0.80;
    double Level5 = ((board_size) - 1) * 2;

    cout << "\033[1;32mThe player is feeling..." << endl;

    if (X > Level0 && X <= Level1) { cout << endl << "\033[1;31mBOILING"; }
    if (X > Level1 && X <= Level2) { cout << endl << "\033[1;31mHOT"; }
    if (X > Level2 && X <= Level3) { cout << endl << "\033[1;33mWARM"; }
    if (X > Level3 && X <= Level4) { cout << endl << "\033[1;36mCOLD"; }
    if (X > Level4 && X <= Level5) { cout << endl << "\033[1;36mFROZEN"; }
}

void WhereIsMyMoon(int playerPosition, int moonPosition) {
    Vertex *Start = board.at(playerPosition - 1);
    Vertex *Aux;

    int rec = 0;
    Add(Start, rec);

    Start->setCheck();

    while ((First->getId()) != moonPosition) {
        Start = board.at(First->getId() - 1);

        // Check North
        if (Start->getN() != nullptr) {
            Aux = Start->getN()->getDestiny(Start);
            if (!Aux->getCheck()) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }

        // Check South
        if (Start->getS() != nullptr) {
            Aux = Start->getS()->getDestiny(Start);
            if (!Aux->getCheck()) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }

        // Check East
        if (Start->getE() != nullptr) {
            Aux = Start->getE()->getDestiny(Start);
            if (!Aux->getCheck()) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }

        // Check West
        if (Start->getW() != nullptr) {
            Aux = Start->getW()->getDestiny(Start);
            if (!Aux->getCheck()) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }

        DeleteClient();
    }

    if (dummyMode) {
        cout << endl << "There are " << First->getDistance() << " spaces between the player and the moon" << endl;
        cout << "The moon is here -> " << moonPosition << endl;
    } else {
        HotOrCold(First->getDistance());
        cout << endl << "There are " << First->getDistance() << " spaces between the player and the moon" << endl;
    }

    while (First != nullptr) {
        DeleteClient();
    }

    for (int i = 0; i < (board_size * board_size); i++) {
        if (board[i]->getCheck()) {
            board[i]->setCheck();
        }
    }
}

int main() {
    int noOfPlayers, n, moves, move;

    system("clear");

    cout << "\033[1;36mWelcome to the game of the moon - MoonFinder!\033[0m" << endl;
    cout << "\033[1;35mThe game consists of a board of squares, where each square is connected to its adjacent squares.\033[0m" << endl;
    cout << "\033[1;35mThe objective of the game is to find the moon, which will be placed in a random position.\033[0m" << endl;
    cout << "\033[1;35mThe game will last for a certain number of moves, and the player who finds the moon the most times will win.\033[0m" << endl;
    cout << "\033[1;35mThe game will be played by a certain number of players, and each player will roll a dice to move.\033[0m" << endl;
    cout << "\033[1;35mThe game will be played in turns, and each player will move according to the number rolled on the dice.\033[0m" << endl;
    cout << "\033[1;35mThe game will be played in a terminal, and the players will move using the arrow keys.\033[0m" << endl;

    cout << "Do you want to play in dummy mode? (y/n) ";
    string dummyModeInput;
    cin >> dummyModeInput;
    if (dummyModeInput == "y") {
        dummyMode = true;
    }

    cout << "Setting up the game..." << endl;

    cout << "How many players will play? ";
    cin >> noOfPlayers;
    cout << "What size will the board be? ";
    cin >> n;
    board_size = n;
    cout << "How many moves until the game ends? ";
    cin >> moves;

    board.resize(n * n);
    boardEdge.resize(board_size * (2 * (board_size - 1)));

    CreateBoard(); // Creation of vertexes
    AssembleBoard(); // Creation of edges
    cout << "Board created and ready to play for " << noOfPlayers << " players" << endl;

    Player *player[noOfPlayers];

    for (int i = 0; i < noOfPlayers; i++) {
        player[i] = new Player(i + 1);
        srand(time(nullptr));
        player[i]->setV(board.at(rand() % (board_size * board_size)));
    }

    NewMoon(rand() % (board_size * board_size));

    move = 0;

    PRESS_ENTER_TO_CONTINUE_AFTER_INPUT;

    while (move < moves) {
        for (int i = 0; i < noOfPlayers; i++) { // Represents the player's turn
            if (move == moves) break; // If the game has ended, break the loop

            cout << "\033[1;35mThis is the turn number " << move + 1 << " of " << moves << endl << endl;
            cout << "Turn of the player " << i + 1 << endl;

            int diceResult = RollDice();
            cout << "\033[1;35mThe dice rolled a " << diceResult << " for the player " << i + 1 << endl;

            PRESS_ENTER_TO_CONTINUE_NO_PREVIOUS_INPUT;

            for (int k = 0; k < diceResult; k++) {
                system("clear");
                cout << "\033[1;31mMovements: " << diceResult - k << endl;

                PrintPlayerStatus(player[i]);

                while (!PlayerMove(
                        player[i])) { // If the player can't move in the direction, it will keep asking for a new direction
                    system("clear");

                    cout << "\033[1;31mMovements: " << diceResult - k << endl;
                    PrintPlayerStatus(player[i]);
                    cout << endl ;
                    cout << "\033[1;35mInvalid movement, try again" << endl;
                }
            }

            system("clear");

            cout << "The player " << i + 1 << " has moved " << diceResult << " spaces" << " no more movements left"
                 << endl;

            PrintPlayerStatus(player[i]);

            if (CheckIfMoonFound(player[i]->getV()->getId())) { // If the player finds the moon, it will increase its moon score and the moon will move to a new position
                player[i]->increaseMoonScore();
                cout << "The player " << i + 1 << " has found the moon!" << endl;
                cout << "New moon score for the player " << i + 1 << " is " << player[i]->getMoonScore() << endl;
                NewMoon(rand() % (board_size * board_size));
                cout << "The moon has moved to a new position" << endl;
            } else {
                WhereIsMyMoon(player[i]->getV()->getId(), moon);
            }

            PRESS_ENTER_TO_CONTINUE_NO_PREVIOUS_INPUT;
        }

        move++;
    }

    for (int i = 0; i < noOfPlayers; i++) {
        cout << "The player " << i + 1 << " found " << player[i]->getMoonScore() << " moons" << endl;
    }

    cout << "The game has ended" << endl;

    PRESS_ENTER_TO_CONTINUE_NO_PREVIOUS_INPUT
}
