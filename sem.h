#ifndef SEM_H
#define SEM_H

#include <semaphore.h>
#include <Qdebug>
#include <vector>
using namespace std;

/*
 * Classe sem organiza os semáforos utilizados pelos trens
 * verificando as nove regiões críticas (R.C.)
 *
*/

class sem{
    static const int T=9; // trabalhamos com as 9 R.C.
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
