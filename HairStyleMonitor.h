/**
 * Moniteur du salon de coiffure/tatouage
 * ======================================
 *
 *
 *
 *
 * Note:
 *  - barberIsWorking est à true lorsque le barbier n'est pas sur sont lieu de travail
 *
 */
#ifndef HAITSTYLEMONITOR_H
#define HAITSTYLEMONITOR_H

#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

#define NB_SIEGES 8

#define HAIRCUT 0
#define TATOO 1

class HairStyleMonitor {

protected:
    QMutex mutex;
    QWaitCondition client[2];
    QWaitCondition working;
    QWaitCondition barber;
    int nbClients[2]; // Clients à coiffer/tatouer actuellement dans la salle d'attente.
    bool barberIsWorking = true;

public:
    HairStyleMonitor() {
        nbClients[HAIRCUT] = 0;
        nbClients[TATOO] = 0;
    };
    ~HairStyleMonitor() {};

    /**
     * Permet au barbier d'annoncer qu'il ouvre son salon de coiffure
     */
    void openStore() {
        mutex.lock();

        barberIsWorking = false;

        mutex.unlock();
    }

    /**
     * Attente passive du barbier lorsqu'il n'y a pas de clients
     */
    void waitClient() {
        mutex.lock();

        if (nbClients[HAIRCUT] + nbClients[TATOO] < 1) {
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
    bool tryEnter(int type) {
        mutex.lock();

        if (nbClients[HAIRCUT] + nbClients[TATOO] < NB_SIEGES) {
            nbClients[type]++;
            qDebug() << "mon: New client in waiting room (" << nbClients[HAIRCUT] << "/" << nbClients[TATOO] << ")";
            mutex.unlock();
            return true;
        }

        mutex.unlock();
        return false;
    }

    /**
     * Le client attend que le barbier soit libre et se fait tatouer/couper les cheveux
     */
    void goToBarber(int type) {
        mutex.lock();

        while (barberIsWorking) {
            client[type].wait(&mutex);
        }

        nbClients[type]--;

        // réveil d barbier
        barberIsWorking = true;
        barber.wakeOne();

        while (barberIsWorking) {
            working.wait(&mutex);
        }

        // Réveil le prochain client de la salle d'attente
        // !!! Priorité au client à tatouer
        if (nbClients[TATOO] > 0) {
            qDebug() << "mon: Prioritity for tatoo";
            client[TATOO].wakeOne();
        } else {
            client[HAIRCUT].wakeOne();
        }

        mutex.unlock();
    }

};

#endif // MONITOR_H
