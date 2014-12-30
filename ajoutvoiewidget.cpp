#include "ajoutvoiewidget.h"
#include <QString>

AjoutVoieWidget::AjoutVoieWidget(QWidget * widget) : QWidget(widget)
{
    setWindowModality(Qt::ApplicationModal);

    pLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    formLayout = new QFormLayout();
    dateEdit = new QDateEdit(QDate::currentDate());
    coteEdit = new QComboBox();
    nomEdit = new QLineEdit();
    secteurEdit = new QLineEdit();
    commentaireEdit = new QLineEdit();
    perfEdit = new QComboBox();
    okButton = new QPushButton(QString("Ok"));
    annulerButton = new QPushButton(QString("Annuler"));

    QStringList s;
    s << "5a" << "5a+" << "5b" << "5b+" << "5c" << "5c+" << "6a" << "6a+" << "6b" << "6b+" << "6c" << "6c+";
    s << "7a" << "7a+" << "7b" << "7b+" << "7c" << "7c+" << "8a" << "8a+" << "8b" << "8b+" << "8c" << "8c+";
    s << "9a" << "9a+" << "9b" << "9b+" << "9c";
    coteEdit->addItems(QStringList(s));

    s.clear();
    s << "" << "On sight" << "Flash" << "Second go";
    perfEdit->addItems(s);

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
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(creerVoie()));
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

void AjoutVoieWidget::creerVoie()
{
    Voie v(dateEdit->date(), coteEdit->currentText(), nomEdit->text(), secteurEdit->text(), commentaireEdit->text(), perfEdit->currentText());
    emit accepted(v);
    hide();
}

void AjoutVoieWidget::reinit()
{
    dateEdit->setDate(QDate::currentDate());
    coteEdit->setCurrentIndex(0);
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
