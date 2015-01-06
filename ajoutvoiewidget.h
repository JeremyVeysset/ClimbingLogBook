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
#include <QSharedPointer>
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
    QSharedPointer <QVBoxLayout> pLayout;
    QSharedPointer <QHBoxLayout> buttonLayout;
    QSharedPointer <QFormLayout> formLayout;
    QSharedPointer <QPushButton> okButton, annulerButton;
    QSharedPointer <QLineEdit> nomEdit, secteurEdit, commentaireEdit;
    QSharedPointer <QDateEdit> dateEdit;
    QSharedPointer <QComboBox> perfEdit, coteEdit;
};

#endif // AJOUTVOIEWIDGET_H
