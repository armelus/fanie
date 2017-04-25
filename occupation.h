#ifndef OCCUPATION_H
#define OCCUPATION_H
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QMenuBar>
#include <QCloseEvent>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QGridLayout>

class Occupation: public QWidget
{
    Q_OBJECT

protected:
    QLineEdit *LoyerBase;
    QDateEdit *DateEntree;
    QDateEdit *DateSortie;
    QLineEdit *arriere;
    QTextEdit *Description;
    QPushButton *btn_renitial;
    QPushButton *btn_enreg;
    QPushButton *btn_fermer;
    QHBoxLayout *cadreHbtn;
    QVBoxLayout *cadrev;
    QFormLayout *mon_form;



public:
    Occupation(QString t="Créer une occupation", QWidget *parent=NULL);


public slots:

    void Renitialiser();
    void EnvoyerForm();
};

#endif // OCCUPATION_H
