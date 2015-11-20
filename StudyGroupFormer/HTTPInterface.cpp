#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "AppWindow.h"

bool HTTPInterface::instanceFlag = false;
HTTPInterface* HTTPInterface::singleinstance = NULL;

HTTPInterface* HTTPInterface::getInstance()
{
    if(! instanceFlag)
    {
        singleinstance = new HTTPInterface();
        instanceFlag = true;
        return singleinstance;
    }
    else
    {
        return singleinstance;
    }
}


//pass QjsonArray from get requests
void HTTPInterface::groupstoString(QJsonArray jsonResponse){

    foreach (const QJsonValue &value, jsonResponse) {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
    }
}

//get all studygroups
QJsonArray HTTPInterface::getAllGroups(){
    QJsonArray json_array;
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"

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


QJsonArray HTTPInterface::getAllUsers(){
    QJsonArray json_array;
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/users") ) );
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

//get all groups for a particular user
void HTTPInterface::getUserGroups(User current_user){
   QJsonArray json_array;
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"

    QByteArray headerData;
    QUrlQuery qu;
    qu.addQueryItem("user[email]",current_user.m_email); //pass in the user email
    headerData.append(qu.toString());



    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/mygroups") ) );
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = mgr.post(req, headerData);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString strReply = (QString)reply->readAll();

        //parse json

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
         json_array = jsonResponse.array();



        //update appUser
        AppUser.updateGroups(json_array);
        delete reply;


    }
    else{
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }

}



//post a new study group to DB
void HTTPInterface::postCreateGroup(QString department, QString class_number, QString date, QString time, QString description){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/studygroups"));
    QNetworkRequest request(myURL);


    QByteArray postData;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery qu;
    qu.addQueryItem("studygroup[department]",department);
    qu.addQueryItem("studygroup[class_number]",class_number);
    qu.addQueryItem("studygroup[date]",date);
    qu.addQueryItem("studygroup[time]",time);
    qu.addQueryItem("studygroup[description]",description);
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

void HTTPInterface::postJoinGroup(QString group_id, int user_id){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/studygroups_users"));
    QNetworkRequest request(myURL);


    QByteArray postData;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery qu;
    qu.addQueryItem("studygroups_user[studygroup_id]",group_id);
    qu.addQueryItem("studygroups_user[user_id]",QString::number(user_id));

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
void HTTPInterface::postCreateUser(QString email, QString password, QString firstname, QString lastname, QString username){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/users"));
    QNetworkRequest request(myURL);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


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





bool HTTPInterface::postLogin(QString email, QString password){

    QUrl myURL(QString("https://studygroupformer.herokuapp.com/login"));
    QNetworkRequest request(myURL);


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
             //qDebug() << json_obj;
            int userID = json_obj["id"].toInt();

             //define current user object here
             AppUser.updateUser(json_obj["Firstname"], json_obj["Lastname"], json_obj["Username"], json_obj["email"], userID);

             //qDebug() << AppUser.m_email <<  AppUser.m_id;

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

//get group info
QJsonObject HTTPInterface::getStudyGroup(QString group_id){
    QJsonObject json_obj ;
    QString url = "https://studygroupformer.herokuapp.com/studygroups/" + group_id;
    QUrl myURL(url);
    QNetworkRequest request(myURL);




    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = mgr.get(request);


    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //success
            qDebug() << " Success";
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            json_obj = jsonResponse.object();
             qDebug() << json_obj;




             delete reply;
             return json_obj;

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return json_obj;

    }
}


void HTTPInterface::postLeaveGroup(QString group_id, int user_id){
    //QJsonArray json_array;
     // create custom temporary event loop on stack
     QEventLoop eventLoop;

     // "quit()" the event-loop, when the network request "finished()"

     QByteArray headerData;
     QUrlQuery qu;
     qu.addQueryItem("studygroups_user[studygroup_id]",group_id); //pass in the group id
     qu.addQueryItem("studygroups_user[user_id]",QString::number(user_id)); //pass in the user id
     headerData.append(qu.toString());



     QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

     // the HTTP request
     QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/seekdestroy") ) );
     req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
     QNetworkReply *reply = mgr.post(req, headerData);
     eventLoop.exec(); // blocks stack until "finished()" has been called

     if (reply->error() == QNetworkReply::NoError) {
         //success
         QString strReply = (QString)reply->readAll();
           qDebug() << strReply;





         delete reply;


     }
     else{
         //failure
         qDebug() << "Failure" <<reply->errorString();
         delete reply;
     }

}

//post a comment to the db for a specific group
void HTTPInterface::postCreateComment(QString group_id, QString username, QString comment_text){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"

    QByteArray headerData;
    QUrlQuery qu;
    qu.addQueryItem("group_comment[studygroup_id]",group_id); //pass in the group id
    qu.addQueryItem("group_comment[comment]",comment_text); //pass in the comment text
    qu.addQueryItem("group_comment[user]",username); //pass in the user
    headerData.append(qu.toString());



    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/group_comments") ) );
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = mgr.post(req, headerData);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QString strReply = (QString)reply->readAll();
          qDebug() << strReply;


        delete reply;


    }
    else{
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}

QJsonArray HTTPInterface::getGroupComments(QString group_id){
    QJsonArray json_array;
     // create custom temporary event loop on stack
     QEventLoop eventLoop;

     // "quit()" the event-loop, when the network request "finished()"

     QByteArray headerData;
     QUrlQuery qu;
     qu.addQueryItem("group_comment[studygroup_id]",group_id); //pass in the user email
     headerData.append(qu.toString());



     QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

     // the HTTP request
     QNetworkRequest req( QUrl( QString("https://studygroupformer.herokuapp.com/groupchats") ) );
     req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
     QNetworkReply *reply = mgr.post(req, headerData);
     eventLoop.exec(); // blocks stack until "finished()" has been called

     if (reply->error() == QNetworkReply::NoError) {
         //success
         QString strReply = (QString)reply->readAll();

         //parse json

         QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
          json_array = jsonResponse.array();
           qDebug() << "hello" << json_array;



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


void HTTPInterface::deleteGroup(QString group_id){
    QString url = "https://studygroupformer.herokuapp.com/studygroups/" + group_id;
    QUrl myURL(url);
    QNetworkRequest request(myURL);




    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = mgr.deleteResource(request);


    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {



        //success
            qDebug() << " Success";

             delete reply;


    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;

    }
}

void HTTPInterface::deleteUser(QString user_id){

        QString url = "https://studygroupformer.herokuapp.com/users/" + user_id;
        QUrl myURL(url);
        QNetworkRequest request(myURL);




        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        QNetworkReply *reply = mgr.deleteResource(request);


        QEventLoop eventLoop;
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        eventLoop.exec();

        if (reply->error() == QNetworkReply::NoError) {



            //success
                qDebug() << " Success";

                 delete reply;


        }
        else {
            //failure
            qDebug() << "Failure" <<reply->errorString();
            delete reply;

        }
}



User HTTPInterface::getAppUser(){
    return AppUser;
}
