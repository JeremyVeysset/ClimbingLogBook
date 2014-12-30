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
    Q_OBJECT

public:
    AjoutVoieWidget(QWidget * widget=0);
    ~AjoutVoieWidget();
    void reinit();

public slots:
    void creerVoie();
    void hide();

signals:
    void accepted(Voie const & v);

private:
    QVBoxLayout * pLayout;
    QHBoxLayout * buttonLayout;
    QFormLayout * formLayout;
    QPushButton * okButton, * annulerButton;
    QLineEdit * nomEdit, * secteurEdit, * commentaireEdit;
    QDateEdit * dateEdit;
    QComboBox * perfEdit, * coteEdit;
};

#endif // AJOUTVOIEWIDGET_H
