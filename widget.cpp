#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <iostream>
#include <QFileDialog>
#include <QtAlgorithms>
#include <iostream>
#include <iterator>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    layoutPrincipal = new QVBoxLayout;
    layoutBarreIcones = new QHBoxLayout;
    fichier = new QFile;

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

    layoutPrincipal->addLayout(layoutBarreIcones);
    layoutPrincipal->addWidget(vue);
    setLayout(layoutPrincipal);

    //modele->setHorizontalHeaderLabels(headersVoies);

    QObject::connect(boutonChargerCarnet, SIGNAL(clicked()), this, SLOT(ouvrirFichier()));
    QObject::connect(choixTri, SIGNAL(currentIndexChanged(QString)), this, SLOT(trierVue(QString)));
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
    delete fichier;
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
    delete fichier;
    fichier = new QFile(QFileDialog::getOpenFileName(this, "Ouvrir un Carnet de croix", QString(), "Fichiers CSV (*.csv)"));

    QString ext = fichier->fileName();
    QStringList fileNameSplit;
    fileNameSplit = ext.split(".");
    ext = fileNameSplit.last();

    if (ext == "csv")
        lectureFichierCSV();

    rafraichirModele();
    trierVue(choixTri->currentText());
}

void Widget::lectureFichierCSV()
{
    fichier->open(QIODevice::ReadWrite);
    QString ligne;
    QStringList param;

    while (!fichier->atEnd())
    {
        ligne = fichier->readLine();
        param = ligne.split(";");
        QDate date(QStringToDate(param[0]));
        param.pop_front();
        listeVoies.push_back(new Voie(date, param));
    }

    trierVue(choixTri->currentText());

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


QDate QStringToDate(QString dateStr, QString sep)
{
    QStringList list;
    list = dateStr.split(sep);
    QDate date(list[2].toInt(), list[1].toInt(), list[0].toInt());

    return date;
}
