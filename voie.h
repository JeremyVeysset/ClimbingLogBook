#ifndef VOIE_H
#define VOIE_H

#include <QDate>
#include <QString>
#include <QStringList>

class Voie
{
public:
    Voie();
    Voie(QDate date, QString cote, QString nom, QString secteur, QString perf="", QString commentaire="");
    Voie(QDate date, QStringList list);
    QDate getDate() const {return m_date;}
    QString getNom() const {return m_nom;}
    QString getSecteur() const {return m_secteur;}
    QString getCommmentaire() const {return m_commentaire;}
    QString getCote() const {return m_cote;}
    QString getPerf() const {return m_perf;}
    void setDate(QDate date) {m_date = date;}
    void setNom(QString const & nom) {m_nom = nom;}
    void setSecteur(QString const & secteur) {m_secteur = secteur;}
    void setCommentaire(QString const & commentaire) {m_commentaire = commentaire;}
    void setCote(QString const & cote) {m_cote = cote;}
    void setPerf(QString const & perf) {m_perf = perf;}
    void setParametres(QDate const & date, QStringList list);
    static QStringList nomParametres();
private:
    QDate m_date;
    QString m_nom, m_cote, m_secteur, m_commentaire, m_perf;
};

#endif // VOIE_H
