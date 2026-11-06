#include "trem.h"
#include <QtCore>
#include <QMutex>


QMutex regiao1;
QMutex regiao2;
QMutex regiao3;
QMutex regiao4;
QMutex regiao5;
QMutex regiao6;
QMutex regiao7;
QMutex regiao8;
QMutex regiao9;


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
    // B e C começam ocupando trechos compartilhados.
    if (ID == 2) {
        regiao1.lock();
    }
    if (ID == 3) {
        regiao2.lock();
        regiao3.lock();
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
                if (y == 160) regiao1.lock();
                y += 10;
            } else if (y == 180 && x < 740) {
                if (x == 460) regiao2.lock();
                x += 10;
                if (x == 480) regiao1.unlock();
            } else if (x == 740 && y > 50) {
                y -= 10;
                if (y == 160) regiao2.unlock();
            } else if (y == 50 && x > 200) {
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 2: // B
            if (x == 200 && y < 320) {
                y += 10;
                if (y == 200) regiao1.unlock();
            } else if (y == 320 && x < 470) {
                if (x == 440) regiao3.lock();
                x += 10;
            } else if (x == 470 && y > 180) {
                if (y == 200) regiao1.lock();
                y -= 10;
            } else if (y == 180 && x > 200) {
                x -= 10;
                if (x == 440) regiao3.unlock();
            }
            emit updateGUI(ID, x, y);
            break;

        case 3: // C
            if (x == 470 && y < 320) {
                y += 10;
                if (y == 200) regiao2.unlock();
            } else if (y == 320 && x < 740) {
                x += 10;
                if (x == 500) regiao3.unlock();
            } else if (x == 740 && y > 180) {
                if (y == 200) regiao2.lock();
                y -= 10;
            } else if (y == 180 && x > 470) {
                if (x == 500) regiao3.lock();
                x -= 10;
            }
            emit updateGUI(ID, x, y);
            break;

        case 4: // D
            if (x == 60 && y < 440)
                y += 10;
            else if (y == 440 && x < 330)
                x += 10;
            else if (x == 330 && y > 320)
                y -= 10;
            else if (y == 320 && x > 60)
                x -= 10;
            emit updateGUI(ID, x, y);
            break;

        case 5: // E
            if (x == 330 && y < 440)
                y += 10;
            else if (y == 440 && x < 600)
                x += 10;
            else if (x == 600 && y > 320)
                y -= 10;
            else if (y == 320 && x > 330)
                x -= 10;
            emit updateGUI(ID, x, y);
            break;

        case 6: // F
            if (x == 600 && y < 440)
                y += 10;
            else if (y == 440 && x < 870)
                x += 10;
            else if (x == 870 && y > 320)
                y -= 10;
            else if (y == 320 && x > 600)
                x -= 10;
            emit updateGUI(ID, x, y);
            break;

        default:
            break;
        }

        // Slider 1..200 corresponde a uma espera de 200..1 ms.
        msleep(static_cast<unsigned long>(201 - velocidadeAtual));
    }
}
