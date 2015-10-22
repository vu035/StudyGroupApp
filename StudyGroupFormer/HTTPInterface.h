#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <QJsonArray>


QJsonArray getRequest();
void postRequest(QString department, QString class_num);
void postCreateUser(QString email, QString password);


#endif // HTTPINTERFACE_H
