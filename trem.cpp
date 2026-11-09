#include "trem.h"
#include <QtCore>
#include <QMutex>


/*QMutex regiao1;
QMutex regiao2;
QMutex regiao3;
QMutex regiao4;
QMutex regiao5;
QMutex regiao6;
QMutex regiao7;
QMutex regiao8;
QMutex regiao9;*/

QMutex regiao[10];
QSemaphore triade(2);


//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 0;
}

void Trem::speed(int valor) {
    if (valor < 0) valor = 0;
    if (valor > 200) valor = 200;
    velocidade.store(valor, std::memory_order_relaxed);
}

//Função a ser executada após executar trem->START
void Trem::run(){
    // B, C, E e F começam ocupando trechos compartilhados.
    if (ID == 2) {
        /*triade.acquire();*/
        regiao[1].lock();
    }
    if (ID == 3) {
        /*triade.acquire();*/
        regiao[2].lock();
        regiao[3].lock();
    }
    if(ID == 5) {
        regiao[5].lock();
        regiao[8].lock();
    }
    if(ID == 6){
        regiao[7].lock();
        regiao[9].lock();
    }

    while (true) {
        const int velocidadeAtual = velocidade.load(std::memory_order_relaxed);
        if (velocidadeAtual == 0) {
            msleep(10);
            continue;
        }

        switch (ID) {
        case 1: // A:
            if (x == 200 && y < 180) {
                //if (y == 150) triade.acquire();
                if (y == 160) regiao[1].lock();
                y += 10;
            } else if (y == 180 && x < 740) {
                if (x == 440) regiao[2].lock();
                x += 10;
                if (x == 480) regiao[1].unlock();
            } else if (x == 740 && y > 50) {
                y -= 10;
                if (y == 160) regiao[2].unlock();
                /*if (y == 170) triade.release();*/
            } else if (y == 50 && x > 200) {
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 2: // B
            if (x == 200 && y < 320) {
                y += 10;
                if (y == 200) regiao[1].unlock();
                if (y == 310) regiao[4].lock();
                /*if (y == 210) triade.release();*/
            } else if (y == 320 && x < 470) {
                if (x == 440) regiao[3].lock();
                if (x == 430) regiao[1].lock();
                if (x == 350) regiao[4].unlock();
                if (x == 300) regiao[5].lock();
                /*if (x == 430) triade.acquire();*/
                x += 10;
            } else if (x == 470 && y > 180) {
                /*if (y == 200) regiao[1].lock();*/
                if (y == 300) regiao[5].unlock();
                y -= 10;
            } else if (y == 180 && x > 200) {
                x -= 10;
                if (x == 440) regiao[3].unlock();
            }
            emit updateGUI(ID, x, y);
            break;

        case 3: // C
            if (x == 470 && y < 320) {
                y += 10;
                if (y == 200) regiao[2].unlock();
                if (y == 310) regiao[6].lock();
            } else if (y == 320 && x < 740) {
                x += 10;
                if (x == 500) regiao[3].unlock();
                if (x == 620) regiao[6].unlock();
                if (x == 580) regiao[7].lock();
                //if (x == 510) triade.release();
            } else if (x == 740 && y > 180) {
                if (y == 200) regiao[2].lock();
                if (y == 310) regiao[7].unlock();
                //if (y == 210) triade.acquire();
                y -= 10;
            } else if (y == 180 && x > 470) {
                if (x == 500) regiao[3].lock();
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 4: // D
            if (x == 60 && y < 440)
                y += 10;
            else if (y == 440 && x < 330) {
                if (x == 300) regiao[8].lock();
                if (x == 290) regiao[4].lock();
                x += 10;
            }
            else if (x == 330 && y > 320) {
                //if (y == 340) regiao[4].lock();
                y -= 10;
            }
            else if (y == 320 && x > 60) {
                if (x == 190) regiao[4].unlock();
                if (x == 300) regiao[8].unlock();
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 5: // E
            if (x == 330 && y < 440) {
                if (y == 340) regiao[5].unlock();
                y += 10;
            }
            else if (y == 440 && x < 600) {
                if (x == 350) regiao[8].unlock();
                if (x == 570) regiao[9].lock();
                x += 10;
            }
            else if (x == 600 && y > 320) {
                if (y == 340) regiao[6].lock();
                if (y == 350) regiao[5].lock();
                y -= 10;
            }
            else if (y == 320 && x > 330) {
                //if (x == 500) regiao[5].lock();
                if (x == 440) regiao[6].unlock();
                if (x == 360) regiao[8].lock();
                if (x == 580) regiao[9].unlock();
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 6: // F
            if (x == 600 && y < 440) {
                if (y == 340) regiao[7].unlock();
                y += 10;
            }
            else if (y == 440 && x < 870) {
                if (x == 620) regiao[9].unlock();
                x += 10;
            }
            else if (x == 870 && y > 320)
                y -= 10;
            else if (y == 320 && x > 600) {
                if (x == 770) regiao[7].lock();
                if (x == 780) regiao[9].lock();
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        default:
            break;
        }

        // Slider 1..200 corresponde a uma espera de 200..1 ms.
        msleep(static_cast<unsigned long>(201 - velocidadeAtual));
    }
}
