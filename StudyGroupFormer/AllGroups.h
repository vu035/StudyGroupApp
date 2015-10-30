#ifndef ALLGROUPS_H
#define ALLGROUPS_H

#include <QWidget>

namespace Ui {
class AllGroups;
}

class AllGroups : public QWidget
{
    Q_OBJECT

public:
    explicit AllGroups(QWidget *parent = 0);
    ~AllGroups();

private:
    Ui::AllGroups *ui;
};

#endif // ALLGROUPS_H
