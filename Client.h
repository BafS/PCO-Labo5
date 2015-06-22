/**
 * Client
 *
 * Processus du client selon la donnée
 * ===================================
 *
 * Boucle infinie:
 *  1) Attendre que les cheveux poussent.
 *  2) Obtenir un siège dans la salle d’attente.
 *  3) Attendre que le barbier devienne libre.
 *  4) S’asseoir sur le fauteuil et attendre la fin de la coupe.
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QThread>
#include <QDebug>
#include <cstdlib>

// In [ms]
#define HAIR_GROW_TIME_MIN  1
#define HAIR_GROW_TIME_MAX  5

#define ID_RANGE 32000



class Client : public QThread {
private:
    unsigned int id;
    bool alive = true;

Q_OBJECT
    void run() {

        qDebug() << "New client n°" << id;

        while (alive) {
            qDebug() << "Client("<<id<<"): " << "hair growing";
            waitHairGrow();
            qDebug() << "Client("<<id<<"): " << "hair ready to cut";
            qDebug() << "Client("<<id<<"): " << "go to waiting room";
            goToWaitingRoom();
            qDebug() << "Client("<<id<<"): " << "enter in waiting room";
            qDebug() << "Client("<<id<<"): " << "wait barber";
            waitingBarber();
            qDebug() << "Client("<<id<<"): " << "go to barber";
            goToBarber();
            qDebug() << "Client("<<id<<"): " << "wait for the haircut is finished";
            waitHairCutIsFinished();
            qDebug() << "Client("<<id<<"): " << "hair cut";
        }
    }

    void waitHairGrow() {
        unsigned int sleepTime = (rand() % (HAIR_GROW_TIME_MAX + 1)) + HAIR_GROW_TIME_MIN;
        this->sleep(sleepTime);
    }

    void goToWaitingRoom() {

    }

    void waitingBarber() {

    }

    void goToBarber() {

    }

    void waitHairCutIsFinished() {

    }

public:
    Client() {
        id = rand() % ID_RANGE; // generate random id
    };

    ~Client() {};
};


#endif // CLIENT_H
