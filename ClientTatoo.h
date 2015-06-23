/**
 * ClientTatoo
 *
 * Processus d'un client pour un tatouage selon la donnée
 * ======================================================
 *
 * Boucle infinie:
 *  1) Décider de se faire ou re-faire tatouer.
 *  2) Obtenir un siège dans la salle d’attente.
 *  3) Attendre que le barbier devienne libre.
 *  4) S’asseoir sur le fauteuil et attendre la fin du tatouage.
 */
#ifndef CLIENTTATOO_H
#define CLIENTTATOO_H

#include "Client.h"

class ClientTatoo : public Client {

    Q_OBJECT
        void run() {

            qDebug() << "New client n°" << id;

            while (alive) {
                qDebug() << "Client("<<id<<"): want a tatoo";

                // Essaye de rentrer dans la salle d'attente
                qDebug() << "Client("<<id<<"): try to enter in waiting room";

                while(!mon->tryEnter()) {
                    // @TODO wait ?
                }

                mon->goToBarber();
            }
        }
};

#endif // CLIENTTATOO_H
