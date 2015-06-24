#ifndef HAITSTYLEMONITOR_H
#define HAITSTYLEMONITOR_H

#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

#define NB_SIEGES 8

class HairStyleMonitor {

protected:
    QMutex mutex;
    QWaitCondition client;
    QWaitCondition clientTatoo; // @TODO
    QWaitCondition working;
    QWaitCondition barber;
    int nbClients = 0; // Clients actuellement dans la salle d'attente.
    bool barberIsFree = false;
    bool barberIsWorking = false;

public:
    HairStyleMonitor() {};
    ~HairStyleMonitor() {};

    /**
     * Permet au barbier d'annoncer qu'il ouvre son salon de coiffure
     */
    void openStore() {
        mutex.lock();

        barberIsFree = true;

        mutex.unlock();
    }

    /**
     * Attente passive du barbier lorsqu'il n'y a pas de clients
     */
    void waitClient() {
        mutex.lock();

        if (nbClients < 1) {
            barber.wait(&mutex);
        }

        mutex.unlock();
    }

    /**
     * Lors de la fin d'une coupe ou d'une coiffure, réveil
     * le prochain client
     */
    void ejectClient() {
        mutex.lock();

        qDebug() << "mon: next!";
        barberIsWorking = false;
        working.wakeOne();

        mutex.unlock();
    }


    /**
     * Le client esssaie d'entrer dans la salle d'attente
     * @return vrai si l'entrée est réussie
     */
    bool tryEnter() {
        mutex.lock();

        if (nbClients < NB_SIEGES) {
            qDebug() << "mon: New client in waiting room";

            nbClients++;
            mutex.unlock();
            return true;
        }

        mutex.unlock();
        return false;
    }

    /**
     * Le client attend que le barbier soit libre et se fait tatouer/couper les cheveux
     */
    void goToBarber() {
        mutex.lock();

        while (!barberIsFree) {
            client.wait(&mutex);
        }

        nbClients--;

        // réveil d barbier
        barberIsFree = false;
        barberIsWorking = true;
        barber.wakeOne();

        while (barberIsWorking) {
            working.wait(&mutex);
        }

        barberIsFree = true;
        client.wakeOne();

        mutex.unlock();
    }

};

#endif // MONITOR_H
