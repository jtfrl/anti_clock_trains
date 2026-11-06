#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int); //> atualização de interface
    void ativarTrens(); //> inicialização do movimento dos trens

private slots:

    // controladores de velocidade para cada trem
    void t1_on_horizontalSlider_valueChanged(int value);
    void t2_on_horizontalSlider_valueChanged(int value);
    void t3_on_horizontalSlider_valueChanged(int value);
    void t4_on_horizontalSlider_valueChanged(int value);
    void t5_on_horizontalSlider_valueChanged(int value);
    void t6_on_horizontalSlider_valueChanged(int value);

    void on_sliderM_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
    Trem *trem6;
};

#endif // MAINWINDOW_H
