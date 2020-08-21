#ifndef ARTIST_H
#define ARTIST_H

#include <QString>

namespace cddb {
class Artist
{
public:
    Artist() : id(0), name(""), sortName(""), localizedName(""), country(""), notes("") {}

    QString getCountry() const;
    int getID() const;
    QString getLocalizedName() const;
    QString getName() const;
    QString getNotes() const;
    QString getSortName() const;

    void setCountry(const QString &value);
    void setID(int value);
    void setLocalizedName(const QString &value);
    void setName(const QString &value);
    void setNotes(const QString &value);
    void setSortName(const QString &value);

private:
    int id;
    QString name;
    QString sortName;
    QString localizedName;
    QString country;
    QString notes;
};
}

#endif // ARTIST_H
