#include "User.h"


User::User(){
    m_firstname = "null";
    m_lastname = "null";
    m_username = "null";
}

User::User(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username){
    m_firstname = first.toString();
    m_lastname = last.toString();
    m_username = username.toString();

}

void User::updateUser(QJsonValueRef first, QJsonValueRef last, QJsonValueRef username){
    this->m_firstname = first.toString();
    this->m_lastname = last.toString();
    this->m_username = username.toString();

}



