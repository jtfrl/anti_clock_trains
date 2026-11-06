#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 1. Sliders de cada um dos trens:
    connect(ui->sliderT1, &QSlider::valueChanged, this, &MainWindow::t1_on_horizontalSlider_valueChanged);
    connect(ui->sliderT2, &QSlider::valueChanged, this, &MainWindow::t2_on_horizontalSlider_valueChanged);
    connect(ui->sliderT3, &QSlider::valueChanged, this, &MainWindow::t3_on_horizontalSlider_valueChanged);
    connect(ui->sliderT4, &QSlider::valueChanged, this, &MainWindow::t4_on_horizontalSlider_valueChanged);
    connect(ui->sliderT5, &QSlider::valueChanged, this, &MainWindow::t5_on_horizontalSlider_valueChanged);
    connect(ui->sliderT6, &QSlider::valueChanged, this, &MainWindow::t6_on_horizontalSlider_valueChanged);
    connect(ui->sliderM, &QSlider::valueChanged, this, &MainWindow::on_sliderM_valueChanged);

    // Cada letra acompanha o valor do seu slider, como o marcador M.
    auto configurarMarcador = [](QSlider *slider, QLabel *marcador) {
        marcador->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        marcador->setParent(slider);
        marcador->show();
        marcador->raise();

        auto posicionar = [slider, marcador](int value) {
            const int x = QStyle::sliderPositionFromValue(
                slider->minimum(), slider->maximum(), value,
                slider->width() - marcador->width());
            marcador->move(x, 0);
        };

        QObject::connect(slider, &QSlider::valueChanged, slider, posicionar);
        posicionar(slider->value());
    };

    configurarMarcador(ui->sliderT1, ui->label_slider);
    configurarMarcador(ui->sliderT2, ui->label_slider1);
    configurarMarcador(ui->sliderT3, ui->label_slider2);
    configurarMarcador(ui->sliderT4, ui->label_slider3);
    configurarMarcador(ui->sliderT5, ui->label_slider4);
    configurarMarcador(ui->sliderT6, ui->label_slider5);
    configurarMarcador(ui->sliderM, ui->label_sliderM);
    
    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,200,50);
    trem2 = new Trem(2,200,180);
    trem3 = new Trem(3,470,180);
    trem4 = new Trem(4,60,320);
    trem5 = new Trem(5,330,320);
    trem6 = new Trem(6,600,320);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    case 6: //Atualiza a posição do objeto da tela (quadrado) que representa o trem6
        ui->label_trem6->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// === MODIFICADORES DE VELOCIDADE PARA CADA UM DOS TRENS === 
// com seis funções dedicadas, o usuário pode livremente
// ativar um ou múltiplos trens ao mesmo tempo

void MainWindow::t1_on_horizontalSlider_valueChanged(int value){
    trem1->speed(value);
}


void MainWindow::t2_on_horizontalSlider_valueChanged(int value){
    trem2->speed(value);
}


void MainWindow::t3_on_horizontalSlider_valueChanged(int value){
    trem3->speed(value);
}


void MainWindow::t4_on_horizontalSlider_valueChanged(int value){
    trem4->speed(value);
}

void MainWindow::t5_on_horizontalSlider_valueChanged(int value){
    trem5->speed(value);
}

void MainWindow::t6_on_horizontalSlider_valueChanged(int value){
    trem6->speed(value);
}

void MainWindow::on_sliderM_valueChanged(int value)
{
    ui->sliderT1->setValue(value);
    ui->sliderT2->setValue(value);
    ui->sliderT3->setValue(value);
    ui->sliderT4->setValue(value);
    ui->sliderT5->setValue(value);
    ui->sliderT6->setValue(value);
}

