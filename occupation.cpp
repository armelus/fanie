#include "occupation.h"

Occupation::Occupation(QString t, QWidget *parent)
{
    LoyerBase = new QLineEdit;
    DateEntree =new QDateEdit ;
    DateSortie = new QDateEdit ;
    arriere = new QLineEdit ;
    Description = new QTextEdit ;
    btn_renitial = new QPushButton("Rénitialiser");
    btn_enreg = new QPushButton("Enregistrer");
    btn_fermer = new QPushButton("Fermer") ;
    cadreHbtn = new QHBoxLayout ;
    cadrev = new QVBoxLayout ;
    mon_form = new QFormLayout ;


    LoyerBase->setMaxLength(9);
    LoyerBase->setPlaceholderText("saisissez un montant");
    LoyerBase->setInputMask("999999999");

    DateEntree->calendarPopup();
    DateSortie->calendarPopup();

    arriere->setMaxLength(9);
    arriere->setPlaceholderText("999999999");
    arriere->setPlaceholderText("entrez le montant des arriérés");


    mon_form->addRow("Loyer de base:", LoyerBase);
    mon_form->addRow("Date d'entrée:" , DateEntree);
    mon_form->addRow("Date de sortie", DateSortie);
    mon_form->addRow("Arriéré de loyer", arriere);
    mon_form->addRow("Observation", Description);


    cadreHbtn->addWidget(btn_renitial);
    cadreHbtn->addWidget(btn_enreg);
    cadreHbtn->addWidget(btn_fermer);


    cadrev->addLayout(mon_form);
    cadrev->addLayout(cadreHbtn);


    this->setWindowTitle(t);
    this->setLayout(cadrev);



}


void Occupation::Renitialiser()
{

}



void Occupation::EnvoyerForm()
{

}
