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
#include <QString>


QJsonArray getAllGroups();
void getUserGroups(User current_user);
void postCreateGroup(QString department, QString class_num, QString date, QString time, QString description);
void postCreateUser(QString email, QString password, QString firstname, QString lastname, QString username);
void postJoinGroup(QString group_id, int user_id);
bool postLogin(QString email, QString password);
QJsonObject getStudyGroup(QString group_id);
User getAppUser();

#endif // HTTPINTERFACE_H
