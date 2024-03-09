#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


#define UP        0x48
#define DOWN   0x50
#define LEFT     0x4B
#define RIGHT   0x4D
//Juego de MoonFinder (EncuentraLunas). Estructura de Datos. Por Armando Herrera Alonso y Arturo Padilla Ayala
using namespace std;

class Vertice;

class Arista;

class Arista {
    int ID;
    Vertice *A;
    Vertice *B;

public:
    Arista() {}

    Arista(int i, Vertice *a, Vertice *b) {
        this->A = a;
        this->B = b;
        this->ID = i;
    }

    int getID() { return this->ID; }

    Vertice *getDestiny(Vertice *x) {
        if (x == this->A) {
            return this->B;
        } else if (x == this->B) {
            return this->A;
        } else {
            return NULL;
        }
    }

    Vertice *getA() { return this->A; }

    Vertice *getB() { return this->B; }

};

class Vertice {
    Arista *Norte;
    Arista *Sur;
    Arista *Este;
    Arista *Oeste;
    bool check;
    int ID;

public:
    Vertice() {
    }

    Vertice(int i) {
        this->ID = i;
        this->Norte = NULL;
        this->Sur = NULL;
        this->Este = NULL;
        this->Oeste = NULL;
        this->check = false;
    }

    void setN(Arista *C) {
        this->Norte = C;
    }

    void setS(Arista *C) {
        this->Sur = C;
    }

    void setE(Arista *C) {
        this->Este = C;
    }

    void setO(Arista *C) {
        this->Oeste = C;
    }

    void setCheck() {
        this->check != this->check;
    }

    bool getCheck() {
        return this->check;
    }

    int getID() { return this->ID; }

    Arista *getN() { return this->Norte; }

    Arista *getS() { return this->Sur; }

    Arista *getE() { return this->Este; }

    Arista *getO() { return this->Oeste; }


};

class Jugador {
    Vertice *Pos;
    int ID;
    int MoonC;

public:
    Jugador() {
    }

    Jugador(int i) {
        this->ID = i;
        this->Pos = NULL;
        this->MoonC = 0;

    }

    int getID() { return this->ID; }

    void setPos(Vertice *p) { this->Pos = p; }

    void incMoonC() { this->MoonC++; }

    int getMoonC() { return this->MoonC; }

    Vertice *getPos() { return this->Pos; }
};

//Clase para hacer recorrido
class Client {
    int id;
    int Distance;
    Client *Next;

public:

    Client(int n, int d) {
        this->id = n;
        this->Distance = d;
        this->Next = NULL;
    }

    void setNext(Client *s) { this->Next = s; }

    Client *getNext() { return this->Next; }

    int getID() { return this->id; }

    int getDistance() { return this->Distance; }
};




//VARIABLES DE CLASE PARA RECORRIDO(CLIENT)

int SPACE_VAR;//a.k.a. n = numero de filas y columnas en el tablero
int PLAY_VAR;
int TURN_VAR;
int moon;
bool IdiotMode = false;
vector<Vertice *> TABLERO(0);
vector<Arista *> ArDeTABLERO(0);
//Global Queue Variables
Client *First = NULL;
Client *Last = NULL;
Client *AuxCl;

//Queue Functions
void Add(Vertice *v, int dis) {

    Client *NewCl = new Client(v->getID(), dis);
    if (First == NULL) {
        First = NewCl;
        Last = NewCl;
    } else {
        Last->setNext(NewCl);
        Last = NewCl;

    }

}

void DeleteClient() {
    Client *VictimCl;
    if (First == NULL) {
        cout << "Sin registros" << endl;
    } else {
        if (First == Last) { Last = NULL; }
        VictimCl = First;

        First = First->getNext();
        delete VictimCl;
        VictimCl = NULL;
    }
}

void HotOrCold(int X) {
    /*float X=(float)x;*/
    float Level0 = 0;
    float Level1 = (float) (((SPACE_VAR) - 1) * 2) * 0.20;
    float Level2 = (float) (((SPACE_VAR) - 1) * 2) * 0.40;
    float Level3 = (float) (((SPACE_VAR) - 1) * 2) * 0.60;
    float Level4 = (float) (((SPACE_VAR) - 1) * 2) * 0.80;
    float Level5 = (float) ((SPACE_VAR) - 1) * 2;

    if (X > Level0 && X <= Level1) { cout << endl << "HIRVIENDO"; }
    if (X > Level1 && X <= Level2) { cout << endl << "CALIENTE"; }
    if (X > Level2 && X <= Level3) { cout << endl << "TIBIO"; }
    if (X > Level3 && X <= Level4) { cout << endl << "FRIO"; }
    if (X > Level4 && X <= Level5) { cout << endl << "HELADO"; }

}

void WhereIsMyMoon(int PlayerP, int MoonP) {
    Vertice *Start = TABLERO.at(PlayerP - 1);
    Vertice *Aux;
    //Vertice * Finish= TABLERO.at(MoonP-1);

    int rec = 0;
    Add(Start, rec);
    Start->setCheck();
    while ((First->getID()) != MoonP) {


        Start = TABLERO.at(First->getID() - 1);
        //Checar Norte
        if (Start->getN() != NULL) {
            Aux = Start->getN()->getDestiny(Start);
            if (Aux->getCheck() == false) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }
        //Checar Sur
        if (Start->getS() != NULL) {
            Aux = Start->getS()->getDestiny(Start);
            if (Aux->getCheck() == false) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }
        //Checar Este
        if (Start->getE() != NULL) {
            Aux = Start->getE()->getDestiny(Start);
            if (Aux->getCheck() == false) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }
        //Checar Oeste
        if (Start->getO() != NULL) {
            Aux = Start->getO()->getDestiny(Start);
            if (Aux->getCheck() == false) {

                Add(Aux, First->getDistance() + 1);
                Aux->setCheck();

            }
        }
        //Delete First
        Delet();


    }

    //PrintHot(First->getDistance());
    if (IdiotMode) {
        cout << endl << "Entre el jugador y la luna hay " << First->getDistance() << " espacios" << endl;
        cout << "La luna esta aqui mero perro -> " << MoonP << endl;

    } else {

        HotOrCold(First->getDistance());
        cout << endl << "Entre el jugador y la luna hay " << First->getDistance() << " espacios" << endl;
        cout << endl << "La luna esta aqui mero perro -> " << MoonP << endl;

    }
    while (First != NULL) {
        Delet();
    }
    for (int i = 0; i < (SPACE_VAR * SPACE_VAR); i++) {
        if (TABLERO[i]->getCheck()) {
            TABLERO[i]->setCheck();
        }
    }


}


void CreateBoard() {
    Vertice *Aux;

    for (int i = 0; i < (SPACE_VAR * SPACE_VAR); i++) {
        Aux = new Vertice(1 + i);
        TABLERO[i] = Aux;
    }

}

void AssembleBoard() {

    int c = 0;
    int id;
    Arista *auxA = NULL;
    for (int i = 0; i < (SPACE_VAR * SPACE_VAR); i++) {
        id = i + 1;
        if (id + SPACE_VAR > (SPACE_VAR * SPACE_VAR)) {}
        else {
            ArDeTABLERO[c] = new Arista(c, TABLERO.at(i), TABLERO.at(i + SPACE_VAR));
            (TABLERO[i])->setS(ArDeTABLERO.at(c));
            (TABLERO[i + SPACE_VAR])->setN(ArDeTABLERO.at(c));

            c++;
        }

        if (id % SPACE_VAR == 0) {}
        else {
            ArDeTABLERO[c] = new Arista(c, TABLERO.at(i), TABLERO.at(i + 1));
            (TABLERO[i])->setE(ArDeTABLERO[c]);
            (TABLERO[i + 1])->setO(ArDeTABLERO[c]);

            c++;
        }
    }

}


bool PlayerMove(Jugador *Player) {
    char flecha = std::cin.get();
    Vertice *CurrentPos = Player->getPos();
    Vertice *NewPos;


    if (flecha == 0) { flecha = getch(); }
    //else {flecha=getch();}

    switch (getch()) {
        case KEY_UP:
            if (CurrentPos->getN() == NULL) {
                //cout<<"No se puede mover en esa direccion"<<endl;
                return false;
                //PlayerMove(Player);
            } else {
                NewPos = (CurrentPos->getN())->getDestiny(CurrentPos);
                Player->setPos(NewPos);
                return true;

            }
            break;
        case KEY_DOWN:
            if (CurrentPos->getS() == NULL) {
                //cout<<"No se puede mover en esa direccion"<<endl;
                return false;
                //PlayerMove(Player);
            } else {
                NewPos = (CurrentPos->getS())->getDestiny(CurrentPos);
                Player->setPos(NewPos);
                return true;
            }
            break;
        case KEY_LEFT:
            if (CurrentPos->getO() == NULL) {
                //cout<<"No se puede mover en esa direccion"<<endl;
                return false;
                //PlayerMove(Player);
            } else {
                NewPos = (CurrentPos->getO())->getDestiny(CurrentPos);
                Player->setPos(NewPos);
                return true;
            }
            break;
        case KEY_RIGHT:
            if (CurrentPos->getE() == NULL) {

                return false;
                //PlayerMove(Player);
            } else {
                NewPos = (CurrentPos->getE())->getDestiny(CurrentPos);
                Player->setPos(NewPos);
                return true;
            }
            break;
        default:
            cout << "null" << endl;
            Sleep(500);
            flecha = getch();
            return false;  // not arrow
    }
    //return true;
}


void PlayerStatus(Jugador *Player) {
    //Player id
    cout << "Jugador " << Player->getID() << endl;
    //North Arrow
    cout << "    ";
    if ((Player->getPos())->getN() == NULL) { cout << " "; }
    else { cout << "A"; }
    cout << "    " << endl;
    cout << "    ";
    if ((Player->getPos())->getN() == NULL) { cout << " "; }
    else { cout << "|"; }
    cout << "    " << endl;
    //WestArrow
    if ((Player->getPos())->getO() == NULL) { cout << " "; }
    else { cout << "<"; }
    if ((Player->getPos())->getO() == NULL) { cout << " "; }
    else { cout << "-"; }
    //Position
    cout << "[";
    if ((Player->getPos())->getID() < 100) { cout << "0"; }
    if ((Player->getPos())->getID() < 10) { cout << "0"; }
    cout << (Player->getPos())->getID();
    cout << "]";
    //EastArrow
    if ((Player->getPos())->getE() == NULL) { cout << " "; }
    else { cout << "-"; }
    if ((Player->getPos())->getE() == NULL) { cout << " "; }
    else { cout << ">"; }
    cout << endl;

    //SouthArrow
    cout << "    ";
    if ((Player->getPos())->getS() == NULL) { cout << " "; }
    else { cout << "|"; }
    cout << "    " << endl;
    cout << "    ";
    if ((Player->getPos())->getS() == NULL) { cout << " "; }
    else { cout << "V"; }

    //MoonCounter
    cout << endl;
    cout << "Moons=" << Player->getMoonC();
}

int Tirar() {
    int dados;
    srand(time(NULL));
    dados = 1 + rand() % (7 - 1);//variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior)

    return dados;
}

bool CheckMoon(int posicion) {
    bool encontrada;//true si hay luna
    if (position == moon) {
        encontrada = true;
    } else {
        encontrada = false;
    }

    return encontrada;
}

void NewMoon(int x) {
    moon = x;
}

void PrintAristas() {
    for (int i = 0; i < ArDeTABLERO.size(); i++) {
        cout << "Arista " << ArDeTABLERO[i]->getID() << " (" << ArDeTABLERO[i]->getA()->getID() << "-"
             << ArDeTABLERO[i]->getB()->getID() << ")" << endl;

    }
    for (int k = 0; k < (SPACE_VAR * SPACE_VAR); k++) {
        cout << "vERTICE " << TABLERO.at(k)->getID();
        if ((TABLERO.at(k)->getN()) != NULL) {
            cout << " N(" << (TABLERO.at(k)->getN())->getID() << ")";
        }
        if ((TABLERO.at(k)->getS()) != NULL) {
            cout << " S(" << (TABLERO.at(k)->getS())->getID() << ")";;
        }
        if ((TABLERO.at(k)->getE()) != NULL) {
            cout << " E(" << (TABLERO.at(k)->getE())->getID() << ")";;
        }
        if ((TABLERO.at(k)->getO()) != NULL) {
            cout << " O(" << (TABLERO.at(k)->getO())->getID() << ")";;
        }
        cout << endl;

    }


}

int main(void) {
    int j, n, turnos, cont;
    cout << "Cuantos jugadores van a participar? ";
    cin >> j;
    cout << "Cuantas filas y columnas habra en el tablero (el tablero sera cuadrado)? ";
    cin >> n;
    SPACE_VAR = n;
    cout << "Cuantos turnos va a durar la partida? ";
    cin >> turnos;

    TABLERO.resize(SPACE_VAR * SPACE_VAR);
    ArDeTABLERO.resize(SPACE_VAR * (2 * (SPACE_VAR - 1)));

    CreateBoard();//se crea el tablero
    AssembleBoard();//se ensambla el tablero
    cout << "Tablero listo para jugar con " << j << " jugadores" << endl;
    //PrintAristas();
    system("PAUSE");
    system("cls");

    Jugador *Player[j];//arreglo de jugadores creados en el siguiente ciclo
    for (int i = 0; i < j; i++) {
        Player[i] = new Jugador(i + 1);
        srand(time(NULL));
        Player[i]->setPos(TABLERO.at(1 + rand() % (1 - (SPACE_VAR *
                                                        SPACE_VAR))));//variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
    }
    NewMoon((1 + rand() % (1 - (SPACE_VAR * SPACE_VAR))));
    cont = 0;
    while (cont < turnos) {//el juego termina despues de determinado numero de turnos
        for (int i = 0; i < j; i++) {//turno de cada jugador
            if (cont == turnos) break;
            system("cls");
            cout << "Este es el turno " << cont + 1 << " de " << turnos << endl;
            cout << "Turno del Jugador " << i + 1 << endl;
            Sleep(1500);
            system("cls");
            //tira el dado y sigue un for
            int dado = Tirar();
            for (int k = 0; k < dado; k++) {
                system("cls");
                cout << "Movimientos: " << dado - k << endl;
                PlayerStatus(Player[i]);
                while (!PlayerMove(Player[i])) {//se mueve
                    system("cls");
                    cout << "Movimientos: " << dado - k << endl;
                    PlayerStatus(Player[i]);
                    cout << endl << "No se puede mover en esa direccion" << endl;
                }


            }
            system("cls");
            cout << "Movimientos: " << 0 << endl;
            PlayerStatus(Player[i]);
            if (CheckMoon(Player[i]->getPos()->getID())) {//encontro la luna
                Player[i]->incMoonC();
                NewMoon((1 + rand() % (1 - (SPACE_VAR * SPACE_VAR))));
            } else {
                WhereIsMyMoon(Player[i]->getPos()->getID(), moon);
            }


            system("PAUSE");
        }
        cont++;
    }
    for (int i = 0; i < j; i++) {
        cout << "El jugador " << i + 1 << " encontro " << Player[i]->getMoonC() << " lunas" << endl;
    }
    system("PAUSE");

}

/*Pendientes:
que no descuente movimiento al moverse fuera del tablero
determinar distancia luna-jugador
*/







/*
int ID;
this->ID=x;
int getID(){return this->ID;}


Vertice * TABLERO [(SPACE_VAR*SPACE_VAR)];
Arista * ArDeTABLERO [SPACE_VAR*(2*(SPACE_VAR-1))];


srand(clock());

1+rand()%(800-700)
*/
