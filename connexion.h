#ifndef CONNEXION_H
#define CONNEXION_H

#include "login.h"

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QApplication>
#include <QtGui>
#include <QtSql/QtSql>
#include <QAbstractTableModel>
#include <QApplication>

namespace Ui {
class connexion;
}

class connexion : public QDialog
{
    Q_OBJECT

public:
    explicit connexion(QWidget *parent = nullptr);
    ~connexion();

   QSqlDatabase Data_BDD = QSqlDatabase::addDatabase("QSQLITE", "Connection");





private slots:
    void on_Pbu_Recherche_clicked();


    void on_Validation_clicked();

private:
    Ui::connexion *ui;

};

#endif // CONNEXION_H
