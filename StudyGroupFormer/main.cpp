#include "LoginWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>


void sendRequest(){

    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("http://localhost:3000/studygroups") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success


        QString strReply = (QString)reply->readAll();

                //parse json
                qDebug() << "Response:" << strReply;
                QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

                QJsonArray json_array = jsonResponse.array();

                    foreach (const QJsonValue &value, json_array) {
                        QJsonObject json_obj = value.toObject();
                        qDebug() << json_obj["department"].toString();
                        qDebug() << json_obj["class_number"].toInt();
                    }
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow login;

    login.show();
    sendRequest();
    return a.exec();
}
