/**
 * Barbier
 *
 * Processus du barbier selon la donnée
 * ===================================
 *
 * Boucle infinie:
 *  1) Attendre que les cheveux poussent.'un client se présente.
 *  2) Installer le client sur le fauteuil et lui couper les cheveux ou le tatouer.
 *
 */
#ifndef BARBER_H
#define BARBER_H
#include <QThread>
#include <QDebug>
#include <cstdlib>
#include "HairStyleMonitor.h"

// In seconds
#define MIN_WORKING_TIME    1
#define MAX_WORKING_TIME    4

class Barber : public QThread {
private:
    bool alive = true;
    HairStyleMonitor *mon;

Q_OBJECT
    void run() {

        mon->openStore();

        while(alive) {
            qDebug() << "Barber: waiting client";
            mon->waitClient();
            qDebug() << "Barber: cut/tatoo client";
            working();
            mon->ejectClient();
        }

    }

    void working() {
        unsigned int sleepTime = (rand() % MAX_WORKING_TIME) + MIN_WORKING_TIME;
        this->sleep(sleepTime);
    }

public:
    Barber (HairStyleMonitor *m) {
        mon = m;
    };

    ~Barber() {};
};

#endif // BARBER_H
