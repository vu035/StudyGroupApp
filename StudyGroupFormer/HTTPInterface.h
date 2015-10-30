#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <QJsonArray>


QJsonArray getRequest();
void postCreateGroup(QString department, QString class_num, QString date, QString time);
void postCreateUser(QString email, QString password);
bool postLogin(QString email, QString password);


#endif // HTTPINTERFACE_H
