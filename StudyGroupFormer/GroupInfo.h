#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QDialog>

namespace Ui {
class GroupInfo;
}

class GroupInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GroupInfo(QWidget *parent = 0);
    void displayGroupInfo();
    ~GroupInfo();
    
public slots:
    void setLabelText(QString gID);

private slots:
    void on_joinButton_clicked();

    void on_commentButton_clicked();

private:
    Ui::GroupInfo *ui;
};

#endif // GROUPINFO_H
