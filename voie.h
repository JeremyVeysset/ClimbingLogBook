#ifndef VOIE_H
#define VOIE_H

#include <QDate>
#include <QString>
#include <QStringList>
#include <QVariant>

class Voie
{
public:
    Voie();
    Voie(QDate date, QString cote, QString nom, QString secteur, QString perf="", QString commentaire="");
    Voie(QDate date, QStringList list);
    Voie(QString str, QString sep = "/");
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
    static void initVoieSystem();

private:
    QDate m_date;
    QString m_cote, m_nom, m_secteur, m_commentaire, m_perf;

    friend QDataStream & operator<<(QDataStream & out, const Voie & v);
    friend QDataStream & operator>>(QDataStream & in, Voie & v);
};

QDate QStringToDate(QString date, QString sep = "/");

Q_DECLARE_METATYPE(Voie)
QDataStream & operator<<(QDataStream & out, const Voie & v);
QDataStream & operator>>(QDataStream & in, Voie & v);

#endif // VOIE_H
