#include "ajoutvoiewidget.h"
#include <QString>

AjoutVoieWidget::AjoutVoieWidget(QWidget * widget) : QWidget(widget)
{
    setWindowModality(Qt::ApplicationModal);

    pLayout = QSharedPointer <QVBoxLayout> (new QVBoxLayout());
    buttonLayout = QSharedPointer <QHBoxLayout> (new QHBoxLayout());
    formLayout = QSharedPointer <QFormLayout> (new QFormLayout());
    dateEdit = QSharedPointer <QDateEdit> (new QDateEdit(QDate::currentDate()));
    coteEdit = QSharedPointer <QComboBox> (new QComboBox());
    nomEdit = QSharedPointer <QLineEdit> (new QLineEdit());
    secteurEdit = QSharedPointer <QLineEdit> (new QLineEdit());
    commentaireEdit = QSharedPointer <QLineEdit> (new QLineEdit());
    perfEdit = QSharedPointer <QComboBox> (new QComboBox());
    okButton = QSharedPointer <QPushButton> (new QPushButton(QString("Ok")));
    annulerButton = QSharedPointer <QPushButton> (new QPushButton(QString("Annuler")));

    QStringList s;
    s << "5a" << "5a+" << "5b" << "5b+" << "5c" << "5c+" << "6a" << "6a+" << "6b" << "6b+" << "6c" << "6c+";
    s << "7a" << "7a+" << "7b" << "7b+" << "7c" << "7c+" << "8a" << "8a+" << "8b" << "8b+" << "8c" << "8c+";
    s << "9a" << "9a+" << "9b" << "9b+" << "9c";
    coteEdit->addItems(QStringList(s));

    s.clear();
    s << "" << "On sight" << "Flash" << "Second go";
    perfEdit->addItems(s);

    formLayout->addRow(QString("Date"), dateEdit.data());
    formLayout->addRow(QString("Côte"), coteEdit.data());
    formLayout->addRow(QString("Nom"), nomEdit.data());
    formLayout->addRow(QString("Secteur"), secteurEdit.data());
    formLayout->addRow(QString("Commentaire"), commentaireEdit.data());
    formLayout->addRow(QString("Performance"), perfEdit.data());

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton.data());
    buttonLayout->addWidget(annulerButton.data());

    pLayout->addLayout(formLayout.data());
    pLayout->addLayout(buttonLayout.data());
    this->setLayout(pLayout.data());

    QObject::connect(annulerButton.data(), SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(okButton.data(), SIGNAL(clicked()), this, SLOT(creerVoie()));
}

AjoutVoieWidget::~AjoutVoieWidget()
{
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
