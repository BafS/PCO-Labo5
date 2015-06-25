/**
 * PCO - Laboratoire n°5 Barbier
 * =============================
 *
 * @author Fabien Salathe
 * @author Benoît Zuckschwerdt
 *
 */
#include <QCoreApplication>
#include <QList>
#include <iostream>
#include "HairStyleMonitor.h"
#include "Barber.h"
#include "ClientHaircut.h"
#include "ClientTatoo.h"
#include "Client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    int SIZE_OF_WAINTING_ROOM = 0;
    int NB_CLIENTS_HAIRCUT = 0;
    int NB_CLIENTS_TATOO = 0;

    do {

        do {
            std::cout << "Enter the number of clients for a haircut: ";
            std::cin >> NB_CLIENTS_HAIRCUT;
        } while (NB_CLIENTS_HAIRCUT < 0);

        do {
            std::cout << "Enter the number of clients for a tatoo: ";
            std::cin >> NB_CLIENTS_TATOO;
        } while (NB_CLIENTS_TATOO < 0);

    } while(NB_CLIENTS_HAIRCUT + NB_CLIENTS_TATOO < 1);

    do {
        std::cout << "Enter size of the waiting room ";
        std::cin >> SIZE_OF_WAINTING_ROOM;
    } while(SIZE_OF_WAINTING_ROOM < 1);

    std::cout << "Start simulation <<<";

    /**
     * init. des clients, du barbier et du moniteur
     */
    HairStyleMonitor mon;
    //unsigned int randNumber;
    Barber barber(&mon);
    //barber = new Barber(&mon);
    barber.start();
    QList<ClientHaircut*> clientsHaircut;
    QList<ClientTatoo*> clientsTatoo;

    for (int i = 0; i < NB_CLIENTS_HAIRCUT; i++) {
        clientsHaircut.append(new ClientHaircut(&mon));
        clientsHaircut.at(i)->start();
    }

    for (int i = 0; i < NB_CLIENTS_TATOO; i++) {
        clientsTatoo.append(new ClientTatoo(&mon));
        clientsTatoo.at(i)->start();
    }

    // Wait all clients
    for (int i = 0; i < NB_CLIENTS_HAIRCUT; i++) {
        clientsHaircut.at(i)->wait();
    }

    for (int i = 0; i < NB_CLIENTS_TATOO; i++) {
        clientsTatoo.at(i)->wait();
    }

    std::cout << ">>> end of simulation";

    return a.exec();
}
