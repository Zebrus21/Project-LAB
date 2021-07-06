#include "mainwindow.h"
#include <iostream>
#include <string>
#include <fstream>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include <QtCore/QCoreApplication>
#include <QUrl>
#include "settings.h"

using namespace std;

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

QStringList strList;
QFile file("config.txt");

// Путь файла конфигуратора
//string path_config = "config.txt";
void doSome();


// Объявление функции чтения конфига
void read_config(QFile file);

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



    /*Считываем исходный файл в контейнер*/
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        while(!file.atEnd())
        {
        strList << file.readLine();
        }
        file.close();
    }
    /*Добавляем строку и сохраняем содержимое контейнера в тот же файл*/
    if ((file.exists())&&(file.open(QIODevice::WriteOnly)))
    {
        strList.insert(2,"Inserted string\n");
        QTextStream stream(&file);
        foreach(QString s, strList)
        {
            stream<<s;
        }
        file.close();
    }



    //данные параметры используются QSettings для определения куда сохранять конфигурацию
       QCoreApplication::setOrganizationName("unixod");
       QCoreApplication::setApplicationName("app");

       //по желанию можем установить дефолтную конфигурацию:
       QFile cfgDefaults(":/config/default.cfg");  // я обычно дефолтовые настройки помещаю в ресурсы
       cfgDefaults.open(QIODevice::ReadOnly);
       Settings::setDefaults(cfgDefaults.readAll());
       //...
       doSome();
       //...


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


//void read_config(QFile file)
//{

    /*
    ifstream fin;
    fin.open(path_config);

    if (!fin.is_open())
    {
        cout << "Ошибка открытия файла config.txt!" << endl;
    }
    else
    {
        cout << "Файл config.txt открыт!" << endl;
        string str;
        while (!fin.eof())
        {
            str = "";
            getline(fin, str);
            cout << str << endl;
        }
    }
    fin.close();
    */

//}

void doSome(){
    //чтение из секции General
    QString login = Settings::get(Settings::User).toString();    // login == "unixod"

    QUrl proxyUrl = Settings::get(Settings::URI, Settings::Proxy).toUrl();    // http://proxy_uri

    QString generalUrl = Settings::get(Settings::URI).toString();    // пусто
    if(generalUrl.isEmpty())
        Settings::set(Settings::URI) = "http://some_uri";
}
