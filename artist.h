#ifndef ARTIST_H
#define ARTIST_H

#include <QString>

namespace cddb {
class Artist
{
public:
    Artist(int id);
    Artist(const Artist &other);

    QString getCountry() const;
    int getID() const;
    QString getLocalizedName() const;
    QString getName() const;
    QString getNotes() const;
    QString getSortName() const;
    int getScore() const;

    void setCountry(const QString &value);
    void setLocalizedName(const QString &value);
    void setName(const QString &value);
    void setNotes(const QString &value);
    void setSortName(const QString &value);
    void setScore(int value);

private:
    const int id;
    QString name;
    QString sortName;
    QString localizedName;
    QString country;
    QString notes;
    int score;
};
}

#endif // ARTIST_H
