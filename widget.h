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
    void lectureFichierCSV();

public slots:
    void ouvrirFichier();
    void trierVue(QString const & str);

private:
    Ui::Widget *ui;
    QVBoxLayout * layoutPrincipal;
    QHBoxLayout * layoutBarreIcones;
    QPushButton * boutonAjouterUtilisateur;
    QPushButton * boutonSauvegarder;
    QPushButton * boutonChargerCarnet;
    QHBoxLayout * layoutTri;
    QLabel * labelTri;
    QComboBox * choixTri;
    QFile * fichier;
    QStandardItemModel * modele;
    QTableView * vue;
    QVector <Voie *> listeVoies;

    void rafraichirModele();
    void parametresVue();
};

QDate QStringToDate(QString date, QString sep = "/");
#endif // WIDGET_H
