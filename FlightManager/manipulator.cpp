#include "exceptions.h"
#include "manipulator.h"
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

Manipulator::Manipulator() {
    #if (defined (_WIN32) || defined (_WIN64))
        pathToFile = "../FlightManager/graph.json";
    #elif (defined (Q_OS_MAC) || defined (Q_OS_OSX) || defined (Q_OS_MACX))
        pathToFile = "../../../../FlightManager/graph.json";
    #endif
}

QJsonObject Manipulator::read() {

    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly)) {
        throw FileException(pathToFile.toStdString());
    }
    QByteArray rawData = QByteArray::fromBase64(file.readAll());
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    return doc.object();
}

void Manipulator::write(QJsonObject json) {
    QJsonDocument json_doc(json);
    QString json_string = json_doc.toJson();

    QFile save_file(pathToFile);
    if (save_file.exists())
        save_file.remove();
    if (!save_file.open(QIODevice::WriteOnly)) {
        throw FileException(pathToFile.toStdString());
    }

    save_file.write(json_string.toLocal8Bit().toBase64());
    save_file.close();
}
