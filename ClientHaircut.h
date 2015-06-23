/**
 * ClientHaircut
 *
 * Processus d'un client pour une coupe selon la donnée
 * ======================================================
 *
 * Boucle infinie:
 *  1) Attendre que les cheveaux poussent.
 *  2) Obtenir un siège dans la salle d’attente.
 *  3) Attendre que le barbier devienne libre.
 *  4) S’asseoir sur le fauteuil et attendre la fin dde la coupe.
 */
#ifndef CLIENTHAIRCUT_H
#define CLIENTHAIRCUT_H

#include "Client.h"

class ClientHaircut : public Client {

    Q_OBJECT
        void run() {

            qDebug() << "New client n°" << id;

            while (alive) {
                qDebug() << "Client("<<id<<"): hair growing";
                this->sleep(sleepTime);
                qDebug() << "Client("<<id<<"): hair ready to cut";

                // Essaye de rentrer dans la salle d'attente
                qDebug() << "Client("<<id<<"): try to enter in waiting room";
                while(!mon->tryEnter()) {
                    this->sleep(sleepTime * MULT_GO_HOME); // Si la salle est pleine, le client rentre
                                                           // chez lui et reviens plus tard
                }

                mon->goToBarber();
            }
        }

public:
        ClientHaircut(HairStyleMonitor *m) : Client(m) {

        }
};

#endif // CLIENTHAIRCUT_H
