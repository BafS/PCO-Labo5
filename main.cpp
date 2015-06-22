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
#include "Client.h"

void display() {

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

    std::cout << "Start simulation <<<";

    unsigned int randNumber;
    QList<Client*> clients;
    for (int i = 0; i < NB_CLIENTS_HAIRCUT; i++) {

        clients.append(new Client());
        clients.at(i)->start();
    }

    // Wait all clients
    for (int i = 0; i < NB_CLIENTS_HAIRCUT; i++) {
        clients.at(i)->wait();
    }

    std::cout << ">>> end of simulation";

    return a.exec();
}
