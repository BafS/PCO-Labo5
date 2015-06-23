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
    QWaitCondition working;
    QWaitCondition barber;
    int nbClients = 0; // Clients actuellement dans la salle d'attente.
    bool barberIsFree = false;
    bool barberIsWorking = false;

public:
    HairStyleMonitor() {};
    ~HairStyleMonitor() {};

    void openStore() {
        mutex.lock();

        barberIsFree = true;

        mutex.unlock();
    }


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

    void goToBarber() {
        mutex.lock();

        while (!barberIsFree) {
            client.wait(&mutex);
        }

        nbClients--;
        barberIsFree = false;
        barberIsWorking = true;
        barber.wakeOne();

        while (barberIsWorking) {
            working.wait(&mutex);
        }

        barberIsFree = true;
        barberIsWorking = false;

        mutex.unlock();
    }

    void waitClient() {
        mutex.lock();

        if (nbClients < 1) {
            barber.wait(&mutex);
        }

        mutex.unlock();
    }

    void ejectClient() {
        mutex.lock();

        working.wakeOne();

        mutex.unlock();
    }

    /*void enter() {
        mutex.lock();

        while(nbClients < NB_SIEGES)
            client.wait(&mutex);

        mutex.unlock();
    }

    void quit() {
        mutex.lock();

        nbClients--;
        client.wakeOne();

        mutex.unlock();
    }*/


};

#endif // MONITOR_H
