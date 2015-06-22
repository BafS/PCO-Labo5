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
#include <QDebug>
#include "HairStyleMonitor.h"
#include "Client.h"

#define NB_CLIENTS 10

void display() {

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Start simulation <<<";

    unsigned int randNumber;
    QList<Client*> clients;
    for (int i = 0; i < NB_CLIENTS; i++) {

        clients.append(new Client());
        clients.at(i)->start();
    }

    // Wait all clients
    for (int i = 0; i < NB_CLIENTS; i++) {
        clients.at(i)->wait();
    }

    qDebug() << ">>> end of simulation";

    return a.exec();
}
