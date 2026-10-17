#ifndef SEM_H
#define SEM_H

#include <semaphore.h>
#include <Qdebug>
#include <vector>
using namespace std;

/*
 * Classe sem organiza os semáforos utilizados pelos trens
 *
 *
*/

class sem{
    // sem_t semaforo1;
    // sem_t semaforo2;
    // sem_t semaforo3;
    // sem_t semaforo4;
    // sem_t semaforo5;
    // sem_t semaforo6;
    // sem_t semaforo7;
    static const int T=7;
    sem_t sems[T];

    // Valores a serem usados
    // nos "gradientes" de semáforos
    int s[T];


    public:
        sem(unsigned int ini=1);
        ~sem();
        sem_t* showSemaforo(int id);
        int showGradSemaforo(int num);

};

#endif // SEM_H
