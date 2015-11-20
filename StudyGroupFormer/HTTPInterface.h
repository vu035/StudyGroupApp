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


/*
*/
class HTTPInterface
{
private:
    static bool instanceFlag;
    static HTTPInterface *singleinstance;
    User AppUser;
    QNetworkAccessManager mgr;

    HTTPInterface()
    {
        //private constructor
    }
public:
    static HTTPInterface* getInstance(); //returns mem address of single instance

    QJsonArray getAllGroups();
    void getUserGroups(User current_user);
    void postCreateGroup(QString department, QString class_num, QString date, QString time, QString description);
    void postCreateUser(QString email, QString password, QString firstname, QString lastname, QString username);
    void postJoinGroup(QString group_id, int user_id);
    void postLeaveGroup(QString group_id, int user_id);
    bool postLogin(QString email, QString password);
    void postCreateComment(QString group_id, QString username, QString comment_text);
    QJsonArray getGroupComments(QString group_id);
    QJsonObject getStudyGroup(QString group_id);
    User getAppUser();

    ~HTTPInterface()
    {
        instanceFlag = false;
    }
    void groupstoString(QJsonArray jsonResponse);
};

#endif // HTTPINTERFACE_H
