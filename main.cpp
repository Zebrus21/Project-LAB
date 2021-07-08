#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include "ass.h"
#include <QDir>
#include <QProcess>
#include <QDebug>
#include "LoggingCategories.h"

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

// path of the file
const char *PATH = "D:/test.txt";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL, "Russian");
    // Устанавливаем файл логирования,
    // путь для файла
    m_logFile.reset(new QFile("D:/Programming/Qt/Log/logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();


    Conf *config = new Conf(PATH);

    // чтение конфиг файла
    qInfo() << config->read();

//     теперь можем посмотреть параметры системы

    qInfo(logInfo()) << "общий список настроек:    " << config->setting;
    qInfo(logInfo()) << "language:                 " << config->language;
    qInfo(logInfo()) << "название лабы:            " << config->name_laba;
    qInfo(logInfo()) << "серийный номер:           " << config->serial_nom;
    qInfo(logInfo()) << "версия:                   " << config->version;


//    // создание класса Worker (класс режима)
    Worker *mode_1 = new Worker((config->Mode)[0]);
//    Worker *mode_1 = new Worker((config->Mode)[1]);

//    // теперь можем смотреть парамерты выбранного режима
    qInfo(logInfo()) << "режим:                    " << mode_1->name;
    qInfo(logInfo()) << "доступ:                   " << mode_1->valible;
    qInfo(logInfo()) << "конфигурация блока:       "<< mode_1->block;
    qInfo(logInfo()) << "схема:                    "<< mode_1->image;
    qInfo(logInfo()) << "расположение файла *.exe: "<< mode_1->file_exe;

//     удаление
    delete mode_1;

    delete  config;

    return a.exec();

}


// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": " << msg << "\n";
    out.flush();    // Очищаем буферизированные данные
}
