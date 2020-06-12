#include "mainwindow.h"

#include <QDebug>

#include "constants.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug("Elevator is waiting\n");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button1_clicked()
{
    qDebug("Was clicked Button 1 on lift controller.");
    _elevator.call(1);
}

void MainWindow::on_button2_clicked()
{
    qDebug("Was clicked Button 2 on lift controller.");
    _elevator.call(2);
}

void MainWindow::on_button3_clicked()
{
    qDebug("Was clicked Button 3 on lift controller.");
    _elevator.call(3);
}

void MainWindow::on_button4_clicked()
{
    qDebug("Was clicked Button 4 on lift controller.");
    _elevator.call(4);
}

void MainWindow::on_button5_clicked()
{
    qDebug("Was clicked Button 5 on lift controller.");
    _elevator.call(5);
}

void MainWindow::on_button6_clicked()
{
    qDebug("Was clicked Button 6 on lift controller.");
    _elevator.call(6);
}

void MainWindow::on_button7_clicked()
{
    qDebug("Was clicked Button 7 on lift controller.");
    _elevator.call(7);
}

void MainWindow::on_button8_clicked()
{
    qDebug("Was clicked Button 8 on lift controller.");
    _elevator.call(8);
}

void MainWindow::on_button9_clicked()
{
    qDebug("Was clicked Button 9 on lift controller.");
    _elevator.call(9);
}
