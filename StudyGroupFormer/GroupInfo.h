#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QDialog>
#include <QTime>
#include "HTTPInterface.h"
#include "AppWindow.h"
#include <QScrollBar>

namespace Ui {
class GroupInfo;
}

class HTTPInterface;

class GroupInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GroupInfo(QWidget *parent = 0);
    void displayGroupInfo();
    void updateChatWindow(QString group_id);
    void chatPoller();
    ~GroupInfo();
    
public slots:
    void setLabelText(QString gID);

private slots:
    void on_joinButton_clicked();

    void on_btnSendMessage_clicked();

    void on_chatRefreshButton_clicked();
    void on_leGroupMessage_returnPressed();
private:
    Ui::GroupInfo *ui;
    HTTPInterface *web_interface;
};

#endif // GROUPINFO_H
