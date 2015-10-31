#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

class User
{
public:

    QString m_firstname;
    QString m_lastname;
    QString m_username;
    QString m_email;
    QJsonArray m_studygroups;

    User();
    User(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonArray groups);
    void updateUser(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonValueRef email);
    void updateGroups(QJsonArray studygroups);

signals:

public slots:

};

#endif // USER_H
