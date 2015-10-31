#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "AppWindow.h"



User AppUser;

//pass QjsonArray from get requests
void groupstoString(QJsonArray jsonResponse){

    foreach (const QJsonValue &value, jsonResponse) {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
    }
}




//get all studygroups
QJsonArray getAllGroups(){
    QJsonArray json_array;
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/studygroups") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString strReply = (QString)reply->readAll();

        //parse json
        //qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        json_array = jsonResponse.array();
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();


        }
        delete reply;
        return json_array;

    }
    else{
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
    return json_array;
}




//post a new study group to DB
void postCreateGroup(QString department, QString class_number, QString date, QString time){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/studygroups"));
    QNetworkRequest request(myURL);
    QNetworkAccessManager mgr;

    QByteArray postData;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery qu;
    qu.addQueryItem("studygroup[department]",department);
    qu.addQueryItem("studygroup[class_number]",class_number);
    qu.addQueryItem("studygroup[date]",date);
    qu.addQueryItem("studygroup[time]",time);
    postData.append(qu.toString());
    QNetworkReply *reply = mgr.post(request, postData);


    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        //Success
        QString strReply = (QString)reply->readAll();
        qDebug() << "Success" << strReply;
        delete reply;
    }
    else {
        //Failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}




//post a new user to the db
void postCreateUser(QString email, QString password, QString firstname, QString lastname, QString username){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/users"));
    QNetworkRequest request(myURL);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkAccessManager mgr;

    QByteArray postData;
    QUrlQuery qu;
    qu.addQueryItem("user[email]",email);
    qu.addQueryItem("user[password]",password);
    qu.addQueryItem("user[Firstname]",firstname);
    qu.addQueryItem("user[Lastname]",lastname);
    qu.addQueryItem("user[Username]",username);


    postData.append(qu.toString());
    QNetworkReply *reply = mgr.post(request, postData);


    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        //success

        QString strReply = (QString)reply->readAll();
        qDebug() << "Success" << strReply;
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}





bool postLogin(QString email, QString password){

    QUrl myURL(QString("http://localhost:3000/login"));
    QNetworkRequest request(myURL);
    QNetworkAccessManager mgr;

    QByteArray postData;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery qu;
    qu.addQueryItem("user[email]",email);
    qu.addQueryItem("user[password]",password);
    postData.append(qu.toString());
    QNetworkReply *reply = mgr.post(request, postData);


    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //Login success
        if(strReply != "false"){
            qDebug() << "Login Success";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject json_obj = jsonResponse.object();
             qDebug() << json_obj;


             //define current user object here
             AppUser.updateUser(json_obj["Firstname"], json_obj["Lastname"], json_obj["Username"]);
            qDebug() << AppUser.m_firstname;

             delete reply;
             return true;
        }
        else {
            //Login Failed
            qDebug() << "Login Failed";
            delete reply;
            return false;
        }
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return false;
    }
}


User getAppUser(){
    return AppUser;
}
