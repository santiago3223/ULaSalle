#include "iostream"
#include "mainwindow.h"
#include "glcm.h"
#include "image.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include "app.h"


TApp app;
string Singleton::ruta =  "/home/santiago/ProyectoFinal/database/clases/";
Singleton *Singleton::inst = 0;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    app.Init();
    //Image im ("obj1__0.png", "", 8);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnMatrizNumerica_clicked()
{
    ui->lstValores->clear();
    Image im (ui->txtValoresMatriz->toPlainText().toStdString(), ui->txtSize->text().toInt(), ui->txt_EscalaGrises->text().toInt(),ui->cmbAngulo->currentIndex());
    for(int i = 0; i<13;i++){
        ui->lstValores->addItem("f"+QString::number(i+1) + ": " +QString::number(im.features[i]));
    }
}

void MainWindow::CargarAlternativas(const char * fileName){
    QString ruta = QString::fromStdString(Singleton::instance()->getRuta());
    ui->lstQuery->clear();
    ui->lstQuery->setIconSize(QSize(100,100));
    ifstream in(fileName);
    char imageName[200];
    while(in.getline(imageName, 200, '\t')){
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(imageName);
        QString r = ruta + imageName;
        item->setIcon(QIcon(r));
        ui->lstQuery->addItem(item);
        in.ignore();
    }
    ui->lstQuery->setCurrentRow(0);

}

void MainWindow::on_btn_CargarConsultas_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/santiago/",tr("All Files (*.*)"));
    app.LoadVectorFromFile(path.toStdString().c_str(),ui->txtNivelGrisesImg->text().toInt());
    CargarAlternativas(path.toStdString().c_str());
}

void MainWindow::on_btn_CargarDatos_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/santiago/",tr("All Files (*.*)"));
    app.LoadTree(path.toStdString().c_str(),ui->txtNivelGrisesImg->text().toInt());
}

void MainWindow::on_btnCalcularResultados_clicked()
{
    vector<string> v;
    switch (ui->cmbType->currentIndex()) {
    case 0:
        cout<<"llama a range query"<<endl;
        v = app.PerformRangeQuery(ui->lstQuery->currentRow(),ui->txt_param->text().toDouble());
        break;
    case 1:
        cout<<"llama a nearest query"<<endl;
        v = app.PerformNearestQuery(ui->lstQuery->currentRow(),ui->txt_param->text().toInt());
        break;
    };
    ui->lstResult->clear();
    ui->lstResult->setIconSize(QSize(100,100));
    QString ruta = QString::fromStdString(Singleton::instance()->getRuta());
    for(int i = 0; i < v.size(); i++){
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(QString(v.operator [](i).c_str()));
        QString r = ruta + QString(v.operator [](i).c_str());
        item->setIcon(QIcon(r));
        ui->lstResult->addItem(item);

    }
}
