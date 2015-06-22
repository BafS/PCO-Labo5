/**
 * Barbier
 *
 * Processus du barbier selon la donnée
 * ===================================
 *
 * Boucle infinie:
 *  1) Attendre qu'e les cheveux poussent.'un client se présente.
 *  2) Installer le client sur le fauteuil et lui couper les cheveux ou le tatouer.
 *
 */
#ifndef BARBER_H
#define BARBER_H

class Barber : public QThread {
public:
    Barber() {};
    ~Barber() {};

private:
    bool alive = true;

Q_OBJECT
    void run() {

        while(alive) {
            qDebug() << "Barber: I'm free";
        }

    }

};

#endif // BARBER_H
