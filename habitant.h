#ifndef HABITANT_H
#define HABITANT_H

#include <QWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
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

namespace Ui {
class Habitant;
}

class Habitant : public QWidget
{
    Q_OBJECT

public:
    explicit Habitant(int idUser, QWidget *parent = 0);
    ~Habitant();
    void ihmEnregistrerHabitant(QWidget *parent = 0);
    void initialiserListe();
    void ihmUpdateHabitant(int idHabit, QWidget *parent = 0);


private slots:
    void on_ajouter_clicked();
    void reiinitialiser_NewForm();
    void save();
    void update();
    void remove();

    void on_afficher_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();

private:
    Ui::Habitant *ui;
    QWidget *fenetre;
    QLineEdit *nomLE;
    QLineEdit *prenomLE;
    QLineEdit *tel1LE;
    QLineEdit *tel2LE;
    QLineEdit *emailLE;
    QLineEdit *professionLE;
    QDateTimeEdit *birthdayDTE;
    int id_user;
    int id_habit;
    QSqlTableModel *model;

};

#endif // HABITANT_H
