#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    ui->ButtonBox->button(QDialogButtonBox::Ok)->setText("Connect");
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::accept()
{
    QString url = ui->ServerEntry->text();
    QString name = ui->NameEntry->text();

    emit submitted(url, name);
    QDialog::accept();
}

void ConnectDialog::reject()
{
    QDialog::reject();
}
