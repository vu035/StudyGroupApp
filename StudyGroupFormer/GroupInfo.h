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

private:
    Ui::GroupInfo *ui;
};

#endif // GROUPINFO_H
