#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <iostream>
#include <QFileDialog>
#include <QtAlgorithms>
#include <iostream>
#include <iterator>
#include <QSettings>
#include <QTextStream>
#include <QFrame>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Voie::initVoieSystem();

    ui->setupUi(this);
    layoutPrincipal = new QVBoxLayout;
    layoutBarreIcones = new QHBoxLayout;

    boutonAjouterUtilisateur = new QPushButton(QIcon(QString("./Pictures/IconeHomme.png")), QString(""));
    boutonChargerCarnet = new QPushButton(QIcon(QString("./Pictures/IconeOuvrir.png")), QString(""));
    boutonSauvegarder = new QPushButton(QIcon(QString("./Pictures/IconeSauvegarder.png")), QString(""));
    choixTri = new QComboBox();
    choixTri->addItem(QString("Côte croissante"));
    choixTri->addItem(QString("Côte décroissante"));
    choixTri->addItem(QString("Date croissante"));
    choixTri->addItem(QString("Date décroissante"));
    choixTri->addItem(QString("Nom croissant"));
    choixTri->addItem(QString("Nom décroissant"));
    choixTri->addItem(QString("Secteur"));
    labelTri = new QLabel(QString("Trier par :"));
    layoutTri = new QHBoxLayout();
    layoutTri->addWidget(labelTri);
    layoutTri->addWidget(choixTri);
    //QPushButton BoutonAjouterVoie();

    layoutBarreIcones->addWidget(boutonAjouterUtilisateur);
    layoutBarreIcones->addWidget(boutonChargerCarnet);
    layoutBarreIcones->addWidget(boutonSauvegarder);
    layoutBarreIcones->addStretch();
    layoutBarreIcones->addLayout(layoutTri);

    modele = new QStandardItemModel();
    vue = new QTableView();
    vue->setModel(modele);
    vue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    vue->setLineWidth(2);

    layoutPrincipal->addLayout(layoutBarreIcones);
    layoutPrincipal->addWidget(vue);
    setLayout(layoutPrincipal);

    QObject::connect(boutonChargerCarnet, SIGNAL(clicked()), this, SLOT(ouvrirFichier()));
    QObject::connect(choixTri, SIGNAL(currentIndexChanged(QString)), this, SLOT(trierVue(QString)));
    QObject::connect(boutonSauvegarder, SIGNAL(clicked()), this, SLOT(sauvegarderFichier()));
}

Widget::~Widget()
{
    delete ui;
    delete layoutPrincipal;
    delete layoutBarreIcones;
    delete boutonAjouterUtilisateur;
    delete boutonSauvegarder;
    delete boutonChargerCarnet;
    delete layoutTri;
    delete labelTri;
    delete choixTri;
    delete vue;

    modele->clear();
    delete modele;

    for (int i=0; i<listeVoies.size(); i++)
        delete listeVoies[i];
}

void Widget::parametresVue()
{
    QStringList headersVoies = Voie::nomParametres();
    return;
}

void Widget::trierVue(QString const & str)
{
    if (str == choixTri->itemText(0))
        vue->sortByColumn(2,Qt::AscendingOrder);
    else if (str == choixTri->itemText(1))
        vue->sortByColumn(2,Qt::DescendingOrder);
    else if (str == choixTri->itemText(2))
        vue->sortByColumn(0,Qt::AscendingOrder);
    else if (str == choixTri->itemText(3))
        vue->sortByColumn(0,Qt::DescendingOrder);
    else if (str == choixTri->itemText(4))
        vue->sortByColumn(1,Qt::AscendingOrder);
    else if (str == choixTri->itemText(5))
        vue->sortByColumn(1,Qt::DescendingOrder);
    else if (str == choixTri->itemText(6))
        vue->sortByColumn(3,Qt::AscendingOrder);
}

void Widget::ouvrirFichier()
{
    QFile fichier(QFileDialog::getOpenFileName(this, "Ouvrir un Carnet de croix", QString(), "Fichiers Climb (*.cmb);;Fichiers CSV (*.csv)"));

    QString format = fichier.fileName().split(".").last();

    if (format.toLower() == "csv")
        lectureFichierCSV(fichier);
    else if (format.toLower() == "cmb")
        lectureFichierCMB(fichier);

    rafraichirModele();
    trierVue(choixTri->currentText());
}

void Widget::sauvegarderFichier()
{
    QFile fichierEcrire(QFileDialog::getSaveFileName(this, "Sauvegarder un Carnet de croix", QString(), "Fichiers Climb (*.cmb);;Fichiers CSV (*.csv)"));
    QString format(fichierEcrire.fileName().split(".").last());

    if (format.toLower() == "cmb")
        ecrireFichierCMB(fichierEcrire);
    else if (format.toLower() == "csv")
        ecrireFichierCSV(fichierEcrire);

    return;
}

void Widget::lectureFichierCMB(QFile & fichier)
{
    int i;
    fichier.open(QIODevice::ReadOnly);
    QDataStream in(&fichier);

    for (i=0; i<listeVoies.size(); i++)
        delete listeVoies[i];
    listeVoies.clear();

    i = 0;
    while (!fichier.atEnd())
    {
        Voie v;
        in >> v;
        listeVoies.append(new Voie(v));
    }

    fichier.close();

    return;
}

void Widget::lectureFichierCSV(QFile & fichier)
{
    fichier.open(QIODevice::ReadOnly);
    QString ligne;
    QStringList param;

    while (!fichier.atEnd())
    {
        ligne = fichier.readLine();
        listeVoies.push_back(new Voie(ligne));
    }

    trierVue(choixTri->currentText());

    return;
}

void Widget::ecrireFichierCMB(QFile & fichier)
{
    fichier.open(QIODevice::WriteOnly);
    QDataStream out(&fichier);

    for (int i=0; i<listeVoies.size(); i++)
        out << *listeVoies[i];
    fichier.close();

    return;
}

void Widget::ecrireFichierCSV(QFile & fichier)
{
    fichier.open(QIODevice::WriteOnly);
    QTextStream out(&fichier);

    QStringList param;
    for (int i=0; i<listeVoies.size(); i++)
    {
        param.clear();
        param << listeVoies[i]->getDate().toString(QString("dd/MM/yyyy"))
              << listeVoies[i]->getCote()
              << listeVoies[i]->getNom()
              << listeVoies[i]->getSecteur()
              << listeVoies[i]->getCommmentaire()
              << listeVoies[i]->getPerf();

        out << param.join(QString(";"));
    }

    fichier.close();

    return;
}

void Widget::rafraichirModele()
{
    modele->clear();
    modele->setHorizontalHeaderLabels(Voie::nomParametres());
    for (int i=0; i<listeVoies.size(); i++)
    {
        QList <QStandardItem *> l;
        l.append(new QStandardItem(listeVoies[i]->getDate().toString(QString("yyyy/MM/dd"))));
        l.append(new QStandardItem(listeVoies[i]->getNom()));
        l.append(new QStandardItem(listeVoies[i]->getCote()));
        l.append(new QStandardItem(listeVoies[i]->getSecteur()));
        l.append(new QStandardItem(listeVoies[i]->getPerf()));
        l.append(new QStandardItem(listeVoies[i]->getCommmentaire()));

        modele->appendRow(l);
    }

    return;
}
