#include "helper.h"
#include "logement.h"

Helper::Helper(QWidget *parent) :
    QWidget(parent)
{
    type = new QLineEdit;
    prixmax =  new QLineEdit;
    prixmin = new QLineEdit;
    descrip = new QTextEdit;
    btn_annul = new QPushButton("Annuler");
    btn_enreg = new QPushButton("Enregistrer");
    btn_fermer = new QPushButton("Fermer");
    mon_form = new QFormLayout;
    cadreHbtn = new QHBoxLayout;
    cadrev = new QVBoxLayout;
}

Helper::~Helper()
{
    delete type;
    delete prixmax;
    delete prixmin;
    delete descrip;
    delete btn_annul;
    delete btn_enreg;
    delete btn_fermer;
    delete mon_form;
    delete cadreHbtn;
    delete cadrev;
}

void Helper::ihmUpdateLogement(int idLoge, QString t, QWidget *parent)
{
    this->id_loge = idLoge;

    /*
     * Get Datas from database
     */
    QSqlQuery query;
    query.prepare("SELECT * FROM logement WHERE id_loge = :id");
    query.bindValue(":id", idLoge);

    int id;
    int user;
    QString typeLoge;
    QString description;
    double prixMax;
    double prixMin;

    if(query.exec())
    {
        while(query.next())
        {
            id = query.value(0).toInt();
            user = query.value(1).toInt();
            typeLoge = query.value(2).toString();
            description = query.value(4).toString();
            prixMin = query.value(5).toDouble();
            prixMax = query.value(6).toDouble();
        }
    }

    this->id_user = user;

    type->setMaxLength(50);
    // type->setPlaceholderText("donnez le type de logement");
    type->setText(typeLoge);

    prixmin->setMaxLength(9);
    prixmin->setInputMask("999999999");
    //prixmin->setToolTip("saisisez le prix minimum du logement");
    prixmin->setText(QString::number(prixMin));


    prixmax->setMaxLength(9);
    prixmax->setInputMask("999999999");
    // prixmax->setToolTip("saisisez le prix maximum du logement");
    prixmax->setText(QString::number(prixMax));

    descrip->setText(description);

    mon_form = new QFormLayout;
    mon_form->addRow("Type du logement:", type);
    mon_form->addRow("Description", descrip);
    mon_form->addRow("prix minimum", prixmin);
    mon_form->addRow("prix maximum",prixmax);

    cadreHbtn->addWidget(btn_annul);
    cadreHbtn->addWidget(btn_enreg);
    cadreHbtn->addWidget(btn_fermer);

    cadrev = new QVBoxLayout;
    cadrev->addLayout(mon_form);
    cadrev->addLayout(cadreHbtn);

    this->setLayout(cadrev);
    this->setWindowTitle(t);

   // connect(btn_annul,SIGNAL(clicked()),this,SLOT(Renitialiser()));
    connect(btn_enreg,SIGNAL(clicked()),this,SLOT(updateLogement()));
   // connect(btn_fermer,SIGNAL(clicked()),this,SLOT(GestionFermeture()));
}

void Helper::updateLogement()
{
    QString typeLogement = type->text();
    QString description = descrip->toPlainText();
    QString prixMaxStr = prixmax->text();
    QString prixMinStr = prixmin->text();

    if(typeLogement.isEmpty() || description.isEmpty() || prixMaxStr.isEmpty() || prixMinStr.isEmpty())
    {
        QMessageBox::information(this,"Erreur de saisie","Veuillez remplir tous les champs...",QMessageBox::Ok);
    }
    else
    {
        double prixMax = prixMaxStr.toDouble();
        double prixMin = prixMinStr.toDouble();

        if(prixMin > prixMax)
        {
            QMessageBox::critical(this,"Erreur de saisie","Le prix Minimum ne peut être suppérieur au prix maximal",QMessageBox::Ok);
        }
        else
        {
            QSqlQuery query;

            query.prepare("UPDATE logement SET type_logement = :type, description = :desc, prix_min = :prixMin, prix_max = :prixMax WHERE id_loge = :idLoge");
            query.bindValue(":type", typeLogement);
            query.bindValue(":desc", description);
            query.bindValue(":prixMin", prixMin);
            query.bindValue(":prixMax", prixMax);
            query.bindValue(":idLoge", this->id_loge);

            if(query.exec())
            {
                query.next();

                QMessageBox::information(this,"Enregistrement du logement","Enregistement réussie",QMessageBox::Ok);

                Logement *logement = new Logement;
                logement->ihmList(this->id_user);
                logement->setWindowModality(Qt::ApplicationModal);
                logement->setVisible(true);
                this->close();
            }
            else
            {
                qDebug() << query.lastError().text();
            }
        }
    }

}

void Helper::removeLogement(int idLoge, int idUser, QString t, QWidget *parent)
{
    int choix = QMessageBox::question(this,"confirmation de la suppression","voulez_vous vraiment supprimer ce Logement ?", QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM logement WHERE id_loge = :idLoge");
        query.bindValue(":idLoge", idLoge);

        if(query.exec())
        {
            query.next();
            QMessageBox::information(this,"Suppression du logement","Suppression réussie",QMessageBox::Ok);
        }
    }
    this->close();

    Logement *logement = new Logement;
    logement->ihmList(idUser);
    logement->setWindowModality(Qt::ApplicationModal);
    logement->setVisible(true);
}
