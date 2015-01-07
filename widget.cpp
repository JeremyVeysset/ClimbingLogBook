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
#include <QPalette>
#include <QInputDialog>
#include "ajoutvoiewidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Voie::initVoieSystem();

    ui->setupUi(this);

    setWindowTitle(QString("Climbing Log Book"));
    layoutPrincipal = QSharedPointer <QVBoxLayout> (new QVBoxLayout);
    layoutBarreIcones = QSharedPointer <QHBoxLayout> (new QHBoxLayout);

    boutonAjouterUtilisateur = QSharedPointer <QPushButton> (new QPushButton(QIcon(QString("./Pictures/IconUser.png")), QString("")));
    boutonChargerCarnet = QSharedPointer <QPushButton> (new QPushButton(QIcon(QString("./Pictures/OpenIcon.png")), QString("")));
    boutonSauvegarder = QSharedPointer <QPushButton> (new QPushButton(QIcon(QString("./Pictures/SaveIcon.png")), QString("")));
    BoutonAjouterVoie = QSharedPointer <QPushButton> (new QPushButton(QIcon(QString("./Pictures/AddRouteIcon.png")), QString("")));
    choixTri = QSharedPointer <QComboBox> (new QComboBox());
    choixTri->addItem(QString("Côte croissante"));
    choixTri->addItem(QString("Côte décroissante"));
    choixTri->addItem(QString("Date croissante"));
    choixTri->addItem(QString("Date décroissante"));
    choixTri->addItem(QString("Nom croissant"));
    choixTri->addItem(QString("Nom décroissant"));
    choixTri->addItem(QString("Secteur"));
    labelTri = QSharedPointer <QLabel> (new QLabel(QString("Trier par :")));
    layoutTri = QSharedPointer <QHBoxLayout> (new QHBoxLayout());
    layoutTri->addWidget(labelTri.data());
    layoutTri->addWidget(choixTri.data());

    layoutBarreIcones->addWidget(boutonAjouterUtilisateur.data());
    layoutBarreIcones->addWidget(boutonChargerCarnet.data());
    layoutBarreIcones->addWidget(boutonSauvegarder.data());
    layoutBarreIcones->addWidget(BoutonAjouterVoie.data());
    layoutBarreIcones->addStretch();
    layoutBarreIcones->addLayout(layoutTri.data());

    modele = QSharedPointer <QStandardItemModel> (new QStandardItemModel());
    vue = QSharedPointer <QTableView> (new QTableView());
    vue->setModel(modele.data());
    parametresVue();

    layoutPrincipal->addLayout(layoutBarreIcones.data());
    layoutPrincipal->addWidget(vue.data());
    setLayout(layoutPrincipal.data());

    setAutoFillBackground(true);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(248,248,255));
    setPalette(Pal);

    ajoutWidgetVoie = QSharedPointer <AjoutVoieWidget> (new AjoutVoieWidget());
    ajoutWidgetVoie->hide();

    QObject::connect(boutonChargerCarnet.data(), SIGNAL(clicked()), this, SLOT(ouvrirFichier()));
    QObject::connect(choixTri.data(), SIGNAL(currentIndexChanged(QString)), this, SLOT(trierVue(QString)));
    QObject::connect(boutonSauvegarder.data(), SIGNAL(clicked()), this, SLOT(sauvegarderFichier()));
    QObject::connect(BoutonAjouterVoie.data(), SIGNAL(clicked()), ajoutWidgetVoie.data(), SLOT(show()));
    QObject::connect(ajoutWidgetVoie.data(), SIGNAL(accepted(Voie)), this, SLOT(ajouterVoie(Voie)));
}

Widget::~Widget()
{
}

void Widget::parametresVue()
{
    modele->setHorizontalHeaderLabels(Voie::nomParametres());
    vue->verticalHeader()->hide();
    vue->setShowGrid(false);
    vue->resizeColumnsToContents();
    vue->horizontalHeader()->setSectionsClickable(false);
    vue->setLineWidth(2);

    return;
}

void Widget::trierVue(QString const & str)
{
    if (str == choixTri->itemText(0))
        vue->sortByColumn(1,Qt::AscendingOrder);
    else if (str == choixTri->itemText(1))
        vue->sortByColumn(1,Qt::DescendingOrder);
    else if (str == choixTri->itemText(2))
        vue->sortByColumn(0,Qt::AscendingOrder);
    else if (str == choixTri->itemText(3))
        vue->sortByColumn(0,Qt::DescendingOrder);
    else if (str == choixTri->itemText(4))
        vue->sortByColumn(2,Qt::AscendingOrder);
    else if (str == choixTri->itemText(5))
        vue->sortByColumn(2,Qt::DescendingOrder);
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

    listeVoies.clear();

    i = 0;
    while (!fichier.atEnd())
    {
        Voie v;
        in >> v;
        listeVoies.append(QSharedPointer <Voie> (new Voie(v)));
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
        listeVoies.push_back(QSharedPointer <Voie> (new Voie(ligne)));
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
    for (int i=0; i<listeVoies.size(); i++)
    {
        QList <QStandardItem *> l;
        l.append(new QStandardItem(listeVoies[i]->getDate().toString(QString("yyyy/MM/dd"))));
        l.append(new QStandardItem(listeVoies[i]->getCote()));
        l.append(new QStandardItem(listeVoies[i]->getNom()));
        l.append(new QStandardItem(listeVoies[i]->getSecteur()));
        l.append(new QStandardItem(listeVoies[i]->getPerf()));
        l.append(new QStandardItem(listeVoies[i]->getCommmentaire()));

        modele->appendRow(l);
    }

    parametresVue();

    return;
}

void Widget::ajouterVoie(Voie const & v)
{
    listeVoies.push_back(QSharedPointer <Voie> (new Voie(v)));
    rafraichirModele();
    trierVue(choixTri->currentText());
    return;
}
