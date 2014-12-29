#include "ajoutvoiewidget.h"
#include <QString>

AjoutVoieWidget::AjoutVoieWidget(QWidget * widget) : QWidget(widget)
{
    pLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    formLayout = new QFormLayout();
    dateEdit = new QDateEdit(QDate::currentDate());
    coteEdit = new QLineEdit();
    nomEdit = new QLineEdit();
    secteurEdit = new QLineEdit();
    commentaireEdit = new QLineEdit();
    perfEdit = new QComboBox();
    okButton = new QPushButton(QString("Ok"));
    annulerButton = new QPushButton(QString("Annuler"));

    perfEdit->addItem(QString(""));
    perfEdit->addItem(QString("On sight"));
    perfEdit->addItem(QString("Flash"));
    perfEdit->addItem(QString("Second go"));

    formLayout->addRow(QString("Date"), dateEdit);
    formLayout->addRow(QString("Côte"), coteEdit);
    formLayout->addRow(QString("Nom"), nomEdit);
    formLayout->addRow(QString("Secteur"), secteurEdit);
    formLayout->addRow(QString("Commentaire"), commentaireEdit);
    formLayout->addRow(QString("Performance"), perfEdit);

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(annulerButton);

    pLayout->addLayout(formLayout);
    pLayout->addLayout(buttonLayout);
    this->setLayout(pLayout);

    QObject::connect(annulerButton, SIGNAL(clicked()), this, SLOT(hide()));
}

AjoutVoieWidget::~AjoutVoieWidget()
{
    delete pLayout;
    delete formLayout;
    delete buttonLayout;
    delete okButton;
    delete annulerButton;
    delete dateEdit;
    delete coteEdit;
    delete nomEdit;
    delete secteurEdit;
    delete commentaireEdit;
    delete perfEdit;
}

Voie AjoutVoieWidget::creerVoie()
{
    Voie v(dateEdit->date(), coteEdit->text(), nomEdit->text(), secteurEdit->text(), commentaireEdit->text(), perfEdit->currentText());
    return v;
}

void AjoutVoieWidget::reinit()
{
    dateEdit->setDate(QDate::currentDate());
    coteEdit->setText(QString(""));
    nomEdit->setText(QString(""));
    secteurEdit->setText(QString(""));
    commentaireEdit->setText(QString(""));
    perfEdit->setCurrentIndex(0);

    return;
}

void AjoutVoieWidget::hide()
{
    reinit();
    QWidget::hide();
    return;
}
