#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования,
    // путь для файла
    m_logFile.reset(new QFile("D:/Programming/Qt/Logger/Log/logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();
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
    case QtInfoMsg:     out << "INFO "; break;
    case QtDebugMsg:    out << "DEBG "; break;
    case QtWarningMsg:  out << "WARN "; break;
    case QtCriticalMsg: out << "CRIT "; break;
    case QtFatalMsg:    out << "FATL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": " << msg << "\n";
    out.flush();    // Очищаем буферизированные данные
}
