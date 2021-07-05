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
    qDebug(logDebug()) << "Debug Button";
}


void MainWindow::on_pushButton_2_clicked()
{
    qInfo(logInfo()) << "Info Button";
}


void MainWindow::on_pushButton_3_clicked()
{
    qWarning(logWarning()) << "Warning Button";
}


void MainWindow::on_pushButton_4_clicked()
{
    qCritical(logCritical()) << "Critical Button";
}

