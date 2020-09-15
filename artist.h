#ifndef ARTIST_H
#define ARTIST_H

#include <vector>

#include <QString>

namespace cddb {
class Artist
{
public:
    Artist(int id);
    Artist(const Artist &other);

    void addAlbumID(int albumID);

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

    // Recalculate the artist's score.
    // The new score is returned, and the artist object.
    int computeScore();

private:
    const int id;
    QString name;
    QString sortName;
    QString localizedName;
    QString country;
    QString notes;
    int score;
    std::vector<int> albumIDs;
};
}

#endif // ARTIST_H
