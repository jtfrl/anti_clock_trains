#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 50 && x < 740)
                x+=10;
            else if (x == 740 && y < 180)
                y+=10;
            else if (x > 200 && y == 180)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 180 && x < 470)
                x+=10;
            else if (x == 470 && y < 320)
                y+=10;
            else if (x > 200 && y == 320)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3:
            if (y == 180 && x < 740)
                x+=10;
            else if (x == 740 && y < 320)
                y+=10;
            else if (x > 470 && y == 320)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4:
            if (y == 320 && x < 330)
                x+=10;
            else if (x == 330 && y < 440)
                y+=10;
            else if (x > 60 && y == 440)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5:
            if (y == 320 && x < 600)
                x+=10;
            else if (x == 600 && y < 440)
                y+=10;
            else if (x > 330 && y == 440)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 6:
            if (y == 320 && x <870)
                x+=10;
            else if (x == 870 && y < 440)
                y+=10;
            else if (x > 600 && y == 440)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




