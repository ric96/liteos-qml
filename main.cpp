#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

std::string getLastLine(std::ifstream& in)
{
    std::string line;
    std::string delimiter = ">=";
    while (in >> std::ws && std::getline(in, line)) // skip empty lines
        ;
    line = line.substr(line.find("temp: ") + 5);
    return line;
}

QString MyObject::setTemp(){
    std::ifstream file("/home/sahaj/liteos-qml/test.txt");
    std::string temp;
    if (file)
        {
            temp = getLastLine(file);
        }
        else
            std::cout << "Unable to open file.\n";
    file.close();
    QString qtemp = QString::fromStdString(temp);
    return qtemp;
};

Q_DECL_EXPORT int main(int argc, char *argv[])
{
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));

        qmlRegisterType<MyObject>("com.myself", 1, 0, "MyObject");

        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        return app.exec();
}
