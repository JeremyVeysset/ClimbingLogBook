#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QFile>
#include <QStringList>
#include <QDate>
#include <QComboBox>
#include <QLabel>
#include <QVector>
#include <QSharedPointer>
#include "voie.h"
#include "ajoutvoiewidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void lectureFichierCMB(QFile & fichier);
    void lectureFichierCSV(QFile & fichier);
    void ecrireFichierCMB(QFile & fichier);
    void ecrireFichierCSV(QFile & fichier);

public slots:
    void ouvrirFichier();
    void trierVue(QString const & str);
    void sauvegarderFichier();
    void ajouterVoie(Voie const & v);

private:
    QSharedPointer <Ui::Widget> ui;
    QSharedPointer <QVBoxLayout> layoutPrincipal;
    QSharedPointer <QHBoxLayout> layoutBarreIcones;
    QSharedPointer <QPushButton> boutonAjouterUtilisateur, boutonSauvegarder, boutonChargerCarnet, BoutonAjouterVoie;
    QSharedPointer <QHBoxLayout> layoutTri;
    QSharedPointer <QLabel> labelTri;
    QSharedPointer <QComboBox> choixTri;
    QSharedPointer <QStandardItemModel> modele;
    QSharedPointer <QTableView> vue;
    QVector <QSharedPointer <Voie> > listeVoies;
    QSharedPointer <AjoutVoieWidget> ajoutWidgetVoie;

    void rafraichirModele();
    void parametresVue();
};

#endif // WIDGET_H
