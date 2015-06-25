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

/**
 * @brief Représente le client qui souhaite se faire faire un tatouage
 */
class ClientTatoo : public Client {

    Q_OBJECT
        void run() {

            qDebug() << "New tatoo client n°" << id;

            while (alive) {
                qDebug() << "ClientT("<<id<<"): Do I want a tatoo ? Mmmh...";
                this->sleep(sleepTime);
                qDebug() << "ClientT("<<id<<"): Yes, I want a tatoo !";

                // Essaye de rentrer dans la salle d'attente
                qDebug() << "ClientT("<<id<<"): try to enter in waiting room";

                while(!mon->tryEnter(TATOO)) {
                    this->sleep(sleepTime * MULT_GO_HOME); // Si la salle est pleine, le client rentre
                                                           // chez lui et reviens plus tard
                }

                mon->goToBarber(TATOO);
            }
        }

public:
        ClientTatoo(HairStyleMonitor *m) : Client(m) {}
};

#endif // CLIENTTATOO_H
