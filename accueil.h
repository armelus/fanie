#ifndef ACCUEIL_H
#define ACCUEIL_H
#include<QFileDialog>
#include<QPalette>
#include <QCloseEvent>
#include<QPixmap>
#include<QMainWindow>
#include "utilisateur.h"


class accueil : public QMainWindow

{
    Q_OBJECT//INDISPENSABLE POUR CREER SES PROPRES METHODES

protected:
    QLabel *lib;
    QLabel *libelleImage;
    QVBoxLayout *cadrev;
    QGridLayout *grille;
    QWidget *widgetFen;
    QPixmap *pixi;


    //les menus
     QMenuBar *barreDeMenu;
     QMenu *MenuFichier;
     QMenu *MenuConsulter;
     QMenu *MenuImmprimer;
     QMenu *MenuUtilisateur;
     QMenu *MenuBatiment;
     QMenu *MenuContratDeBail;
     QMenu *MenuFacture;
     QMenu *MenuHabitant;
     QMenu *MenuLogement;
     QMenu *MenuOccupation;
     QMenu *MenuTypeLogement;
     QAction *ActionUtilisateur;
     QAction *ActionBatiment;
     QAction *ActionEnregL;
     QAction *ListeUtilisateur;
     QAction *Actionquiter;
     QAction *ActionListerLogement;
     QAction *ActionListerHabitant;

     QString nom;
     int id_user;

public:
    // accueil(QWidget *parent = 0);
     accueil (QString t="LE MAISONIER",int id=0, QWidget *parent = NULL);
     void closeEvent(QCloseEvent *evt);
     QString getNom();
     int getID();
     void setNom(QString nomUser);
     void setID(int idUser);


public slots:
    void FenEnregistremtUtilisateur();
    void FenEnregistremtLogement();
    void fermeture();
    void AffichListeUtilisateur();
    void AfficherListeLogment();
    void AfficherListeHabitant();

   // void callloger;


};



#endif // ACCUEIL_H
