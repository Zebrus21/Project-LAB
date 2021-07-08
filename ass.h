#ifndef ASS_H
#define ASS_H

#pragma once
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>
#include "LoggingCategories.h"


class Conf
{
  public:
    static int head_len;
    //head
    QString setting;
    QString name_laba;
    QString serial_nom;
    QString date;
    QString version;
    QString language;

    QStringList Mode_name; // название режимов
    QStringList Mode; // конфигурация режимов в виде строки вида <<str> -- <str>>

    Conf(const char *filename):file(filename){ // конструктор
        file.open(QIODevice::ReadOnly);
        if (!file.exists()){
            qWarning(logWarning(),"Конфиг файл не существует");
        }
        else{
            qWarning(logWarning(),"Конфиг файл открыт");
        }
    }
    ~Conf(); // деконструктор

    QStringList read(); // чтение файла в класс (return get_list()) - или return <name error>

   private:
       QFile file;

//       bool get_is_opened(); // можно ли читать? -- <bool>

       QStringList get_lines(); // чтение файла -- <список строк>
       QString set_str(QString); // Замена пустой строки на None
};

int Conf::head_len = 6;

Conf::~Conf(){
    qWarning(logWarning(), "Конфиг файл закрыт");
    file.close();
};


//bool Conf::get_is_opened(){
//    return bool(file.open(QIODevice::ReadOnly));
//}

QStringList Conf::get_lines(){
        // Создаем входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
        QTextStream in(&file);

        in.setCodec(QTextCodec::codecForName("UTF-8"));

        QStringList list;
        // Считываем файл строка за строкой
        while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
            QString line = in.readLine(); // метод readLine() считывает одну строку из потока
            list << line;
        }
        return list;
};

QStringList Conf::read(){
    QString empty = QString();
    QStringList list = get_lines();

//    return list;

    // проверка на пустой файл или недостаточное количество строк
    if (list.empty()){
        qWarning(logWarning(),"ERROR: The file is empty");
//        return QStringList() << "ERROR: The file is empty";
    }
    if (list.length() < head_len){
        qWarning(logWarning(), "ERROR: There are too few lines in the config.file");
//        return QStringList() << "ERROR: There are too few lines in the config.file";
    }

    QStringList::iterator it = list.begin();

    // основные параметры
    setting = set_str(*(++it));
    (++it)++;
    name_laba = set_str(*(++it));
    (++it)++;
    serial_nom = set_str(*(++it));
    (++it)++;
    date = set_str(*(++it));
    (++it)++;
    version = set_str(*(++it));
    (++it)++;
    language = set_str(*(++it));

    // параметры режимов
    while (it++ != list.end()){
        if ((*(it) != empty) && (*it != "-----")){
            QStringList _mode;
            Mode_name << *(++it);
            _mode << *(it++);

            while ((it != list.end()) && (*it != "-----")){
                if ((*it != empty)){
                    _mode << *(++it);
//                    std::cout << (*it).toStdString() << std::endl;
                }
              ++it;
            }
            Mode << _mode.join(" -- ");
        }

}
    return Mode;
};

QString Conf::set_str(QString str){
    if (str == QString()){
        //qWarning("The empty place, where it is not necessary");
        return QString("None");
    }
    return str;
}



class Worker
{
public:
    static int len;
    QString name;
    QString valible;
    QString block;
    QString image;
    QString file_exe;

    Worker(QString);

};

Worker::Worker(QString list){
    QStringList param = list.split(" -- ");

    if (param.length() != len)
        qWarning(logWarning(),"ERROR: Length MODE");

    QStringList::iterator it = param.begin();

    // основные параметры
    name = *(it++);
    valible = *(it++);
    block = *(it++);
    image = *(it++);
    file_exe = *(it++);
}

int Worker::len = 5;

#endif // ASS_H
