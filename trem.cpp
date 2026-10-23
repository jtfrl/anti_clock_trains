#include "trem.h"
#include <QtCore>

// Construtor
// sem é o tipo que definimos para semáforos (ver sem.h)
Trem::Trem(int ID, int x, int y, sem *&sem){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    this->semaforos=sem;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:
                if(velocidade==200){
                    break;
                }
                if(x<510 && y==33){
                    if(x==450 && sem->showGradSemaforo(0)>0){
                        if( sem->showGradSemaforo(2)==0 &&
                            sem->showGradSemaforo(4)==0 &&
                            sem->showGradSemaforo(6)==0 &&
                            sem->showGradSemaforo(6)==0 ){
                            break; // correspondência trem-r.c.:
                                    // (1,4), (2, 2), (4,8) e (5,6)
                        }
                        if( sem->showGradSemaforo(1)==0 &&
                            sem->showGradSemaforo(3)==0 &&
                            sem->showGradSemaforo(5)==0 &&
                            sem->showGradSemaforo(7)==0 )
                            break; // (1,3), (3,7), (2,1), (4,5)

                        if( sem->showGradSemaforo(1)==0 &&
                            sem->showGradSemaforo(4)==0 &&
                            sem->showGradSemaforo(5)==0)
                            break; // (1,4), (4,5), (2,1)
                    }
                    sem_wait(sem->showSemaforo(0));
                }else if(x==490 && semaforos->showGradSemaforo(0)==0){
                    break;
                }
                x+=10;
            }else if(x==510 && y<252){
                // TODO
                // sem post para R.C.s 0 e 1
                x-=10;
            }if(velocidade){
                emit updateGUI(ID, x, y);
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        default:
            break;
        }
        msleep(velocidade);
    }
}
/*
 * INDICADO PELO PROFESSOR

 *
 *
 *         case 1:     //Trem 1
            if (y == 3 && x <330)
                x+=10;
            else if (x == 330 && y < 150)
                y+=10;
            else if (x > 60 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600)
                x+=10;
            else if (x == 600 && y < 150)
                y+=10;
            else if (x > 330 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
 * /






