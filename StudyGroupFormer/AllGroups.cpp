#include "AllGroups.h"
#include "ui_AllGroups.h"

AllGroups::AllGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllGroups)
{
    ui->setupUi(this);
}

AllGroups::~AllGroups()
{
    delete ui;
}

