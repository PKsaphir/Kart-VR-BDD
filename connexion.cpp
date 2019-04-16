#include "connexion.h"
#include "ui_interface.h"
#include "login.h"



connexion::connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexion)
{

    login login;
    login.setModal(false);
    login.exec();

    ui->setupUi(this);


    Data_BDD.setHostName("127.0.0.1");
    Data_BDD.setUserName("root");
    Data_BDD.setPassword("");

    Data_BDD.setDatabaseName("C:/Users/Quentin/Desktop/projet_karte/codes/Interface_BDD/connexionBDD/connexionBDD/BDD/Data_BDD.db");

    if (!Data_BDD.open()) {
            qDebug("Erreur d'ouverture de la base de donnée !");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
    }else{
        QMessageBox::information( this, "connexion BDD","connexion établie ", QMessageBox::Ok, 0 );
    }

        ui->Chx_Table->addItem("");
        ui->Chx_Table->addItem("Data");
        ui->Chx_Table->addItem("Joueurs");

        ui->Chx_Colonne->addItem("");
        ui->Chx_Colonne->addItem("Nom");
        ui->Chx_Colonne->addItem("Type");
        ui->Chx_Colonne->addItem("Valeurs");
        ui->Chx_Colonne->addItem("Nom_Joueurs");
        ui->Chx_Colonne->addItem("Temps");


        ui->Chx_Variable->addItem("");
        ui->Chx_Variable->addItem("getCourantChargeBatt");
        ui->Chx_Variable->addItem("getPuissanceTotaleBatt");



        ui->Num_Ligne->addItem("");
       for (int i = 1 ; i < 101 ; i++)
        {
            ui->Num_Ligne->addItem(QString::number(i));
        }

}


void connexion::on_Pbu_Recherche_clicked()
{



    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
    "C:/Users/Quentin/Desktop/projet_karte/codes/Interface_BDD/connexionBDD/connexionBDD/BDD",("BDD (*.db)"));


    if ( Data_BDD.open() )
       {
        // Insert table Data. CREATE TABLE Data (Num_Ligne INTEGER PRIMARY KEY,Nom longchar(40), Type longchar(10), Valeurs float(10));
        QSqlQuery Data(Data_BDD);
        Data.prepare("CREATE TABLE IF NOT EXISTS Data (Num_Ligne INTEGER PRIMARY KEY,Nom longchar(40), Type longchar(10), Valeurs float(10))"); //création de la base de donnée
        if (!Data.exec()) {
            qDebug("Erreur lors de la crétion de la base de donnée.");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
        }

        // Insert Data .
        Data.prepare("INSERT INTO Data VALUES (null, 'getCourantChargeBatt', 'float', '1.5')");
        if (!Data.exec()) {
            qDebug("Erreur lors de l'insertion.");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
        }

        Data.prepare("INSERT INTO Data VALUES (null, 'getPuissanceTotaleBatt', 'float', '50')");
        if (!Data.exec()) {
            qDebug("Erreur lors de l'insertion.");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
        }

        // Insert table Joueurs. CREATE TABLE Joueurs (Num_Ligne INTEGER PRIMARY KEY, Nom_Joueurs longchar(20), Temps TIME);
        QSqlQuery Joueurs(Data_BDD);
        Joueurs.prepare("CREATE TABLE IF NOT EXISTS Joueurs (Num_Ligne INTEGER PRIMARY KEY, Nom_Joueurs longchar(20), Temps TIME)"); //création de la base de donnée
        if (!Joueurs.exec()) {
            qDebug("Error occurred creating table.");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
        }

        // Insert Joueurs .
        Joueurs.prepare("INSERT INTO Joueurs VALUES (null, 'quentin', '125')");
        if (!Joueurs.exec()) {
            qDebug("Error occurred inserting.");
            qDebug("%s.", qPrintable(Data_BDD.lastError().text()));
        }


            QSqlQueryModel* model1 = new QSqlQueryModel();
            QSqlQuery *commande1 = new QSqlQuery(Data_BDD);
            commande1->prepare("Select * FROM Data");
            commande1->exec();
            model1->setQuery(*commande1);
            ui->tableView1_BDD->setModel(model1);

            QSqlQueryModel* model2 = new QSqlQueryModel();
            QSqlQuery *commande2 = new QSqlQuery(Data_BDD);
            commande2->prepare("Select * FROM Joueurs");
            commande2->exec();
            model2->setQuery(*commande2);
            ui->tableView2_BDD->setModel(model2);


       }
          Data_BDD.close();


}


void connexion::on_Validation_clicked()
{
                    //select
    QString command = "Select ";
    if ( Data_BDD.open() )
       {
        if(ui->Chx_Colonne->currentText()!="")
        {
            //select (Nom de la Colonne)
            command += ui->Chx_Colonne->currentText() + " ";
            qDebug() <<  command;
        }else
        {
            //select *
            command += "* ";
            qDebug() <<  command;
        }

        if(ui->Chx_Table->currentText()!="")
        {
            /* select (Nom de la Colonne) from (Nom de la Table)
             * ou
             * select * from (Nom de la Table) */
            command += "FROM " + ui->Chx_Table->currentText() + " ";
            qDebug() <<  command;
        }

        if(ui->Chx_Variable->currentText()!="")
        {
            //select (Nom de la Colonne) from (Nom de la Table) Where (Nom de la Colonne) = '(Nom de la Variable)'
            command += "WHERE " + ui->Chx_Colonne->currentText() + " = '" + ui->Chx_Variable->currentText() + "' ";
            qDebug() <<  command;
        }

        if(ui->Num_Ligne->currentText()!="" && ui->Chx_Variable->currentText()!="")
        {
            //select * from (Nom de la Table) Where (Nom de la Colonne) = '(Nom de la Variable)' AND Num_Ligne = (Num_Ligne)
            command +=  "AND Num_Ligne = '" + ui->Num_Ligne->currentText() + "' ";
            qDebug() <<  command;
        }

        if(ui->Num_Ligne->currentText()!="" && ui->Chx_Variable->currentText()=="")
        {
            //select (Nom de la Colonne) from (Nom de la Table) Where Num_Ligne = '(Num_Ligne)'
            command +=  "WHERE Num_Ligne = '" + ui->Num_Ligne->currentText() + "' ";
            qDebug() <<  command;
        }



        if((ui->Chx_Table->currentText()=="Data" && ui->Chx_Colonne->currentText()=="Nom_Joueurs") ||
          (ui->Chx_Table->currentText()=="Data" && ui->Chx_Colonne->currentText()=="Temps") ||
          (ui->Chx_Table->currentText()=="Joueurs" && ui->Chx_Colonne->currentText()=="Type") ||
          (ui->Chx_Table->currentText()=="Joueurs" && ui->Chx_Colonne->currentText()=="Nom") ||
          (ui->Chx_Table->currentText()=="Joueurs" && ui->Chx_Colonne->currentText()=="Valeurs"))
            {
                QMessageBox::critical(this, "Erreur", "Choix de la table incorrect");
            }


             QSqlQueryModel* model = new QSqlQueryModel();
             QSqlQuery *commande = new QSqlQuery(Data_BDD);
             commande->prepare(command);
             commande->exec();
             model->setQuery(*commande);
             ui->tableView1_BDD->setModel(model);

             QSqlQueryModel* model2 = new QSqlQueryModel();
             QSqlQuery *commande2 = new QSqlQuery(Data_BDD);
             commande2->prepare(command);
             commande2->exec();
             model2->setQuery(*commande);
             ui->tableView2_BDD->setModel(model2);


             if(ui->Chx_Table->currentText()=="Data")
             {
                 QSqlQueryModel* model = new QSqlQueryModel();
                 ui->tableView2_BDD->setModel(model);
             }else {
                 QSqlQueryModel* model = new QSqlQueryModel();
                 ui->tableView1_BDD->setModel(model);
             }



       }

}



connexion::~connexion()
{
    delete ui;
}



