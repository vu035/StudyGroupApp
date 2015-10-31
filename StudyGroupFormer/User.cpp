#include "User.h"


User::User(){
    m_firstname = "null";
    m_lastname = "null";
    m_username = "null";
}

User::User(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonArray groups){
    m_firstname = first.toString();
    m_lastname = last.toString();
    m_username = username.toString();
    m_studygroups = groups;

}

void User::updateUser(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username, QJsonValueRef email){
    this->m_firstname = first.toString();
    this->m_lastname = last.toString();
    this->m_username = username.toString();
    this->m_email = email.toString();

}

void User::updateGroups(QJsonArray studygroups){
    this->m_studygroups = studygroups;
}

