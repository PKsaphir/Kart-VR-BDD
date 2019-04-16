#include "ui_login.h"
#include "connexion.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}


void login::on_Validation_2_clicked()
{
    QString login = ui->lineEdit_Login_2->text();
    QString MDP = ui->lineEdit_MDP_2->text();

    if (login == "snir" && MDP == "snir")
    {
        QMessageBox::information(this, "connexion ", " login et le mot de passe est correct");

    }else {
        QMessageBox::warning(this, "connexion ", " login et le mot de passe n'est pas correct");
        class login login;
        login.setModal(false);
        login.exec();
    }

}



login::~login()
{
    delete ui;
}
