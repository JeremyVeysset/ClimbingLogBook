#ifndef AJOUTVOIEWIDGET_H
#define AJOUTVOIEWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include "voie.h"

class AjoutVoieWidget : public QWidget
{
public:
    AjoutVoieWidget(QWidget * widget=0);
    ~AjoutVoieWidget();
    void reinit();

public slots:
    Voie creerVoie();
    void hide();

private:
    QVBoxLayout * pLayout;
    QHBoxLayout * buttonLayout;
    QFormLayout * formLayout;
    QPushButton * okButton, * annulerButton;
    QLineEdit * coteEdit, * nomEdit, * secteurEdit, * commentaireEdit;
    QDateEdit * dateEdit;
    QComboBox * perfEdit;
};

#endif // AJOUTVOIEWIDGET_H
