#include "about.h"
#include "ui_about.h"
#include "about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
{
    close();
}

