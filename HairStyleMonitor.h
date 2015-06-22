#ifndef HAITSTYLEMONITOR_H
#define HAITSTYLEMONITOR_H

#include <QMutex>
#include <QWaitCondition>

#define NB_SIEGES 8

class HairStyleMonitor {

protected:
    QMutex mutex;
    QWaitCondition client;
    QWaitCondition barber;
    int nbClients = 0;


public:
    HairStyleMonitor() {};
    ~HairStyleMonitor() {};

    void enter() {
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
    }


};

#endif // MONITOR_H
