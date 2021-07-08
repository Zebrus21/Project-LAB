#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "LoggingCategories.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_1_clicked()
{
    qDebug(logDebug()) << "Программная ошибка";
}


void MainWindow::on_pushButton_2_clicked()
{
    qInfo(logInf()) << "Информационное сообщение";
}


void MainWindow::on_pushButton_3_clicked()
{
    qWarning(logWarning()) << "Предупреждение!";
}


void MainWindow::on_pushButton_4_clicked()
{
    qCritical(logCritical()) << "Критическая ошибка!";
}

