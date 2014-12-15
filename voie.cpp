#include "voie.h"

Voie::Voie()
{
}

Voie::Voie(QDate date, QString cote, QString nom, QString secteur, QString commentaire, QString perf):m_date(date), m_cote(cote), m_nom(nom), m_secteur(secteur), m_commentaire(commentaire), m_perf(perf)
{
}

Voie::Voie(QDate date, QStringList list):m_date(date)
{
        m_date = date;
        m_cote = list[0];
        m_nom = list[1];
        m_secteur = list[2];
        m_commentaire = list[3];
        m_perf = list[4];
}

void Voie::setParametres(QDate const & date, QStringList list)
{
    m_date = date;
    m_cote = list[0];
    m_nom = list[1];
    m_secteur = list[2];
    m_commentaire = list[3];
    m_perf = list[4];
}

QStringList Voie::nomParametres()
{
    QStringList list;
    list.push_back(QString("Date"));
    list.push_back(QString("Cote"));
    list.push_back(QString("Nom"));
    list.push_back(QString("Secteur"));
    list.push_back(QString("Performance"));
    list.push_back(QString("Commentaire"));

    return list;
}
