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
 *
 * Note:
 *  - On admet que le temps de pousse des cheveux est constant pour un client.
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QThread>
#include <QDebug>
#include <cstdlib>
#include "HairStyleMonitor.h"

// In seconds
#define HAIR_GROW_TIME_MIN  1
#define HAIR_GROW_TIME_MAX  5

#define ID_RANGE        32000
#define MULT_GO_HOME    0.5


class Client : public QThread {
protected:
    unsigned int id;
    bool alive = true;
    unsigned int sleepTime;
    HairStyleMonitor *mon;

Q_OBJECT
    void run() {
    }


public:
    Client(HairStyleMonitor *m) {
        mon = m;

        id = rand() % ID_RANGE; // generate random id

        // Random sleep time
        sleepTime = (rand() % (HAIR_GROW_TIME_MAX + 1)) + HAIR_GROW_TIME_MIN;

    };

    virtual ~Client() {};
};


#endif // CLIENT_H
