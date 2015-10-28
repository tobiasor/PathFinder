#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicsscene.h"
#include <QGraphicsRectItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  MyGraphicsScene* scene = new MyGraphicsScene(this);

  ui->graphicsView->setScene(scene);


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::mousePress(){
  qDebug() << "apa";
}
