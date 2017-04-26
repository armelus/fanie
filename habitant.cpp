#include "habitant.h"
#include "ui_habitant.h"
#include "accueil.h"

Habitant::Habitant(int idUser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Habitant)
{
    ui->setupUi(this);
    this->id_user = idUser;
    this->initialiserListe();
}

Habitant::~Habitant()
{
    delete ui;
}

void Habitant::ihmEnregistrerHabitant(QWidget *parent)
{
    fenetre = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    QPushButton *reinitialier = new QPushButton("Reinitialiser");
    QPushButton *enregistrer = new QPushButton("Enregistrer");
    QPushButton *annuler = new QPushButton("Annuler");

    nomLE = new QLineEdit;
    prenomLE = new QLineEdit;
    tel1LE = new QLineEdit;
    tel2LE = new QLineEdit;
    emailLE = new QLineEdit;
    professionLE = new QLineEdit;
    birthdayDTE = new QDateTimeEdit(QDateTime::currentDateTimeUtc());

    nomLE->setMaxLength(50);
    nomLE->setPlaceholderText("Entrez le nom de l'habitant");

    prenomLE->setMaxLength(50);
    prenomLE->setPlaceholderText("Entrez le nom de l'habitant");

    professionLE->setMaxLength(50);
    professionLE->setPlaceholderText("Entrez la profession du locataire");

    emailLE->setPlaceholderText("Entrez l'adresse email de l'ahbitant");

    tel1LE->setInputMask("999999999");
    tel2LE->setInputMask("999999999");

    birthdayDTE->setCalendarPopup(true);
    birthdayDTE->setMinimumDateTime(QDateTime::currentDateTimeUtc().addYears(-100));
    birthdayDTE->setMaximumDateTime(QDateTime::currentDateTimeUtc());
    birthdayDTE->setDisplayFormat("dd-MM-yyyy hh:mm:ss");

    formLayout->addRow("Nom ", nomLE);
    formLayout->addRow("Prenom ", prenomLE);
    formLayout->addRow("Date de Naissance", birthdayDTE);
    formLayout->addRow("Email", emailLE);
    formLayout->addRow("profession", professionLE);
    formLayout->addRow("Tel ", tel1LE);
    formLayout->addRow("Tel ", tel2LE);

    boutonsLayout->addWidget(reinitialier);
    boutonsLayout->addWidget(enregistrer);
    boutonsLayout->addWidget(annuler);

    layout->addLayout(formLayout);
    layout->addLayout(boutonsLayout);

    fenetre->setLayout(layout);
    fenetre->setWindowModality(Qt::ApplicationModal);
    fenetre->setWindowTitle("Nouvel Habitant");
    fenetre->show();

    connect(reinitialier, SIGNAL(clicked()), this, SLOT(reiinitialiser_NewForm()));
    connect(annuler, SIGNAL(clicked()), fenetre, SLOT(close()));
    connect(enregistrer, SIGNAL(clicked()), this, SLOT(save()));
}

void Habitant::ihmUpdateHabitant(int idHabit, QWidget *parent)
{
    this->id_habit = idHabit;

    fenetre = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    QPushButton *reinitialier = new QPushButton("Reinitialiser");
    QPushButton *enregistrer = new QPushButton("Enregistrer");
    QPushButton *annuler = new QPushButton("Annuler");

    nomLE = new QLineEdit;
    prenomLE = new QLineEdit;
    tel1LE = new QLineEdit;
    tel2LE = new QLineEdit;
    emailLE = new QLineEdit;
    professionLE = new QLineEdit;
    birthdayDTE = new QDateTimeEdit(QDateTime::currentDateTimeUtc());

    QSqlQuery query;
    query.prepare("SELECT * FROM habitant WHERE id_habit = :id");
    query.bindValue(":id", this->id_habit);


    QString nom;
    QString prenom;
    QString birthdaySTR;
    QString tel1;
    QString tel2;
    QString email;
    QString profession;

    if(query.exec())
    {
        while(query.next())
        {
            nom = query.value(2).toString();
            prenom = query.value(3).toString();
            birthdaySTR = query.value(4).toString();
            tel1 = query.value(5).toString();
            tel2 = query.value(6).toString();
            email = query.value(7).toString();
            profession = query.value(8).toString();
        }
    }

    nomLE->setMaxLength(50);
    nomLE->setText(nom);
    nomLE->setPlaceholderText("Entrez le nom de l'habitant");

    prenomLE->setMaxLength(50);
    prenomLE->setText(prenom);
    prenomLE->setPlaceholderText("Entrez le nom de l'habitant");

    professionLE->setMaxLength(50);
    professionLE->setText(profession);
    professionLE->setPlaceholderText("Entrez la profession du locataire");

    emailLE->setPlaceholderText("Entrez l'adresse email de l'ahbitant");
    emailLE->setText(email);

    tel1LE->setInputMask("999999999");
    tel1LE->setText(tel1);

    tel2LE->setInputMask("999999999");
    tel2LE->setText(tel2);

    birthdayDTE->setCalendarPopup(true);
    birthdayDTE->setMinimumDateTime(QDateTime::currentDateTimeUtc().addYears(-100));
    birthdayDTE->setMaximumDateTime(QDateTime::currentDateTimeUtc());
    birthdayDTE->setDateTime(QDateTime::fromString(birthdaySTR, "dd-MM-yyyy hh:mm:ss"));
    birthdayDTE->setDisplayFormat("dd-MM-yyyy hh:mm:ss");

    formLayout->addRow("Nom ", nomLE);
    formLayout->addRow("Prenom ", prenomLE);
    formLayout->addRow("Date de Naissance", birthdayDTE);
    formLayout->addRow("Email", emailLE);
    formLayout->addRow("profession", professionLE);
    formLayout->addRow("Tel ", tel1LE);
    formLayout->addRow("Tel ", tel2LE);

    boutonsLayout->addWidget(reinitialier);
    boutonsLayout->addWidget(enregistrer);
    boutonsLayout->addWidget(annuler);

    layout->addLayout(formLayout);
    layout->addLayout(boutonsLayout);

    fenetre->setLayout(layout);
    fenetre->setWindowModality(Qt::ApplicationModal);
    fenetre->setWindowTitle("Mis à jour des informations d'un habitant");
    fenetre->show();

    connect(reinitialier, SIGNAL(clicked()), this, SLOT(reiinitialiser_NewForm()));
    connect(annuler, SIGNAL(clicked()), fenetre, SLOT(close()));
    connect(enregistrer, SIGNAL(clicked()), this, SLOT(update()));
}

void Habitant::reiinitialiser_NewForm()
{
    nomLE->clear();
    prenomLE->clear();
    birthdayDTE->clear();
    professionLE->clear();
    emailLE->clear();
    tel1LE->clear();
    tel2LE->clear();
}

void Habitant::save()
{
    QString nom = nomLE->text();
    QString prenom = prenomLE->text();
    QString birthday = birthdayDTE->dateTime().toString("dd-MM-yyyy hh:mm:ss");
    QString profession = professionLE->text();
    QString email = emailLE->text();
    QString tel1 = tel1LE->text();
    QString tel2 = tel2LE->text();

    if(nom.isEmpty() || prenom.isEmpty())
    {
        QMessageBox::information(this,"Erreur de saisie","Veuillez remplir les champs Nom et prénom",QMessageBox::Ok);
    }
    else
    {
        int etat = 0;

        if(tel1.isEmpty())
            tel1 = "000000000";

        if(tel2.isEmpty())
            tel2 = "000000000";

        if(email.isEmpty())
            email = "nothing@localhost.lc";

        if(profession.isEmpty())
            profession = "Unknown";


        //qDebug() << id_user << nom << prenom << birthday << tel1 << tel2 << email << profession;
        QSqlQuery query;

        query.prepare("INSERT INTO habitant(id_user, nom, prenom, date_de_naissance, tel1, tel2, e_mail, profession, etat) VALUES(:id, :nom, :prenom, :birthday, :tel1, :tel2, :email, :profession, :etat)");
        query.bindValue(":id", id_user);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":birthday", birthday);
        query.bindValue(":tel1", tel1);
        query.bindValue(":tel2", tel2);
        query.bindValue(":email", email);
        query.bindValue(":profession", profession);
        query.bindValue(":etat", etat);

        if(query.exec())
        {
            query.next();

            QMessageBox::information(0,"Enregistrement du nouvel Habitant","Enregistement réussie",QMessageBox::Ok);
            this->reiinitialiser_NewForm();
            this->fenetre->close();
            this->initialiserListe();
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }

}

void Habitant::update()
{
    QString nom = nomLE->text();
    QString prenom = prenomLE->text();
    QString birthday = birthdayDTE->dateTime().toString("dd-MM-yyyy hh:mm:ss");
    QString profession = professionLE->text();
    QString email = emailLE->text();
    QString tel1 = tel1LE->text();
    QString tel2 = tel2LE->text();

    if(nom.isEmpty() || prenom.isEmpty())
    {
        QMessageBox::information(this,"Erreur de saisie","Veuillez remplir les champs Nom et prénom",QMessageBox::Ok);
    }
    else
    {
        if(tel1.isEmpty())
            tel1 = "000000000";

        if(tel2.isEmpty())
            tel2 = "000000000";

        if(email.isEmpty())
            email = "nothing@localhost.lc";

        if(profession.isEmpty())
            profession = "Unknown";


        //qDebug() << id_user << nom << prenom << birthday << tel1 << tel2 << email << profession;
        QSqlQuery query;

        query.prepare("UPDATE habitant SET id_user = :user, nom = :nom, prenom = :prenom, date_de_naissance = :birthday, tel1 = :tel1, tel2 = :tel2, e_mail = :email, profession = :profession WHERE id_habit = :id");
        query.bindValue(":id", id_habit);
        query.bindValue(":user", id_user);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":birthday", birthday);
        query.bindValue(":tel1", tel1);
        query.bindValue(":tel2", tel2);
        query.bindValue(":email", email);
        query.bindValue(":profession", profession);

        if(query.exec())
        {
            query.next();

            QMessageBox::information(0,"Mis à jour d'un Habitant","Mis à jour réussie",QMessageBox::Ok);
            this->reiinitialiser_NewForm();
            this->fenetre->close();
            this->initialiserListe();
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }
}

void Habitant::remove()
{
   // qDebug() << this->id_habit;

    int choix = QMessageBox::question(this,"confirmation de la suppression","voulez_vous vraiment supprimer cet Habitant ?", QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM habitant WHERE id_habit = :id");
        query.bindValue(":id", this->id_habit);

        if(query.exec())
        {
            query.next();
            QMessageBox::information(this,"Suppression de l'Habitant","Suppression réussie",QMessageBox::Ok);
        }
    }

    this->initialiserListe();
}

void Habitant::initialiserListe()
{
    model = new QSqlTableModel;
    model->setTable("habitant");
    model->select();

    this->ui->tableView->setModel(model);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setColumnHidden(0, true);
    this->ui->tableView->setColumnHidden(1, true);
    this->ui->tableView->setColumnHidden(9, true);
}

void Habitant::on_ajouter_clicked()
{
    this->ihmEnregistrerHabitant(this);
}

void Habitant::on_afficher_clicked()
{
    QItemSelectionModel *selection = this->ui->tableView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index = indexes.at(0);
    QVariant element = model->data(index, Qt::DisplayRole);

    id_habit = element.toInt();
}

void Habitant::on_modifier_clicked()
{
    QItemSelectionModel *selection = this->ui->tableView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index = indexes.at(0);
    QVariant element = model->data(index, Qt::DisplayRole);

    id_habit = element.toInt();
    this->ihmUpdateHabitant(id_habit);
}

void Habitant::on_supprimer_clicked()
{
    QItemSelectionModel *selection = this->ui->tableView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();
    QModelIndex index = indexes.at(0);
    QVariant element = model->data(index, Qt::DisplayRole);

    id_habit = element.toInt();
    this->remove();
}
