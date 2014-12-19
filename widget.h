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
#include "voie.h"
#include <QVector>

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
    void ajouterVoie();

private:
    Ui::Widget *ui;
    QVBoxLayout * layoutPrincipal;
    QHBoxLayout * layoutBarreIcones;
    QPushButton * boutonAjouterUtilisateur, * boutonSauvegarder, * boutonChargerCarnet, * BoutonAjouterVoie;
    QHBoxLayout * layoutTri;
    QLabel * labelTri;
    QComboBox * choixTri;
    QStandardItemModel * modele;
    QTableView * vue;
    QVector <Voie *> listeVoies;

    void rafraichirModele();
    void parametresVue();
};

#endif // WIDGET_H
