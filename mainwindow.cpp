#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 1. Sliders de cada um dos trens:
    connect(ui->sliderT1, &QSlider::valueChanges, this, &MainWindow::t1_on_horizontalSlider_valueChanged);
    connect(ui->sliderT2, &QSlider::valueChanges, this, &MainWindow::t2_on_horizontalSlider_valueChanged);
    connect(ui->sliderT3, &QSlider::valueChanges, this, &MainWindow::t3_on_horizontalSlider_valueChanged);
    connect(ui->sliderT4, &QSlider::valueChanges, this, &MainWindow::t4_on_horizontalSlider_valueChanged);
    connect(ui->sliderT5, &QSlider::valueChanges, this, &MainWindow::t5_on_horizontalSlider_valueChanged);
    connect(ui->sliderT6, &QSlider::valueChanges, this, &MainWindow::t6_on_horizontalSlider_valueChanged);
    
    // 2. Torna o label 100% transparente para cliques ANTES de tudo
    ui->label_sliderM->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    
    // 3. Define o slider como pai e exibe
    ui->label_sliderM->setParent(ui->horizontalSlider_M);
    ui->label_sliderM->show();
    ui->label_sliderM->raise();
    
    // 4. Conecta o sinal do slider
    connect(ui->horizontalSlider_M, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_M_valueChanged);
    
    // 5. Posiciona inicialmente
    on_horizontalSlider_M_valueChanged(ui->horizontalSlider_M->value());
    
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

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
    trem6->terminate();
}

// === MODIFICADORES DE VELOCIDADE PARA CADA UM DOS TRENS === 
// com seis funções dedicadas, o usuário pode livremente
// ativar um ou múltiplos trens ao mesmo tempo

void MainWindow::t1_on_horizontalSlider_valueChanged(int value){
    trem1->velocidade(value);
}


void MainWindow::t2_on_horizontalSlider_valueChanged(int value){
    trem2->velocidade(value);
}


void MainWindow::t3_on_horizontalSlider_valueChanged(int value){
    trem3->velocidade(value);
}


void MainWindow::t4_on_horizontalSlider_valueChanged(int value){
    trem4->velocidade(value);
}


void MainWindow::t5_on_horizontalSlider_valueChanged(int value){
    trem5->velocidade(value);
}

void MainWindow::t6_on_horizontalSlider_valueChanged(int value){
    trem6->velocidade(value);
}

void MainWindow::on_horizontalSlider_M_valueChanged(int value)
{
    // Calcula a posição X exata do botão cinza (handle) em pixels
    int x_do_handle = QStyle::sliderPositionFromValue(
        ui->horizontalSlider_M->minimum(),
        ui->horizontalSlider_M->maximum(),
        value,
        ui->horizontalSlider_M->width() - ui->label_sliderM->width() // Desconta a largura da letra
        );
    
    
    ui->label_sliderM->move(x_do_handle, 0);
    
    ui->sliderT1->setValue(value);
    ui->sliderT2->setValue(value);
    ui->sliderT3->setValue(value);
    ui->sliderT4->setValue(value);
    ui->sliderT5->setValue(value);
    ui->sliderT6->setValue(value);    
}
