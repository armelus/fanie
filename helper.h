#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class Helper : public QWidget
{
    Q_OBJECT
public:
    explicit Helper(QWidget *parent = 0);
    ~Helper();
    void ihmUpdateLogement(int idLoge, QString t="Modifier un Logement", QWidget *parent = NULL);
    void removeLogement(int idLoge, int idUser, QString t="Suppression d'un Logement", QWidget *parent = NULL);

protected:
    int id_user;
    int id_loge;
    QLineEdit *type;
    QLineEdit *prixmin;
    QLineEdit *prixmax;
    QTextEdit *descrip;
    QPushButton *btn_annul;
    QPushButton *btn_enreg;
    QPushButton *btn_fermer;
    QFormLayout *mon_form;
    QHBoxLayout *cadreHbtn;
    QVBoxLayout *cadrev;

signals:

public slots:
    void updateLogement();
};

#endif // HELPER_H
