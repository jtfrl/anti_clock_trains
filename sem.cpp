#include "sem.h"
// TODO adicionar destroyers (~)

sem::sem(unsigned int n) {

    for(int i=1;i<7;i++){
        sem_init(&sems[i], 0, n);
        s[i]=0;
    }
}

sem_t* sem::showSemaforo(int num){
    if(num<0 || n>6){
        cerr<<"Número fora do escopo. Escolha um número entre 0 e 6";
        return NULL;
    }
    return sems[num];
}

int sem::showGradSemaforo(int num){
    if(num<0 || n>6){
        cerr<<"Número fora do escopo. Escolha um número entre 0 e 6";
        return NULL;
    }
    sem_getvalue(&sems[num], &s[num]);
    int valor=s[num];
    return valor;
}
