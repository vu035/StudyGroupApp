#include "User.h"


User::User(){
    m_firstname = "null";
    m_lastname = "null";
    m_username = "null";
    isAdmin = false;
}

User::User(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonArray groups){
    m_firstname = first.toString();
    m_lastname = last.toString();
    m_username = username.toString();
    m_studygroups = groups;

}

void User::updateUser(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonValueRef email, int id){
    this->m_firstname = first.toString();
    this->m_lastname = last.toString();
    this->m_username = username.toString();
    this->m_email = email.toString();
    this->m_id = id;

}

void User::setAdmin(bool isadmin){
    isAdmin = admin;
}

void User::updateGroups(QJsonArray studygroups){
    this->m_studygroups = studygroups;
}

