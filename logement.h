#ifndef LOGEMENT_H
#define LOGEMENT_H
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QString>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QCheckBox>
#include <QDialog>


class Logement:public QWidget
{
    Q_OBJECT

protected:
    int id_user;
    int id_loge;
    QLineEdit *type;
    QDateEdit *date;
    QTextEdit *descrip;
    QLineEdit *prixmin;
    QLineEdit *prixmax;
    QCheckBox *etatLoge;
    QPushButton *btn_annul;
    QPushButton *btn_enreg;
    QPushButton *btn_fermer;
    QHBoxLayout *cadreHbtn;
    QVBoxLayout *cadrev;
    QFormLayout *mon_form;
    QTableView *vue;
    QSqlQueryModel *model;

public:
    Logement(QString t="Créer un Logement", QWidget *parent = NULL);
    void ihmInsert(int idUser, QString t="Créer un Logement", QWidget *parent = NULL);
    void ihmList(int idUser, QString t="Afficher les logements", QWidget *parent = NULL);
    //void closeEvent(QCloseEvent *evt);


public slots:
   void Renitialiser();
  // void EnregForm();
   void GestionFermeture();
   void EnregistrerLogement();
   void on_modifier_clicked();
   void on_supprimer_clicked();
};

#endif // LOGEMENT_H


