#include "accueil.h"
#include "logement.h"
#include "listeutilisateurs.h"
#include "habitant.h"

accueil::accueil(QString t, int id, QWidget *parent):QMainWindow(parent)
{
    //paramétragebdes variables dynamiques
    lib=new QLabel("LE MAISONIER");
    libelleImage=new QLabel;
    cadrev=new QVBoxLayout;
    grille=new QGridLayout;
    widgetFen=new QWidget;
    pixi=new QPixmap("image.jpg");

    //paramétragebdes variables dynamiques du menu
    barreDeMenu=new QMenuBar;
    MenuFichier=new QMenu("Fichier");
    MenuConsulter=new QMenu("Consulter");
    MenuImmprimer=new QMenu("Imprimer");
    MenuUtilisateur=new QMenu("utilisateur");
    MenuBatiment=new QMenu("Batiment");
    MenuContratDeBail=new QMenu("Contrat de Bail");
    MenuFacture=new QMenu("Facture");
    MenuHabitant = new QMenu("Habitants");
    MenuLogement=new QMenu("Logement");
    MenuOccupation=new QMenu("Occupation");
    MenuTypeLogement=new QMenu("Type de Logement");
    ActionUtilisateur=new QAction("Utilisateur",this);
    ActionBatiment=new QAction("enregitrer",this);
    ActionEnregL=new QAction("Enregistrer",this);
    ListeUtilisateur=new QAction("Liste des utilisateurs",this);
    Actionquiter=new QAction("Quitter",this);
    ActionListerLogement = new QAction("Liste des Logements", this);
    ActionListerHabitant = new QAction("Liste des Habitants", this);

    //paramétrage de la barre de menu

        //les menus
    barreDeMenu->addMenu(MenuConsulter);
    barreDeMenu->addMenu(MenuFichier);
    barreDeMenu->addMenu(MenuImmprimer);


        //les sous_menu

    MenuConsulter->addMenu(MenuContratDeBail);
    MenuConsulter->addMenu(MenuFacture);
    MenuConsulter->addMenu(MenuHabitant);
    MenuConsulter->addMenu(MenuLogement);
    MenuConsulter->addMenu(MenuOccupation);
    MenuConsulter->addMenu(MenuUtilisateur);


        //les actions
    MenuFichier->addAction(Actionquiter);
    MenuUtilisateur->addAction(ListeUtilisateur);
    MenuUtilisateur->addAction(ActionUtilisateur);
    MenuBatiment->addAction(ActionBatiment);

    // Les Logements
    MenuLogement->addAction(ActionEnregL);
    MenuLogement->addAction(ActionListerLogement);

    //Les Habitants
    MenuHabitant->addAction(ActionListerHabitant);




    //paramétrage du libellé
    QFont fonte("arial",20);
    fonte.setBold(true);
    lib->setFont(fonte);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::blue);
    lib->setPalette(pal);

    libelleImage->setPixmap(QPixmap("D:/Programmes/loyer/image.jpg"));


    //paramétrage du cadre vertical
    cadrev->addWidget(lib);
    cadrev->addWidget(libelleImage,0,0);


     //paramétrage de la grille
    grille->addLayout(cadrev,0,0,1,2,Qt::AlignHCenter);
   // grille->addWidget(btn_connexion,1,0,1,1,Qt::AlignVCenter);



    //paramétrage de l'age du nom sur la fenetre d'image
    nom=t;
    id_user=id;

    widgetFen->setLayout(grille);




    //paramétrage de la fenetre(this)
    this->setWindowTitle("Gestionnaire des loyers__"+t);
    this->setMenuBar(barreDeMenu);
    this->setCentralWidget(widgetFen);
    //this->setFixedSize(250,250);



    //paramétrage des conneions
    connect(ActionUtilisateur,SIGNAL(triggered()),this,SLOT(FenEnregistremtUtilisateur()));
    connect(ActionEnregL,SIGNAL(triggered()),this,SLOT(FenEnregistremtLogement()));
    connect(Actionquiter,SIGNAL(triggered()),this,SLOT(fermeture()));
    connect(ListeUtilisateur,SIGNAL(triggered()),this,SLOT(AffichListeUtilisateur()));
    connect(ActionListerLogement, SIGNAL(triggered()), this, SLOT(AfficherListeLogment()));
    connect(ActionListerHabitant, SIGNAL(triggered()), this, SLOT(AfficherListeHabitant()));

     //connect(btn_connexion,SIGNAL(clicked()),this,SLOT(FenNewAb()));
}

void accueil::FenEnregistremtUtilisateur()
{
   Utilisateur *f=new Utilisateur;
   f->setWindowModality(Qt::ApplicationModal);
   f->setVisible(true);
}



void accueil::AffichListeUtilisateur()
{
    ListeUtilisateurs *userIHM = new ListeUtilisateurs;
    userIHM->setWindowModality(Qt::ApplicationModal);
    userIHM->setVisible(true);
}


void accueil::FenEnregistremtLogement()
{
    Logement *f=new Logement;
    f->ihmInsert(this->id_user);
    f->setWindowModality(Qt::ApplicationModal);
    f->setVisible(true);
}

void accueil::AfficherListeLogment()
{
    Logement *logement = new Logement;
    logement->ihmList(this->id_user);
    logement->setWindowModality(Qt::ApplicationModal);
    logement->setVisible(true);
}

void accueil::AfficherListeHabitant()
{
    Habitant *habitant = new Habitant;
    habitant->setWindowModality(Qt::ApplicationModal);
    habitant->setVisible(true);
}

void accueil::closeEvent(QCloseEvent *evt)
{
   // evt->ignore();//refuser la fermeture

    int choix=QMessageBox::question(this," de la fermeture","voulez_vous vraiment fermer cette fenetre? ",
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No);

    if(choix==QMessageBox::Yes)
    {
        QSqlQuery update;
        update.prepare("update utilisateur set date_derniere_deconnex=NOW() where id_user=:id");
        update.bindValue(":id", this->id_user);
        update.exec();
        evt->accept();//accepter la fermeture
    }
    else
        evt->ignore();
}



void accueil::fermeture()
{
    this->close();
}


void accueil::setNom(QString nomUser)
{
    this->nom = nomUser;
}

void accueil::setID(int idUser)
{
    this->id_user = idUser;
}

QString accueil::getNom()
{
    return  this->nom;
}

int accueil::getID()
{
    return this->id_user;
}
