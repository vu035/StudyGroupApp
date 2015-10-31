#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H
#include "User.h"
#include "AppWindow.h"
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



QJsonArray getAllGroups();
QJsonObject getUserGroups(User current_user);
void postCreateGroup(QString department, QString class_num, QString date, QString time);
void postCreateUser(QString email, QString password, QString firstname, QString lastname, QString username);
bool postLogin(QString email, QString password);
User getAppUser();

#endif // HTTPINTERFACE_H
