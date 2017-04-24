#include "logement.h"
#include "accueil.h"
#include "helper.h"

Logement::Logement(QString t, QWidget *parent)
{
    type = new QLineEdit;
    date = new QDateEdit;
    descrip = new QTextEdit;
    prixmin = new QLineEdit;
    prixmax = new QLineEdit;
    btn_annul = new QPushButton("Annuler");
    btn_enreg = new QPushButton("Enregistrer");
    btn_fermer = new QPushButton("Fermer") ;
    mon_form = new QFormLayout;
    cadreHbtn = new QHBoxLayout;
    cadrev = new QVBoxLayout;

}

void Logement::Renitialiser()
{
    int rep=QMessageBox::question(this,"Réinitialisation du formulaire","voulez-vous vraiment effacer les informations saisies?",

                                  QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::Cancel);

    if(rep==QMessageBox::Yes)
    {

        type->clear();
        date->clear();
        descrip->clear();
        prixmin->clear();
        prixmax->clear();

    }
}


void Logement::EnregistrerLogement()
{
    //   qDebug() << this->id_user;
    QString type1= type->text();
    QString descrip1= descrip->toPlainText();
    QString prixma1=prixmax->text();
    QString date1=date->date().toString("dd-MM-yyyy");
    QString prixmin1=prixmin->text();

    if(type1.isEmpty()|| descrip1.isEmpty()|| prixma1.isEmpty()|| date1.isEmpty()|| prixmin1.isEmpty())
        QMessageBox::information(this,"Erreur de saisie","Veuillez remplir tous les champs...",QMessageBox::Ok);
    else
    {
        double prixMin = prixmin1.toDouble();
        double prixMax = prixma1.toDouble();

        if(prixMin > prixMax)
        {
            QMessageBox::critical(this,"Erreur de saisie","Le prix Minimum ne peut être suppérieur au prix maximal",QMessageBox::Ok);
        }
        else
        {
            QSqlQuery ins, rek;

            rek.prepare("insert into logement (id_user, type_logement, date_creation,description , prix_min, prix_max, etat) VALUES ( :id, :type, :date,:descrip,:prixmin,:prixmax, :etat)" );
            rek.bindValue(":id", this->id_user);
            rek.bindValue(":type",type1);
            rek.bindValue(":date",date1);
            rek.bindValue(":descrip",descrip1);
            rek.bindValue(":prixmin",prixmin1);
            rek.bindValue(":prixmax",prixma1);
            rek.bindValue(":etat", 0);

            if(rek.exec())
            {
                rek.next();

                QMessageBox::information(this,"Enregistrement du logement","Enregistement réussie",QMessageBox::Ok);

                this->close();
            }
            else{
                //QMessageBox::information(this,"Erreur","Echec D'inscription",QMessageBox::Ok);
                qDebug() << rek.lastError().text();

            }
        }
    }

}


void Logement::GestionFermeture()
{
    this->close();
}

/*
void Logement::closeEvent(QCloseEvent *evt)
{
    // evt->ignore();//refuser la fermeture

    int choix=QMessageBox::question(this,"confirmation de la fermeture","voulez_vous vraiment fermer cette fenetre?",
                                    QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    if(choix==QMessageBox::Yes)
    {
        evt->accept();//accepter la fermeture
    }
    else
        evt->ignore();
}
*/

void Logement::ihmInsert(int idUser, QString t, QWidget *parent)
{
    type->setMaxLength(50);
    type->setPlaceholderText("donnez le type de logement");

    prixmin->setMaxLength(9);
    prixmin->setInputMask("999999999");
    prixmin->setToolTip("saisisez le prix minimum du logement");

    date->setCalendarPopup(true);
    date->setMinimumDate(QDate(1990,5,2));
    date->setMaximumDate(QDate(2017,5,30));
    date->setDate(QDate(1994,5,5));



    prixmax->setMaxLength(9);
    prixmax->setInputMask("999999999");
    prixmax->setToolTip("saisisez le prix maximum du logement");

    mon_form->addRow("Type du logement:", type);
    mon_form->addRow("Datede création", date);
    mon_form->addRow("Description", descrip);
    mon_form->addRow("prix minimum", prixmin);
    mon_form->addRow("prix maximum",prixmax);


    cadreHbtn->addWidget(btn_annul);
    cadreHbtn->addWidget(btn_enreg);
    cadreHbtn->addWidget(btn_fermer);


    cadrev->addLayout(mon_form);
    cadrev->addLayout(cadreHbtn);


    this->setWindowTitle(t);

    this->setLayout(cadrev);

    //qDebug()<< idUser;
    this->id_user = idUser;

    connect(btn_annul,SIGNAL(clicked()),this,SLOT(Renitialiser()));
    connect(btn_enreg,SIGNAL(clicked()),this,SLOT(EnregistrerLogement()));
    connect(btn_fermer,SIGNAL(clicked()),this,SLOT(GestionFermeture()));
}

void Logement::ihmList(int idUser, QString t, QWidget *parent)
{
    this->id_user = idUser;
    this->setWindowTitle(t);

    model = new QSqlQueryModel;
    QString query;
    query = QString("select * from logement where id_user = %1").arg(QString::number(this->id_user));
    model->setQuery(query);

    vue = new QTableView;
    vue->setModel(model);
    vue->setSelectionBehavior(QAbstractItemView::SelectRows);
    vue->resizeColumnsToContents();
    vue->resizeRowsToContents();
    vue->setColumnHidden(0, true);
    vue->setColumnHidden(1, true);

    QGroupBox *boutonsGroup = new QGroupBox("Options");

    QPushButton *modifier = new QPushButton(tr("Modifier"));
    QPushButton *supprimer = new QPushButton(tr("Supprimer"));

    QHBoxLayout *groupVbox = new QHBoxLayout;
    groupVbox->addWidget(modifier);
    groupVbox->addWidget(supprimer);

    boutonsGroup->setLayout(groupVbox);
    cadrev->addWidget(vue);
    cadrev->addWidget(boutonsGroup);

    this->setLayout(cadrev);
    this->layout()->SetFixedSize;

    connect(modifier, SIGNAL(clicked()), this, SLOT(on_modifier_clicked()));
    connect(supprimer, SIGNAL(clicked()), this, SLOT(on_supprimer_clicked()));
}

void Logement::on_modifier_clicked()
{
    QItemSelectionModel *selection = this->vue->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index = indexes.at(0);
    QVariant element = model->data(index, Qt::DisplayRole);

    int idLoge = element.toInt();
    this->id_loge = idLoge;
    Helper *helper = new Helper;
    helper->ihmUpdateLogement(this->id_loge);
    helper->setWindowModality(Qt::ApplicationModal);
    helper->setVisible(true);
    this->close();
}

void Logement::on_supprimer_clicked()
{
    QItemSelectionModel *selection = this->vue->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index = indexes.at(0);
    QVariant element = model->data(index, Qt::DisplayRole);

    int idLoge = element.toInt();
    this->id_loge = idLoge;
    Helper *helper = new Helper;
    helper->removeLogement(this->id_loge, this->id_user);
    helper->setWindowModality(Qt::ApplicationModal);
    helper->setVisible(true);
    this->close();
}

